// Geeks for Geeks - Least Prime Factor 
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=1399 
#include <iostream>
#include <vector>
using namespace std;

void sieve(vector<int>& p){
    vector<bool> v(1000, true);
    v[1] = false;
    v[2] = true;
    for(int i=2; i<33; i++){
        if(v[i] == true){
            for(int j=i+1; j<1000/i; j++){
                v[i*j] = false;    
            }    
        }
    }
    for(int i=2; i<1000; i++){
        if(v[i]){
            p.push_back(i);
        }
    }
}

int main() {
    int t; cin >> t;
    vector<int> p;
    sieve(p);
    while(t--){
        int n; cin >> n;
        if(n == 1){
            cout << "1" << endl;
        }
        else{
            for(int i=1; i<=n; i++){
                if(i == 1){
                    cout << "1 ";
                    continue;
                }
                vector<int>::iterator it = p.begin();
                for(;it!=p.end(); it++){
                    if (i%*it==0){
                        cout << *it << " ";
                        break;
                    }
                }
            }           
            cout << endl;
        }
    }
    return 0;
}
