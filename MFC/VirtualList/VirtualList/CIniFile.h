// 2018.03.07 19:46
// 配置文件操作类
// 2020.02.12 优化兼容多字节与Unicode字符集
#pragma once

////#include "stdafx.h"
//#include "pch.h"
//#include <afxtempl.h>	//存在 #include "stdafx.h" 则不需要

class CIniFile
{
public:
	CIniFile();
	CIniFile(LPCTSTR lpszFileName);
	virtual ~CIniFile();

public:
	//Attributes
	//设置文件名及路径值
	void SetFileName(LPCTSTR lpszFileName);		

public:
	//Operations
	/*读取节、键、值*/
	//使用 wcout 进行字符串的控制台输出，由于使用CString
	DWORD	GetProfileString(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, CString& szKeyValue);	//读取字符串型键值（默认值为""）
	//可以写入并读取int（负整数亦可）。
	int		GetProfileInteger(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);	//读取整型键值（默认值为0）
	bool	GetProfileBool(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);		//读取布尔键值（默认值为false）
	double	GetProfileDouble(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);		//读取实数键值（默认值为0.0）
	//返回section数量
	DWORD	GetProfileSectionNames(CStringArray& strArray);					

	/*写入节、键、值*/
	BOOL SetProfileString(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, LPCTSTR lpszKeyValue);	//写入字符串型键值
	BOOL SetProfileInteger(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, int nKeyValue);		//写入整型键值
	BOOL SetProfileBool(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, bool bKeyValue);			//写入布尔键值
	//实数用setProfileString()存储，避免出现精度误差！
	BOOL SetProfileDouble(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName, double dKeyValue);		//写入实数键值

	/*删除节、键*/
	BOOL DeleteSection(LPCTSTR lpszSectionName);					//删除节
	BOOL DeleteKey(LPCTSTR lpszSectionName, LPCTSTR lpszKeyName);	//删除键值对

private:
	CString m_szFileName;			//文件名及路径
	UINT	m_unMaxSection;			//最多支持的Section数，设为256
	UINT	m_unSectionNameMaxSize;	//Section名称长度，设为32(Null-terminated)
	
	void init();	//Section初始化
};