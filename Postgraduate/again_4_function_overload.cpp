/*  2017.3.3 19:55
	函数重载：
	利用重载函数分别计算两个整数、实数、复数的和
*/
#include <iostream>
using namespace std;

struct Complex  //定义复数结构体
{
	double real;	   //实部
	double imaginary;  //虚部
};

int add(int x, int y);
double add(double x, double y);
Complex add(Complex x, Complex y);

int main(void)
{
	int iX, iY;  //两个整数
	double dX, dY;  //两个实数
	Complex xx, yy, zz;  //两个复数，复数之和
	int iType;  //类型选择编号

	cout << "Calculate the summary of two integers, floats and complexs" <<endl;
	cout << "1.Integer  2.Float  3.Complex\n";
	cout << "numeber selected is ";
	cin >> iType;
	switch(iType)
	{
	case 1: 
		cout << "first = ";
		cin >> iX;
		cout << "second = ";
		cin >> iY;
		cout << iX << " + " << iY << " = " << add(iX, iY) <<endl;
		break;
	case 2:
		cin >> dX >> dY;
		cout << dX << " + " << dY << " = " << add(dX, dY) <<endl;
		break;
	case 3:
		cout << "first's real and imaginary part = ";
		cin >> xx.real >> xx.imaginary;
		cout << "second's real and imaginary part = ";
		cin >> yy.real >> yy.imaginary;
		zz = add(xx, yy);
		//换行也没问题，C++好强大！但必须以运算符作为转折点。老铁，没毛病！
		//延续运算符\也是可以的,但是后面不能出现其它字符，包括空格
		cout << "Complex: (" << xx.real << "," << xx.imaginary << ") + (" 
			<< yy.real << "," << yy.imaginary << ") = (" 
			<< zz.real << "," << zz.imaginary << ")" <<endl;
	/*	cout << "Complex: (" << xx.real << "," << xx.imaginary << ") \
			+ (" << yy.real << "," << yy.imaginary << ") \
			= (" << zz.real << "," << zz.imaginary << ")" <<endl;
	*/
		break;
	default: 
		cout << "Select Error!" << endl;
		break;
	}
	return 0;
}

//计算两个整数的和
int add(int x, int y)
{
	return x+y;
}
//计算两个实数的和
double add(double x, double y)
{
	return x+y;
}
//计算两个复数的和
Complex add(Complex x, Complex y)
{
	Complex z;
	z.real = x.real + y.real;
	z.imaginary = x.imaginary + y.imaginary;
	return z;
}