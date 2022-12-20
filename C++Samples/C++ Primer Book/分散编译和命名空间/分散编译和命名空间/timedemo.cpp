//应用程序文件/驱动文件timedemo.cpp。
#include <iostream>
#include "dtime.h"

void readHour(int& theHour);

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;
	using DTimeSavitch::DigitalTime;
	int theHour;
	readHour(theHour);
	DigitalTime clock(theHour, 0), oldClock;
	oldClock = clock;
	clock.advance(15);
	if (clock == oldClock)
		cout << "Something is wrong.";
	cout << "You entered " << oldClock << endl;
	cout << "15 minutes later the time will be "
		<< clock << endl;
	return 0;
}

void readHour(int& theHour)
{
	using std::cout;
	using std::cin;
	cout << "Let's play a time game.\n"
		<< "Let's pretend the hour has just changed,\n"
		<< "you may write midnight as either 0 or 24.\n"
		<< "but,I will always write it as 0.\n"
		<< "Enter the hour as a number (0 to 24): ";
	cin >> theHour;
}