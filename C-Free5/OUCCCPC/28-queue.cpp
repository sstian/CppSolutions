/*	
	2018.05.17 16:03
	
*/
#include <iostream>
#define N 105
using namespace std;

int main()
{
	int ages[N];	//年龄 
	int diss[N]; //不满程度 
	int num;	//数量
	cin >> num;
	for(int i = 0; i < num; i++)
	{
		cin >> ages[i];
		diss[i] = -1;
	} 
	
	for(int j = 0; j < num; j++)
	{
		for(int k = j + 1; k < num; k++)
		{
			if(ages[k] < ages[j])
				diss[j]++;
		}
	}
	
	for(int m = 0; m < num; m++)
		cout << diss[m] << " ";
	cout << endl;
	return 0;
}
