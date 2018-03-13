// This is a demonstration for Skiena book page 67
// Compile this source with c++ flag (std=c++11, in case of g++)
#include <iostream>
using namespace std;


class Expansible_Array{
public:
	Expansible_Array();	
	~Expansible_Array();	
	void AddElem(int e);
	void Print();
	int GetRecopy();
private:
	int* a;		
	int next_av;
	int curr_sz;
	int recopy;
};


Expansible_Array::Expansible_Array() : 
	a{new int[1]}, 
	next_av{0}, 
	curr_sz{1}, 
	recopy{0}{
}

Expansible_Array::~Expansible_Array(){
	delete a;
}

void Expansible_Array::AddElem(int e){
	if(next_av == curr_sz){
		int* b = new int[curr_sz*2];
		recopy += curr_sz;
		for(int i=0; i<curr_sz; i++)
			b[i] = a[i];
		int* c = a;
		a = b;
		delete c;	
		curr_sz*=2;	
	}
	a[next_av++] = e;
}

void Expansible_Array::Print(){
	cout << "Print : ";
	for(int i=0; i<next_av; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}

int Expansible_Array::GetRecopy(){
	return recopy;
}

int test_Expansible_Array(int quantity){
	Expansible_Array* a = new Expansible_Array();
	for(int i=0; i<quantity; i++){
		a->AddElem(i);
	}
	//a->Print();
	cout << "Inserted " << quantity << " items."  
			" For this we have an upper of bound 2n == " <<  2*quantity << 
			" and get " << a->GetRecopy() << " recopies " 
			<< endl;

	delete a;
}

int main(){
	for(int i=1; i<1<<16; i+=1000){
		test_Expansible_Array(i);	
	}
	return 0;
}
