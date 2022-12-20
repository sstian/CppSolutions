/*	2018.05.17 10:00
	输入一个四位正整数，将其加密后输出。
方法是将该数每一位上的数字加9,然后除以10 取余,作为该位上的新数字,
最后将千位和十位上的数字互换,百位和个位上的数字互换,组成加密后的新四位数?
*/
#include <iostream>

using namespace std;

const int LEN = 4;
void DigitialResolution(const int& number, int result[]);
void DigitialSwap(int& first, int& second); 
int main()
{
	int num, value = 0;
	int result[LEN];
	cout << "Enter a number:";
	cin >> num;
	
	DigitialResolution(num, result);
	for(int i = 0; i < LEN; i++)
	{
		result[i] = (result[i] + 9) % 10; 
	}
	DigitialSwap(result[3], result[1]);
	DigitialSwap(result[2], result[0]);

	for(int j = LEN - 1; j >= 0; j--)
	{
		value = value * 10 + result[j]; 
	}
	cout << "The encrypted number is " << value << endl; 
	return 0;
}

/* 数字拆分 
	number: 输入的数字，result: 输出的结果 */
void DigitialResolution(const int& number, int result[]) 
{
	int value = number;
	int index = 0;
	while(value)
	{
		result[index++] = value % 10;
		value /= 10;
	}
}
/* 数字交换 */
void DigitialSwap(int& first, int& second)
{
	int temp;
	temp = first;
	first = second;
	second = temp;
}
