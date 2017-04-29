#include<stdio.h>

int main(){
    char n[16];
    int s,sum;
    for(;;){
        scanf("%s", n);
        if(n[0]=='0')
            break;
        while(n[1]!='\0'){
            s=-1;
            while(n[++s]!='\0');
            sum=0;
            while(--s>=0)
                sum+=n[s]-'0';
            sprintf(n,"%d", sum);
        }
        printf("%c\n", n[0]);
    }
    return 0;
}
