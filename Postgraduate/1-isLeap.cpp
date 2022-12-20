/*  2017.1.9 16:53
	判断某一年是否为闰年
*/
#include <iostream>
using namespace std;

bool isLeap(int year)
{
	if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;
	else
		return false;
}

int main(void)
{
	int year;
	cout << "Please input a year:";
	cin >> year;
	if(isLeap(year))
		cout << year << " is a leap year."<< endl;
	else
		cout << year << " is not a leap year!"<< endl;

	system("pause");
	return 0;
}