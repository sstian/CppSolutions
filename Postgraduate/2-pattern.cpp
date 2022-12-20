/*  2017.1.10 18:31
	用算法打印图案
	            *
              ***
            *****
          *******
          *****
          ***
          *
*/
#include <iostream>
using namespace std;

int main(void)
{
	int i, j, t, s;  //分别控制行，列，左端空格，每行空格
	int n, space;    //图案最宽行的域宽，图案左端空格数

	cout << "****** Print Pattern ******\n";
	cout << "Please input widthest row n = ";
	cin >> n;
	cout << "Plese input left white space = ";
	cin >> space;
	
	for(i = 1; i <= n/2+1; i++)  //输出打印前n/2+1行
	{
		for(t = 1; t <= space; t++)
			cout << ' ';         //左端space个空格
		for(s = 1; s <= n-2*i+1; s++)
			cout << ' ';         //打印每行的空格
		for(j = 1; j <= 2*i-1; j++)
			cout << '*';		 //打印每行的星星
		cout << endl;			 //该行结束，换行
	}
	for(i = n/2; i >=1; i--)	 //输出打印后n/2行
	{
		for(t = 1; t <= space; t++)
			cout << ' ';		 //左端space个空格
		for(j = 1; j <= 2*i-1; j++)
			cout << '*';	     //打印每行的星星
		cout << endl;			 //该行结束，换行
	}

	system("pause");
	return 0;
}