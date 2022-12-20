/*  2017.3.5 11:39
	复数与直线
*/
//类使用文件
//#include <iostream>  //友元函数 操作符重载 类模板的要求！
#include <iostream.h>
#include "complex.h"
#include "line.h"
//using namespace std;

int main(void)
{
	Complex<int> a, b(3,4);  //定义两个整型的复数
	cout << "Complex:\n";
	cout << "a = (" << a.getReal() << "," << a.getImag() << ")" << endl;
	cout << "b = (" << b.getReal() << "," << b.getImag() << ")" << endl;

	Complex<int> c(b);  //定义整型复数c，并赋以b
	cout << "c = (" << c.getReal() << "," << c.getImag() << ")" << endl;
	cout << "abs of Complex c = " << c.absComplex() <<endl;

	Complex<int> d(4,7);
	Complex<int> bd = d.addComplex(b);  //两个复数相加
	cout << "b(3,4) + d(4,7) = " << "(" << bd.getReal() << "," << bd.getImag() << ")" << endl;  //函数莫忘加括号

	Complex<double> aa;
	aa.setReal(10.1);
	aa.setImag(20.2);
	cout << "aa = (" << aa.getReal() << "," << aa.getImag() << ")" << endl;
////参数类型不匹配，double->int，出错！必须为同一数据类型，对于类模板实例化来说
	//Complex<int> e(aa);  
	//Complex<double> bb = aa.addComplex(d);

	Point mp, np(3,7);  //定义两个点
	cout << "\nPoint:\n";
	cout << "mp = (" << mp.getX() << "," << mp.getY() << ")" << endl;
	cout << "np = (" << np.getX() << "," << np.getY() << ")" << endl;
	Line mn(mp,np);
	cout << "distance = " << mn.distance() << endl;
	cout << "line mn label is " << mn.getLabel() << endl;

	Complex<double> x(2.2, 3.3), y(1.1, 4.4), z;
	cout << "x = (" << x.getReal() << "," << x.getImag() <<")" << endl;
	cout << "y = (" << y.getReal() << "," << y.getImag() <<")" << endl;
	z = x + y;
	cout << "z = x + y = (" << z.getReal() << "," << z.getImag() <<")" << endl;
	z = x - y;
	cout << "z = x - y = (" << z.getReal() << "," << z.getImag() <<")" << endl;
	z = x * y;
	cout << "z = x * y = ";
	z.show();
	z = x / y;
	cout << "z = x / y = ";
	z.show();

	cout << "1 -> " << endl;
	cout << "x = ";
	x.show();
	cout << "z = ";
	z.show();
	cout << "2 -> z = ++x" << endl;
	z = ++x;
	cout << "x = ";
	x.show();
	cout << "z = ";
	z.show();
	cout << "3 -> z = x++" << endl;
	z = x++;
	cout << "x = ";
	x.show();
	cout << "z = ";
	z.show();
	cout << "4 -> z = --x" << endl;
	z = --x;
	cout << "x = ";
	x.show();
	cout << "z = ";
	z.show();
	cout << "5 -> z = x--" << endl;
	z = x--;
	cout << "x = ";
	x.show();
	cout << "z = ";
	z.show();

	cout << "z = x + y + z";
	z = x + y + z;
	cout << "z = ";
	z.show();
	
	cout << "operator << and >> overload..." << endl;
	cout << z;
	cout << "Input the real and imag part of z: " << endl;
	cin >> z;
	cout << z;
	return 0;
}
