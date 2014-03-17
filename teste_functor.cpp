#include<vector>
#include<functional>

using namespace std;

int main()
{
typedef vector<int> V;
V v;
auto b1 = bind(v::at, &v);

auto b2 = bind( static_cast<std::function<int()>(&V::at), &v);
}			
			