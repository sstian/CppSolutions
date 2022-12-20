#include <iostream>
#include <cstdlib>	  //exit�������ڿ�
using namespace std;
class DayOfYear
{
public:
	DayOfYear(int monthValue, int dayValue);//���캯��    //��ʼ���·ݺ�����Ϊ��Ӧ�Ĳ���ֵ��
	DayOfYear(int monthValue);				//���캯��    //��ʼ������Ϊ�����·ݵĵ�һ�졣
	DayOfYear();							//Ĭ�Ϲ��캯��//��ʼ������Ϊ1��1�ա�
	void input();							//��Ա��������������
	void output();
	int getMonthNumber() { return month; }//ȡֵ��������������//���ش����·ݵ���������1�·���1,2�·���2�ȡ�
	int getDay() { return day; }		  //ȡֵ��������������(���ඨ����ֱ�Ӷ���ĳ�Ա����)
private:
	int month;
	int day;
	void testDate();
};
int main()
{
	DayOfYear date1(2, 21), date2(5), date3;     //����date3������������Ĭ�Ϲ��캯��
	cout << "Initialized dates:\n";
	date1.output(); cout << endl;				//���ó�Ա����output������
	date2.output(); cout << endl;
	date3.output(); cout << endl;
	date1 = DayOfYear(10, 31);					//���캯��DayOfYear::DayOfYear����ʾ����
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
{/*����������Ϊ��*/
}
//��Ա�������壺
void DayOfYear::input()
{
	cout << "Enter the month as a number: ";
	cin >> month;								//˽�г�Ա����month,day�����ڳ�Ա�����Ķ�����ʹ��
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