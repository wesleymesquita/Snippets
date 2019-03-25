/* Silberschatz 9th edition - exercise 3.27 */
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
	int pipefd[2], fdin, fdout;
	const int BUF_SIZE = 512;
	pid_t pid;
	ssize_t rwbytes;
	char buf[512];
	
	if(argc != 3){
		fprintf(stdout, "Usage : filecopy <input_file> <copied_file>\n");
		return EXIT_FAILURE;
	}

	if(pipe(pipefd) == -1){
		fprintf(stderr, "Could not open pipes. Reason : %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	pid = fork();
	if(pid == 0){
		close(pipefd[1]);
		fdout = open(argv[2], O_CREAT|O_WRONLY);
		if(fdout == -1){
				fprintf(stdout, "Cannot open file for writing. Reason: %s\n", strerror(errno));
				return EXIT_FAILURE;
		}
		while((rwbytes = read(pipefd[0], buf, BUF_SIZE)) > 0){
			if(write(fdout, buf, rwbytes) == -1){
				fprintf(stdout, "Cannot write to copied file. Reason: %s\n", strerror(errno));
				return EXIT_FAILURE;
			}
		}
		close(pipefd[0]);
		close(fdout);
	}else{
		close(pipefd[0]);
		fdin = open(argv[1], O_RDONLY);
		if(fdin == -1){
				fprintf(stdout, "Cannot open file for writing. Reason: %s\n", strerror(errno));
				return EXIT_FAILURE;
		}
		while((rwbytes=read(fdin, buf, BUF_SIZE))>0){
			write(pipefd[1], buf, rwbytes);
		}	
		close(pipefd[1]);
		close(fdin);
	}

	return EXIT_SUCCESS;
}
