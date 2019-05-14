#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct {
    int c;
    vector<int> m;
} comm;

int main() {
    int n, q; cin >> n >> q;
    n++;
    vector<comm> c(n);
    for(int i=0; i<n; i++) {
        c[i].c = i;
        c[i].m.push_back(i);
    }
    while(q>0){
       char ch; cin >> ch;
       if (ch == 'Q'){
          int c1; cin >> c1;
          cout << c[c[c1].c].m.size() << "\n";
       }else{
           int c1, c2; cin >> c1 >> c2; 
           if(c[c[c1].c].m.size() < c[c[c2].c].m.size()){
              swap(c1, c2); 
           }
           if (c[c1].c != c[c2].c) {
              copy(c[c[c2].c].m.begin(), c[c[c2].c].m.end(), back_inserter(c[c[c1].c].m));
              for(auto&m : c[c[c2].c].m){
                  c[m].c = c[c1].c;
              }
            }
        }
       q = q - 1;
    }
    return 0;
}

