#include<stdio.h>
#include<math.h>

#define sin60 0.86602540378
#define sin60_2 0.75

int main(){
	int t;
	double v, a, h;
	scanf("%d", &t);
	while(t--){
		scanf("%lf", &v);	
		a = cbrt((3*v)/(sin60_2)); 
		h = 2*v/(a*a*sin60);
		printf("%lf\n", (a*a*sin60 + 3*a*h)); 
	}
	return 0;
}