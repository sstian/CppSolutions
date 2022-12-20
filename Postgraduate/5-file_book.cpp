/*  2017.3.22 19:29
	文件Book存书清单
*/
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
//using namespace std;

#define N 2

struct Book  //书结构体
{
	char name[20];  //书名
	char no[10];  //编号
	int number;  //库存量
	double price;  //价格
};

int main(void)
{
	fstream flib("5data", ios::in|ios::out|ios::binary);  //建立文件关联对象
	if(flib.fail())  //或if(!flib)  //打开失败
	{
		cout << "Can't open the file!" << endl;
		exit(1);
	}
	Book temp;
	cout << "Input " << N << " books' name, no, number, price:" << endl;
	for(int i = 0; i < N; i++)  //写入N本书的信息
	{
		cout << "Book " << i+1 << " : ";
		cin >> temp.name >> temp.no >> temp.number >> temp.price;
		flib.write((char*)&temp, sizeof(Book));
	}

	for(i = N; i > N/2; i--)  //移动后一半，在中间插入一本书
	{
		flib.seekg((N-1)*sizeof(Book), ios::beg);  //定位
		flib.read((char*)&temp, sizeof(Book));  //读取
		flib.write((char*)&temp, sizeof(Book));  //写入
	}
	cout << "Insert a book infomation:" << endl;
	cin >> temp.name >> temp.no >> temp.number >> temp.price;
	flib.seekg(N/2*sizeof(Book), ios::beg);
	flib.write((char*)&temp, sizeof(Book));  //插入

	int total = 0;  //总的库存量
	double amount = 0.0;  //总价格
	flib.seekg(0,ios::beg);  //定位至起始处
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