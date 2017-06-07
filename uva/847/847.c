#include <stdio.h>

int main(){

    unsigned int n,p,s, max, min, t;
    for(;;){
        if(scanf("%u",&n)==EOF)
            break;
        p=1;
        s=1;
        min=2;
        max=9;
        for(;;){
           /*printf("%d , [%d,%d] %s \n", n, min, max, s==1?"Stan":"Ollie"); 
             */
           if(n>=min && n<=max){
               s==1 ? printf("Stan wins.\n") : printf("Ollie wins.\n");
               break;
           }
           s=(~s)&0x1;
           t=max+1;
           if(s){
               max=max*9;
           }
           else{
               max=max*2;
           }
           min=t;  
        }
    }
    return 0;
}


