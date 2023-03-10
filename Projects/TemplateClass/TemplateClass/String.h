/*
	2018.11.19 16:47 - 23:05
	自定义字符串类，内部实现为char*
*/
#pragma once

#include <iostream>
#include <cstring>

#include "DataIndex.h"

using namespace std;

// 字符串 类
class String
{
public:
	String();
	String(const char* psz);
	String(const char ch, int repeat = 1);
	String(const char* psz, int length);
	// 赋值构造函数
	String(const String& rstr);

	~String();

	// 返回字符串长度
	int GetLength() const { return m_length; }
	int GetSize()   const { return (int)strlen(m_pData); }
	// 类型转换
	operator const char*() { return m_pData; }
	// 返回C风格字符串
	const char* c_str() const { return m_pData; }

	// 重载运算符[]
	char& operator [](int index) { return m_pData[index]; }
	char  operator [](int index) const { return m_pData[index]; }

	// 删除已有堆空间重新分配
	String  operator + (const char* psz);
	String  operator + (const String& rstr);
	String& operator = (const char* psz);
	String& operator = (const String& rstr);
	String& operator +=(const char* psz);
	String& operator +=(const String& rstr);

	// 字符串比较：== != < <= > >=
	// 比较运算符重载，函数重载
	bool operator ==(const char* psz)		{ return strcmp(this->m_pData, psz)				== 0;	}
	bool operator ==(const String& rstr)	{ return strcmp(this->m_pData, rstr.m_pData)	== 0;	}
	bool operator !=(const char* psz)		{ return strcmp(this->m_pData, psz);					}
	bool operator !=(const String& rstr)	{ return strcmp(this->m_pData, rstr.m_pData);			}
	bool operator < (const char* psz)		{ return strcmp(this->m_pData, psz)				<  0;	}
	bool operator < (const String& rstr)	{ return strcmp(this->m_pData, rstr.m_pData)	<  0;	}
	bool operator <=(const char* psz)		{ return strcmp(this->m_pData, psz)				<= 0;	}
	bool operator <=(const String& rstr)	{ return strcmp(this->m_pData, rstr.m_pData)	<= 0;	}
	bool operator > (const char* psz)		{ return strcmp(this->m_pData, psz)				>  0;	}
	bool operator > (const String& rstr)	{ return strcmp(this->m_pData, rstr.m_pData)	>  0;	}
	bool operator >=(const char* psz)		{ return strcmp(this->m_pData, psz)				>= 0;	}
	bool operator >=(const String& rstr)	{ return strcmp(this->m_pData, rstr.m_pData)	>= 0;	}	

	//亦可以用友元函数
	//friend bool operator==(const String& rstr, const char* psz) { return 0 == strcmp(rstr.m_pData, psz); }	//或rstr.c_str()

	// 友元函数重载输出输入运算符 << >>，！类内为函数声明，必须在类外定义函数
	friend ostream& operator <<(ostream& out, const String& rstr);
	friend istream& operator >>(istream& in, String& rstr);

	// 查找：默认从头开始
	int Find(const char ch, int start = 0);
	int Find(const char* psz, int start = 0);

	// 字符串本身全部大写、小写、反转
	/// tydefine unsigned __int64 size_t;
	String& MakeUpper() { _strupr_s(this->m_pData, this->GetSize() + 1); return *this; }	/// errno_t _strupr_s(char* _String, size_t _Size);
	String& MakeLower() { _strlwr_s(this->m_pData, this->GetSize() + 1); return *this; }
	String& MakeReverse();

	// 字符串截取：从中间、从左边、从右边
	String Middle(int index, int count) const;
	String Middle(int index) const;
	String Left(int count = 1) const	{ return Middle(0, count); }
	String Right(int count = 1) const	{ return Middle(this->GetSize() - count, count); }

private:
	int m_length;	//字符串长度
	char* m_pData;	//字符串指针
};

String::String()
{
	m_length = 0;
	m_pData = new char(0);	//申请一个字节并初始化为0
}

inline String::String(const char * psz)
{
	m_length = (int)strlen(psz);
	m_pData = new char[m_length + 1];
	strcpy_s(m_pData, m_length + 1, psz);		/// int strcpy_s(char *dst, size_t num, const char *src ); // num = strlen(dst) + 1 //目的字符串缓冲区
	//std::wcout << "sizeof(m_pData) = " << sizeof(m_pData) << std::endl;
	//std::wcout << "strlen(m_pData) = " << strlen(m_pData) << std::endl;
	//std::wcout << "m_length + 1 = " << m_length + 1 << std::endl;
} 

inline String::String(const char ch, int repeat)
{
	this->m_length = repeat;
	this->m_pData = new char[this->m_length + 1];
	/// void* __cedcl memset(void* _Dest, int _Val, size_t _Size);
	memset(this->m_pData, ch, repeat);
	this->m_pData[repeat] = '\0';
}

