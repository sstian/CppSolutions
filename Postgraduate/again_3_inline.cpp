/*  2017.3.3 19:34
	�������� inline
*/
#include <iostream>
using namespace std;

const double pi = 3.1415926;  //������

inline double area(double x);  //������������

int main(void)
{
	double x;
	cout << "x = ";
	cin >> x;
	cout << "The circle's radius = " << x << ", area = " << area(x) <<endl;

	return 0;
}

inline double area(double x)  //��������ʵ��
{
	return pi*x*x;
}
