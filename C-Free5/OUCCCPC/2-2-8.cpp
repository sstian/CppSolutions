/*	2018.05.17 10:00
	����һ����λ��������������ܺ������
�����ǽ�����ÿһλ�ϵ����ּ�9,Ȼ�����10 ȡ��,��Ϊ��λ�ϵ�������,
���ǧλ��ʮλ�ϵ����ֻ���,��λ�͸�λ�ϵ����ֻ���,��ɼ��ܺ������λ��?
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

/* ���ֲ�� 
	number: ��������֣�result: ����Ľ�� */
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
/* ���ֽ��� */
void DigitialSwap(int& first, int& second)
{
	int temp;
	temp = first;
	first = second;
	second = temp;
}
