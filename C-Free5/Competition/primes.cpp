/*
	2018.05.12 10:23 
	�����ֽ�1  
Ҫ�󣺴ӿ���̨����һ�������������Ĵ�С���ᳬ��int�������ͱ�ʾ�ķ�Χ����������������Էֽ�ɵ�ֻ����һ�ε�������
�������1260�ֽ�������˻�Ϊ��2*2*3*3*5*7,2��3�������Σ�5��7����һ�Σ�������õĽ��Ϊ5��7�� 
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool IsPrimer(int number);
void DecomposeFactor(int combine, vector<int>& factors);
int FindElement(vector<int>& collections, int value);
int main()
{
	int combine;
	vector<int> factors;	//���������� 
	vector<int> primers;	//�������ͼ��� 
	vector<int> numbers;	//�����Ӹ������� 
//	factors.clear();	//��տɲ�Ҫ 
//	primers.clear();
//	numbers.clear();
	cout << "Input a combined number: ";
	cin >> combine;
	// �ֽ������� 
	DecomposeFactor(combine, factors);
//	for(int i = 0; i < factors.size(); i++)
//		cout << factors.at(i) << " ";
//	cout << endl;
	// ͳ��������������� 
	int index, value;
	for(int j = 0; j < factors.size(); j++)
	{
		value = factors.at(j);
		index = FindElement(primers,value);	//primers vector
		if(index == -1)
		{	//û��Ҫ׷�� 
			primers.push_back(value);
			numbers.push_back(1);
		}
		else
		{	//�еľͲ���ʹ��������1 
			//numbers[index] = numbers.at(index) + 1;
			*(numbers.begin() + index) = numbers.at(index) + 1;	//�������޸�Ԫ�ص�ֵ 
		}
		
	}
//	for(int m = 0; m < numbers.size(); m++)
//	{
//		cout << numbers.at(m) << "-";
//	}
//	cout << endl;
	// ��������ʹ������������ 
	vector<int>::iterator itprimer = primers.begin();
	vector<int>::iterator itnumber = numbers.begin();
	for(; itnumber != numbers.end(); itnumber++, itprimer++)
	{
		if(*itnumber == 1)
			cout << *itprimer << " ";
	}
	cout << endl;
	return 0;
}

/* �ж����� */
bool IsPrimer(int number)
{
	int k = (int)sqrt(number);
	for(int i = 2; i <= k; i++)
	{
		if(number % i == 0)
			return false;
	}
	return true;
} 


/* �ֽ������� 
	combine: ������factors: �������������� */
void DecomposeFactor(int combine, vector<int>& factors)
{
	for(int i = 2; i <= combine; i++)
	{
		if(IsPrimer(i))
		{
			while(combine >= i)
			{
				if(combine % i == 0)
				{
					factors.push_back(i);
					combine /= i;
				}
				else
					break;
			}
		}
	}
}
/* ����Ԫ�أ���������
	�鵽�����ص�һ���±ꣻû�У�����-1 */
int FindElement(vector<int>& collections, int value)
{
	for(int i = 0; i < collections.size(); i++)
	{
		if(collections.at(i) == value)
			return i;
	}
	return -1;
} 
