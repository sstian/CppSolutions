#include <iostream>
#include <locale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "chs");
	wchar_t wt[] = L"中华人民共和国";
	wcout << wt << endl;
	return 0;
}