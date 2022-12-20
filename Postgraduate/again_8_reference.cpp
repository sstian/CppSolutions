/*  2017.3.8 15:53
	引用：
	无论更改原始变量或引用变量都会引起原始内存数据的更改
*/
#include <iostream>
using namespace std;

int main(void)
{
	int a = 3;
	int& ra = a;
	cout << "a = " << a << endl;
	cout << "ra = " << ra << endl;
	a = 7;
	cout << "a = 7;;;;" << endl;
	cout << "a = " << a << endl;
	cout << "ra = " << ra << endl;
	ra = 9;
	cout << "ra = 9;;;;" << endl;
	cout << "a = " << a << endl;
	cout << "ra = " << ra << endl;

	return 0;
}

/*在VC++6.0中的运行结果：
=========================================================
a = 3
ra = 3
a = 7;;;;
a = 7
ra = 7
ra = 9;;;;
a = 9
ra = 9
Press any key to continue
=========================================================*/