/*	2018.05.17 11:28
	求存款到期利息
输入存款金额money、存期year和年利率rate，根据下列公式计算存款到期时的利息interest（税前），输出时保留2位小数。

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
