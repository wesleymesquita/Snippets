#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define ERROR_BUF_SZ 128

#define __FPRINTF_F(stream, func, format, args...) \
	fprintf(stream, "[%s:%d] (%s):" format "\n", __FILE__, __LINE__, #func, args)

#define __FPRINTF(stream, func, msg) \
	fprintf(stream, "[%s:%d] (%s): %s\n", __FILE__, __LINE__, #func, msg)

/* ERROR_BUFFER defines an statically allocated error 
   buffer to be used on strerror_r (thread safe) */ 
#define ERROR_BUFFER() \
	char __error_buffer[ERROR_BUF_SZ]; \
	int __error_no;

/* LOG_ERRNO is to be used when errno is set. It will send a human 
   readable message to stderr */ 
#define LOG_ERRNO(func) \
	__error_no = errno; \
	strerror_r(__error_no, __error_buffer, ERROR_BUF_SZ); \
	__FPRINTF_F(stderr, func, "Errno: %d  what: %s\n", __error_no,  __error_buffer); 

/* LOG_ERR_F logs error level messaegs, especially when errno is NOT set */
#define LOG_ERR_F(func, format, args...) \
	__FPRINTF_F(stderr, func, format, args); 

/* LOG_F logs formated messages to stdout */
#define LOG_F(func, format, args...)\
	__FPRINTF_F(stdout, func, format, args); 

/* LOG_ERR logs non-formated error messages on stderr */
#define LOG_ERR(func, msg) __FPRINTF(stderr, func, msg); 

/* LOG logs (non-formated) messages to stdout */
#define LOG(func, msg) __FPRINTF(stderr, func, msg); 

/* CONN_BACKLOG defines the maximum simultaneos connections to the server */
#define CONN_BACKLOG 1024

/* DATE_BUF_SZ defines the needed buffer size to allocated default date string */
#define DATE_BUF_SZ 26

#define NOT_USED -1
#define INVALID_SLOT -1

/* got_interrupted indicates where the program has found (== 1) or not (== 0)
   a state where it should be (gracefully) shut down */
int got_interrupted;

int date_now(char *date)
{
	time_t now;
	
	now = time(NULL);
	ctime_r(&now, date);		
	return 1;
}

int test_date_now()
{
	char *date;
	date = malloc(sizeof(char)*DATE_BUF_SZ);
	date_now(date);	
	printf("Current date is %s\n", date);
	free(date);
	return 1;
}

/** struct client_sockets stores info about current open connections to the server 
*/
struct client_sockets{
	int *sockets;	/* client sockets from accepted connections */
	pthread_t *threads; /* thread ids for each accepted connection */
	int size; 
	pthread_mutex_t locker; /* mutex to grant thread safety while altering this object */
};


void client_sockets_init(struct client_sockets *client, int size)
{
	int i;

	client->sockets = malloc(sizeof(int)*size);	
	client->threads = malloc(sizeof(pthread_t)*size);	
	for(i=0; i<size; i++){
		client->sockets[i] = NOT_USED;	
		client->threads[i] = NOT_USED;
	}
	client->size = size;
	pthread_mutex_init(&client->locker, NULL);
}

void client_socket_destroy(struct client_sockets *client)
{
	ERROR_BUFFER()
	int i, ret;
	/* join all remaining threads to make sure all resources will
       be released */
	for(i=0; i<client->size; i++){
		if(client->threads[i] != NOT_USED) {
			ret = pthread_join(client->threads[i], NULL);
			if(ret != 0){
				LOG_ERRNO("client_socket_destroy");	
			}
		}
	}
	free(client->sockets);
	free(client->threads);
	pthread_mutex_destroy(&client->locker);
} 

int client_socket_insert(struct client_sockets *client, int sock_num)
{
	int free_slot, i;
	
	pthread_mutex_lock(&client->locker);
	free_slot = INVALID_SLOT;
	/* Surely there are better ways to find a free slot. but it will require more 
	   effort */
	for(i=0; i<client->size; i++){
		if(client->sockets[i] == NOT_USED){
			client->sockets[i] = sock_num;
			free_slot = i;
			break;
		}
	}
	pthread_mutex_unlock(&client->locker);
	return free_slot;
}

void client_socket_clean(struct client_sockets *client, int slot)
{
	ERROR_BUFFER() 
	int err;
	pthread_mutex_lock(&client->locker);
	err = shutdown(client->sockets[slot], SHUT_RDWR);
	if(err == -1){
		LOG_ERRNO("client_socket_clean");
	}
	close(client->sockets[slot]);
	client->sockets[slot]=NOT_USED;	
	client->threads[slot]=NOT_USED;
	pthread_mutex_unlock(&client->locker);
}

struct socket_entry {
	int slot;
	struct client_sockets *client;
};

struct socket_entry* socket_entry_create(int slot, struct client_sockets *client)
{	
	struct socket_entry *entry;
	entry = malloc(sizeof(struct socket_entry));
	entry->slot = slot;
	entry->client = client;	
	return entry;
}

void socket_entry_destroy(struct socket_entry *entry)
{
	free(entry);
}

void* send_date(void *arg)
{
	struct socket_entry *entry;
	char date[DATE_BUF_SZ];
	int sent_bytes;	
	
	entry = (struct socket_entry*)arg;
	date_now(date);	
	sent_bytes = write(entry->client->sockets[entry->slot], date, DATE_BUF_SZ); 
	if (sent_bytes != DATE_BUF_SZ){
		LOG_ERR_F("send_date", "Error to send data to client. Socket %d", entry->client->sockets[entry->slot]);
	}	
	client_socket_clean(entry->client, entry->slot);
	free(entry);
	pthread_detach(pthread_self());
	return NULL;
}


void interrupted_handler(int signal)
{
	LOG("interrupted_handler", "Received SIGINT\n");
	got_interrupted = 1;
}


/** start_date_tcp starts the listening tcp port
* 	to get incomming connection.
*
*	param port : receives TCP port number in host byte order
*
**/	
int start_date_tcp_server(int port)
{
	ERROR_BUFFER()
	int listen_tcp_sock, ret, client_sock, slot;
	struct sockaddr_in addr, client_addr;	
	socklen_t addrlen;	
	struct client_sockets client_socks;	
	struct socket_entry *entry;
	pthread_attr_t pattr;
	struct sigaction saction;
	
	/* setup SIGINT handling */	
	saction.sa_handler = interrupted_handler;
	saction.sa_flags = SA_NODEFER;
	sigaction(SIGINT, &saction, NULL);
	got_interrupted=0;

	pthread_attr_init(&pattr);
	client_sockets_init(&client_socks, CONN_BACKLOG);

	listen_tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_tcp_sock == -1){
		LOG_ERR("start_date_tcp_server", "Could not open socket for listening")
		got_interrupted=1;
	}		
	if(!got_interrupted) {
		memset(&addr, 0, sizeof(struct sockaddr_in));
		addr.sin_family = AF_INET;
		addr.sin_port = htons((uint16_t)port);
		addr.sin_addr.s_addr = INADDR_ANY;
		ret = bind(listen_tcp_sock, (const struct sockaddr*)&addr, sizeof(struct sockaddr_in));
		if (ret == -1){
			LOG_ERRNO("start_date_tcp_server")
			got_interrupted=1;
		}	
	}
	if (!got_interrupted) {	
		ret = listen(listen_tcp_sock, CONN_BACKLOG);
		if (ret == -1){
			LOG_ERRNO("start_date_tcp_server")
			got_interrupted=1;
		}	

		LOG_F("start_date_tcp_server", "start Listening on port %d", port);
	}else{
		LOG_ERR_F("start_date_tcp_server", "could not start server on port %d", port);
	}
	
	/* main loop to get client requests. "got_interrupted" is being constantly 
		checked just in case someone pressed CRTL-C. It is ugly, but it is a 
		need to be conservative */
	for(;!got_interrupted;){

		memset(&client_addr, 0, sizeof(struct sockaddr_in));
		client_sock = accept(listen_tcp_sock, (struct sockaddr*)&client_addr, &addrlen);
		if (got_interrupted || client_sock == -1){
			LOG_ERR(start_date_tcp_server, "could not accept connection");
			LOG_ERRNO("start_date_tcp_server");
			continue;
		}		
		LOG_F(start_date_tcp_server, "Got connection at socket %d", client_sock);
		
		/* get a valid slot to store client information */ 	
		slot = client_socket_insert(&client_socks, client_sock);
		if (got_interrupted || slot == INVALID_SLOT){
			LOG_ERR(start_date_tcp_server, "number of connection slots exceeded");
			shutdown(client_sock, SHUT_RDWR);
			close(client_sock);
			continue;
		}	

		if(!got_interrupted){
			entry = socket_entry_create(slot, &client_socks);	
			pthread_create(&client_socks.threads[slot], &pattr, send_date, (void*)entry);
		}
	}	

	LOG(start_date_tcp_server, "Stopped server. Started cleaning up");

	client_socket_destroy(&client_socks);	
	pthread_attr_destroy(&pattr);
	shutdown(listen_tcp_sock, SHUT_RDWR);
	close(listen_tcp_sock);		

	return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
	int listening_port;
		
	if(argc != 2){
		LOG_ERR(main, "Wrong parameter -> Usage ./date_server_thread [tcp port]");
		return EXIT_FAILURE;
	}		
		
	listening_port = atoi(argv[1]);	
	LOG(main, "Starting date server. To kill, hit CRTL-C");
	start_date_tcp_server(listening_port);
	LOG(main, "Finished date server");	
	return 0;
}
