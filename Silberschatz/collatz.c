/* Silberschatz 9th ed ex 3.21 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	int n;
	pid_t pid;
	if(argc != 2){
		fprintf(stderr, "Usage ./collatz [n]\n");
		return 1;
	}
	n = atoi(argv[1]);	
	pid = fork();
	if (pid == 0){
		while(n != 1){
			printf("%d ", n);
			n = n%2==0 ? n/2 : 3*n+1;		
		}
		printf("1\n");
	}
	else{
		wait(NULL);	
	}	
	return 0;
}
