/*	2018.05.17 10:37
	闰年、季节和月天数
*/
#include <iostream>

using namespace std;

bool IsLeap(int year); 
int ShowFestival(int month);
int CountDays(int year, int month);
int main()
{
	int year, month;
	char* festival[4] = {
		"Spring", "Summer", "Fall", "Winter"
	};
	
	cin >> year >> month;
	
	cout << (IsLeap(year)?"Leap year":"Common year") << ",";
	cout << festival[ShowFestival(month)] << ",";
	cout << CountDays(year, month) << endl;
	return 0;
}
/* 判断闰年 */
bool IsLeap(int year)
{
	if((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
		return true;
	else
		return false;
}
/* 显示季节 */
int ShowFestival(int month)
{
	int fes = -1;
	switch(month)
	{
		case 3: case 4: case 5: 
			fes = 0;
			break;
		case 6: case 7: case 8: 
			fes = 1;
			break;
		case 9: case 10: case 11: 
			fes = 2;
			break;
		case 12: case 1: case 2: 
			fes = 3;
			break;
		default:
			break; 
	}
	return fes;
}
/* 各月天数 */
int CountDays(int year, int month)
{
	int days = 0;
	switch(month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
			days = 31;
			break;
		case 4: case 6: case 9: case 11: 
			days = 30;
			break;
		case 2: 
			if(IsLeap(year))
				days = 29;
			else
				days = 28;
			break;
		default:
			break;
	}
	return days;
}
