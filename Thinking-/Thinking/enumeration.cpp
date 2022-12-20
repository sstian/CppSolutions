#include <iostream>
using namespace std;
int main()
{
	enum day{Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday};
	day today;
	today = Wednesday;
	if (today == Saturday || today == Sunday)
		cout << "休息日" << endl;
	else
		cout << "工作日" << endl;
	return 0;
}