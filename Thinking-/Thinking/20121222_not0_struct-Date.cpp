/*
	2018.12.04 22:29 - 2018.12.05 16:18
	心灵感应之数，20121221游戏的暴力破解版
	测试结果：其实任何一个八位数经过此番变化均为9的倍数。
	调整：以2012122为被减数可去除0的干扰，理由为世界末日的后一天，因为东西方存在时差。
2018.11.04 23:00 - 23:59 设计简易日期结构体可以实现按天数递增。
2018.11.05 15:43 - 16:16 增加struct Date: operator int(), ++/--Date, Date++/--, << 等运算符重载/类型转换函数。
*/
#include <iostream>
#include <vector>
using namespace std;

const int START = 20121201;
const int GOAL = 9;
int Reverse(int data);
int Summary(int data);
bool IsExist(int number, const int value = 0);


// Data结构体
struct Date
{
	int year_;
	int month_;
	int day_;

	Date(int year = 1970, int month = 1, int day = 1) :year_(year), month_(month), day_(day) { }
	~Date() { }
	bool operator =(int value)
	{
		int remain = value / 100000000;
		if (remain <= 0 || remain >= 10)
			return false;	//数据不是八位数
		year_ = value / 10000;
		month_ = value % 10000 / 100;
		day_ = value % 100;
		return true;
	}
	int operator ++()	//前置 ++date
	{
		++day_;
		switch (month_)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (day_ > 31)
			{
				day_ = 1;
				++month_;
				if (month_ > 12)
				{
					month_ = 1;
					++year_;
				}
			}
			break;
		case 4: case 6: case 9: case 11:
			if (day_ > 30)
			{
				day_ = 1;
				++month_;
			}
			break;
		case 2:
			if (Date::IsLeep(year_) && day_ > 29)
			{
				day_ = 1;
				++month_;
			}
			if (!Date::IsLeep(year_) && day_ > 28)
			{
				day_ = 1;
				++month_;
			}
			break;
		default:
			break;
		}
		return (year_ * 10000 + month_ * 100 + day_);
	}
	int operator ++(int ignore) //后置 date++
	{
		int value = toint();
		this->operator++();
		return value;
	}
	int operator --()	//前置 --date
	{
		--day_;
		switch (month_)
		{
		case 1: case 2: case 4: case 6: case 8: case 9: case 11: 
			if (day_ < 1)
			{
				day_ = 31;
				--month_;
				if (month_ < 1)
				{
					month_ = 12;
					--year_;
				}
			}
			break;
		case 5: case 7: case 10: case 12:
			if (day_ < 1)
			{
				day_ = 30;
				--month_;
			}
			break;
		case 3:
			if (Date::IsLeep(year_) && day_ < 1)
			{
				day_ = 29;
				--month_;
			}
			if (!Date::IsLeep(year_) && day_ < 1)
			{
				day_ = 28;
				--month_;
			}
			break;
		default:
			break;
		}
		return toint();	//(year_ * 10000 + month_ * 100 + day_);
	}
	int operator --(int ignore) //后置 date--
	{
		int value = toint();
		this->operator--();
		return value;
	}
	int toint()
	{
		return (year_ * 10000 + month_ * 100 + day_);
	}
	// 重载基本类型，类型转换函数，返回类型由 operator 后面的目的类型标明
	operator int()
	{
		return (year_ * 10000 + month_ * 100 + day_);
	}
	// 重载输出运算符
	friend ostream& operator <<(ostream& output, const Date& rdate)
	{
		output << rdate.year_ << "-" << rdate.month_ << "-" << rdate.day_;
		return output;
	}
	// 判断闰年
	static bool IsLeep(int year)
	{
		return (0 == year % 4 && 0 != year % 100) || (0 == year % 400);
	}
};

int main()
{
	int data = 19981010;		//测试数据
	vector<int> vecValid;		//符合要求之数
	vecValid.clear();
	//Date dates(2012);
	//int ns = dates;
	//cout << "Date<<: " << dates << endl;
	//cout << "Date->int: " << ns << endl;
	//cout << Summary(1125) << endl;
	//cout << IsExist(2112, 0) << endl;
	//for (int index = START; index < START + 1000; index++)	//START * 10
	for(Date date(2012); date.toint() < START+1000; date++)
	{
		int diff = date.toint() - data;	//int diff = index - data;
		cout << "diff = " << diff << endl;
		//cout << "Reverse(diff) = " << Reverse(diff) << endl;
		int reverse = abs(diff - Reverse(diff));
		cout << "reverse = " << reverse << endl;
		//int sum = Summary(reverse);
		//cout << "sum = " << sum << endl;
		if (!IsExist(reverse, 0))
		{
			vecValid.push_back(date.toint());
			//cout << "index = " << index << endl;
		}
	}

	vector<int>::iterator it;
	for (auto& vi : vecValid)
		wcout << vi << " ";
	wcout << endl << "size = " << vecValid.size() << endl;

	system("pause");
	return 0;
}

/* 整数逆序 */
int Reverse(int data)
{
	int result = 0;
	while (data)
	{
		result = result * 10 + data % 10;
		data /= 10;
	}
	return result;
}

/* 求取各位数字之和 */
int Summary(int data)
{
	int sum = 0;
	while (data)
	{
		sum += data % 10;
		data /= 10;
	}
	return sum;
}

/* 数字number包含value */
bool IsExist(int number, const int value)
{
	int absnumber = abs(number);
	while (absnumber)
	{
		if (value == absnumber % 10)
			return true;
		absnumber /= 10;
	}
	return false;
}
