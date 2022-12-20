/*
	2018.05.12 09:47
	求x的n次方
*/
#include <iostream>

using namespace std;

int power(int x, int n); 
int main()
{
	int x, n;
//	int result;
	cout << "Enter x: ";
	cin >> x;
	cout << "Enter n: ";
	cin >> n;
//	result = power(x, n);
	
	cout << x << "的" << n << "次方是" << power(x, n) << endl;
	return 0;
}
/* 计算乘方 */
int power(int x, int n)
{
	int result;
	if(n < 0)
		return 0;
	else if(1 == n)
		return x;
	else
		result = x * power(x, n-1);
	return result;
}
