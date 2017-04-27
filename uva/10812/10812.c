#include <stdio.h>

int main(){
    int t, s, d, x, y;
    scanf("%d", &t);

    for(;t-->0;){
        scanf("%d %d", &s, &d);
        if((s+d)%2!=0){
            printf("impossible\n");
            continue;
        }
        x = (s+d)/2;
        y = s-x;
        if(y<0){
            printf("impossible\n");
            continue;
        }

        if(x+y == s && (x-y==d || y-x==d))
            printf("%d %d\n", x>y?x:y, x>y?y:x);
        else
            printf("impossible\n");
    }
    return 0;
}

