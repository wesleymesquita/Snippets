#include<regex>
#include<string>
#include<string>
#include<iostream>

int main(){
	
	std::regex reg("(.*)(@)(.*)(\\.com|\\.com\\.br)");
	
	std::string str = "a@b.com.gr";
	
	bool matched = std::regex_match(str, reg);

	std::cout << str << " is "  << [&](){ return matched?"":"not "; }() << "a valid email" << std::endl;
	
	return 0;
}
