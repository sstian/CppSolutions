#include "stdafx.h"
//#include "pch.h"
#include "CIniFile.h"


CIniFile::CIniFile()
{
	m_szFileName.Empty();
	m_szSectionName.Empty();
}

CIniFile::CIniFile(LPCTSTR lpszFileName)
{
	m_szFileName = lpszFileName;
}

CIniFile::~CIniFile()
{
}

void CIniFile::SetFileName(LPCTSTR lpszFileName)
{
	m_szFileName = lpszFileName;
}

void CIniFile::SetSectionName(LPCTSTR lpszSectionName)
{
	m_szSectionName = lpszSectionName;
}

//读取
DWORD CIniFile::GetProfileStrings(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, CString& strKeyValue)
{
	/// #define MAX_PATH          260
	/// LPTSTR CString::GetBuffer( int nMinBufLength ); 
	/// 返回值：一个指向对象的（以空字符结尾的）字符缓冲区的LPTSTR指针。
	///	nMinBufLength: 字符缓冲区的以字符数表示的最小容量。这个值不包括一个结尾的空字符的空间。 
	DWORD dwCopied = 0;
	dwCopied = ::GetPrivateProfileString(lpszSectionName, lpszKeyName, _T(""), strKeyValue.GetBuffer(MAX_PATH), MAX_PATH, m_szFileName);
	strKeyValue.ReleaseBuffer();	//结束对由GetBuffer分配的缓冲区的使用。
	return dwCopied;
}

int CIniFile::GetProfileInteger(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName)
{
	int nKeyValue = ::GetPrivateProfileInt(lpszSectionName, lpszKeyName, 0, m_szFileName);	//存在 UINT->int 的转换
	return nKeyValue;
}

bool CIniFile::GetProfileBool(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName)
{
	CString szKeyValue;
	::GetPrivateProfileString(lpszSectionName, lpszKeyName, CString(_T("False")), szKeyValue.GetBuffer(MAX_PATH), MAX_PATH, m_szFileName);
	bool bResult = ((szKeyValue == CString(_T("True")) || szKeyValue == CString(_T("true"))) ? true : false);
	return bResult;
}

double CIniFile::GetProfileDouble(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName)
{
	CString szKeyValue;
	::GetPrivateProfileString(lpszSectionName, lpszKeyName, CString(_T("0.0")), szKeyValue.GetBuffer(MAX_PATH), MAX_PATH, m_szFileName);
	double dResult = _tcstod(szKeyValue.GetString(), nullptr);
	return dResult;
}

//写入
BOOL CIniFile::SetProfileString(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszKeyValue)
{
	return ::WritePrivateProfileString(lpszSectionName, lpszKeyName, lpszKeyValue, m_szFileName);
}

BOOL CIniFile::SetProfileInteger(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, int nKeyValue)
{
	CString szKeyValue;
	szKeyValue.Format(_T("%d"), nKeyValue);
	return ::WritePrivateProfileString(lpszSectionName, lpszKeyName, szKeyValue, m_szFileName);
}

BOOL CIniFile::SetProfileBool(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, bool bKeyValue)
{
	CString szKeyValue;
	szKeyValue.Format(_T("%s"), (bKeyValue ? _T("True") : _T("False")));
	return ::WritePrivateProfileString(lpszSectionName, lpszKeyName, szKeyValue, m_szFileName);
}

BOOL CIniFile::SetProfileDouble(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, double dKeyValue)
{
	CString szKeyValue;
	szKeyValue.Format(_T("%lf"), dKeyValue);
	return ::WritePrivateProfileString(lpszSectionName, lpszKeyName, szKeyValue, m_szFileName);
}

//删除
BOOL CIniFile::DeleteSection(LPCTSTR lpszSectionName)
{
	return ::WritePrivateProfileSection(lpszSectionName, NULL, m_szFileName);
}

BOOL CIniFile::DeleteKey(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName)
{
	return ::WritePrivateProfileString(lpszSectionName, lpszKeyName, NULL, m_szFileName);
}


// 改进版
DWORD CIniFile::GetProfileStrings(LPCTSTR lpszKeyName, CString & strKeyValue)
{
	return this->GetProfileStrings(this->m_szSectionName, lpszKeyName, strKeyValue);
}

int CIniFile::GetProfileInteger(LPCTSTR lpszKeyName)
{
	return this->GetProfileInteger(this->m_szSectionName, lpszKeyName);
}

bool CIniFile::GetProfileBool(LPCTSTR lpszKeyName)
{
	return this->GetProfileBool(this->m_szSectionName, lpszKeyName);
}

double CIniFile::GetProfileDouble(LPCTSTR lpszKeyName)
{
	return this->GetProfileDouble(this->m_szSectionName, lpszKeyName);
}

