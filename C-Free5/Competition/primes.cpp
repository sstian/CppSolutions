/*
	2018.05.12 10:23 
	合数分解1  
要求：从控制台读入一个合数（合数的大小不会超过int数据类型表示的范围），求这个合数可以分解成的只出现一次的素数。
例如合数1260分解成素数乘积为：2*2*3*3*5*7,2和3出现两次，5和7出现一次，所以求得的结果为5和7。 
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
	vector<int> factors;	//质因数集合 
	vector<int> primers;	//因子类型集合 
	vector<int> numbers;	//各因子个数集合 
//	factors.clear();	//清空可不要 
//	primers.clear();
//	numbers.clear();
	cout << "Input a combined number: ";
	cin >> combine;
	// 分解质因数 
	DecomposeFactor(combine, factors);
//	for(int i = 0; i < factors.size(); i++)
//		cout << factors.at(i) << " ";
//	cout << endl;
	// 统计因子类型与个数 
	int index, value;
	for(int j = 0; j < factors.size(); j++)
	{
		value = factors.at(j);
		index = FindElement(primers,value);	//primers vector
		if(index == -1)
		{	//没有要追加 
			primers.push_back(value);
			numbers.push_back(1);
		}
		else
		{	//有的就查找使计数器加1 
			//numbers[index] = numbers.at(index) + 1;
			*(numbers.begin() + index) = numbers.at(index) + 1;	//迭代器修改元素的值 
		}
		
	}
//	for(int m = 0; m < numbers.size(); m++)
//	{
//		cout << numbers.at(m) << "-";
//	}
//	cout << endl;
	// 输出结果：使用向量迭代器 
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

/* 判断素数 */
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


/* 分解质因数 
	combine: 合数，factors: 质因数向量集合 */
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
/* 查找元素：向量集合
	查到，返回第一个下标；没有，返回-1 */
int FindElement(vector<int>& collections, int value)
{
	for(int i = 0; i < collections.size(); i++)
	{
		if(collections.at(i) == value)
			return i;
	}
	return -1;
} 
