/*
	2019/01/04 17:20:10
	字符串与数值之间的转换
*/
#include <iostream>
#include <locale>
#include <vector>
#include <tchar.h>	// TCHAR
#include <afxtempl.h>
using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs");
	wcout << L"*** string <-> value ***" << endl;
	cout << "=== number to string ===" << endl;
	int n = 12;
	long l = 24;
	float f = 3.14f;
	double d = 123.456789123456789;
	vector<string> vecstr;
	vecstr.clear();
	vecstr.push_back(to_string(n));
	vecstr.push_back(to_string(l));
	vecstr.push_back(to_string(f));
	vecstr.push_back(to_string(d));
	for (auto& at : vecstr)
		cout << at << " ";
	cout << endl;

	cout << "=== string to number ===" << endl;
	//int n3 = atoi(vecstr.at(0).c_str());
	int n2 = stoi(vecstr.at(0));
	long l2 = stol(vecstr.at(1));
	float f2 = stof(vecstr.at(2));
	double d2 = stof(vecstr.at(3));
	cout << "int = " << n2 << endl
		<< "long = " << l2 << endl
		<< "float = " << f2 << endl
		<< "double = " << d2 << endl;

	cout << "=== TCHAR ===" << endl;
	const TCHAR* tchar = _T("24");
	int n3 = _tstoi(tchar);
	cout << "_tstoi() = " << n3 << endl;

	system("pause");
	return 0;
}

/***
1. 数值类型 转换为 字符串类型：C++11 std::to_string() / std::to_wstring()
std::string to_string(int value);
std::string to_string(long int value);
std::string to_string(long long int value);
std::string to_string(unsigned int value);
std::string to_string(unsigned long long int value);
std::string to_string(float value);
std::string to_string(double value);

std::wstring to_wstring(int value);
std::wstring to_wstring(long int value);
std::wstring to_wstring(long long int value);
std::wstring to_wstring(unsigned int value);
std::wstring to_wstring(unsigned long long int value);
std::wstring to_wstring(float value);
std::wstring to_wstring(double value);

2.1 string / wstring 转换为 数值类型：stoxx()
int					stoi(const string& _Str, size_t *_Idx = 0, int _Base = 10);
long				stol(const string& _Str, size_t *_Idx = 0,int _Base = 10);
unsigned long		stoul(const string& _Str, size_t *_Idx = 0,int _Base = 10);
long long			stoll(const string& _Str, size_t *_Idx = 0,int _Base = 10);
unsigned long long	stoull(const string& _Str, size_t *_Idx = 0,int _Base = 10);
float				stof(const string& _Str, size_t *_Idx = 0);
double				stod(const string& _Str, size_t *_Idx = 0);
long double			stold(const string& _Str, size_t *_Idx = 0);

int					stoi(const wstring& _Str, size_t *_Idx = 0,int _Base = 10);
......

2.2 char* / wchar_t* 转换为 数值类型：atoxx()
int       __cdecl atoi   (_In_z_ char const* _String);
long      __cdecl atol   (_In_z_ char const* _String);
long long __cdecl atoll  (_In_z_ char const* _String);
__int64   __cdecl _atoi64(_In_z_ char const* _String);
double    __cdecl atof   (_In_z_ char const* _String);

int			__cdecl		_wtoi(_In_z_ wchar_t const* _String);
long		__cdecl		_wtol(_In_z_ wchar_t const* _String);
long long	__cdecl		_wtoll(_In_z_ wchar_t const* _String);
double		__cdecl		_wtof(_In_z_ wchar_t const* _String);

long				__cdecl wcstol(wchar_t const* _String, wchar_t** _EndPtr, int _Radix);
long long			__cdecl wcstoll(wchar_t const* _String, wchar_t** _EndPtr, int _Radix);
unsigned long		__cdecl wcstoul(wchar_t const* _String, wchar_t** _EndPtr, int _Radix);
unsigned long long	__cdecl wcstoull(wchar_t const* _String, wchar_t** _EndPtr, int _Radix);
float				__cdecl wcstof(wchar_t const* _String, wchar_t** _EndPtr);
double				__cdecl wcstod(wchar_t const* _String, wchar_t** _EndPtr);
long double			__cdecl wcstold(wchar_t const* _String, wchar_t** _EndPtr);

2.3 TCHAR 转换为 数值类型：_tstoxx(), _tcstoxx()
					ANSI:		Unicode:
#define _tstoi      atoi		_wtoi
#define _tstol      atol		_wtol
#define _tstoll     atoll		_wtoll
#define _tstoi64    _atoi64		_wtoi64
#define _tstof      atof		_wtof

								Unicode:
#define _tcstol					wcstol
#define _tcstoll				wcstoll
#define _tcstoul				wcstoul
#define _tcstoull				wcstoull
#define _tcstof					wcstof
#define _tcstod					wcstod
#define _tcstold				wcstold
*/

/**在VS2017中运行结果：
*** string <-> value ***
=== number to string ===
12 24 3.140000 123.456789
=== string to number ===
int = 12
long = 24
float = 3.14
double = 123.457
请按任意键继续. . .
*/