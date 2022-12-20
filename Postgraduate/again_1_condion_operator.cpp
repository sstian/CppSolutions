//#include <iostream.h>
#include <iostream>
using namespace std;

int main(void)
{
	int sum(100);  //这样初始化变量居然也对！
	cout << sum << endl;
	cout << (2>2.5 ? 2 : 2.5) <<endl;
	return 0;
}

/*在VC++6.0中的运行结果：
=================================================================
100
2.5
Press any key to continue
=================================================================
*/
