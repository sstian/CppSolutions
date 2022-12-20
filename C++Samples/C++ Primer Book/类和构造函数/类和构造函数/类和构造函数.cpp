#include <iostream>
#include <cstdlib>	  //exit函数所在库
using namespace std;
class DayOfYear
{
public:
	DayOfYear(int monthValue, int dayValue);//构造函数    //初始化月份和日期为相应的参数值。
	DayOfYear(int monthValue);				//构造函数    //初始化日期为给定月份的第一天。
	DayOfYear();							//默认构造函数//初始化日期为1月1日。
	void input();							//成员函数声明、、、
	void output();
	int getMonthNumber() { return month; }//取值函数，内联函数//返回代表月份的整数，如1月份是1,2月份是2等。
	int getDay() { return day; }		  //取值函数，内联函数(在类定义中直接定义的成员函数)
private:
	int month;
	int day;
	void testDate();
};
int main()
{
	DayOfYear date1(2, 21), date2(5), date3;     //对象date3的声明将调用默认构造函数
	cout << "Initialized dates:\n";
	date1.output(); cout << endl;				//调用成员函数output、、、
	date2.output(); cout << endl;
	date3.output(); cout << endl;
	date1 = DayOfYear(10, 31);					//构造函数DayOfYear::DayOfYear的显示调用
	cout << "date1 reset to the following:\n";
	date1.output(); cout << endl;
	return 0;
}
DayOfYear::DayOfYear(int monthValue, int dayValue)
	:month(monthValue), day(dayValue)
{
	testDate();
}
DayOfYear::DayOfYear(int monthValue)
	: month(monthValue), day(1)
{
	testDate();
}
DayOfYear::DayOfYear() : month(1), day(1)
{/*函数体有意为空*/
}
//成员函数定义：
void DayOfYear::input()
{
	cout << "Enter the month as a number: ";
	cin >> month;								//私有成员变量month,day可以在成员函数的定义中使用
	cout << "Enter the day of the month: ";
	cin >> day;
	if ((month < 1) || (month > 12) || (day < 1) || (day > 31))
	{
		cout << "Illegal dates! Program aborted.\n";
		exit(1);
	}
}
void DayOfYear::output()
{
	switch (month)
	{
	case 1: cout << "January "; break;
	case 2: cout << "February "; break;
	case 3: cout << "March "; break;
	case 4: cout << "April "; break;
	case 5: cout << "May "; break;
	case 6: cout << "June "; break;
	case 7: cout << "July "; break;
	case 8: cout << "August "; break;
	case 9: cout << "September "; break;
	case 10: cout << "October "; break;
	case 11: cout << "November "; break;
	case 12: cout << "December "; break;
	default: cout << "Error in DayOfYear::output. Contact software vendor.";
	}
	cout << day;
}
void DayOfYear::testDate()
{
	if ((month < 1) || (month > 12))
	{
		cout << "Illegal month value!\n";
		exit(1);
	}
	if ((day < 1) || (day > 31))
	{
		cout << "Illegal day value!\n";
		exit(1);
	}
}