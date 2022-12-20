/*  2017.3.22 19:29
	�ļ�Book�����嵥
*/
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
//using namespace std;

#define N 2

struct Book  //��ṹ��
{
	char name[20];  //����
	char no[10];  //���
	int number;  //�����
	double price;  //�۸�
};

int main(void)
{
	fstream flib("5data", ios::in|ios::out|ios::binary);  //�����ļ���������
	if(flib.fail())  //��if(!flib)  //��ʧ��
	{
		cout << "Can't open the file!" << endl;
		exit(1);
	}
	Book temp;
	cout << "Input " << N << " books' name, no, number, price:" << endl;
	for(int i = 0; i < N; i++)  //д��N�������Ϣ
	{
		cout << "Book " << i+1 << " : ";
		cin >> temp.name >> temp.no >> temp.number >> temp.price;
		flib.write((char*)&temp, sizeof(Book));
	}

	for(i = N; i > N/2; i--)  //�ƶ���һ�룬���м����һ����
	{
		flib.seekg((N-1)*sizeof(Book), ios::beg);  //��λ
		flib.read((char*)&temp, sizeof(Book));  //��ȡ
		flib.write((char*)&temp, sizeof(Book));  //д��
	}
	cout << "Insert a book infomation:" << endl;
	cin >> temp.name >> temp.no >> temp.number >> temp.price;
	flib.seekg(N/2*sizeof(Book), ios::beg);
	flib.write((char*)&temp, sizeof(Book));  //����

	int total = 0;  //�ܵĿ����
	double amount = 0.0;  //�ܼ۸�
	flib.seekg(0,ios::beg);  //��λ����ʼ��
	cout << "information..." << endl;
	cout << "name\t no\t number\t price" << endl;
	for(i = 0; i < N+1; i++)
	{
		flib.read((char*)&temp, sizeof(Book));
		cout << temp.name << "\t" << temp.no << "\t"
			 << temp.number << "\t" << temp.price << endl;
		total += temp.number;
		amount += temp.number * temp.price;
	}
	cout << "Total: " << total << ", Amount: " << amount << endl;
	flib.close();
	system("pause");
	return 0;
}