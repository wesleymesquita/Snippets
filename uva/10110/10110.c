#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int* calc_sieve(unsigned int sz, int *psz){
    unsigned int *s, *t, i,j,pc;
    s = (unsigned int*)malloc((sz+1)*sizeof(unsigned int));
    s[0]=0; s[1]=1; s[2]=1;
    for(i=3; i<=sz; i++)
        s[i]=1;
    pc=2;
    i=2;
    while(i<=sz){
        j=i;
        while(i*j<=sz){
            s[i*j]=0;
            j++;
        }
        i++;
    }
    
    for(i=3;i<=sz;i++){
        if(s[i]==1)
            pc++;
    }

    *psz=pc;
    t = (unsigned int*)malloc(sizeof(unsigned int)*pc);
    j=0;
    for(i=0;i<=sz;i++){
        if(s[i]==1)
            t[j++]=i;
    }
    free(s);
    return t;
}
        
void add_mult(unsigned int **m, int *mend, int *msz, int n){
    if(*mend == *msz){
        (*msz)*=2;
        *m=(unsigned int*)realloc(*m,(*msz)*sizeof(unsigned int));
    }
    (*m)[*mend]=n;
    (*mend)++;
}

int main(){
    unsigned int n;
    unsigned int *s, *t,tend, tsz, ssz, pf, i, j,k;

    s = calc_sieve(1<<16, &ssz);

    for(;;){
        scanf("%u", &n);
        if(n==0)
            break;
        tend=0;
        tsz=1;
        t = (unsigned int*)malloc(sizeof(unsigned int));
        for(i=0;i<ssz && s[i]<=n;i++){
            if(n%s[i]==0){
                add_mult(&t, &tend, &tsz, s[i]);  
            }
        }
        pf=1;
        i=1;
        while(n>1 && i<tend){
            k=0;
            while(n>1 && n%t[i]==0){
                n/=t[i];            
                k++;
            }
            pf*=(k+1);
            i++;
        }
        if(n!=1)
            pf*=2;
        printf("%s\n", pf%2==0?"no":"yes");
        free(t);
    }
    free(s);
    return 0;
}
