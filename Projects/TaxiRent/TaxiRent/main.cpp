/*	2018.03.24 13:38 - 2018.3.25 16:50
	青岛出租车运价收费模拟程序
*/
#include <iostream>
#include <cstdlib>
#include "TaxiRent.h"

using namespace std;

int main()
{
	cout << "*** Taxi Rent ***" << endl;
	TaxiRent t;
	t.SetDistance(28.8);
	t.SetTime(72);
	t.SetPrice(99);
	//t.SetTimeWaiting(27);
	//t.SetTaxiType(Limousine);
	cout << "Distance = " << t.GetDistance() << " km " << endl
		<< "Time = " << t.GetTime() << " min " << endl
		<< "Price = " << t.GetPrice() << " RMB " << endl
		<< "TaxiType = " << t.GetTaxiType() << endl << endl;
	cout << "TotalPrice = " << t.TotalPrice() << " RMB " << endl;
	cout << "TimeWaiting = " << t.GetTimeWaiting() << " min " << endl
		<< "SpeedMax = " << t.GetSpeedMax() << " km/h " << endl
		<< "SpeedMin = " << t.GetSpeedMin() << " km/h " << endl << endl;
	cout << "After adding TimeWaiting:" << endl
		<< "TotalPrice2 = " <<t.TotalPrice() << " RMB " << endl;
	system("Pause");
	return 0;
}