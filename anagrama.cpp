#include <iostream>
#include <vector>
#include <iostream>
#include <cstring>

void getFeatureVector(int* alpha, const  char* str)
{
	for (int i=0; i<256; i++)
		alpha[i] = 0;	
	
	
	for(int j=0; j<strlen(str); j++){
		alpha[str[j]]++;
	}
}

bool compareFeatureVector(const  int* a1, const  int* a2)
{
	for(int i=0; i<256; i++){
		if(a1[i] != a2[i])
			return false;
	}
	
	return true;	
}

class input_entry{
public:
    bool deleted;
	std::string entry;
	input_entry(bool d, const char* s){
		deleted = d;
		entry = s;
	}	
}; 

int main(){
	
	std::vector<input_entry> input = { {false, "star"} , {false, "astr"}, {false,  "car"} , {false, "rac"}, {false,"st"} };	
	std::cout << "[";
	
	auto it = input.begin();
	
	while(it != input.end()){
		
		if(it->deleted){
			it++;
			continue;
		}
		
		int str_alpha[256];				
		std::string tmp = it->entry;
		it->deleted = true;
		
		std::cout << "[" << tmp; 
		getFeatureVector(str_alpha, tmp.c_str());					
		
		if(it == input.end()){
			std::cout << "]";
			break;
		}
				
		auto it2 = it+1;
		while( it2 != input.end() ){					
			if(!it2->deleted){
				int str2_alpha[256];
				std::string tmp2 = it2->entry;				
				getFeatureVector(str2_alpha, tmp2.c_str());		
				if( compareFeatureVector(str_alpha, str2_alpha) ){
					std::cout << "," << tmp2;
					it2->deleted = true;
				}
				else {
					std::cout << "]";	
					break;
				}					
			}			
			it2++;
		}			
		
		it++;	
	}

	
	std::cout << "]";
	
	return 0;
}