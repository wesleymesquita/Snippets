/*
   * @brief Solution to http://www.spoj.com/problems/TOANDFRO/
   * @author Wesley Mesquita
   * @email wesleymesquita@gmail.com
   *
   * @note Pay attention in how the matrix is constrcted
   *
   */



#include<stdio.h>

int main(){
    char m[201];
    int n,i,j,l,sz;
    scanf("%d\n", &n);
    while(n!=0){
        scanf("%s", m);
        sz = -1;
        while(m[++sz]!='\0');
        l = sz/n;
        
        for(i=0; i<n; i++){
            for(j=0; j<l; j++){
                if(j%2 == 0){
                    printf("%c", m[i+n*j]);
                }
                else{
                    printf("%c", m[n*(j+1)-i-1]);
                }
            }
        }
        printf("\n");
        scanf("%d", &n);
    }
    
    return 0;
}
