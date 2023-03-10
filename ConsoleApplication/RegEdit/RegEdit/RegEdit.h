// 2019.11.18 20:38 - 2019.11.19 03:24
// 注册表编辑类的封装	
// 建立控制台应用程序时，需要在预编译头文件 pch.h 中添加 #include "RegEdit.h"
// 使用时，LPCTSTR 和 CString 均可
// 设置/获取，组合使用，推荐使用Ex版本。
//   如：SetValue(.)/GetValue(.) 和 SetValueEx(.)/GetValueEx(.)
// 区别：非 Ex 版本操作key(子项下的项|目录名)，Ex 版本操作value(子项中的值)
// 可以读写 REG_SZ: LPCTSTR, REG_DWORD: DWORD=unsigned long , REG_BINARY: BYTE=unsigned char


#pragma once

#include <afxtempl.h>	//CString

// 注册表编辑类
class CRegEdit
{
public:
	// 常用根键
	struct SRootKey
	{
		static HKEY KEY_CLASSES_ROOT;
		static HKEY KEY_CURRENT_USER;
		static HKEY KEY_LOCAL_MACHINE;
		static HKEY KEY_USERS;
		static HKEY KEY_CURRENT_CONFIG;
	};

	// 访问权限
	enum EAccess
	{
		ACCESS_READ = KEY_READ,
		ACCESS_WRITE = KEY_WRITE ,
		ACCESS_EXECUTE = KEY_EXECUTE,
		ACCESS_ALL = KEY_ALL_ACCESS
	};
public:
	CRegEdit();
	virtual ~CRegEdit();

	// 打开注册表
	// key是指有子节点和value的注册表项，value是指有值的注册表项
	// 形象地说，key是左边的文件夹，value是右边的项
	BOOL OpenKey(HKEY hRootKey, LPCTSTR szSubKey, enum EAccess access = ACCESS_ALL);

	// 创建注册表
	// out_dwDisposition: 返回信息
	// 使用：OpenKey(...)为 FALSE 时，需要调用 CreateKey() 创建
	BOOL CreateKey(DWORD* out_dwDisposition = nullptr);

	// 设置键值：该子项下，键名(项名|目录名) - 值数据
	BOOL SetValue(LPCTSTR szKeyName, LPCTSTR szValueData);
	// 设置键值：该子项中，值名(名称) - 值数据
	BOOL SetValueEx(LPCTSTR szValueName, LPCTSTR szValueData);
	BOOL SetValueEx(LPCTSTR szValueName, DWORD dwValueData);
	BOOL SetValueEx(LPCTSTR szValueName, LPBYTE byValueData, DWORD cdData);

	// 获得键值：该子项下，键名(项名|目录名) - 值数据
	BOOL GetValue(LPCTSTR szKeyName, CString& strValueData);
	// 获得键值：该子项中，值名(名称) - 值数据
	BOOL GetValueEx(LPCTSTR szValueName, CString& strValueData);
	BOOL GetValueEx(LPCTSTR szValueName, DWORD& dwValueData);
	BOOL GetValueEx(LPCTSTR szValueName, LPBYTE byValueData, DWORD& cdData);

	// 删除键值：该子项下，键名(项名|目录名) - 值数据
	BOOL DeleteValue(LPCTSTR szKeyName);
	// 删除键值：该子项中，值名(名称) - 值数据
	BOOL DeleteValueEx(LPCTSTR szValueName);

	// 关闭注册表
	BOOL CloseKey();

public:
	HKEY	m_rootKey;			// 根键
	LPCTSTR m_szSubKey;			// 子键
	enum EAccess m_access;		// 访问权限

	HKEY	m_key;				// 子项句柄 

};

