
#include <iostream>

using namespace std;

int main() 
{
	cout << "hhh" << endl;

	char a[100] = { 0 };
	for (int i = 0; i < 100; i++)
	{
		a[i] = i;
	}


	int* p = (int*)a;
	double* p1 = (double*)((int)p + 2);
	double* p2 = (double*)(p + 2);

	cout << "a = " << a << ", " << &a << endl;
	cout << "p = " << p << ", " << *p << endl;
	cout << "p1 = " << p1 << ", " << *p1 << endl;
	cout << "p2 = " << p2 << ", " << *p2 << endl;

	
}
