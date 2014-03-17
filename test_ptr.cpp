#include<iostream>

void this_dont_change_ptr(int* a, int val){
	a = new int;
	*a = val;	
}

void this_changes_ptr_itself(int** a, int val){
	*a = new int;
	*(*a) = val; 
}

int main(){
	
	int *my_ptr = NULL;
	this_dont_change_ptr(my_ptr, 5);

	if(my_ptr == NULL){
		std::cout << "In fact, ptr is still NULL" << std::endl;
	}
	
	// What I do with allocated memo??
	
	// grants that my_ptr is NULL again
	my_ptr = NULL;	
	this_changes_ptr_itself(&my_ptr, 5);
	if(my_ptr == NULL){
		std::cout << "MUST never get here!" << std::endl;
	}
	else{
		std::cout << "Now we have a new value " << *my_ptr << std::endl;	
	}
	
	delete my_ptr;	
	
	return 0;
}