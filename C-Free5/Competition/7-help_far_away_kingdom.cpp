/*
	2018.05.12 19:41
	Help Far Away Kingdom
	小数四舍五入转换成整数？ 
*/
#include <iostream>
//#include <cstdlib>
#define N 100
using namespace std;

int main()
{
	char num[N];
	int index;
	cout << "Input a char number:" << endl;
	cin >> num;
	for(index = 0; ; index++)
	{
		if(num[index] == '.')
			break;
	}
	//cout << index << endl; 
	if(index <= 0)
	{
		cout << "Input error!" << endl;
		//exit(1);
	} 
	else if(num[index-1] == '9')
		cout << "GOTO Vasilisa." << endl;
	else 
	{
		if(num[index+1] >= '5')
		{
			num[index-1] = num[index-1] - '0' + 1 + '0';
		}
		for(int j = 0; j < index; j++)
			cout << num[j];
	}
	cout << endl;
	return 0;
}
