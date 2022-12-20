#include <iostream>     //cout
#include <fstream>      //�ļ�����/���
#include <cstdlib>      //exit()
#include <iomanip>      //�������ӣ���Ҫsetw
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::ios;
using std::setw;

void makeneat(ifstream& messyFile, ofstream& neatFile, int numberAfterDecimalpoint, int fieldWidth);
//ǰ����������messyFile��neatFile�Ѻ�������ͬ���ļ���������ļ�messyFile��ֻ������������
//ִ�н��������messyFile��������ļ��������ѱ�д����Ļ�ϼ�����neatFile��������ļ��С�
//��������һ��дһ������С�����̶�λ���ĸ�ʽ(�ǿ�ѧ������)��д��
//С������λ��ΪnumberAfterDecimalpoint��ÿ��������֮ǰ����һ��"+"��"-"���ű�ǣ�
//ÿ�����ֵĿ�ȶ���fieldWidth(�ú���û�йر��ļ�)��

int main()
{
	ifstream fin;					//����finΪһ���ļ���������
	ofstream fout;					//����foutΪһ���ļ��������
	fin.open("rawdata.txt");		//�ļ�����1>�ⲿ�ļ���������ϵͳʹ�õĸ��ļ���ʵ���ƣ�2>�����������
	if (fin.fail())					//��Ա����fail����������Ƿ�ʧ�ܣ��޲��������ز���ֵ����
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
	fin.close();				  //�ر��ļ�����
	fout.close();
	cout << "End of program.\n";
	return 0;
}
void makeneat(ifstream& messyFile, ofstream& neatFile, int numberAfterDecimalpoint, int fieldWidth)
{													//������һ�������õ��ò���
	neatFile.setf(ios::fixed);
	neatFile.setf(ios::showpoint);
	neatFile.setf(ios::showpos);
	neatFile.precision(numberAfterDecimalpoint);
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.setf(ios::showpos);
	cout.setf(numberAfterDecimalpoint);
	double next;
	while (messyFile >> next)						//�ļ�ĩβ��飬=��while(!messyFile.eof())
	{
		neatFile << setw(fieldWidth) << next << endl;
		cout << setw(fieldWidth) << next << endl;
	}
}
