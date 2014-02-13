/*
* @brief Solution to http://www.spoj.com/problems/ADDREV/
* @author Wesley Mesquita
* @email wesleymesquita@gmail.com
*
* @note Long far from optimal solution using many std::stringstream, 
*        but was 15 min work.
*/

#include<iostream>
#include<sstream> 
#include<algorithm>
int main(){
	
	int n_tests;
	bool first = true;
	std::cin >> n_tests;
	std::string a_str,b_str, c_str;
	unsigned int a, b, c;
	while(n_tests--){
		
		std::cin >> a_str >> b_str;
		std::reverse(a_str.begin(), a_str.end() );
		std::reverse(b_str.begin(), b_str.end() );
		
		std::stringstream asstr(a_str);
		asstr >> a;
		
		std::stringstream bsstr(b_str);
		bsstr >> b;
		
		c = a + b;
		
		std::stringstream csstr("");
		csstr << c;
		
		csstr >> c_str;
				
		std::reverse(c_str.begin(), c_str.end());
		
		std::stringstream res(c_str);	
		
		res >> c;
		
		if(first){
			first = false;
			std::cout << c;
		}
		else
			std::cout << std::endl << c;
	}

	return 0;
}