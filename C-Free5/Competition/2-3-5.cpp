/*
	2018.05.12 10;03
	��1-1/4+1/7-1/10+1/13-1/16+����ǰn ��֮��  
*/
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int n;
	double sum = 0.0;
	int signal = 1;		//�������� 
	double item;		//ÿһ��ֵ 
	cout << "Enter n: ";
	cin >> n;
	
	for(int i = 1; i <= n; i++)
	{
		item = signal * 1.0 / (3 * i - 2);
		sum += item;
		signal *= -1;
	}
	
	cout << "sum=" << setprecision(3) <<sum << endl;	//����3λС�� 
	return 0;
}
