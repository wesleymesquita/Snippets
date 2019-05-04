#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define ERROR_BUF_SZ 128	

#define ERROR_BUFFER char __error_buffer[ERROR_BUF_SZ];

#define HANDLE_ERROR_AND_RETURN(func, msg) \
	__ERROR_TO_STDERR(func, msg, __FILE__, __LINE__)

#define __ERROR_TO_STDERR(func, msg, file, line) \
	strerror_r(errno, __error_buffer, ERROR_BUF_SZ); \
	fprintf(stderr, "Error at function '%s' [%s:%d]. What: %s. Cause:  %s\n", func, file, line, msg, __error_buffer); \
	return EXIT_FAILURE;

#define LOG(func, msg) \
	fprintf(stdout, "[%s:%d] (%s) %s\n", __FILE__, __LINE__, func, msg);

#define CONN_BACKLOG 1024
#define DATE_BUF_SZ 26

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

struct client_sockets{
	int *sockets;
	pthread_t *threads;
	int size;
	pthread_mutex_t locker;
};


void client_sockets_init(struct client_sockets *client, int size)
{
	client->sockets = malloc(sizeof(int)*size);	
	client->threads = malloc(sizeof(pthread_t)*size);	
	client->size = size;
	pthread_mutex_init(&client->locker, NULL);
}

void client_socket_destroy(struct client_sockets *client)
{
	free(client->sockets);
	free(client->threads);
} 

int client_socket_insert(struct client_sockets *client, int sock_num)
{
	int free_slot, i;
	
	pthread_mutex_lock(&client->locker);
	free_slot = -1;
	for(i=0; i<client->size; i++){
		if(client->sockets[i] == -1){
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
	pthread_mutex_lock(&client->locker);
	client->sockets[slot]=-1;	
	client->threads[slot]=-1;
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
		fprintf(stderr, "Error to send data to client. Socket %d\n", entry->client->sockets[entry->slot]);
	}	
	client_socket_clean(entry->client, entry->slot);
	socket_entry_destroy(entry);
	pthread_exit(NULL);
}


/** start_date_tcp starts the listening tcp port
* 	to get incomming connection.
*
*	param port : receives TCP port number in host byte order
*
**/	
int start_date_tcp_server(int port)
{
	ERROR_BUFFER

	int listen_tcp_sock, ret, client_sock, slot;
	struct sockaddr_in addr, client_addr;	
	socklen_t addrlen;	
	struct client_sockets client_socks;	
	struct socket_entry *entry;
	pthread_attr_t pattr;

	client_sockets_init(&client_socks, CONN_BACKLOG);
	pthread_attr_init(&pattr);

	listen_tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_tcp_sock == -1){
		close(listen_tcp_sock);		
		HANDLE_ERROR_AND_RETURN("start_date_server", "Could not open socket for listening")
	}		

	addr.sin_family = AF_INET;
	addr.sin_port = htonl(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(listen_tcp_sock, (const struct sockaddr*)&addr, sizeof(struct sockaddr_in));
	if (ret == -1){
		HANDLE_ERROR_AND_RETURN("start_date_server", "Could not bind socket to local network")
		close(listen_tcp_sock);		
	}	

	ret = listen(listen_tcp_sock, CONN_BACKLOG);
	if (ret == -1){
		close(listen_tcp_sock);		
		HANDLE_ERROR_AND_RETURN("start_date_server", "Could not start listening socket")
	}	
	LOG("start_date_tcp_server", "Start Listening")
	for(;;){
		client_sock = accept(listen_tcp_sock, (struct sockaddr*)&client_addr, &addrlen);
		if (client_sock == -1){
			fprintf(stderr, "Error on 'start_date_server': Could not handle incomming connection");
			continue;
		}		
		slot = client_socket_insert(&client_socks, client_sock);
		if (slot == -1){
			fprintf(stderr, "Error on 'start_date_server': Number of connection slots exceeded");
			close(client_sock);
			continue;
		}	
		entry = socket_entry_create(slot, &client_socks);	
		pthread_create(&client_socks.threads[slot], &pattr, send_date, (void*)entry);
	}	
	
	pthread_attr_destroy(&pattr);
	client_socket_destroy(&client_socks);	
	close(listen_tcp_sock);		

	return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
	ERROR_BUFFER
	int listening_port;

	if(argc != 2){
		errno = EINVAL;
		HANDLE_ERROR_AND_RETURN("main", "Wrong parameter -> Usage ./date_server_thread [tcp port]")
	}		
	
	listening_port = atoi(argv[1]);	
	
	start_date_tcp_server(listening_port);
	
	return 0;
}
