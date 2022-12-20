/*
	2018.05.12 09:39
	，求解并输出该数的个位数、十位数和百位数。	
*/
#include <iostream>
using namespace std;

int main()
{
	int num;
	int one, ten, hundred;
	cout << "Input a three bit positive integer: " << endl;
	cin >> num;
	one = num % 10;
	ten = num / 10 % 10;
	hundred = num / 100;
	cout << one << " " << ten << " " << hundred << endl;
	return 0;
}
