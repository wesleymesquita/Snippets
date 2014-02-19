#include<stdio.h>
int main(){
	double n, t;
	
	int c;
	scanf("%lf", &n);
	
	
	while( n != 0.00 ){
		
		if(n <= 0.50)
			printf("1 card(s)\n");
		else{		
			c = 1;
			t = 0.00;
			while( t < n ){
				t += 1.00/((double)c+1);
				c++;
			}		
			printf("%d card(s)\n", c-1);		
		}
		scanf("%lf", &n);	
	}	
	return 0;
}