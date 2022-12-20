// 2018.03.07 19:46
// 配置文件操作类的封装
// 2020.02.12 优化兼容多字节与Unicode字符集
// 2020.05.06 改进在当前Section下操作，增加获取某Section的Key=Value

#pragma once

//#include <afxtempl.h>	//CIniFile.cpp 存在 #include "stdafx.h" 则不需要

// 配置文件操作类
class CIniFile
{
// Constructor & Deconstructor
public:
	CIniFile();
	CIniFile(LPCTSTR lpszFileName);
	virtual ~CIniFile();

//Attributes
public:
	// 设置文件名及路径值. "./"表示当前目录下，不能省略！
	void SetFileName(LPCTSTR lpszFileName);
	// 设置当前操作的Section名
	void SetSectionName(LPCTSTR lpszSectionName);

//Operations
public:
	/*读取节、键、值*/
	// 使用 wcout 进行字符串的控制台输出，由于使用CString
	DWORD	GetProfileStrings(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, CString& strKeyValue);	//读取字符串型键值（默认值为""）
	// 可以写入并读取int（负整数亦可）。
	int		GetProfileInteger(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);	//读取整型键值（默认值为0）
	bool	GetProfileBool(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);		//读取布尔键值（默认值为false）
	double	GetProfileDouble(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);		//读取实数键值（默认值为0.0）

	/*写入节、键、值*/
	BOOL SetProfileString(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszKeyValue);	//写入字符串型键值
	BOOL SetProfileInteger(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, int nKeyValue);		//写入整型键值
	BOOL SetProfileBool(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, bool bKeyValue);			//写入布尔键值
	//写入实数键值//实数用setProfileString()存储，避免出现精度误差！
	BOOL SetProfileDouble(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, double dKeyValue);		//写入实数键值

	/*删除节、键*/
	BOOL DeleteSection(LPCTSTR lpszSectionName);					//删除节
	BOOL DeleteKey(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);	//删除键值对

	/*操作节、键、值，改进版：在当前Section下*/
	DWORD	GetProfileStrings(LPCTSTR lpszKeyName, CString& strKeyValue);
	int		GetProfileInteger(LPCTSTR lpszKeyName);
	bool	GetProfileBool(LPCTSTR lpszKeyName);
	double	GetProfileDouble(LPCTSTR lpszKeyName);

	BOOL SetProfileString(LPCTSTR lpszKeyName, LPCTSTR lpszKeyValue);
	BOOL SetProfileInteger(LPCTSTR lpszKeyName, int nKeyValue);
	BOOL SetProfileBool(LPCTSTR lpszKeyName, bool bKeyValue);	
	BOOL SetProfileDouble(LPCTSTR lpszKeyName, double dKeyValue);

	BOOL DeleteSection();
	BOOL DeleteKey(LPCTSTR lpszKeyName);	

	// 获取全部Section名。缓冲区大小 = sectionNum * sectionSize + 1，考虑终止符
	// sectionNum: 支持的最大Section数量；sectionSize: Section名称长度，包括\0
	DWORD GetProfileSectionNames(CStringArray& strArray, UINT sectionNum = 256, UINT sectionSize = 33);
	
	// 获取某个Section的所有Key=Value
	// nSize: 缓冲区大小
	DWORD GetProfileKeyValues(CMapStringToString& strMap, LPCTSTR lpszSectionName = nullptr, UINT nSize = 2048);
	
	// Section是否存在

	// Key是否存在

	// Value是否存在，即Key的值是否为空
	bool HasValue(LPCTSTR lpszKeyName, LPCTSTR lpszSectionName = nullptr);

// Data
private:
	CString m_szFileName;			//文件名及路径	
	CString m_szSectionName;		//当前操作的Section名
};