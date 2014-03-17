//main cpp file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

splitLine(const char* str, vector<string> results){
	// splits str and stores each value in results vector
}

int main()
{
    ifstream fin;
    fin.open("customers.txt");
	char buffer[128];
	if(fin.good()){
		while(!fin.eof()){
			fin.getline(buffer, 256);
			cout << buffer << endl;
			
			vector<string> results;			
			splitLine(buffer, results);
			// now results MUST contain 4 strings, for each 
			// column in a line
		}
	
	}
    return 0;
}

