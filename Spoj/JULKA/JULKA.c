/*
   * @brief Solution to http://www.spoj.com/problems/JULKA/
   * @author Wesley Mesquita
   * @email wesleymesquita@gmail.com
   *
   * @note All arithmetic algos were ad-hoc implemented. Got AC in 0.00s/1.6M
   *
   */

#include<stdio.h>
#include<string.h>
#define S 256 

void print(int* v, int v_p){
    int i=v_p;
    while(v[i]==0)i++;
    while(i<S)
        printf("%d", v[i++]);
}

void add(int* m, int m_p, int* z, int z_p, int* r, int* r_p){
     int i, j, k, c;
     
     memset(r,0, S);   

     i = S-1;
     c = 0;
     while(i>=m_p && i>=z_p){
        r[i] = (m[i] + z[i] + c)%10;
        c = (m[i] + z[i] + c)/10;             
        i--;
     }
    
    if(i>=m_p && i<z_p){
        while( i>=m_p ){
           r[i] =(m[i]+c)%10;
           c = (m[i]+c)/10;
           i--;    
        }
    }
    
    if(i<m_p && i>=z_p){ 
       
        while(i >= z_p){
         r[i] = (z[i]+c)%10;
         c = (z[i] + c)/10;
         i--;
       }
    }
    
    *r_p = m_p < z_p ? m_p : z_p;   
    
    if(c)
        r[--*r_p] = c;
    
   
}
//r =  m -z
void sub(int* m, int m_p, int* z, int z_p, int* r, int* r_p ){
    int i,c;
    c = 0;
    memset(r, 0, S);
    for(i=S-1; i>=z_p; i--){
        if(m[i] < (z[i] + c)){
            
            r[i] = m[i]+10-z[i]-c;        
            c = 1;
        }
        else{
            r[i] = m[i]-z[i]-c;
            c = 0;
        }
    }
    
    while(i>=m_p){
        if(m[i] < c){
            r[i] = m[i]+10-c; 
            c = 1;
        }
        else{
            r[i] = m[i] - c;
            c = 0;
        }
        i--;
    }
    
    *r_p = m_p;
    if(r[*r_p]==0) *r_p++; 
}

void div2(int* m, int m_p, int* r, int* r_p){
    int i, n, rm;
    memset(r,0,S);
    n = 0;
    rm = 0;
    *r_p = m_p;
    for(i=m_p; i<S;i++){       
        if(i == 1 && m[i] == 1){           
            n = 10 + m[i+1];           
            i++;
            r[i] = n/2;
            rm = n%2;
        }
        else{
            n = rm*10 + m[i];
            r[i] = n/2;
            rm = n%2;
        }
    }
}

int main(){
    int m[S], z[S], r[S], y[S];    
    char tmp[S];
    int y_p, m_p, z_p, r_p, sz, t=10;
    
    while(t--){
        
        scanf("%s", &tmp);
        sz=-1;
        while(tmp[++sz]!='\0');
        memset(m,0,S);
        memset(m,0,S);
        m_p=S;
        y_p=S;
        sz--; 
        while(sz>=0){
            m[--m_p]=tmp[sz]-'0'; 
            y[--y_p]=tmp[sz]-'0';
            sz--;
        }
        
		scanf("%s", &tmp);
        sz=-1;
        memset(m, 0, S);
        while(tmp[++sz]!='\0');
        z_p=S;
        while(sz)z[--z_p]=tmp[--sz]-'0'; 
                
        add(m, m_p, z, z_p, r, &r_p);
        sz=S-1;    
        m_p=r_p;
        while(sz){
            m[sz]=r[sz];
            sz--;
        }

        div2(m, m_p, r, &r_p);
        print(r,r_p);
        printf("\n");
   

        sub(y, y_p, z, z_p, r, &r_p);
        div2(r, r_p, m, &m_p);

        print(m, m_p);
        printf("\n");
    }

   return 0; 
}


