#include <iostream>
using namespace std;
int main()
{
	enum day{Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday};
	day today;
	today = Wednesday;
	if (today == Saturday || today == Sunday)
		cout << "��Ϣ��" << endl;
	else
		cout << "������" << endl;
	return 0;
}