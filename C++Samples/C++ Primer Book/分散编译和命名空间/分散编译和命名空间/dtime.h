//��DigitalTime�Ľӿ��ļ���
//����������������Ϊ���������ռ��С�
//�����ֵ��ʾһ���е�ĳ��ʱ�䣬ʱ����24Сʱ�Ʊ�ʾ��
#ifndef DTIME_H            //�����α���
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
		DigitalTime();                            //��ʼ��ʱ��Ϊ0:00������ҹ��
		int getHour() const;
		int getMinute() const;
		void advance(int minutesAdded);
		//��ʱ�����ΪminutesAdded����ʾ�ķ������Ժ�
		void advance(int hoursAdded, int minutesAdded);
		//��ʱ�����ΪhoursAdded�������Сʱ������minutesAdded����ʾ�ķ������Ժ�
		friend bool operator ==(const DigitalTime& time1, const DigitalTime& time2);
		friend istream& operator >>(istream& ins, DigitalTime& theObject);
		friend ostream& operator <<(ostream& outs, const DigitalTime& theObject);
	private:                                     //˽�г�Ա�������ʵ�ֲ���
		int hour;
		int minute;
	};
}
#endif