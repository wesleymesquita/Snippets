/*
   * @brief Solution to http://www.spoj.com/problems/MISERMAN/
   * @author Wesley Mesquita
   * @email wesleymesquita@gmail.com
   *
   * @note Simple DP solution
   *
   */

#include<stdio.h>

int main(){
	int k[100][100];
	int p[100][100];
	int i, j, v, val, m, n;

	scanf("%d %d", &n, &m);	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			scanf("%d", &k[i][j]);
		}
	}
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			p[i][j] = -1;
		}
	}
		
	for(j=0; j<m; j++){
		p[0][j] = k[0][j];
	}
			
	for(i=1; i<n; i++){
		
		p[i][0] = p[i-1][0]+k[i][0] <  p[i-1][1]+k[i][0] ? p[i-1][0]+k[i][0] :  p[i-1][1]+k[i][0];	 
		p[i][m-1] = p[i-1][m-1]+k[i][m-1] <  p[i-1][m-2]+k[i][m-1] ? p[i-1][m-1]+k[i][m-1] : p[i-1][m-2]+k[i][m-1];	 
		
		for(j=1; j<m-1; j++){
			v = p[i-1][j-1] + k[i][j]; 		
			
			if(p[i-1][j] + k[i][j] < v) v = p[i-1][j]+k[i][j];
			if(p[i-1][j+1] + k[i][j] < v) v = p[i-1][j+1]+k[i][j];		
			
			p[i][j] = v;
		}	
	}
	
	v = 0;
	val = p[n-1][v];
	for(j=1; j<m; j++){
		if(p[n-1][j] < val){
			val = p[n-1][j]; 
			v = j;
		}
	}
	
	printf("%d\n", p[n-1][v]);
	
	return 0;
}