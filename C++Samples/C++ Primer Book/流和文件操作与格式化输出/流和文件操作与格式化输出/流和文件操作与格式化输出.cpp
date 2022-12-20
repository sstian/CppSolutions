#include <iostream>     //cout
#include <fstream>      //文件输入/输出
#include <cstdlib>      //exit()
#include <iomanip>      //操作算子，需要setw
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::ios;
using std::setw;

void makeneat(ifstream& messyFile, ofstream& neatFile, int numberAfterDecimalpoint, int fieldWidth);
//前提条件：流messyFile和neatFile已和两个不同的文件相关联，文件messyFile中只包含浮点数。
//执行结果：与流messyFile相关联的文件浮点数已被写到屏幕上及与流neatFile相关联的文件中。
//浮点数按一行写一个数、小数点后固定位数的格式(非科学计数法)书写；
//小数点后的位数为numberAfterDecimalpoint；每个浮点数之前均有一个"+"或"-"符号标记；
//每个数字的宽度都是fieldWidth(该函数没有关闭文件)。

int main()
{
	ifstream fin;					//声明fin为一个文件的输入流
	ofstream fout;					//声明fout为一个文件的输出流
	fin.open("rawdata.txt");		//文件名：1>外部文件名：操作系统使用的该文件真实名称；2>流对象的名称
	if (fin.fail())					//成员函数fail检查流操作是否失败，无参数，返回布尔值、、
	{
		cout << "Input file opening failed.\n";
		exit(1);
	}
	fout.open("neat.txt");
	if (fout.fail())
	{
		cout << "Output file opening failed.\n";
		exit(1);
	}
	makeneat(fin, fout, 5, 12);
	fin.close();				  //关闭文件、、
	fout.close();
	cout << "End of program.\n";
	return 0;
}
void makeneat(ifstream& messyFile, ofstream& neatFile, int numberAfterDecimalpoint, int fieldWidth)
{													//流参数一定是引用调用参数
	neatFile.setf(ios::fixed);
	neatFile.setf(ios::showpoint);
	neatFile.setf(ios::showpos);
	neatFile.precision(numberAfterDecimalpoint);
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.setf(ios::showpos);
	cout.setf(numberAfterDecimalpoint);
	double next;
	while (messyFile >> next)						//文件末尾检查，=》while(!messyFile.eof())
	{
		neatFile << setw(fieldWidth) << next << endl;
		cout << setw(fieldWidth) << next << endl;
	}
}
