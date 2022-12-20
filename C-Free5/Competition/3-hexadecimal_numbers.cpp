/*
	2018.05.12 18:32
	Hexadecimal's Numbers
	二进制 -> 十进制？ 
*/
#include <iostream>

using namespace std;

int rtod(int radix, int base);
int main()
{
	int number;
	cout << "Input a number (binary):" << endl;
	cin >> number;
	cout << rtod(number, 2) << endl;
	return 0;
}

/* R进制 转换为 十进制 */
int rtod(int radix, int base)
{
	int decimal = 0;
	int power = 1;
	int remainder;
	while(radix)
	{
		remainder = radix % 10;
		if(remainder >= base)
		{
			cout << "The number is valid!" << endl;
			return -1;
		}
		decimal += remainder * power;
		power *= base;
		radix /= 10;
	}
	return decimal;
}