inline String::String(const char * psz, int length)
{
	int szlen = (int)strlen(psz);
	if (szlen > length)
		szlen = length;					//相当于截取前length个字符串

	this->m_pData = new char[szlen + 1];
	memcpy(this->m_pData, psz, szlen);	//字符串没有那么长length，则只需要复制整个psz
	this->m_pData[szlen] = '\0';
	this->m_length = szlen;
}

inline String::String(const String & rstr)
{
	// 深层复制
	this->m_length = rstr.m_length;
	this->m_pData = new char[this->m_length + 1];
	strcpy_s(this->m_pData, this->m_length + 1, rstr.m_pData);
}

String::~String()
{
	m_length = 0;
	delete m_pData;
}


ostream & operator<<(ostream & out, const String & rstr)
{
	out << rstr.c_str();
	return out;
}

istream & operator>>(istream & in, String & rstr)
{
	in >> rstr.m_pData;
	return in;
}

String String::operator+(const char * psz)
{
	int n = this->GetSize() + (int)strlen(psz);
	String str;
	str.m_pData = new char[n + 1];
	strcpy_s(str.m_pData, n + 1,this->m_pData);
	strcat_s(str.m_pData, n + 1, psz);
	return str;
}

inline String String::operator+(const String & rstr)
{
	int n = this->GetSize() + rstr.GetSize();
	String str;
	str.m_pData = new char[n + 1];
	strcpy_s(str.m_pData, n + 1, this->m_pData);
	strcat_s(str.m_pData, n + 1, rstr.m_pData);
	return str;
}

inline String & String::operator=(const char * psz)
{
	int length = (int)strlen(psz);
	if (length > this->GetSize())
	{
		delete[] m_pData;
		this->m_pData = new char[length + 1];	
	}

	this->m_length = length;
	strcpy_s(m_pData, m_length + 1, psz);

	return *this;
}

inline String & String::operator=(const String & rstr)
{
	int length = rstr.GetSize();
	if (length > this->GetSize())
	{
		delete[] m_pData;
		this->m_pData = new char[length + 1];
	}

	this->m_length = length;
	strcpy_s(m_pData, m_length + 1, rstr.m_pData);

	return *this;
}

inline String & String::operator+=(const char * psz)
{
	int total = this->GetSize() + (int)strlen(psz);
	char* pChar = new char[total + 1];
	strcpy_s(pChar, total + 1, this->m_pData);
	strcat_s(pChar, total + 1, psz);

	delete[] this->m_pData;
	this->m_pData = pChar;

	return *this;
}

inline String & String::operator+=(const String & rstr)
{
	int total = this->GetSize() + rstr.GetSize();
	char* pChar = new char[total + 1];
	strcpy_s(pChar, total + 1, this->m_pData);
	strcat_s(pChar, total + 1, rstr.m_pData);

	delete[] this->m_pData;
	this->m_pData = pChar;

	return *this;
}

inline int String::Find(const char ch, int start)
{
	if (start >= this->GetSize())
		return -1;
	
	/// inline char* __CRTDECL strchr(_In_z_ char* const _String, _In_ int const _Ch);
	char* pFind = strchr(this->m_pData + start, ch);	
	if (!pFind)
		return -1;

	return (int)(pFind - this->m_pData);
}

inline int String::Find(const char * psz, int start)
{
	if (start >= this->GetSize())
		return -1;

	/// inline char* __CRTDECL strstr(_In_z_ char* const _String, _In_z_ char const* const _SubString);
	char* pFind = strstr(this->m_pData + start, psz);	
	if (!pFind)
		return -1;

	return (int)(pFind - this->m_pData);
}

String & String::MakeReverse()
{
	char* pFirst = this->m_pData;
	char* pLast = this->m_pData + this->GetSize() - 1;
	while (pFirst < pLast)
	{
		DataIndex<char>::Swap(*pFirst, *pLast);
		pFirst++;
		pLast--;
	}

	return *this;
}

inline String String::Middle(int index, int count) const
{
	if(index >= this->GetSize())
		return String();
	if (index + count >= this->GetSize())
		count = this->GetSize() - index;

	String strNew;
	delete[] strNew.m_pData;
	strNew.m_pData = new char[count + 1];
	memcpy(strNew.m_pData, this->m_pData + index, count);
	strNew.m_pData[count] = '\0';
	strNew.m_length = count;

	return strNew;
}

inline String String::Middle(int index) const
{
	// 方法1.
	//if(index >= this->GetSize())
	//	return String();

	//String strNew;
	//strNew.m_length = this->GetSize() - index;
	//strNew.m_pData = new char[m_length + 1];
	//memcpy(strNew.m_pData, this->m_pData + index, strNew.m_length);
	//strNew.m_pData[strNew.m_length] = '\0';

	//return strNew;

	// 方法2.
	return Middle(index, this->GetSize() - index);
}
