/*配置文件写类实现文件*/
#include "INIWriter.h"
#include <iostream>
#include <windows.h>

INIWriter::INIWriter(char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));  //用strlen()求字符串长度而不用sizeof
}

void INIWriter::WriteInteger(char* szSection, char* szKey, int iValue)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileString(szSection, szKey, szValue, m_szFileName);
}

void INIWriter::WriteFloat(char* szSection, char* szKey, float fValue)
{
	char szValue[255];
	sprintf(szValue, "%f" ,fValue);
	WritePrivateProfileString(szSection, szKey, szValue, m_szFileName);
}

void INIWriter::WriteBoolean(char* szSection, char* szKey, bool bValue)
{
	char szValue[255];
	sprintf(szValue, "%s", bValue ? "True" : "False");
	WritePrivateProfileString(szSection, szKey, szValue, m_szFileName);
}

void INIWriter::WriteString(char* szSection, char* szKey, char* szValue)
{
	WritePrivateProfileString(szSection, szKey, szValue, m_szFileName);
}

/******函数原型与功能说明******
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
*int sprintf( char *buffer, const char *format, [ argument] … );
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
*BOOL WritePrivateProfileString(
LPCTSTR lpAppName,  //INI文件中的一个字段名
LPCTSTR lpKeyName,  //lpAppName下的一个键名,通俗讲就是变量名
LPCTSTR lpString,  //键值,即变量的值,不过必须为LPCTSTR型或CString型
LPCTSTR lpFileName  //完整的INI文件名，如果没有指定完整路径名，则会在windows目录（默认）查找文件。
					//如果文件没有找到，则函数会在windows目录创建它
);
*
*5、补充信息：
*1.INI文件的路径必须完整,文件名前面的各级目录必须存在,否则写入不成功,该函数返回 FALSE 值。
*2.文件名的路径中必须为 \\ ,因为在VC++中, \\ 才表示一个 \ 。
*3.也可将INI文件放在程序所在目录,此时 lpFileName 参数为: ".\\student.ini"。
*/