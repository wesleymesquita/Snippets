#include<regex>
#include<string>
#include<string>

int main(){
	
	std::regex reg("(.*)(@)(.*)");
	
	std::string str = "a@b.com";
	
	bool matched = std::regex_match(str, reg);

	if(matched)
i		std::cout << str << " is a valid email" << std::endl;
	
	return 0;
}
