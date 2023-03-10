/*
	2019/01/04 16:08:44
	char* / wchar_t* <-> _bstr_t / CComBSTR
	BSTR = Basic STRing，微软在 COM/OLE 中定义的标准字符串数据类型
	-> _bstr_t: C++对BSTR的封装，直接赋值自动转换
	-> CComBSTR: MFC对BSTR的封装
*/
#include <iostream>
#include <locale>

#include <afxtempl.h>
#include <comutil.h> //=com utility. BSTR->_bstr_t, VARIANT->_variant_t
using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs");
	wcout << L"*** BSTR -> -bstr_t ***" << endl;
	BSTR bstr = nullptr;
	// 方法一、直接使用类型转换
	// char* to _bstr_t  其实_bstr_t类内部实现了类型转换
	cout << "=== char* to _bstr_t ===" << endl;

	const char* psz = "abc中国";
	const wchar_t* pwsz = L"ABC中国";
	const TCHAR* ptsz = _T("ABc中华");
	cout << "char* = " << psz << endl;
	wcout << "wchar_t* = " << pwsz << endl;
	wcout << "TCHAT* = " << ptsz << endl << endl;
	
	_bstr_t bsz = psz;
	_bstr_t bwsz = pwsz;
	_bstr_t btsz = ptsz;
	cout << "char* -> _bstr_t =  " << bsz << endl;
	cout << "wchar_t* -> _bstr_t = " << bwsz << endl;
	cout << "TCHAR* -> _bstr_t = " << btsz << endl << endl;

	_bstr_t bstrt;
	bstrt += psz;
	bstrt += pwsz;
	bstrt += ptsz;
	cout << "_bstr_t = " << bstrt << endl << endl;

	// _bstr_t to char*  其实_bstr_t类内部实现了类型转换
	cout << "=== _bstr_t to char* ===" << endl;
	char* psztemp = bstrt;
	wchar_t* pwsztemp = bstrt;
	TCHAR * ptsztemp = bstrt;
	cout << "bstrt.length() = " << bstrt.length() << endl;
	cout << "_bstr_t -> char* = " << psztemp << endl;
	wcout << "_bstr_t -> wchar_t* = " << pwsztemp << endl;
	wcout << "_bstr_t -> TCHAR* = " << ptsztemp << endl << endl;

	//方法二、命名空间 _com_util
	cout << "=== _com_util ===" << endl;
	const char* psz2 = "test计算机";
	_bstr_t bstrt2 = _com_util::ConvertStringToBSTR(psz2);

	char* psz3 = _com_util::ConvertBSTRToString(bstrt);

	cout << "_com_util::ConvertStringToBSTR() = " << bstrt2 << endl;
	cout << "_com_util::ConvertBSTRToString() = " << psz3 << endl;

	// CComBSTR
	cout << "=== CComBSTR ===" << endl;
	CComBSTR combstr;
	combstr += psz;
	combstr += pwsz;
	combstr += ptsz;
	wcout << "-> CComBSTR = " << combstr.m_str << endl;

	char* psz4 = _com_util::ConvertBSTRToString(combstr.m_str);	//BSTR
	wchar_t* pwsz4 = combstr.m_str;
	cout << "->char* = " << psz4 << endl;
	wcout << "-> wchar_t* = " << pwsz4 << endl;

 	system("pause");
	return 0;
}

/***
BSTR
typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character
typedef WCHAR OLECHAR;
typedef OLECHAR *BSTR;
typedef BSTR *LPBSTR;

_bstr_t
// Extractors
operator const wchar_t*() const throw();
operator wchar_t*() const throw();
operator const char*() const ;
operator char*() const ;

namespace _com_util {
// Convert char * to BSTR
BSTR __stdcall ConvertStringToBSTR(const char* pSrc) ;

// Convert BSTR to char *
char* __stdcall ConvertBSTRToString(BSTR pSrc) ;
}

***/

/** 在VS2017中运行结果：
*** BSTR -> -bstr_t ***
=== char* to _bstr_t ===
char* = abc中国
wchar_t* = ABC中国
TCHAT* = ABc中华

char* -> _bstr_t =  abc中国
wchar_t* -> _bstr_t = ABC中国
TCHAR* -> _bstr_t = ABc中华

_bstr_t = abc中国ABC中国ABc中华

=== _bstr_t to char* ===
bstrt.length() = 15
_bstr_t -> char* = abc中国ABC中国ABc中华
_bstr_t -> wchar_t* = abc中国ABC中国ABc中华
_bstr_t -> TCHAR* = abc中国ABC中国ABc中华

=== _com_util ===
_com_util::ConvertStringToBSTR() = test计算机
_com_util::ConvertBSTRToString() = abc中国ABC中国ABc中华
=== CComBSTR ===
-> CComBSTR = abc中国ABC中国ABc中华
->char* = abc中国ABC中国ABc中华
-> wchar_t* = abc中国ABC中国ABc中华
请按任意键继续. . .
**/
