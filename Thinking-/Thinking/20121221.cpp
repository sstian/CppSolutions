/*
	2018.05.05 15:21
	20121221猜对方数字-撩妹互动小游戏
内容：(20121221 - 出生年月日yyyymmdd) - 前面结果的逆序 => 选择其中一个数字num，剩下数字相加之和sum告诉表演者 -> 猜出选择的数字。
原理：num + sum = 9个倍数。
问题：若sum为9的倍数，则选择的数字num可能为 0 或 9 （存在不确定因素!）。
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ORIGINAL = 20121221;	//起始数字 世界末日：20121221
const int START = 19960101;		//开始日期 19960101
const int END = 19960119;		//结束日期 19960119

int reverse(int number);
int IncreaseDate(int& date);
bool IsDate(int date);
bool IsLeap(int year);
bool ContainDigit(int number, int digit);
int SumDigit(int number);

int main()
{
	time_t timestart = time(NULL);	//计算程序运行时间
	time_t timeend;
	vector<int> datadate;	//日期数据集
	vector<int> dataset;	//结果数据集
	vector<int> datazero;	//结果含0的数据集
	vector<int> datanine;	//结果含9的数据集
	dataset.clear();
	datazero.clear();
	datadate.clear();
	datanine.clear();
	for (int date = START; date <= END; IncreaseDate(date))
	{
		datadate.push_back(date);

		int temp = ORIGINAL - date;
		int temp_reverse = reverse(temp);
		int result = temp - temp_reverse;
		dataset.push_back(result);

		if (ContainDigit(result, 0))
		{
			datazero.push_back(abs(SumDigit(result)));
		}
		else
			datazero.push_back(-1);

		if (ContainDigit(result, 9))
		{
			datanine.push_back(abs(SumDigit(result)) - 9);
		}
		else
			datanine.push_back(-2);
	}
	// 使用迭代器遍历矢量
	vector<int>::iterator itdate;
	vector<int>::iterator itset;
	vector<int>::iterator itzero;
	vector<int>::iterator itnine;
	itdate = datadate.begin();
	itset = dataset.begin();
	itzero = datazero.begin();
	itnine = datanine.begin();
	cout << "yyyymmdd\tdataset\t    guess 0\tguess 9" << endl;
	cout << "---------------------------------------------------" << endl;
	for (; itdate != datadate.end(); itdate++, itset++, itzero++, itnine++)
	{
		cout << *itdate << "\t" << *itset << "\t    " << *itzero << "\t\t" << *itnine <<endl;
	}

	cout << " \nThe size = " << datadate.size() << endl;

	timeend = time(NULL);
	cout << "Time of use = " << timeend - timestart << " s" << endl;
	system("pause");
	return 0;
}
/* 数字逆序 */
int reverse(int number)
{
	int value = number;
	int sum = 0;
	while (value)
	{
		sum = sum * 10 + value % 10;
		value /= 10;
	}
	return sum;
}
/* 日期递增：
八位年月日（yyyymmdd）数字按天数递增1 */
int IncreaseDate(int& date)
{
	int year, month, day;
	// 分离数字 年 月 日
	year = date / 10000;
	month = date % 10000 / 100;
	day = date % 100;
	// 日子增加1，存在进位
	if (IsDate(date))
	{
		day++;
		switch (month)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (day > 31)
			{
				day = 1;
				month++;
			}
			break;
		case 4: case 6: case 9: case 11:
			if (day > 30)
			{
				day = 1;
				month++;
			}
			break;
		case 2:
			if (IsLeap(year))
			{
				if (day > 29)
				{
					day = 1;
					month++;
				}
			}
			else
			{
				if (day > 28)
				{
					day = 1;
					month++;
				}
			}
			break;
		default:
			break;
		}
		if (month > 12)
		{
			month = 1;
			year++;
		}
	}
	// 合并数字 yyyymmdd
	date = year * 10000 + month * 100 + day;
	return date;
}
/* 判断八位日期数字合法 */
bool IsDate(int date)
{
	int year, month, day;
	year = date / 10000;
	month = date % 10000 / 100;
	day = date % 100;
	// 判断数字长度合法
	int val = year / 1000;
	if (val <= 0 || val >= 10)
	{
		cout << "The length is ERROR!" << endl;
		return false;
	}
	//判断月份合法
	if (month <= 0 || month >= 13)
	{
		cout << "The month is ERROR!" << endl;
		return false;
	}
	//判断天数合法
	switch (month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (day <= 0 || day > 31)
		{
			cout << "The day is ERROR!" << endl;
			return false;
		}
		break;
	case 4: case 6: case 9: case 11:
		if (day <= 0 || day > 30)
		{
			cout << "The day is ERROR!" << endl;
			return false;
		}
		break;
	case 2:
		if (IsLeap(year))
		{
			if (day <= 0 || day > 29)
			{
				cout << "The day is ERROR!" << endl;
				return false;
			}
		}
		else if(day <= 0 || day > 28)
		{
			cout << "The day is ERROR!" << endl;
			return false;
		}	
		break;
	default:
		break;
	}
	return true;
}
/* 判断闰年 */
bool IsLeap(int year)
{
	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
		return true;
	else
		return false;
}
/* 判断数字中是否含有某个数字 */
bool ContainDigit(int number, int digit)
{
	if (digit < 0 || digit > 10)
	{
		cout << "The digit must be a number!" << endl;
		exit(1);
	}
	int value = abs(number);
	while (value)
	{
		if (value % 10 == digit)
			return true;
		else
			value /= 10;
	}
	return false;
}
/* 计算各位数字之和 */
int SumDigit(int number)
{
	int value = number;
	int sum = 0;
	while (value)
	{
		sum += value % 10;
		value /= 10;
	}
	return sum;
}
