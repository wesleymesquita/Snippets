#include<stdio.h>

int main(){
	char n[128], c[128];
	int i, j, sz, up, und;
	while(scanf("%s", n) > 0){
			
		sz=-1;	
		up=0;
		und=0;
		while(n[++sz]!='\0');
		
		if(sz >= 1 && (n[0]>='A' && n[0]<='Z')){
			printf("Error!\n");
			continue;
		}
		
		for(i=0; i<sz; i++){
			if( !((n[i]>='a' && n[i]<='z') || (n[i]>='A' && n[i]<='Z') || n[i]=='_') )
				break;	
			if((i==0 || i==sz-1) && n[i] == '_' )
				break;
			else if((n[0]>='A' && n[0]<='Z') && (n[i]>='a' && n[i]<='z'))
				break;
			else if(up && n[i] == '_')
				break;
			else if(i>0 && n[i-1] == '_' && n[i] == '_')
				break;	
			else if(!up && n[i] == '_')
				und = 1;
			else if(und && n[i]>='A' && n[i]<='Z')
				break;
			else if(!und && i>0 && (n[i-1]>='a' && n[i-1]<='z') && (n[i]>='A' && n[i]<='Z'))
				up = 1;
		}
		if(i < sz){
			printf("Error!\n");
			continue;
		}
			
		if(up){
			j = -1;
			for(i=0; i<sz; i++){
				if( n[i]>='A' && n[i]<='Z'){
					c[++j] = '_';	
					c[++j] = n[i]+32;	
				}		
				else
					c[++j] = n[i];
			}
			c[++j] = '\0';	
			printf("%s\n", c);
		}		
		else if(und){
			j=-1;
			for(i=0; i<sz; i++){
				if(n[i] == '_'){
					c[++j] = n[i+1]-32;
					i++;
				}
				else
					c[++j] = n[i];
			}			
			c[++j] = '\0';	
			printf("%s\n", c);
		}
		else{
			printf("%s\n", n);
		}	
	}
	return 0;
}