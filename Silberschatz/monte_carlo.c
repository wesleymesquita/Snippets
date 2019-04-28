/* Silberschatz Operating Systems Concepts 9th - Exercise 4.22 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NTHREADS 4

struct point {
	double x, y;
};

struct range {
	double min, max;
};

double random_from_range(struct range *r)	
{
	double scaled;
	
	scaled = ((double)random())*(r->max-r->min);
	scaled /= (double)RAND_MAX;
	scaled += r->min;
	return (double)scaled; 
}	

void random_point(struct point *p, struct range *r)
{
	p->x = random_from_range(r);
	p->y = random_from_range(r);
}

int in_circle(struct point *center, double radius, struct point *p)
{
	double distance;

	distance = (p->x-center->x)*(p->x-center->x)+(p->y-center->y)*(p->y-center->y);
	distance = sqrt(distance);
	return distance < radius ? 1 : 0;
}

double points_circle(int npoints)
{
	struct point p, center;
	struct range r;
	int points_in_circle, i;
		
	center.x=0.0;
	center.y=0.0;
		
	r.min=-1.0;
	r.max=1.0;
	
	points_in_circle=0;				
	for(i=0; i<npoints; i++){
		random_point(&p, &r);		
		points_in_circle += in_circle(&center, 1.0, &p)?1:0;
	}
	return points_in_circle;
}

struct pi_calc{
	int npoints;
	int points_in_circle;
};

void* worker(void *arg)
{
	srandom(time(NULL));
	int npoints;
	npoints = ((struct pi_calc*)arg)->npoints;
	((struct pi_calc*)arg)->points_in_circle= points_circle(npoints);
	printf("Thread %u: Total points %d. In circle: %d\n", pthread_self(), npoints, ((struct pi_calc*)arg)->points_in_circle);
	return NULL;
}

int main()
{
	pthread_t t[NTHREADS];
	struct pi_calc args[NTHREADS];
	pthread_attr_t attr;
	int i, npoints, in_circle;

	npoints = 1024*1024*32;
		
	pthread_attr_init(&attr); 
	for(i=0; i<NTHREADS; i++){
		args[i].npoints = npoints;
		sleep(1);
		pthread_create(&t[i], &attr, worker, (void*)&args[i]); 			
	}

	for(i=0; i<NTHREADS; i++){
		pthread_join(t[i], NULL);
	}	

	in_circle = 0;		
	for(i=0; i<NTHREADS; i++){
		in_circle += args[i].points_in_circle;
	}
	
	printf("pi == %.16lf\n", 4*((double)in_circle/(double)(NTHREADS*npoints)));
	return 0;
}
