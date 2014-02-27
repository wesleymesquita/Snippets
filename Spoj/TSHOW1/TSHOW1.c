/*
   * @brief Solution to http://www.spoj.com/problems/TSHOW1/
   * @author Wesley Mesquita
   * @email wesleymesquita@gmail.com
   *
   *
   */

   #include<stdio.h>
#include<math.h>
#define S 256 

int main(){
	unsigned long long i, j, n, s, b;
	int t;
	
	scanf("%d", &t);
	while(t--){
		scanf("%llu", &n);
		s = 0;	
		i = 0;
		
		while( s<n ){ 
			s += pow((double)2, (double)++i);
		}
		s = s-(unsigned long long)pow((double)2, (double)i) + 1; 
		
		j = n-s;
				
		while(i>0){
			printf("%d", 5+((j>>(i-1))&1));
			i--;
		}			
		printf("\n");
	}
	return 0;
}