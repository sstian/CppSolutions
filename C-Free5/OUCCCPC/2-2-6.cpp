/*	2018.05.17 09��10
	��������������ĺ͡�������������� 
*/
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int num1, num2;
	cout << "Enter num1:";
	cin >> num1;
	cout << "Enter num2:";
	cin >> num2;
	
	cout << num1 << "+" << num2 << "=" << (num1 + num2) << endl;
	cout << num1 << "-" << num2 << "=" << (num1 - num2) << endl;
	cout << num1 << "*" << num2 << "=" << (num1 * num2) << endl;
	cout << num1 << "/" << num2 << "=" << fixed << setprecision(2) <<(1.0 * num1 / num2) << endl;
	cout << num1 << "%" << num2 << "=" << (num1 % num2) << endl;
	return 0;
}
