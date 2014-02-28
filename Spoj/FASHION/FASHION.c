#include<stdio.h>
int main(){
	int i, j, k, p, q, n, t;
	
	int m[1000], w[1000];
	scanf("%d", &t);
	while(t--){
		scanf("%d\n", &n);
		
		if(n == 1)
			scanf("%d", &m[0]);
		else{
			for(i=0; i<n-1; i++){
				scanf("%d ", &m[i]);
			}
			scanf("%d", &m[n-1]);
		}
		
		
		if(n == 1)
			scanf("%d", &w[0]);
		else{
			for(i=0; i<n-1; i++){
				scanf("%d ", &w[i]);
			}
			scanf("%d", &w[n-1]);
		}
			
		for(i=0; i<n; i++){
			k = m[i];
			p = i;		
			for(j=i+1; j<n; j++){
				if(m[j] < k){
					k = m[j];
					p = j;
				}
			}			
			if(p != i){
				q= m[i];	
				m[i] = m[p];
				m[p] = q;
			}
		}
		
		for(i=0; i<n; i++){
			k = w[i];
			p = i;				
			for(j=i+1; j<n; j++){
				if(w[j] < k){
					k = w[j];
					p = j;
				}
			}			
			if(p != i){
				q= w[i];	
				w[i] = w[p];
				w[p] = q;
			}
		}
		
		p = 0;
		for(i=0; i<n; i++){
			p += w[i]*m[i];
		}
		
		printf("%d\n", p);
		
	}
	
	return 0;
}