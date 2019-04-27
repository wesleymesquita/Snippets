/* Silberschatz - Operating System Concepts - Exercise 4.21 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct stat {
	int *v;
	ssize_t size_v;

	int max, min;
	double average;
};

void stat_init(struct stat *stat, int size)
{
	stat->v = (int*)malloc(size*sizeof(int));
	stat->size_v = size;
	stat->max=-1;
	stat->min=-1;
	stat->average=-1.0;
}	

void stat_destroy(struct stat *stat)
{
	free(stat->v);
}

void stat_print(struct stat* s)
{
	int i;
	printf("Input : ");
	printf("%d", s->v[0]);
	for(i=1; i<s->size_v; i++){
		printf(" %d ", s->v[i]);
	} 
	printf("\nMAX == %d\n", s->min);
	printf("MIN == %d\n", s->max);
	printf("AVERAGE == %.4lf\n", s->average);
}

void* average(void* v)
{
	struct stat *s;
	double d;
	int i;
	
	s = (struct stat*)v;
	d = 0.0;
	for(i=0; i<s->size_v; i++){
		d+= (double)s->v[i];
	}
	s->average = d/(double)s->size_v;
	return NULL;
}

void* max(void* v)
{
	struct stat *s;
	int max;
	int i;
	s = (struct stat*)v;
	if (s->size_v <= 0){
		printf("No max in empty array\n");
		return NULL;
	}
	max = s->v[0];
	for(i=0; i<s->size_v; i++){
		if(s->v[i] > max){
			max = s->v[i];
		}
	}
	s->max = max;
	return NULL;
}


void* min(void* v)
{
	struct stat *s;
	int min;
	int i;
	s = (struct stat*)v;
	if (s->size_v <= 0){
		printf("No max in empty array\n");
		return NULL;
	}
	min = s->v[0];
	for(i=0; i<s->size_v; i++){
		if(s->v[i] < min){
			min = s->v[i];
		}
	}
	s->min = min;
	return NULL;
}


void stat_random(struct stat *s)
{
	int i;
	for(i=0; i<s->size_v; i++){
		s->v[i]=rand();
	}	
}

int main()
{
	struct stat stat;
	pthread_t avt, maxt, mint;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	stat_init(&stat, 128);	
	stat_random(&stat);

	pthread_create(&avt, &attr, average, (void*)&stat);
	pthread_create(&maxt, &attr, max, (void*)&stat);
	pthread_create(&mint, &attr, min, (void*)&stat);

	pthread_join(avt, NULL);
	pthread_join(maxt, NULL);
	pthread_join(mint, NULL);
	
	stat_print(&stat);

	return 0;
}
