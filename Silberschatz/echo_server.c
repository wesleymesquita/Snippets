/* Silberschatz 9th edition - Exercise 3.25 */

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <arpa/inet.h> 
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 512

int
main(int argc, char **argv)
{
	int listen_sock, peer_sock;
	in_port_t listen_port;
	ssize_t rw_bytes; 
	struct sockaddr_in addr, peer_addr;	
	socklen_t peer_socklen;
	const int LISTEN_BACKLOG = 16;
	char buf[BUF_SIZE];

	if(argc != 2){
		fprintf(stderr, "Use `./echo_server [listen_port]'\n");
		return (EXIT_FAILURE);
	}
	
	listen_port = atoi(argv[1]);
	fprintf(stdout, "Listening at %d \n", listen_port);
	
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == -1){
		fprintf(stderr, "Could not open listen socket.\
				Reason %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	memset(&addr, 0, sizeof(struct sockaddr_in));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(listen_port);
	addr.sin_addr.s_addr = INADDR_ANY;

		
	if(bind(listen_sock, (const struct sockaddr*)&addr, 
			sizeof(struct sockaddr_in))==-1){
		fprintf(stderr, "Could not bind socket.\
				Reason %s\n", strerror(errno));
		return EXIT_FAILURE;
	}	
	
	if(listen(listen_sock, LISTEN_BACKLOG) == -1){
		fprintf(stderr, "Could not bind socket.\
				Reason %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	peer_socklen = sizeof(struct sockaddr_in);	
	memset(&peer_addr, 0, sizeof(struct sockaddr_in));

	peer_sock = accept(listen_sock, (struct sockaddr*)&peer_addr,
						&peer_socklen);
	if(peer_sock == -1){
		fprintf(stderr, "Get invalid peer socket. Reason %s\n", strerror(errno));
		close(peer_sock);
		close(listen_sock);	
		return EXIT_FAILURE;
	}
	fprintf(stdout, "Received connection from %s:%d\n",\
				inet_ntoa(peer_addr.sin_addr), peer_addr.sin_port);

	while(1){	
		rw_bytes = read(peer_sock, (void*)buf, BUF_SIZE);
		if(rw_bytes == -1){
				fprintf(stderr, "Could not read from peer socket. Reason %s\n", strerror(errno));
				break;
		}
		if(rw_bytes == 0){
			fprintf(stdout, "Connection closed by peer\n");
			break;
		}
					
		rw_bytes = write(peer_sock, (void*)buf, rw_bytes);
		if(rw_bytes == -1){
				fprintf(stderr, "Could not write to peer socket. Reason %s\n", strerror(errno));
				break;
		}
	}	

		close(peer_sock);
		close(listen_sock);	
		return EXIT_FAILURE;
		return 0;
}
