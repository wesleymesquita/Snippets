#include <stdio.h>

int main(){
    int t, max, r, i, c, tmp;

    scanf("%d", &t);
    c=1;
    for(;t-->0;){
        scanf("%d", &r);
        max=-1;
        for(i=0;i<r;i++){
            scanf("%d", &tmp);
            if(tmp>max) 
                max=tmp;
        }
        printf("Case %d: %d\n",c++, max);
    }
    return 0;
}
                
