#include<regex>
#include<string>
#include<fstream>
#include<utility>
#include<algorithm>
#include<iostream>

void loadDomains(const char* fileLocation, 
				std::vector<std::string>& domains){
	std::ifstream domainFileStream; 
	domainFileStream.open(fileLocation, std::ifstream::in);
	if( domainFileStream.good() ){
		while( !domainFileStream.eof() ){
			std::string domain;
			std::getline(domainFileStream, domain);
			if(domain.size() == 0)
				throw std::exception();
			else
				domains.push_back(domain);
		}		
	}	
}

std::regex mount_email_validation_regex(const char* const domainFile ){
	std::string regex_expr = "(.*)@(.*)(";
	
	std::vector<std::string> validDomains;
	loadDomains(domainFile, validDomains);
	bool is_first = true;
	for(std::string domain: validDomains){
		std::string formated_domain = domain;	
		size_t pos = formated_domain.find(".");
		while(pos != std::string::npos){
			formated_domain = formated_domain.replace(domain.begin() + pos, 
				domain.begin() + pos + 1, 
				"\\." );
			pos = domain.find(".", pos);
		}
		
		regex_expr += is_first ? formated_domain  : "|" + formated_domain;	
	}
	regex_expr += ")";
	
	return std::move(std::regex(regex_expr));
}

bool validate_email(const std::string& email, const std::regex& email_rgx){
	if(email.size() == 0){
		return false;
	}	
	else{
		return std::regex_match(email, email_rgx);		
	}
}

bool validate_email_set(const std::vector<std::string>& emails, 
						const std::regex& regex_expr,
						std::vector<bool> results){
	
	for(auto email: emails){	
		results.push_back( validate_email(email, regex_expr) );
	}
}

int main(){
	std::vector<std::string> emails = {
	"a@b.com", 
	"a@b.com.br", 
	"a@b.co.uk", 
	"a@b.qwert"
	};          
	
	std::vector<bool> expected_result = {true, true, true, false};
	
	std::vector<bool> results;
	results.reserve(emails.size());	
	
	const std::regex regex_expr = mount_email_validation_regex("secondary.txt");  
	validate_email_set(emails, regex_expr, results);
	
	bool result =  std::equal( results.begin(), results.end(), expected_result.begin() ); 
	
	std::cout << "Emails were " 
			  << [&](){ return result?"":"not ";}() 
			  << " validated as expected."  
			  << std::endl; 
		
	return 0;
}
