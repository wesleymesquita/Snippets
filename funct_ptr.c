#include <stdio.h>

/* example of function pointer in C  */

int 
apply(int (*fn)(int, int), int vec[], int sz)
{
	int i, total;
	if(sz < 0){
		fprintf(stderr, "Does not make sense to apply a func for a empty set");
		return 0;
	}
	total = vec[0];	
	for(i=1; i<sz; i++)	
		total = fn(vec[i], total);
	return total;
}

int 
sum(int a, int b)
{
	return a + b;
}

int 
mul(int a, int b)
{
	return a * b;
}

int 
test_apply()
{
	int vec[] = {1,2,3,4};
	int total;
	
	fprintf(stdout, "Testing 'apply' with 'sum'\n");
	total  = apply(sum, vec, 4);
	if(total == 10) 
		fprintf(stdout, "Worked!\n");
	else
	 	fprintf(stderr, "Did not work for sum! Expected 10, got %d\n", total);
	
	fprintf(stdout, "Testing 'apply' with 'mul'\n");
	total  = apply(mul, vec, 4);
	if(total == 24) 
		fprintf(stdout, "Worked!\n");
	else
	 	fprintf(stderr, "Did not work for sum! Expected 24, got %d\n", total);
}
			
int 
main()
{
	test_apply();
	return 0;
}

