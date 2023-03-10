/*
	2019.07.20 16:17 - 16:24
	排列、组合、阶乘的简单实现
	Arrangement Combination Factorial
*/
#include <iostream>
using namespace std;

// 排列 A(n, m)
int Anm(int n, int m)
{
	int result = 1;
	int end = n - m + 1;
	while (n >= end)
	{
		result *= n;
		n--;
	}
	return result;
}

// 组合 C(n, m) = A(n, m) / m!
int Cnm(int n, int m)
{
	return Anm(n, m) / Anm(m, m);
}

// 阶乘：通过全排列实现 n!
int fac(int n)
{
	return Anm(n, n);
}

int main()
{
	cout << "*** Arrangement Combination Factorial ***" << endl;
	cout << "A(4,3) = " << Anm(4, 3) << endl;
	cout << "C(4,3) = " << Cnm(4, 3) << endl;
	cout << "A(4,4) = " << Anm(4, 4) << endl;
	cout << "4!     = " << fac(4) << endl;

	system("pause");
	return 0;
}

/***
*** Arrangement Combination Factorial ***
A(4,3) = 24
C(4,3) = 4
A(4,4) = 24
4!     = 24
请按任意键继续. . .
***/