/*
	2018.05.12 09:47
	��x��n�η�
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
	
	cout << x << "��" << n << "�η���" << power(x, n) << endl;
	return 0;
}
/* ����˷� */
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
