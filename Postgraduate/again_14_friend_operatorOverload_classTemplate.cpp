/*  2017.3.17 12:46
	友元函数 操作符重载 类模板
*/
//#include <iostream>
//using namespace std;
#include <iostream.h>

template <class T>
class Complex;

template <class T>
Complex<T> operator +(const Complex<T>& oneComplex, const Complex<T>& otherComplex)
{
	Complex<T> sumComplex;
	sumComplex.real = oneComplex.real + otherComplex.imag;
	sumComplex.imag = oneComplex.imag + otherComplex.imag;
	return sumComplex;
}

template <class T>
class Complex
{
public:
	Complex(T r = 0.0, T i = 0.0):real(r),imag(i) { cout << "Constructor..." << endl; }
	virtual ~Complex() { cout << "Deconstructor." << endl; }
	T getReal() const { return real; }
	T getImag() const { return imag; }
	void show() const { cout << "(" << real << " , " << imag << ")" << endl; }
	//类成员函数重载操作符
//	Complex<T> operator +(const Complex<T>& otherComplex);
	//友元函数重载操作符
	friend Complex<T> operator +(const Complex<T>& oneComplex, const Complex<T>& otherComplex);
/*	{
		Complex sumComplex;
		sumComplex.real = oneComplex.real + otherComplex.imag;
		sumComplex.imag = oneComplex.imag + otherComplex.imag;
		return sumComplex;
		//return Complex(oneComplex.real+otherComplex.real, oneComplex.imag+otherComplex.imag);
	}
*/
private:
	T real;
	T imag;
};

int main(void)
{
	Complex<double> a(1.1,2.2), b(2.2,3.3), c;
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
/*
template <class T>
Complex<T> Complex<T>::operator +(const Complex<T>& otherComplex)
{
	return Complex(real+otherComplex.real, imag+otherComplex.imag);
}
*/

/*在VC++6.0中的运行结果：
============================================================================
Constructor...
Constructor...
Constructor...
a: (1.1 , 2.2)
b: (2.2 , 3.3)
c: (0 , 0)
c = a + b: ->
Constructor...
Deconstructor.
Deconstructor.
a: (1.1 , 2.2)
b: (2.2 , 3.3)
c: (4.4 , 5.5)
Deconstructor.
Deconstructor.
Deconstructor.
Press any key to continue
============================================================================*/