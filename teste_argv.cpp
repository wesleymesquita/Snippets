#include<iostream>
#include<sstream>
#include<algorithm>
#include<locale>

int main(int argc, char** argv){

	// it should be a double, but makes easier 
	// to show ideas above
	int i;
	
	std::stringstream sstr(argv[1]);
	
	bool is_all_digit = true;
	// i tried to use a std::all_of, but get stuck...
	// this for do the same job
	// keep in mind thar for double, exponencial, etc
	//   there should be more valid chars
	// If you use only sstr >> i, if argv is, for instance 
	// 	'12345asdfg' it will consider 12345.
	for(char& c: sstr.str()){
		is_all_digit &= std::isdigit(c);  
	}
		
	if( is_all_digit && !(sstr >> i).fail() )
		std::cout << "i == " << i << std::endl;
	else
		std::cerr << "Could not convert " << argv[1] << " to 'int'" << std::endl;
	return 0;
}