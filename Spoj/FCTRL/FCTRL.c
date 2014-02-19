/*
* @brief Solution to http://www.spoj.com/problems/FCTRL/
* @author Wesley Mesquita
* @email wesleymesquita@gmail.com
*
* @note Just count how many unique '5' there are until the number
* 
*/

#include<stdio.h>

int main(){
	int t, n, f, c; 
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		if(n < 5){
			printf("0\n");	
			continue;
		}
		f = 5;
		c = 0; 	
		while(f <= n){
			c += n/f;
			f *= 5;
		}		
		printf("%d\n", c);		
	}
	return 0;
}