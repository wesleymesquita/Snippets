#include <iostream>
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=152
// Dynamic Programming | Set 4 (Longest Common Subsequence)
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
	//code
	int t; cin >> t;
	while(t--){
	    int sza, szb; cin >> sza >> szb;
	    string sa, sb; cin >> sa; cin >> sb;
	    vector<vector<int> > s(sza+1);
	    for(int i=0; i<=sza;i++){
	        s[i].resize(szb+1);
	        fill(s[i].begin(), s[i].end(), 0);     
	    }
	    for(int i=1; i<=sza; i++){
	        for(int j=1; j<=szb; j++){
	            if(sa[i-1] == sb[j-1]){
	                s[i][j] = s[i-1][j-1] + 1;   
	            }
	            else{
	               s[i][j] = s[i][j-1] > s[i-1][j] ?  s[i][j-1] : s[i-1][j];
	            }
	        }    
	    }
        cout << s[sza][szb] << endl;
	    
	}
	return 0;
}