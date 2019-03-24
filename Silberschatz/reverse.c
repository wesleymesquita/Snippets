/* Silbershatz 9th edtion - Exercise  3.26 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_SIZE 500

int
main(int argc, char **argv)
{	
	pid_t pid;		
	int pipe_to_child[2],pipe_to_parent[2], wstatus;	
	char c;

	if(argc != 2){
		fprintf(stderr, "Usage : reverse <string>\n");
		return EXIT_FAILURE;
	}

	if(pipe(pipe_to_child) == -1){
		fprintf(stderr, "Could not open pipe to child. Cause : %s\n", strerror(errno));
		return EXIT_FAILURE;
	}	
	
		
	if(pipe(pipe_to_parent) == -1){
		fprintf(stderr, "Could not open pipe to parent. Cause : %s\n", strerror(errno));
		return EXIT_FAILURE;
	}	

	pid = fork();
	if(pid == -1){
		fprintf(stderr, "Could not create child process. Cause : %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if(pid == 0){
			close(pipe_to_child[1]);
			close(pipe_to_parent[0]);

			while(read(pipe_to_child[0], &c, 1) > 0){
				if(isalpha(c))
					c  = islower(c)? toupper(c) : tolower(c);
				write(pipe_to_parent[1], &c, 1);
			}
			close(pipe_to_parent[1]);
			return EXIT_SUCCESS;
	} else {
		close(pipe_to_child[0]);
		close(pipe_to_parent[1]);
	
		write(pipe_to_child[1], argv[1], strlen(argv[1]));
		close(pipe_to_child[1]);
	
		pid = waitpid(pid, &wstatus, 0);
		if( pid == -1){
				fprintf(stderr, "Could not wait child process. Cause : %s\n", strerror(errno));
				return EXIT_FAILURE;
		}
		
		while(read(pipe_to_parent[0], &c, 1) > 0){
			write(STDOUT_FILENO, &c, 1);
		}
		close(pipe_to_parent[0]);
		printf("\n");
	}

	return EXIT_SUCCESS;
}

