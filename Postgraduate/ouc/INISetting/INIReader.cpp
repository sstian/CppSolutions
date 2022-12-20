/*配置文件读类实现文件*/
#include "INIReader.h"
#include <iostream>
#include <windows.h>

INIReader::INIReader(char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));  //用strlen()求字符串长度而不用sizeof
}

int INIReader::ReadInteger(char* szSection, char* szKey, int iDefaultValue)
{
		char szSpaceKey[255];  
	strcpy(szSpaceKey, szKey);  //键后添加空格

	int iResult = GetPrivateProfileInt(szSection, strcat(szSpaceKey, " "), iDefaultValue, m_szFileName);
	return iResult;
}

float INIReader::ReadFloat(char* szSection, char* szKey, float fDefaultValue)
{
	char szDefault[255];
	char szResult[255];
	sprintf(szDefault, "%f", fDefaultValue);
	GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_szFileName);
	float fResult = atof(szResult);
	return fResult;
}

bool INIReader::ReadBoolean(char* szSection, char* szKey, bool bDefaultValue)
{
	char szDefault[255];
	char szResult[255];
	sprintf(szDefault, "%s", bDefaultValue ? "True" : "False");
	GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_szFileName);
	bool bResult = (strcmp(szResult, "true") == 0 || strcmp(szResult, "True") == 0) ? true : false;
	return bResult;
}

char* INIReader::ReadSring(char* szSection, char* szKey, const char* szDefaultValue)
{
	char* szResult = new char[255];  //注意变量销毁
//	char szResult[255];
	memset(szResult, 0x00, 255);
	GetPrivateProfileString(szSection, szKey, szDefaultValue,szResult,255,m_szFileName);
	return szResult;
}

/******函数原型与功能说明******
*1、为初始化文件中指定的条目获取它的整数值：
*UINT WINAPI GetPrivateProfileInt
(
_In_LPCTSTR lpAppName,  //指定在其中查找条目的小节。注意这个字串是不区分大小写的
_In_LPCTSTR lpKeyName,  //欲获取的设置项或条目。这个支持不区分大小写
_In_INT nDefault,  //指定条目未找到时返回的默认值
_In_LPCTSTR lpFileName  //初始化文件的名字。如果没有指定完整的路径名，windows就会在Windows目录中搜索文件
);
*函数返回值：Long，找到的条目的值；如指定的条目未找到，就返回默认值。
*	如找到的数字不是一个合法的整数，函数会返回其中合法的一部分。

*2、为初始化文件中指定的条目取得字串：
*DWORD GetPrivateProfileString(
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
*3、typedef unsigned int UINT;
*UINT类型在WINDOWS API中有定义，它对应于32位无符号整数。

*4、typedef unsigned long DWORD;
*DWORD 就是 Double Word， 每个word为2个字节的长度，DWORD 双字即为4个字节，每个字节是8位，共32位。

*/