#include <iostream>
using namespace std;

class Test
{
public:
	void fun1()
	{
		cout << "����һ������" << endl;
		fun2();
	}

	void fun2()
	{
		cout << "�������ǲ�����" << endl;
	}

};
//��˳���޹�
int main()
{
	Test boy;
	boy.fun1();
	return 0;
}
