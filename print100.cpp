
/**
	@summary print from 0 to 100 using C++11 templates
	@author Wesley Mesquita
*/
#include <iostream>

template<int N>
class print100 : print100<N - 1>{
public:
	print100<N>(){
		std::cout << N << std::endl;
	}
};

template<>
class print100<0>{
public:
	print100<0>(){
		std::cout << 0 << std::endl;
	}
};

int main(){
	print100<100>();
	return 0;
}

