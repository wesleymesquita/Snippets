/* Silberschatz 9th edition exercise 4.20 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MIN_PID 64 
#define MAX_PID	1024 
#define NBITS (sizeof(int)*8)
#define NTHREADS 128

int *pid_map;
int used_pids;
pthread_mutex_t map_locker= PTHREAD_MUTEX_INITIALIZER;
int pid_map_nslots;

int allocate_map(void)
{
	pid_map_nslots = ((MAX_PID-MIN_PID)/(NBITS))+1;
	pid_map = (int*)calloc(pid_map_nslots, sizeof(int));
	used_pids=0;
	return pid_map == NULL ? 1 : 0;
}

void release_map(void)
{
	free(pid_map);
}

int allocate_pid(void)
{
	int i, offset, pid;
	pid = -1;
	pthread_mutex_lock(&map_locker);
	for(i=0; i<pid_map_nslots; i++){
		if(pid_map[i] == 0xFFFFFFFF)
			continue;
		offset = 0;

		/** look for a bit 0, if reaches NBITS, 
		*   go for the next slot
		*/
		while(offset < NBITS && 
			((pid_map[i]&(1<<offset))>>offset))
		{
			offset++;
			
		}	
		/* Normalize the PID for the interval 
		*  or reject it this is out 
		*/
		if(offset < NBITS){
			pid = i*NBITS + offset;
			if (pid+MIN_PID > MAX_PID){
				printf("Rejected here %d\n", pid);
				break;
			}
			pid_map[i]|=(1<<offset);
			used_pids++;
			pid += MIN_PID;
			break;
		}
	}
	pthread_mutex_unlock(&map_locker);
	return pid;
}

int release_pid(int pid)
{
	int offset, slot, norm_pid;
	if(pid < MIN_PID){
		return -1;
	}
	pthread_mutex_lock(&map_locker);
	norm_pid = pid-MIN_PID;
	slot = norm_pid/NBITS;
	offset = norm_pid % NBITS;

	pid_map[slot] &=~(0x1<<offset);
	used_pids--;
	printf("Released PID %d from  SLOT %d (%08x)\n", pid, slot, pid_map[slot]); 
	pthread_mutex_unlock(&map_locker);
	return pid;
}

void print_map(){
	int i;
	pthread_mutex_lock(&map_locker);
	printf(">>>>\nSLOT SIZE == %d\n", NBITS);
	printf("NSLOTS == %d\n", pid_map_nslots);
	printf("Used PIDs == %d\n", used_pids);
	for(i=0; i<pid_map_nslots; i++){
		printf("%d : %08x\n", i, pid_map[i]);
	}
	printf("\n<<<<\n");	
	pthread_mutex_unlock(&map_locker);
}	

void* worker(void* arg)
{
	int pid, rpid;
	pid = allocate_pid();		
	printf("Aquired pid %d\n", pid);
	sleep(1);
	rpid = release_pid(pid);
	if(rpid != pid){
		fprintf(stderr, "Could not remove PID %d\n", pid);
	}else {
		printf("Released pid %d\n", pid);
	}
	pthread_exit(NULL);
}

int test_pid_map()
{
	int i, err;	
	/* Prepare and run the worker threads */
	pthread_t workers[NTHREADS];
	pthread_attr_t attr;

	err = allocate_map();
	if(err != 0){
		fprintf(stderr, "Could not allocate pid map");
		return 0;
	}	

	pthread_attr_init(&attr);		
		
	for(i=0; i<NTHREADS; i++){
		pthread_create(&workers[i], &attr, worker, NULL);	
	}		
	for(i=0; i<NTHREADS; i++) {
		pthread_join(workers[i], NULL);
	}
	

	return 1;		
}


int main(){
	int result_ok;
	print_map();
	result_ok = test_pid_map();
	printf("PID map multi-thread test ");
	printf("%s\n", result_ok ? "Passed" : "Failed");
	print_map();
	release_map();
	return 0;
}
