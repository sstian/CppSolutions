/*  2017.3.11 19:00
	指针：动态内存分配 new delete
*/
#include <iostream>
using namespace std;

int main(void)
{
	int m, n;  //行，列
	cout << "***动态创建二维数组***\n";
	cout << "M, N = ";
	cin >> m >> n;
	//变量
	int* p = new int(m);
	cout << "*p = " << *p << endl;
	delete p;
	//一维数组
	int *pm = new int[m];
	cout << "Input " << m << " values:\n";
	for(int i = 0; i < m; i++)
		cin >> *(pm + i);
	for(i = 0; i < m; i++)
		cout << pm[i] << " ";
	cout << endl;
	delete[] pm;
	//二维数组
	cout << "*****************\n";
	int **pNum = new int*[m];  //申请
	int count = 1;
	for(int j = 0; j < m; j++)
		pNum[j] = new int[n];
	for(i = 0; i < m; i++)  //赋值
		for(j = 0; j < n; j++)
			pNum[i][j] = count++;
	for(i = 0; i < m; i++)  //输出
	{
		for(j = 0; j < n; j++)
			cout << pNum[i][j] << " ";
		cout << endl;
	}
	for(i = 0; i < m; i++)  //释放
		delete[] pNum[i];
	delete[] pNum;
	////数组指针：用一维指针指向二维数组
	cout << "*****************\n";
	const int COL = 3;
	int (*fp)[COL] = new int[m][COL];
	for(i = 0; i < m; i++)
		for(j = 0; j < COL; j++)
			*(*(fp + i) + j) = count++;  //fp[i][j]
	for(i = 0; i < m; i++)  //输出
	{
		for(j = 0; j < COL; j++)
			cout << fp[i][j] << " ";
		cout << endl;
	}
	delete[] fp;
	//////内存连续：pp[i*n+j]即pp[i][j]
	cout << "*****************\n";
	int *pp = new int[m * n];
	for(i = 0; i < m; i++)
		for(j = 0; j < n; j++)
			pp[i*n+j] = count++;
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
			cout << pp[i*n+j] << " ";
		cout << endl;
	}
	delete[] pp;
	return 0;
}

/*在VC++6.0中的运行结果：输入“3 4”，“11 12 13”
==============================================================
***动态创建二维数组***
M, N = 3 4
*p = 3
Input 3 values:
11 12 13
11 12 13
*****************
1 2 3 4
5 6 7 8
9 10 11 12
*****************
13 14 15
16 17 18
19 20 21
*****************
22 23 24 25
26 27 28 29
30 31 32 33
Press any key to continue
==============================================================*/