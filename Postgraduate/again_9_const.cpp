/*  2017.3.10 18:41
	������
*/
#include <iostream>
using namespace std;

int main(void)
{
	int x = 100;  //����
	int y = 999;
	const int a = 1;
	const int b = 2;
	int const c = 3;
//	int const a = 1;  //����
	cout << "a = " << a << endl;
	cout << "a = " << a << endl;

	const int* pa = &a;  //ָ������ָ��
	//a = 11;  //error C2166: l-value specifies const object
	//*pa = 111;  //error C2166: l-value specifies const object
	cout << "const int* pa = " << *pa << endl;
	const int* px = &x;
	x = 200;
	//*px = 300;  //error C2166: l-value specifies const object
	cout << "const int* px = " << *px << endl;
	
	//int* const paa = &c;
	//cout << "int* const paa = " << *paa << endl;
	//error C2440: 'initializing' : cannot convert from 'const int *' to 'int *const 'Conversion loses qualifiers
	int* const pxx = &x;  //��ָ��
	x = 400;
	*pxx = 500;
	//pxx = &y;  //error C2166: l-value specifies const object
	cout << "int* cosnt pxx = " << *pxx << endl;
	const int* const ppy = &y;
	cout << "const int* const ppy = " << *ppy << endl;
	cout << "ppy: " << ppy << endl;

	int& const rx = y;
	rx = y;
	rx = b;
	cout << "int &rx = " << rx << endl;
	const int& ry = y;
	//ry = 88;  //error C2166: l-value specifies const object
	y = 777;
	cout << "const &ry = " << ry << endl;
	const int& const rrr = a;
	cout << "const int& const rrr = " << rrr << endl;
	const int arr[3] = {0,0,0};
	int const brr[3] = {0,0,0};
	const int zzz = 0;

	return 0;
}