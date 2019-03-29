/* Silberschatz 9th edition - Chapter 3 - Project 1 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>
#include <sys/wait.h>

#define MAX_LINE 80

int 
parse_cmd_line(char *args[MAX_LINE/2 + 1], const char *line)
{
	ssize_t line_len, i, k, nargs;
		
	line_len = strlen(line);
	nargs = 0;	
	for(i=0; i<line_len;){
		k=0;
		while((i+k)<line_len && line[(i+k)] != ' '
				&& line[(i+k)]!='\n')k++;
		
		args[nargs] = (char*)malloc(sizeof(char)*(k));
		strncpy(args[nargs], (void*)(line)+i, k);
		args[nargs][k] = '\0';
		nargs++;
		i+=k+1;
	}	
	args[nargs++] = NULL;
	return nargs;
}


void
free_cmd_args(char *args[], int nargs)
{
	int i;
	for(i=0; i<nargs; i++)
		if(args[i] != NULL)
				free(args[i]);
} 


int 
test__parse_cmd_line()
{
	const char *line = "ls -altrh &";
	char *args[MAX_LINE/2 + 1];
	const char *expected_args[4] = {"ls", "-altrh", "&", NULL};
	int i, nargs;
	nargs = parse_cmd_line(args, line);	

	if(nargs != 4){
		free_cmd_args(args, nargs);
		fprintf(stderr, "Test OSH : Wrong number of parsed parmaters. Get %d expected 3\n", nargs);
		return 1;
	}
	
	for(i=0; i<nargs-1; i++){
		if(strcmp(args[i], expected_args[i]) != 0){
				free_cmd_args(args, nargs);
				fprintf(stderr, "Test OSH : Get arg %s expected %s\n", args[i], expected_args[i]);
				return 1;
		}
	}	
	free_cmd_args(args, nargs);
	return 0;
}	

int
main()
{
	char *args[MAX_LINE/2 + 1], line[MAX_LINE];
	int should_run, nargs;
	pid_t pid, ret_wait;	
	int wstatus, must_wait;
	
	if(test__parse_cmd_line() != 0)
		return EXIT_FAILURE;

	should_run = 1;
	while(should_run){
		must_wait = 0;
		printf("osh>");
		fflush(stdout);	
		fgets(line, MAX_LINE, stdin);
		nargs = parse_cmd_line(args, line);
		if(nargs == 0){
			fprintf(stderr, "osh errror : No input command\n");
			free_cmd_args(args, nargs);		
			continue;
		}
		if(strcmp(args[0], "exit") == 0){
			should_run = 0;
			free_cmd_args(args, nargs);		
			continue;
		}
		
		if(args[nargs-2][0] == '&'){
			must_wait = 1;
			args[nargs-2] = NULL;
		}	

		pid = fork();
		if(pid == 0){
			if(execvp(args[0], args) == -1){
				fprintf(stderr, "OSH Error : Could no execute %s. Cause : %s\n", line, strerror(errno));
				return EXIT_FAILURE;
			}
			return EXIT_SUCCESS;
		}else{
			if(!must_wait){
					ret_wait = waitpid(pid, &wstatus, 0);
					if(ret_wait != pid){
						fprintf(stderr, "OSH Error : Child process died in a unexpected way. Cause : %s\n", strerror(errno));
					}
			}
			free_cmd_args(args, nargs);	
		}			
	}

	return 0;
}
