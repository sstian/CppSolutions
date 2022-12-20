//类DigitalTime的接口文件。
//将辅助函数隐藏在为命名命名空间中。
//该类的值表示一天中的某个时间，时间以24小时制表示。
#ifndef DTIME_H            //避免多次编译
#define DTIME_H
#include <iostream>
using std::istream;
using std::ostream;
namespace DTimeSavitch
{
	class DigitalTime
	{
	public:
		DigitalTime(int theHour, int theMinute);
		DigitalTime();                            //初始化时间为0:00（即午夜）
		int getHour() const;
		int getMinute() const;
		void advance(int minutesAdded);
		//将时间更改为minutesAdded所表示的分钟数以后
		void advance(int hoursAdded, int minutesAdded);
		//将时间更改为hoursAdded所代表的小时数加上minutesAdded所表示的分钟数以后
		friend bool operator ==(const DigitalTime& time1, const DigitalTime& time2);
		friend istream& operator >>(istream& ins, DigitalTime& theObject);
		friend ostream& operator <<(ostream& outs, const DigitalTime& theObject);
	private:                                     //私有成员属于类的实现部分
		int hour;
		int minute;
	};
}
#endif