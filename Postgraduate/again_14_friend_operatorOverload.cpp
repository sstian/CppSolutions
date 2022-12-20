/*  2017.3.17 12:15
	友元函数 操作符重载
总结：友元函数体内又定义的本类对象同样可以访问类的私有成员
*/

//#include <iostream>
//using namespace std;
#include <iostream.h>  //在vc++6.0中友元函数重载操作符要用".h"头文件

class Complex
{
public:
	Complex(double r = 0.0, double i = 0.0):real(r),imag(i) { cout << "Constructor..." << endl; }
	virtual ~Complex() { cout << "Deconstuctor." << endl; }
	double getReal() const { return real; }
	double getImag() const { return imag; }
	void show() const { cout << "(" << real << " , " << imag << ")" << endl; }
/*	Complex operator +(const Complex& otherComplex)
	{
		return Complex(real+otherComplex.real, imag+otherComplex.imag);
	}
*/  //友元操作符重载函数
	friend Complex operator +(const Complex& oneComplex, const Complex& otherComplex);
private:
	double real;
	double imag;
};

int main(void)
{
	Complex a(1.1,2.2), b(2.2,3.3), c;
	cout << "a: ";
	a.show();
	cout << "b: ";
	b.show();
	cout << "c: ";
	c.show ();

	cout << "c = a + b: ->" << endl;
	c = a + b;
	cout << "a: ";
	a.show();
	cout << "b: ";
	b.show();
	cout << "c: ";
	c.show ();

	return 0;
}

Complex operator +(const Complex& oneComplex, const Complex& otherComplex)
{
	Complex sumComplex;  
	sumComplex.real = oneComplex.real + otherComplex.real;
	sumComplex.imag = oneComplex.imag + otherComplex.imag;
	return sumComplex;
//	return Complex(sumReal, sumImag);
//	return Complex(oneComplex.real+otherComplex.real, oneComplex.imag+otherComplex.imag);
}

/*在VC++6.0中的运行结果：
=============================================================================================
Constructor...
Constructor...
Constructor...
a: (1.1 , 2.2)
b: (2.2 , 3.3)
c: (0 , 0)
c = a + b: ->
Constructor...
Deconstuctor.
a: (1.1 , 2.2)
b: (2.2 , 3.3)
c: (3.3 , 5.5)
Deconstuctor.
Deconstuctor.
Deconstuctor.
Press any key to continue
=============================================================================================*/