BOOL CIniFile::SetProfileString(LPCTSTR lpszKeyName, LPCTSTR lpszKeyValue)
{
	return this->SetProfileString(this->m_szSectionName, lpszKeyName, lpszKeyValue);
}

BOOL CIniFile::SetProfileInteger(LPCTSTR lpszKeyName, int nKeyValue)
{
	return this->SetProfileInteger(this->m_szSectionName, lpszKeyName, nKeyValue);
}

BOOL CIniFile::SetProfileBool(LPCTSTR lpszKeyName, bool bKeyValue)
{
	return this->SetProfileBool(this->m_szSectionName, lpszKeyName, bKeyValue);
}

BOOL CIniFile::SetProfileDouble(LPCTSTR lpszKeyName, double dKeyValue)
{
	return this->SetProfileDouble(this->m_szSectionName, lpszKeyName, dKeyValue);
}

BOOL CIniFile::DeleteSection()
{
	return this->DeleteSection(this->m_szSectionName);
}

BOOL CIniFile::DeleteKey(LPCTSTR lpszKeyName)
{
	return this->DeleteKey(this->m_szSectionName, lpszKeyName);
}


DWORD CIniFile::GetProfileSectionNames(CStringArray & strArray, UINT sectionNum, UINT sectionSize)
{
	//存储所有的节名
	UINT nSize = sectionNum * sectionSize + 1;
	LPTSTR lpszBuffer = new TCHAR[nSize]{ 0 };
	DWORD dwCopied = ::GetPrivateProfileSectionNames(lpszBuffer, nSize, this->m_szFileName);
	strArray.RemoveAll();		//清空字符串数组集合

	TCHAR *pFirst, *pLast;
	pFirst = pLast = lpszBuffer;
	while (*pFirst)				//即 '\0' != *p
	{
		while (*pLast)
			++pLast;

		CString str(pFirst, static_cast<int>(pLast - pFirst));
		strArray.Add(str);
		pFirst = ++pLast;
	}
	delete[] lpszBuffer;
	return dwCopied;
}

DWORD CIniFile::GetProfileKeyValues(CMapStringToString& strMap, LPCTSTR lpszSectionName, UINT nSize)
{
	CString strSectionName = (lpszSectionName ? lpszSectionName : this->m_szSectionName);

	//存储所有的键值对
	LPTSTR lpszBuffer = new TCHAR[nSize]{ 0 };
	DWORD dwCopied = ::GetPrivateProfileSection(strSectionName, lpszBuffer, nSize, this->m_szFileName);
	strMap.RemoveAll();			//清空集合

	TCHAR *pFirst, *pLast;
	pFirst = pLast = lpszBuffer;
	while (*pFirst)				//即 '\0' != *p
	{
		CString strKey, strValue;
		while (*pLast)
		{
			if (_T('=') == *pLast)
			{
				strKey = CString(pFirst, static_cast<int>(pLast - pFirst));
				pFirst = pLast + 1;
			}
			++pLast;
		}

		strValue = CString(pFirst, static_cast<int>(pLast - pFirst));
		strMap.SetAt(strKey, strValue);
		pFirst = ++pLast;
	}
	delete[] lpszBuffer;
	return dwCopied;
}

bool CIniFile::HasValue(LPCTSTR lpszKeyName, LPCTSTR lpszSectionName)
{
	CString strSectionName = (lpszSectionName ? lpszSectionName : this->m_szSectionName);
	
	CString strKeyValue;
	this->GetProfileStrings(lpszKeyName, strKeyValue);

	return ((!strKeyValue.IsEmpty()) ? true : false);
}


