#include<iostream>
#include<vector>
#include<algorithm>


int main(){
	std::vector<std::string*> str_pointer_vec ;
	std::string* ptr1 = new std::string("C");
	std::string* ptr2 = new std::string("B");
	std::string* ptr3 = new std::string("A");	

	str_pointer_vec.push_back(ptr1);
	str_pointer_vec.push_back(ptr2);
	str_pointer_vec.push_back(ptr3);
	
	for(std::string* str: str_pointer_vec){
		std::cout << *str; 
	}
	
	std::cout << std::endl;
	
	std::sort(str_pointer_vec.begin(),  str_pointer_vec.end(), [&](std::string* str1, std::string* str2){return *str1 < *str2;});
	
	for(std::string* str: str_pointer_vec){
		std::cout << *str; 
	}
	
	delete ptr1;
	delete ptr2;
	delete ptr3;
	
	return 0;
}	
