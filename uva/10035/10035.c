#include<stdio.h>
#include<string.h>


void shift(char *a, int sza, int shift_sz){
    int i;
    for(i=sza-1;i>=0;i--){
        a[i+shift_sz] = a[i];
    }
    for(i=0;i<shift_sz; i++){
        a[i]='0';
    }
}

int main(){
    char a[11], b[11];
    int sza, szb, i, j, sz, c, ccount;
    for(;;){
        scanf("%s %s", a, b);
        if(a[0]=='0' && b[0]=='0')
            break;

        sza = strlen(a);
        szb = strlen(b);
        if(sza>=szb){
            sz=sza;
            shift(b, szb, sza-szb);
        }
        else{
            sz=szb;
            shift(a, sza, szb-sza);
        }
        ccount=0;
        c=0;
        for(i=sz-1; i>=0; i--){
           if(a[i]-'0'+b[i]-'0'+c >= 10){
               ccount++;
               c=1;
            }
           else{
               c=0;
           }
        }

        switch(ccount){
            case 0:
                printf("No carry operation.\n");
                break;
            case 1:
                printf("1 carry operation.\n");
                break;
            default:
                printf("%d carry operations.\n", ccount);
                break;
        }
    } 
    return 0;
}
