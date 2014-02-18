/*
* @brief Solution to http://www.spoj.com/problems/BEADS/
* @author Wesley Mesquita
* @email wesleymesquita@gmail.com
*
* @note Naive solution using stl algorithms. Get AC, but 
*		the better/right solutions seems to be use Duval´s algotirhm
*	    http://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation	
*
*/

#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>

int main(){
	int n_tests; scanf("%d", &n_tests);
	char str[20001];	
	int i, j, k, len, diff, diff_tmp, str_p, idx, first, idx_match;
	first = 0;
	while(n_tests--){
		scanf("%s", str);	
		str_p = -1;
		len = 0;
		while(str[++str_p] != '\0') len++;
				
		for(i=0; i<len; i++) str[str_p++] = str[i];
		str[str_p++] = '\0';
		
		diff = 0;
		idx = 0;		
		idx_match = 0;
		
		std::vector<std::string> beads;		
		for(k=0; k<len; k++){
			beads.push_back(std::string(str+k, str+k+len));			
		}
				
		std::vector<std::string>::iterator it = std::min_element(beads.begin(), beads.end());
		printf("%d\n", (it - beads.begin() + 1) );		
	}
	return 0;	
}