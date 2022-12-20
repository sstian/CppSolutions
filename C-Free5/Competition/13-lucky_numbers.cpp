/*
	2018.05.12 18:06
	Lucky Numbers (easy) 
*/
#include <iostream>

using namespace std;

bool IsSuperLucky74(int number);
int main()
{
	int n;
	cout << "Input a positive integer n: "<< endl;
//	while(true)
//	{
//		cin >> n;
//		if(n < 1 || n > 109)
//			cout << "the range is 1¡Ün¡Ü109." << endl;
//		else
//			break;
//	} 
	cin >> n;
	for(int i = n; ; i++)
		if(IsSuperLucky74(i))
		{
			cout << i << endl;
			break;
		}
	return 0;
}
/* ÅÐ¶Ï³¬¼¶ÐÒÔËÊý×Ö */
bool IsSuperLucky74(int number)
{
	int value = number;
	int re, count = 0;
	int s7 = 0, s4 = 0;
	while(value)
	{
		re = value % 10;
		if(re == 7)
			s7++;
		else if(re == 4)
			s4++;
		else
			return false;
		count++;
		value /= 10;
	}
	if(count % 2 != 0 || s7 != s4)
		return false; 
	return true;
} 
