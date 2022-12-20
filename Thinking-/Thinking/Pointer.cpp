#include <iostream>
using namespace std;
int main()
{
/*	int a = 13;
	double b = 3.14;
	int *p1=&a;
	double *p2 = &b;
	cout << "p1: " << p1 << endl;
	cout << "p2: " << p2 << endl;
	p1++;
	p2++;
	cout << "p1: " << p1 << endl;
	cout << "p2: " << p2 << endl;*/

/*	int *p = new int;
	cout << "p: " << p << endl;
	int *p1 = new int;
	cout << "p1: " << p1 << endl;
	*p = p - p1;
	cout << "Á½Ö¸ÕëÏà¼õ£º" << *p << endl;*/

	int a = 3;
	const int *const p = &a;
	cout << *p << endl;
	a = 29;
	cout << *p << endl;
	return 0;
}