/*
	2018.05.12 09:39
	����Ⲣ��������ĸ�λ����ʮλ���Ͱ�λ����	
*/
#include <iostream>
using namespace std;

int main()
{
	int num;
	int one, ten, hundred;
	cout << "Input a three bit positive integer: " << endl;
	cin >> num;
	one = num % 10;
	ten = num / 10 % 10;
	hundred = num / 100;
	cout << one << " " << ten << " " << hundred << endl;
	return 0;
}
