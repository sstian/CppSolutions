//数组操作符"[]"只能作为成员函数重载，
//索引参数必须为整型，即:enum,char,short,int,long,unsigned之一。
#include <iostream>
#include <cstdlib>
using namespace std;
class CharPair
{
public:
	CharPair() {/*函数体有意为空*/}
	CharPair(char firstValue, char secondValue)
		:first(firstValue), second(secondValue)
	{/*函数体有意为空*/}
	char& operator [](int index);
private:
	char first;
	char second;
};
int main()
{
	CharPair a;
	a[1] = 'A';
	a[2] = 'B';
	cout << "a[1] and a[2] are:\n";
	cout << a[1] << a[2] << endl;
	cout << "Enter two letters (no space):\n";
	cin >> a[1] >> a[2];
	cout << "You entered:\n";
	cout << a[1] << a[2] << endl;
	return 0;
}
char& CharPair::operator [](int index)
{										 //对象的成员变量等价于数组的索引变量
	if (index == 1)
		return first;
	else if (index == 2)
		return second;
	else
	{
		cout << "Illegal index value.\n";
		exit(1);
	}
}
