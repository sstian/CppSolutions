/*  2017.3.3 20:52
	����ģ�壺
	��һ�������غ����ĺ��������
*/
#include <iostream>
using namespace std;

template <typename T>
T add(T x, T y)
{
	return x+y;
}

int main(void)
{
	int ix, iy;
	double dx,dy;
	cout << "Input two integers:";
	cin >> ix >> iy;
	cout << ix << " + " << iy << " = " << add(ix,iy) << endl;
	cout << "Input two doubles:";
	cin >> dx >> dy;
	cout << dx << " + " << dy << " = " << add(dx,dy) << endl;

	return 0;
}