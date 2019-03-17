/* Silberschatz 9th edition - exercise 3.22 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv)
{
	const char *SHM_NAME = "memo";
	const int SHM_SIZE = 1024*16;
	pid_t pid;
	int shm_fd, n;	
	void *shm_ptr;
	char tmp_str[16];
	
	if(argc != 2){
		fprintf(stderr, "Use ./collatz_shm [n]\n");
		return 1;
	}
	n = atoi(argv[1]);
		
	shm_fd = shm_open(SHM_NAME, O_CREAT|O_RDWR, 0755);
	if (shm_fd == -1){
		fprintf(stderr, "could not create shared memory. Error %s\n", 
			strerror(errno));
		return 1;
	}
	shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, 
			shm_fd, 0);
	
	if(ftruncate(shm_fd,SHM_SIZE)){
		fprintf(stderr, "could not allocate shared memory size\n");
		shm_unlink(SHM_NAME);
		return -1;
	}
	
		
	pid = fork();
		
	if(pid == 0){

		((char*)shm_ptr)[0] = '\0';
		while(n != 1){
			sprintf(tmp_str, "%d ", n);
			strcat(((char*)shm_ptr), tmp_str);
			n = n%2==0 ? n/2 : 3*n+1;
		}				
		strcat(((char*)shm_ptr),"1");
		printf("Wrote on child %s\n", (char*)shm_ptr);
	}
	else{
		waitpid(pid, NULL, 0);	
		printf("Result (on parent) %s\n", (char*)shm_ptr);
		shm_unlink(SHM_NAME);
	}

	return 0;
}

