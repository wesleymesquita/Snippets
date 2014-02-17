#include<stdio.h>
#include<string.h>
void print(char* a);

void mult(char* a, int a_p, char* b, int b_p, char* c, int* c_p){
    int i, j, t, carry_mul, carry_sum, shift, tmp ;
   
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
                //printf("c[%d]=%d\n", j-shift-1, c[j-shift-1]); 
            }
            

            //printf("t==%d, carr_mul=%d, c[%d]=%d, carry_sum=%d\n", t, carry_mul, j-shift, c[j-shift], carry_sum);

        }
              
        shift++;      
   }
  //printf("c_p == %d\n", *c_p); 
   
   for(i=0; i<256; i++){
             c[i]+='0';    
    //printf("%d\n", a[i]); 

   } 
  
    
  //printf("*****");
  //print(c);
 // printf("\n");
   

   *c_p=-1;
   while(c[++*c_p]=='0');
 }



void bpp(char* b, int* b_p){
    int i, carry, tmp;
    carry = 0;
    
    carry =  (b[255]-'0' + 1)/10;
    b[255] = ((b[255]-'0' + 1)%10)+'0'; 
    
    if(carry==0)
        return;

    for(i=254; i>=*b_p; i--){
       tmp = carry;
       carry =  (b[i]-'0' + carry)/10;
       b[i] = (b[i]-'0'+ tmp)%10 + '0'; 
       if(carry == 0) break;
    }
    
   if(carry != 0)
     b[--*b_p] = carry + '0';
    

}

void copy(char* a, int a_p, char* b, int* b_p){
    int i;
    *b_p = 256;
    for(i=255; i<=0; i--)
        b[i] = '0';
    for(i=255; i>=a_p; i--)
        b[--*b_p] = a[i];
    //printf("b_p == %d\n", *b_p);

}

void print(char* a){
    int i=-1;
    while(a[++i]=='0');
    for(; i<256; i++){
        printf("%c",a[i]);
    }
}

void fac_ptr(int n, char* a){
  const char* fac_20  = "2432902008176640000";         
  
  char b[256], c[256];
  int a_p, b_p, c_p;
  int i;
 
  for(i=0;i<256;i++){
      b[i] = '0';
      a[i] = '0';
  }
 
  a_p = 256;
  for(i=18; i>=0; i--){
    a[--a_p] = fac_20[i];
  }
  
  b[255] = '1';
  b[254] = '2';
  b_p = 254;

  for(i=21; i<=n; i++){
    printf("n == %d: ", i);
    print(a);
    printf(" * ");
    print(b);
    printf(" == " );
    
    mult(a, a_p, b, b_p, c, &c_p);   
    print(c);
    printf("\n");
    bpp(b, &b_p);
    copy(c, c_p, a, &a_p);
  }
   
}

int main(){
    int n_tests, first, n, i;
    unsigned long long resp;
    char res[256];
        
    scanf("%d", &n_tests);
    first = 1;
    while(n_tests--){
         scanf("%d", &n);
         
         if(n <= 20){
            resp = 1;
            for(i=1; i<=n; i++)
                resp *= i;
             printf("%llu\n", resp);
         }
         
         else{
           fac_ptr(n, res);
           print(res);
           printf("\n");    
         }       
    }

    return 0;
}       
