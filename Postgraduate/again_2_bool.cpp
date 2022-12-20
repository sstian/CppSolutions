#include <iostream>
using namespace std;

int main(void)
{
	bool b = true;
//	bool b = false;
	cout << "b = " << b << endl;
	int n = b;
	cout << "n = " << n << "\n";
	int x = 7;
	b = x;
	cout << "xb = " << b << endl;
	return 0;
}