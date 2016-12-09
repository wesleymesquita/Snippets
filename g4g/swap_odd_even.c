// http://www.practice.geeksforgeeks.org/problem-page.php?pid=626
// Swap all odd and even bits

#include <stdio.h>

int main() {
	//code
	int t; scanf("%d", &t);
	while(t--){
	    unsigned int n; scanf("%u", &n);
	    unsigned int r=0;
	    int i=0;
	    while(i < 32){
	        
	        int even = ( (1<<i     &n) >>  i    ) << (i+1);
	        int odd =  ( (1<<(i+1) &n) >> (i+1) ) << i;
	        r |= even;
	        r |= odd;
	        i+=2;
	    } 
	    printf("%u\n", r);
	    
	}
	return 0;
}