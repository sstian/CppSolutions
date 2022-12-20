#include <iostream>
using namespace std;
int main()
{
	int a = 10;
	if (a++ > 9)
	{
		cout << a << endl;
		a++;
		cout << a << endl;
	}
	cout << a << endl;
	return 0;
}