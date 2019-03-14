/* Silberschatz exercise 3.20 */
#include <stdio.h>
#include <stdlib.h>

#define MIN_PID 300
#define MAX_PID	333 
#define NBITS (sizeof(int)*8)

int *pid_map;
int pid_map_nslots;

int allocate_map(void)
{
	pid_map_nslots = ((MAX_PID-MIN_PID)/(NBITS))+1;
	pid_map = (int*)calloc(pid_map_nslots, sizeof(int));
	return pid_map == NULL ? -1 : 1;
}

void release_map(void)
{
	free(pid_map);
}

int allocate_pid(void)
{
	int i, offset, pid;
	
	for(i=0; i<pid_map_nslots; i++){
		if(pid_map[i] == 0xFFFFFFFF)
			continue;
		offset = 0;

		/* look for a bit 0, if reaches NBITS, 
		go for the next slot */
		while(offset < NBITS && 
			((pid_map[i]&(1<<offset))>>offset))
		{
			offset++;
			
		}	
		/* Normalize the PID for the interval 
		or reject it this is out */
		if(offset < NBITS){
			pid = i*NBITS + offset;
			if (pid+MIN_PID > MAX_PID){
				printf("Rejected here %d\n", pid);
				return -1;	
			}
			pid_map[i]|=(1<<offset);
			return pid;
		}
	}
	return -1;
}

void release_pid(int pid)
{
	int offset, slot, norm_pid;
	if(pid < MIN_PID)
		return;
	norm_pid = pid-MIN_PID;
	slot = norm_pid/NBITS;
	offset = norm_pid % NBITS;
	pid_map[slot] &=~(0x1<<offset);
}

void print_map(){
	int i;
	printf(">>>>\nSLOT SIZE == %d\n", NBITS);
	printf("NSLOTS == %d\n", pid_map_nslots);
	for(i=0; i<pid_map_nslots; i++){
		printf("%08x ", pid_map[i]);
	}
	printf("\n<<<<\n");	
}	

int main(){
	int i, pid;
	allocate_map();
	print_map();	
	for(i=MIN_PID; i<=MAX_PID; i++){
		pid = allocate_pid();
		if(pid == -1)
			fprintf(stderr, "Could not allocate %d\n", i);
		else
			printf("i == %d - Got PID == %d\n", i, pid);
	}	
	print_map();	
	for(i=MIN_PID; i<=MAX_PID; i++)
		release_pid(i);
	print_map();
	release_map();
	return 0;
}
