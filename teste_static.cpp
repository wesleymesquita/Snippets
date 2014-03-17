#include<iostream>

class Singleton
{
    public:

        static Singleton* get()
        {
            return &instance;
        }
	
	private:
		static Singleton instance;
							
	
};

Singleton Singleton::instance;

int main(){
	Singleton* s = Singleton::get();
	if(s){
		std::cout << "Here" << std::endl;
	}
}