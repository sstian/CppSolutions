#include<iostream>
using namespace std;

class Prime
{
public:
	int GetNumber(){ return number; }
	void SetNumber(int num){ number = num; }
	void PrimeOutput()
	{
		int sum = 0;
		int i, j;
		for (i = 1; i <= number; i++)
		{
			for (j = 2; j < i; j++)
			{
				if (i%j == 0)
					break;
			}
			if (j >= i)
			{
				cout << i << "\t";
				sum++;
				if (sum % 10 == 0)
					cout << endl;
			}
		}
	}
private:
	int number;  //范围：求取多少以内的素数
};
int main()
{
	Prime range;
	int n;
	cout << "请输入一个整数，用于求取多少以内的素数：\n";
	cin >> n;
	range.SetNumber(n);
	range.PrimeOutput();
	cout << endl;
	return 0;
}