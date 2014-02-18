#include<stdio.h>

int main(){
	int n, i, j, k, count; 
	
	scanf("%d", &n);
	while(n != 0){
		count = 0;
		for(i=n; i>=1; i--)		
			count += i*i;
		
		printf("%d\n", count);
		scanf("%d", &n);
	}
	
	return 0;
}