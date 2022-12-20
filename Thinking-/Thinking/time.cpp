/*	2017.09.27 15:26 
	时间族函数：动态刷新时间
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <ctime>
#include <Windows.h>

using namespace std;

void DynamicTime();
int main()
{
	DynamicTime();
	return 0;
}

void DynamicTime()
{
	time_t tt;
	tm* t;
	while (true)
	{
		tt = time(NULL);	// time_t time(time_t* const _Time);
		cout << "time_t = " << tt << endl;

		char* week[] = { "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六" };
		t = localtime(&tt);	// struct tm* localtime(time_t const* const _Time);
		cout << t->tm_year + 1900 << "年" << t->tm_mon + 1 << "月" << t->tm_mday << "日 " << week[t->tm_wday] << " ";
		cout << setw(2) << setfill('0') << t->tm_hour << ":"
			<< setw(2) << setfill('0') << t->tm_min << ":"
			<< setw(2) << setfill('0') << t->tm_sec << endl;

		Sleep(1000);	// void Sleep(DWORD dwMilliseconds);
		system("cls");	// int system(char const* _Command);
 	}
}
/*****************************************************************************************************
//64位机
typedef __time64_t time_t;
typedef __int64                       __time64_t;

struct tm
{
int tm_sec;   // seconds after the minute - [0, 60] including leap second
int tm_min;   // minutes after the hour - [0, 59]
int tm_hour;  // hours since midnight - [0, 23]
int tm_mday;  // day of the month - [1, 31]
int tm_mon;   // months since January - [0, 11]
int tm_year;  // years since 1900
int tm_wday;  // days since Sunday - [0, 6]
int tm_yday;  // days since January 1 - [0, 365]
int tm_isdst; // daylight savings time flag
};

time_t mktime(tm* const _Tm);	//制作时间数据
******************************************************************************************************/