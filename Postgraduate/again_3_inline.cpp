/*  2017.3.3 19:34
	内联函数 inline
*/
#include <iostream>
using namespace std;

const double pi = 3.1415926;  //常变量

inline double area(double x);  //内联函数声明

int main(void)
{
	double x;
	cout << "x = ";
	cin >> x;
	cout << "The circle's radius = " << x << ", area = " << area(x) <<endl;

	return 0;
}

inline double area(double x)  //内联函数实现
{
	return pi*x*x;
}
