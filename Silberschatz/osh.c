/* Silberschatz 9th edition - Chapter 3 - Project 1 (Phases 1 and 2) 
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_LINE 80
#define MAX_HISTORY 10

int parse_cmd_line(char *args[MAX_LINE/2 + 1], const char *line)
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


void free_cmd_args(char *args[], int nargs)
{
	int i;
	for(i=0; i<nargs; i++)
		if(args[i] != NULL)
				free(args[i]);
} 


int test__parse_cmd_line()
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

struct history{
	char historic[MAX_LINE/2 + 1][10];
	int nentries;
	int top;
};

void history_init(struct history *history)
{
	int i;

	for(i=0; i<MAX_HISTORY; i++)
		history->historic[i][0] = '\0';
	history->top = MAX_HISTORY;
	history->nentries = 0;
}

void history_add_entry(struct history *history, const char* entry)
{
	if(strcmp(history->historic[history->top], entry) == 0)
		return;	
	
	if(history->top == 0)
		history->top = MAX_HISTORY;
	
	history->top--;
	
	if(history->nentries < MAX_HISTORY)
		history->nentries++;	
	strcpy(history->historic[history->top], entry);
}

void history_print(struct history *history)
{		
	int entries, top;
	entries = history->nentries;
	top = history->top-1;
	while(entries > 0){
		if(top < 0 || history->historic[top][0]=='\0')
			top = MAX_HISTORY-1;
		printf("%d %s\n", entries, history->historic[top]);	
		entries--; top--;
	}		  
}

int history_get_cmd(struct history *history, char* cmd, char *args[MAX_LINE/2 + 1])
{
	char cmd_arg[16];	
	int i, cmd_len, ncmd;
	
	/* there is no command to repeat */
	if(history->nentries == 0){
		fprintf(stderr, "event not found\n");
		return 1;
	}
	if(cmd[1] == '!') {
			parse_cmd_line(args, history->historic[history->top]);
			return 0;
	}
	cmd_len = strlen(cmd);
	
	/*	check if all chars after `!' are numeric
		if not return error */		
	for(i=1; i<cmd_len; i++){
		if(!isdigit(cmd[i])){
			fprintf(stderr, "event not found\n");
			return 1;
		}
		cmd_arg[i-1]=cmd[i];
	}
	cmd_arg[i]='\0';				
	ncmd = atoi(cmd_arg);
	i = history->top;
	while(ncmd > 1){
		i = i == MAX_HISTORY-1 ? 0 : i+1;
		ncmd--;	
	}	
	parse_cmd_line(args, history->historic[i]);
	return 0;
}

int main()
{
	char *args[MAX_LINE/2 + 1], line[MAX_LINE];
	struct history history;
	
	int should_run, nargs;
	pid_t pid, ret_wait;	
	int wstatus, must_wait;
	
	if(test__parse_cmd_line() != 0)
		return EXIT_FAILURE;
	
	history_init(&history);

	should_run = 1;
	while(should_run){
		must_wait = 0;
		printf("osh>");
		fflush(stdout);	
		fgets(line, MAX_LINE, stdin);
		/* Just strip out the new line character */
		line[strlen(line)-1] = '\0';
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
		

		if(args[0][0] ==  '!'){
			if(history_get_cmd(&history, args[0], args) != 0)
				continue;
		}else{
				history_add_entry(&history, line);
		}	
	
		if(strcmp(args[0], "history") == 0){
			history_print(&history);
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
