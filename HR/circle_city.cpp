//https://www.hackerrank.com/challenges/circle-city
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t; cin>>t;
    while(t--){
        int d, k; cin>>d>>k;
        double dr=sqrt(d);
        int r = (int)dr;
        unordered_map<int, int> p;
        int c = 0;
        for(int i=0; i<=r; i++){
            int v;
            bool found = true;
            if(p.find(i) != p.end()){
                v = p[i];
            }
            else{
                double tmp = sqrt(d - i*i);
                if(tmp - (double)(int)tmp == 0 ){                    
                    v = (int)tmp;
                    p[i] = v;
                }    
                else{
                    found = false;
                }
            }
            if(found){
                if(v == 0 || dr-(double)v  == 0.0)
                    c += 2;
                else
                    c += 4;                
            }
        }
        cout << [&](){ 
                if(k >= c ){
                    return "possible";             
                }
                else{
                    return "impossible";
                }        
                }() 
        << endl; 
    }
    
    return 0;
}
