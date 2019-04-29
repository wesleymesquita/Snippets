/* Silberschatz Operating Systems Concepts 9th - Exercise 4.22 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


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
	#pragma omp parallel
	for(i=0; i<npoints; i++){
		random_point(&p, &r);		
		points_in_circle += in_circle(&center, 1.0, &p)?1:0;
	}
	return points_in_circle;
}


int main(int argc, char **argv)
{
	int npoints, in_circle;

	if(argc != 2){
		fprintf(stderr, "Use ./monte_carlo [number of points (in MB)]");
		return 1;
	}		
	
	npoints = atoi(argv[1]);			
	npoints *= 1024*1024;

	in_circle = points_circle(npoints);		
	printf("pi == %.16lf\n", 4*((double)in_circle/(double)npoints));
	return 0;
}
