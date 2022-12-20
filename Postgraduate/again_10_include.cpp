/*  2017.3.11 16:00
	include头文件
只能嵌入*.h头文件，*.cpp会出错
*/
#include <iostream>
//#include "again_10_function.cpp"  //error C2872: 'cout' : ambiguous symbol
using namespace std;

int main(void)
{
	cout << "main(): " << endl;
	//fun();
	return 0;
}