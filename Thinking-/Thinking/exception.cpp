#include <iostream>
#include <cstdlib>
#include <stdexcept>
using namespace std;

double fuc(double x, double y)                        //定义函数
{
	if (y == 0)
	{
		throw y;                                    //除数为0，抛出异常
	//	throw invalid_argument("y cannot be zero!");
	}
	return x / y;                                    //否则返回两个数的商
}
void main()
{
	double res;
	try                                            //定义异常
	{
		res = fuc(2, 3);
		cout << "The result of x/y is : " << res << endl;
		res = fuc(4, 0);                                //出现异常
	}
	catch (double)                                    //捕获并处理异常
	//catch (invalid_argument &e)
	{
		 cerr << "error of dividing zero.\n";
		// cerr << e.what() << endl;
		exit(1);                                    //异常退出程序
	}
}