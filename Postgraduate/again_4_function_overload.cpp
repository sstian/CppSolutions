/*  2017.3.3 19:55
	�������أ�
	�������غ����ֱ��������������ʵ���������ĺ�
*/
#include <iostream>
using namespace std;

struct Complex  //���帴���ṹ��
{
	double real;	   //ʵ��
	double imaginary;  //�鲿
};

int add(int x, int y);
double add(double x, double y);
Complex add(Complex x, Complex y);

int main(void)
{
	int iX, iY;  //��������
	double dX, dY;  //����ʵ��
	Complex xx, yy, zz;  //��������������֮��
	int iType;  //����ѡ����

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
		//����Ҳû���⣬C++��ǿ�󣡵��������������Ϊת�۵㡣������ûë����
		//���������\Ҳ�ǿ��Ե�,���Ǻ��治�ܳ��������ַ��������ո�
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

//�������������ĺ�
int add(int x, int y)
{
	return x+y;
}
//��������ʵ���ĺ�
double add(double x, double y)
{
	return x+y;
}
//�������������ĺ�
Complex add(Complex x, Complex y)
{
	Complex z;
	z.real = x.real + y.real;
	z.imaginary = x.imaginary + y.imaginary;
	return z;
}