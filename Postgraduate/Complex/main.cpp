/*  2017.3.5 11:39
	������ֱ��
*/
//��ʹ���ļ�
//#include <iostream>  //��Ԫ���� ���������� ��ģ���Ҫ��
#include <iostream.h>
#include "complex.h"
#include "line.h"
//using namespace std;

int main(void)
{
	Complex<int> a, b(3,4);  //�����������͵ĸ���
	cout << "Complex:\n";
	cout << "a = (" << a.getReal() << "," << a.getImag() << ")" << endl;
	cout << "b = (" << b.getReal() << "," << b.getImag() << ")" << endl;

	Complex<int> c(b);  //�������͸���c��������b
	cout << "c = (" << c.getReal() << "," << c.getImag() << ")" << endl;
	cout << "abs of Complex c = " << c.absComplex() <<endl;

	Complex<int> d(4,7);
	Complex<int> bd = d.addComplex(b);  //�����������
	cout << "b(3,4) + d(4,7) = " << "(" << bd.getReal() << "," << bd.getImag() << ")" << endl;  //����Ī��������

	Complex<double> aa;
	aa.setReal(10.1);
	aa.setImag(20.2);
	cout << "aa = (" << aa.getReal() << "," << aa.getImag() << ")" << endl;
////�������Ͳ�ƥ�䣬double->int����������Ϊͬһ�������ͣ�������ģ��ʵ������˵
	//Complex<int> e(aa);  
	//Complex<double> bb = aa.addComplex(d);

	Point mp, np(3,7);  //����������
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
