/*	2018.05.17 09:55
	����һ����λ����������Ⲣ��������ĸ�λ����ʮλ���Ͱ�λ����
*/
#include <iostream>

using namespace std;

int main()
{
	int num;
	int one, ten, hundred;
	cin >> num;
	one = num % 10;
	ten = num / 10 % 10;
	hundred = num / 100;
	cout << one << " " << ten << " " << hundred << endl;
	return 0;
}
