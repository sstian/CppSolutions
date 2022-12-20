/*	2018.05.17 09:55
	输入一个三位正整数，求解并输出该数的个位数、十位数和百位数。
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
