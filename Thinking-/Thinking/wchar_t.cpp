#include <iostream>
#include <locale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "chs");
	wchar_t wt[] = L"�л����񹲺͹�";
	wcout << wt << endl;
	return 0;
}