//���������"[]"ֻ����Ϊ��Ա�������أ�
//������������Ϊ���ͣ���:enum,char,short,int,long,unsigned֮һ��
#include <iostream>
#include <cstdlib>
using namespace std;
class CharPair
{
public:
	CharPair() {/*����������Ϊ��*/}
	CharPair(char firstValue, char secondValue)
		:first(firstValue), second(secondValue)
	{/*����������Ϊ��*/}
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
{										 //����ĳ�Ա�����ȼ����������������
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
