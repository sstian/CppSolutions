/*	2018.05.17 11:28
	�������Ϣ
��������money������year��������rate���������й�ʽ�������ʱ����Ϣinterest��˰ǰ�������ʱ����2λС����

 interest=money(1+rate)year-money 
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	float money, year, rate;
	float interest;
	cout << "Enter money,year and rate:";
	cin >> money >> year >> rate;
	interest = money * 	pow((1+rate), year) - money;
	cout << "interest=" << fixed << setprecision(2) << interest << endl;
	return 0;
}
