#include<unordered_map>
#include<functional>
#include<string>
#include<iostream>

int main(){
	std::unordered_map<
	std::string, 
		std::function<void(std::string&)> > funcs = {
			{"FUNC", [](std::string& str){std::cout << str << std::endl;} } 

		};
	std::string blz = "BLZZZZ";
	funcs["FUNC"](blz);
	return 0;
}
