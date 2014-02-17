/*
* @brief Solution to http://www.spoj.com/problems/NSTEPS/
* @author Wesley Mesquita
* @email wesleymesquita@gmail.com
*
* @note Brute force solution. 1) Eliminate invalid inputs 
*                             2) Iterate fo find solution (antecipate break, if necessary) 	
*
*/

#include<stdio.h>

int main(){
	int t, x, y, i, j, n;  
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &x, &y);
		
		if(x == 0 && y == 0){
			printf("0\n");
			continue;
		}
		
		if(x == 1 && y == 1){
			printf("1\n");
			continue;
		}
		
		if(y > x){
			printf("No Number\n");
			continue;
		}
		
		if(x%2 == 0 && y%2 == 0){
			n = 0;
			j = -1;			
			for(i=2; i<=x && j<=y; i+=2){
				j = i-2; 	
				n+=2;			
				if(i == x && j== y){
					printf("%d\n", n);
					break;
				}
				
				j = i; 					
				n+=2;
				if(i == x && j== y){
					printf("%d\n", n);
					break;
				}
			}
			if(i != x || j != y)
				printf("No Number\n");
		}
		else if(x%2 == 1 && y%2 == 1){
			n = 1;
			j = -1;
			for(i=3; i<=x && j<=y; i+=2){
				j = i-2; 	
				n+=2;			
				if(i == x && j== y){
					printf("%d\n", n);
					break;
				}
				
				j = i; 					
				n+=2;
				if(i == x && j== y){
					printf("%d\n", n);
					break;
				}	
			}
			
			if(i != x || j != y)
				printf("No Number\n");			
		}		
		else{
			printf("No Number\n");
		}
		
	}
	
	return 0;
}