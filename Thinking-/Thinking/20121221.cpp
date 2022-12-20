/*
	2018.05.05 15:21
	20121221�¶Է�����-���û���С��Ϸ
���ݣ�(20121221 - ����������yyyymmdd) - ǰ���������� => ѡ������һ������num��ʣ���������֮��sum���߱����� -> �³�ѡ������֡�
ԭ��num + sum = 9��������
���⣺��sumΪ9�ı�������ѡ�������num����Ϊ 0 �� 9 �����ڲ�ȷ������!����
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ORIGINAL = 20121221;	//��ʼ���� ����ĩ�գ�20121221
const int START = 19960101;		//��ʼ���� 19960101
const int END = 19960119;		//�������� 19960119

int reverse(int number);
int IncreaseDate(int& date);
bool IsDate(int date);
bool IsLeap(int year);
bool ContainDigit(int number, int digit);
int SumDigit(int number);

int main()
{
	time_t timestart = time(NULL);	//�����������ʱ��
	time_t timeend;
	vector<int> datadate;	//�������ݼ�
	vector<int> dataset;	//������ݼ�
	vector<int> datazero;	//�����0�����ݼ�
	vector<int> datanine;	//�����9�����ݼ�
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
	// ʹ�õ���������ʸ��
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
/* �������� */
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
/* ���ڵ�����
��λ�����գ�yyyymmdd�����ְ���������1 */
int IncreaseDate(int& date)
{
	int year, month, day;
	// �������� �� �� ��
	year = date / 10000;
	month = date % 10000 / 100;
	day = date % 100;
	// ��������1�����ڽ�λ
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
	// �ϲ����� yyyymmdd
	date = year * 10000 + month * 100 + day;
	return date;
}
/* �жϰ�λ�������ֺϷ� */
bool IsDate(int date)
{
	int year, month, day;
	year = date / 10000;
	month = date % 10000 / 100;
	day = date % 100;
	// �ж����ֳ��ȺϷ�
	int val = year / 1000;
	if (val <= 0 || val >= 10)
	{
		cout << "The length is ERROR!" << endl;
		return false;
	}
	//�ж��·ݺϷ�
	if (month <= 0 || month >= 13)
	{
		cout << "The month is ERROR!" << endl;
		return false;
	}
	//�ж������Ϸ�
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
/* �ж����� */
bool IsLeap(int year)
{
	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
		return true;
	else
		return false;
}
/* �ж��������Ƿ���ĳ������ */
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
/* �����λ����֮�� */
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
