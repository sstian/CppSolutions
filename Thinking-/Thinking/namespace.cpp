#include <iostream>
namespace a
{
	int x = 1;
}
namespace b
{
	int x = 2;
}
int main()
{
	using namespace a;
	//int x = 3;
	std::cout << x << "  " << x << "  " << b::x << std::endl;
	return 0;
}