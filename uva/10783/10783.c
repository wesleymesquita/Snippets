#include <stdio.h>

int main(){
    int t, a, b, i, s,c;
    scanf("%d", &t);
    c=1;
    for(;t-->0;){
        scanf("%d", &a);
        scanf("%d", &b);
        s=0;
        for(i=a;i<=b;i++)
            s += i%2==1?i:0; 
        printf("Case %d: %d\n", c, s);
        c++;
    }
    return 0;
}

