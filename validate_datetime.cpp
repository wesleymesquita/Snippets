#include<unordered_map>
#include<iostream>
#include<string>

int main(){
	const std::string date_str = "Fri, 7 Dec 2001 10:06:42 -0800 (PST)";
	std::unordered_map<std::string, std::string> date_parsed_data;
	
	date_parsed_data["week_day"] = date_str.substr(0, 3); 
	date_parsed_data["month_day"] = date_str.substr(5, 1); 
	date_parsed_data["month"] = date_str.substr(7, 3); 
	date_parsed_data["year"] = date_str.substr(10, 5); 
	date_parsed_data["hour"] = date_str.substr(16, 2); 
	date_parsed_data["minute"] = date_str.substr(19, 2); 
	date_parsed_data["second"] = date_str.substr(22, 2); 
	date_parsed_data["time_zone"] = date_str.substr(24, 6); 

	
	auto it = date_parsed_data.begin();
	
	while(it != date_parsed_data.end() ){
		std::cout << it->first << " -- " <<  it->second  << std::endl;
		it++;
	}
	
	return 0;	
}