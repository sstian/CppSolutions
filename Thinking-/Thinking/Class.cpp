#include <iostream>
using namespace std;

class Test
{
public:
	void fun1()
	{
		cout << "你是一个好人" << endl;
		fun2();
	}

	void fun2()
	{
		cout << "可是我们不合适" << endl;
	}

};
//与顺序无关
int main()
{
	Test boy;
	boy.fun1();
	return 0;
}
