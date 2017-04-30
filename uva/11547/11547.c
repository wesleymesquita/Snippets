#include <stdio.h>

int main(){
    int t, n;

    scanf("%d", &t);

    for(;t-->0;)
    {
        scanf("%d", &n);
        n = (((((((n*567)/9)+7492)*235)/47)-498)%100)/10;
        printf("%d\n", n>0?n:-n);
    }
    return 0;
}
