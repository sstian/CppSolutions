#include <iostream>
#include <cstdlib>
#include <stdexcept>
using namespace std;

double fuc(double x, double y)                        //���庯��
{
	if (y == 0)
	{
		throw y;                                    //����Ϊ0���׳��쳣
	//	throw invalid_argument("y cannot be zero!");
	}
	return x / y;                                    //���򷵻�����������
}
void main()
{
	double res;
	try                                            //�����쳣
	{
		res = fuc(2, 3);
		cout << "The result of x/y is : " << res << endl;
		res = fuc(4, 0);                                //�����쳣
	}
	catch (double)                                    //���񲢴����쳣
	//catch (invalid_argument &e)
	{
		 cerr << "error of dividing zero.\n";
		// cerr << e.what() << endl;
		exit(1);                                    //�쳣�˳�����
	}
}