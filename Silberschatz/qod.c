/* Silberschatz 9th edition - Exercise 3.23 
Note: I didn't follow the instructions and created my own
C snippet to solve the problem. You can still test the program
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

int
main()
{
	int sock, send_sock, nbytes;
	struct sockaddr_in addr;	
	const int MAX_N_CONN = 8;
	const char *MY_QUOTE = "D'OH";	
	socklen_t socklen;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1){
		fprintf(stderr, "Could not open socket. Error %s\n", strerror(errno));
		return -1;
	}


	memset((void*)&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6017);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(sock, (const struct sockaddr*)&addr, sizeof(struct sockaddr_in)) == -1){
		fprintf(stderr, "Could not bind socket. Error %s\n", strerror(errno));
		return -1;
	}	

	socklen = sizeof(struct sockaddr_in);
	if(listen(sock, MAX_N_CONN) == -1){
		fprintf(stderr, "Could not listen on socket. Error %s\n", strerror(errno));
		return -1;
	}	
	if((send_sock = accept(sock, (struct sockaddr*)&addr, &socklen)) == -1){
		fprintf(stderr, "Could not accept on socket. Error %s\n", strerror(errno));
		return -1;
	}	

	nbytes = write(send_sock, MY_QUOTE, strlen(MY_QUOTE)) != strlen(MY_QUOTE);
	if(nbytes == -1){
		fprintf(stderr, "Could not write on socket. Error %s\n", strerror(errno));
		return -1;
	}
	close(sock);
	close(send_sock);
	return 0;
}
