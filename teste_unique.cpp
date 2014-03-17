#include<iostream>
#include<memory>
#include<vector>

int main(){
		
	std::vector< std::unique_ptr<int> > vec;
	int a = 1;
	int b = 2;
	vec.push_back(std::unique_ptr<int>(&a));
	vec.push_back(std::unique_ptr<int>(&b));
	
	std::vector< std::unique_ptr<int> > vec2;
	vec2.push_back(vec.pop_front());	
	vec2.push_back(vec.pop_front());
	
	return 0;
}