/*
   * @brief Multiply very big numbers 
   * @author Wesley Mesquita
   * @email wesleymesquita@gmail.com
   *
   * @note This solution is limited by 256 digits. There is no control of
   *       ositive/negative yet
   *
   */

#include<stdio.h>
#include<string.h>

void mult(char* a, int a_p, char* b, int b_p, char* c, int* c_p){
    int i, j, t, carry_mul, carry_sum, shift, tmp ;
    *c_p = 255;
    for(i=255; i>=0; i--)
        c[i]=0;    
    
    shift = 0; 
    for(i=255; i>=b_p; i--){
        carry_mul = 0;
        carry_sum = 0;
        for(j=255; j>=a_p; j--){
            t = ((a[j]-'0')*(b[i]-'0')+carry_mul)%10; 
            carry_mul = ((a[j]-'0')*(b[i]-'0')+carry_mul)/10;  
            
            tmp =  c[j-shift]; 
            c[j-shift]  = (c[j-shift] + carry_sum + t)%10;             
            carry_sum = (tmp + carry_sum + t)/10;           
            
            if(j == a_p && carry_mul != 0){                
                tmp = c[j-shift-1];
                c[j-shift-1] = (c[j-shift-1] + carry_mul)%10;
                c[j-shift-2] = (tmp + carry_mul)/10;
            }

            if(j == a_p && carry_sum != 0){
                c[j-shift-1] = (c[j-shift-1] + carry_sum)%10;
                c[j-shift-2] = (c[j-shift-2] + carry_sum)/10;
                printf("c[%d]=%d\n", j-shift-1, c[j-shift-1]); 
            }
            
            //printf("t==%d, carr_mul=%d, c[%d]=%d, carry_sum=%d\n", t, carry_mul, j-shift, c[j-shift], carry_sum);

        }
              
        shift++;      
   }
   
   //printf("c_p == %d\n", *c_p); 
   
   for(i=255; i>=0; i--)
    c[i]+='0';    
}

void print(char* c){
    int i=-1;
    while(c[++i]=='0');
    
    for(; i<256; i++){
        printf("%c", c[i]);
    }
}

int main(){

    char a[256]; 
    char b[256];
    char tmp[256];
    int sz, a_p, b_p, tmp_p;

    scanf("%s", tmp);
    sz = strlen(tmp);
    a_p = 256;
    while(sz--)a[--a_p]=tmp[sz];

    scanf("%s", tmp);
    sz = strlen(tmp);
    b_p = 256;
    while(sz--)b[--b_p]=tmp[sz];
    
    mult(a, a_p, b, b_p, tmp, &tmp_p);
    print(tmp);

    return 0;
}
