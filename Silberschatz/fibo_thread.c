/* Silberschatz Operating System concepts - Exercise 4.26 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct fib{
	int size;
	unsigned long int *v;
};

void* calc_fib(void *arg)
{
	struct fib *f;
	int i;

	f = (struct fib*)arg;	
	f->v[0] = 0;
	f->v[1] = 1;
	for(i=2; i<f->size; i++){
		f->v[i] = f->v[i-1] + f->v[i-2];
	}		
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	int i;
	struct fib fib;
	pthread_t tid;	
	pthread_attr_t attr;

	if(argc != 2) {
		fprintf(stderr, "Usage ./fibo_thread [fib sequence size >= 2]\n");
		return 1;
	}

	fib.size = atoi(argv[1]);
	if (fib.size < 2){
		fprintf(stderr, "Usage ./fibo_thread [fib sequence size >= 2]\n");
		return 2;
	}
	fib.v = malloc(sizeof(unsigned long int)*fib.size);
	
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, calc_fib, (void*)&fib);
	pthread_join(tid, NULL);	
	
	printf("%lu", fib.v[0]);
	for(i=1; i<fib.size; i++){
		printf(" %lu", fib.v[i]);
	}
	printf("\n");	
	free(fib.v);	
		
	return 0;
}
