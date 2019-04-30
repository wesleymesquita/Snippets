/* Silberschatz Operating System Concepts 9th Edition Exercise 4.23 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h> 

/* The exercise didn't said much about limits, so I implmented 
just a naive https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes */

struct sieve {
	int *s;
	int n;
};

void* sieve_init(void* arg)
{
	int i, j, n;
	struct sieve *sieve;
	
	sieve = (struct sieve*)arg;
	n = sieve->n;
	
	for(i=0; i<n; i++)
		sieve->s[i]=1;
	
	for(i=2; i<n; i++){
		if(sieve->s[i] == 1){
			for(j=2; i*j<n; j++){
				sieve->s[i*j] = 0;
			}
		}
	}
	return NULL;
}

void sieve_print(struct sieve *sieve)
{
	int i;
	
	for(i=2; i<sieve->n; i++){
		if(sieve->s[i])
			printf("%d ", i);
	}
}

int main(int argc, char **argv)
{
	int n;
	struct sieve sieve;
	pthread_t t;
	pthread_attr_t attr;
	
	if(argc != 2){
		fprintf(stderr, "Use ./primes [n]\n");
		return 1;
	}

	n = atoi(argv[1]);
	sieve.s = (int*)malloc(n*sizeof(int));
	sieve.n = n; 

	pthread_attr_init(&attr);	
	pthread_attr_setstacksize(&attr, 1024*1024*256);
	pthread_create(&t, &attr, sieve_init, &sieve);		
	pthread_join(t, NULL);	
	
	sieve_print(&sieve);
	free(sieve.s);

	return 0;
}
