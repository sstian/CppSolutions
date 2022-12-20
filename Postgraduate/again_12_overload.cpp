/*  2017.3.14 16:45
	重载
*/
#include <iostream>
using namespace std;

int max(int a, int b){return a > b ? a : b;}
float max(float a, float b){return a > b ? a : b;}
double max(int a, float b){return a > b ? a : b;}

int main(void)
{
	int a = 12, b = 17;
	cout << "int max = " << max(a, b) << endl;
	float aa = 12.2, bb = 17.7;
	cout << "float max = " << max(aa, bb) << endl;
	int aaa = 12;
	float bbb = 17.9;
	cout << "double max = " << max(aaa, bbb) << endl;
	//error C2666: 'max' : 2 overloads have similar conversions

	return 0;
}

/*在VC++6.0中的运行结果：
==========================================================================
int max = 17
float max = 17.7
double max = 17.9
Press any key to continue
==========================================================================*/