/****** 函数原型与功能说明  读取 ******
*1、为初始化文件中指定的条目获取它的整数值：
UINT WINAPI GetPrivateProfileInt
(
_In_LPCTSTR lpAppName,  //指定在其中查找条目的小节。注意这个字串是不区分大小写的
_In_LPCTSTR lpKeyName,  //欲获取的设置项或条目。这个支持不区分大小写
_In_INT nDefault,		//指定条目未找到时返回的默认值
_In_LPCTSTR lpFileName  //初始化文件的名字。如果没有指定完整的路径名，windows就会在Windows目录中搜索文件
);
*函数返回值：Long，找到的条目的值；如指定的条目未找到，就返回默认值。
*	如找到的数字不是一个合法的整数，函数会返回其中合法的一部分。

*2、为初始化文件中指定的条目取得字串：
DWORD GetPrivateProfileString(
LPCTSTR lpAppName,  //配置文件的section名
LPCTSTR lpKeyName,  //配置文件的key名
LPCTSTR lpDefault,  //如果INI文件中没有前两个参数指定的字段名或键名,则将此值赋给变量
LPTSTR lpReturnedString,  //接收INI文件中的值的CString对象,即目的缓存器
DWORD nSize,  //目的缓存器的大小
LPCTSTR lpFileName  //完整的INI文件名
);
*函数返回值：Long，复制到lpReturnedString缓冲区的字节数量，其中不包括那些NULL中止字符。
*	如lpReturnedString缓冲区不够大，不能容下全部信息，就返回nSize-1
*	（若lpApplicationName或lpKeyName为NULL，则返回nSize-2）
*
lpKeyName = NULL，lpReturnedString返回为节lpAppName下的所有键名
GetPrivateProfileString(lpAppName, NULL, lpDefault, lpReturnedString, nSize, lpFileName)

lpAppName = NULL，(lpKeyName无意义了)，lpReturnedString返回所有的节名 
GetPrivateProfileString(NULL, NULL, lpDefault, lpReturnedString, nSize, lpFileName)
<=> GetPrivateProfileSectionNames 

*3、typedef unsigned int UINT;
*UINT类型在WINDOWS API中有定义，它对应于32位无符号整数。

*4、typedef unsigned long DWORD;
*DWORD 就是 Double Word， 每个word为2个字节的长度，DWORD 双字即为4个字节，每个字节是8位，共32位。

5、读取lpFileName指定的配置文件中所有的节名：
DWORD GetPrivateProfileSectionNames(
LPTSTR lpszReturnBuffer,  // address of return buffer
DWORD nSize,              // size of return buffer
LPCTSTR lpFileName        // address of initialization filename
);
//lpszReturnBuffer字符串形式如下：Section1/0Section2/0…SectionN/0/0

6、获取指定小节所有项名和值的一个列表
WINBASEAPI
DWORD
WINAPI
GetPrivateProfileSectionW(
	_In_     LPCWSTR lpAppName,
	_Out_writes_to_opt_(nSize, return +1) LPWSTR lpReturnedString,
	_In_     DWORD nSize,
	_In_opt_ LPCWSTR lpFileName
);
//__declspec(dllimport) unsigned long __stdcall GetPrivateProfileSectionW(
*/

/****** 函数原型与功能说明  写入 ******
*1、初始化函数：void *memset(void *s, int ch, size_t n);
*函数功能：将s中当前位置后面的n个字节 （typedef unsigned int size_t ）用 ch 替换并返回 s 。
*需要头文件：<memory.h>或<string.h>
*
*2、内存拷贝函数：void *memcpy(void *dest, const void *src, size_t n);
*函数功能：从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中，
*	函数返回指向dest的指针。
*需要头文件：#include<cstring>
*
*3、字符串格式输出：=string print format
int sprintf( char *buffer, const char *format, [ argument] … );
*函数功能：把格式化的数据写入某个字符串缓冲区。
*	返回写入buffer 的字符数，出错则返回-1. 如果 buffer 或 format 是空指针，且不出错而继续，函数将返回-1，
*	并且 errno 会被设置为 EINVAL。sprintf 返回被写入buffer 的字节数，结束字符‘\0’不计入内。
*	即，如果“Hello”被写入空间足够大的buffer后，函数sprintf 返回5。
*buffer：char型指针，指向将要写入的字符串的缓冲区。
*format：格式化字符串。
*[argument]...：可选参数，可以是任何类型的数据。
*需要头文件：stdio.h
*
*4、将信息写入.INI文件中
BOOL WritePrivateProfileString(
LPCTSTR lpAppName,  //INI文件中的一个字段名
LPCTSTR lpKeyName,  //lpAppName下的一个键名,通俗讲就是变量名
LPCTSTR lpString,  //键值,即变量的值,不过必须为LPCTSTR型或CString型
LPCTSTR lpFileName  //完整的INI文件名，如果没有指定完整路径名，则会在windows目录（默认）查找文件。
//如果文件没有找到，则函数会在windows目录创建它
);
*

5、写（替换）指定节lpAppName中的键值：
BOOL WINAPI WritePrivateProfileSection(
_In_ LPCTSTR lpAppName,
_In_ LPCTSTR lpString,
_In_ LPCTSTR lpFileName
);

*6、补充信息：
*1.INI文件的路径必须完整,文件名前面的各级目录必须存在,否则写入不成功,该函数返回 FALSE 值。
*2.文件名的路径中必须为 \\ ,因为在VC++中, \\ 才表示一个 \ ；或者为 / 。
*3.也可将INI文件放在程序所在目录,此时 lpFileName 参数为: ".\\student.ini"。
*4.调用WritePrivateProfileSection，若参数二 lpString为NULL，则可将对应section的全部内容清空；
	调用WritePrivateProfileString，若参数三 lpString为NULL，则可将对应key删除。

*/