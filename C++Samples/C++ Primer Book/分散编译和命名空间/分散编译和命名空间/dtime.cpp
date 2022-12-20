//类DigitalTime的实现文件。
#include <iostream>
#include <cctype>
#include <cstdlib>
using std::istream;
using std::ostream;
using std::cout;
using std::cin;
#include "dtime.h"

namespace                               //未命名命名空间
{                                       //在未命名命名空间中定义的名字局限在该编码单元中，
	int digitToInt(char c)              //在编码单元外可重新使用，则这些辅助函数局限在文件dtime,cpp中。
	{
		return (int(c) - int('0'));
	}
	void readMinute(int& theMinute)
	{
		char c1, c2;
		cin >> c1 >> c2;
		if (!(isdigit(c1) && isdigit(c2)))
		{
			cout << "Error: illegal input to readMinute\n";
			exit(1);
		}
		theMinute = digitToInt(c1) * 10 + digitToInt(c2);
		if (theMinute < 0 || theMinute > 59)
		{
			cout << "Error: illegal input to readMinute\n";
			exit(1);
		}
	}
	void readHour(int& theHour)
	{
		char c1, c2;
		cin >> c1 >> c2;
		if (!(isdigit(c1) && (isdigit(c2) || c2 == ':')))
		{
			cout << "Error: illegal input to readHour\n";
			exit(1);
		}
		if (isdigit(c1) && c2 == ':')
			theHour = digitToInt(c1);
		else
		{
			theHour = digitToInt(c1) * 10 + digitToInt(c2);
			cin >> c2;
			if (c2 != ':')
			{
				cout << "Error: illegal input to readHour\n";
				exit(1);
			}
		}
		if (theHour == 24)
			theHour = 0;
		if (theHour < 0 || theHour > 23)
		{
			cout << "Error: illegal input to readHour\n";
			exit(1);
		}
	}
}
namespace DTimeSavitch                            //在该编码编码单元中，
{                                                 //可直接使用未命名命名空间的名字，而不需要使用限定词。
	DigitalTime::DigitalTime(int theHour, int theMinute)
	{
		if (theHour < 0 || theHour > 24 || theMinute < 0 || theMinute > 59)
		{
			cout << "Illegal argument to DigitalTime constructor.";
			exit(1);
		}
		else
		{
			hour = theHour;
			minute = theMinute;
		}
		if (hour == 24)
			hour = 0;
	}
	DigitalTime::DigitalTime()
	{
		hour = 0;
		minute = 0;
	}
	int DigitalTime::getHour() const
	{
		return hour;
	}
	int DigitalTime::getMinute() const
	{
		return minute;
	}
	void DigitalTime::advance(int minutesAdded)
	{
		int grossMinutes = minute + minutesAdded;
		minute = grossMinutes % 60;
		int hourAdjustment = grossMinutes / 60;
		hour = (hour + hourAdjustment) % 24;
	}
	void DigitalTime::advance(int hoursAdded, int minutesAdded)
	{
		hour = (hour + hoursAdded) % 24;
		advance(minutesAdded);
	}
	bool operator ==(const DigitalTime& time1, const DigitalTime& time2)
	{
		return (time1.hour == time2.hour && time1.minute == time2.minute);
	}
	istream& operator >>(istream& ins, DigitalTime& theObject)
	{
		readHour(theObject.hour);
		readMinute(theObject.minute);
		return ins;
	}
	ostream& operator <<(ostream& outs, const DigitalTime& theObject)
	{
		outs << theObject.hour << ':';
		if (theObject.minute < 10)
			outs << '0';
		outs << theObject.minute;
		return outs;
	}
}