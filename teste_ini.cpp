#include <iostream>
#include<algorithm>
using namespace std;

typedef struct{
 int i;
 char a;
 void erase(){i=0; a=0;}
}mystruct;

int main()
{
    mystruct structure[2];
    //structure{};
	structure[0].i = 69;
    cout << structure[0].i << endl; // Should print 69
    //structure{};
	std::for_each(structure,  structure+2, [&](mystruct& s){s.erase();} );
    cout << structure[0].i << endl; //Should print 0

   return 0;
}