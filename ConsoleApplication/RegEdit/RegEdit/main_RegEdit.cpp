// main_RegEdit.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

int main()
{
    std::cout << "Hello World!\n"; 
	std::cout << "*** RegEdit 注册表编辑 ***" << std::endl;
	std::cout << "=== 写入注册表 1. LPCTSTR ===" << std::endl;
	CRegEdit reg;
	LPCTSTR szSubKey = _T("Software\\RegEdit\\OUC");
	BOOL res = reg.OpenKey(CRegEdit::SRootKey::KEY_CURRENT_USER, szSubKey);
	if (!res)
		reg.CreateKey();
	
	//LPCTSTR szKey = _T("school");
	//LPCTSTR szValue = _T("ouc");
	//reg.SetValue(szKey, szValue);
	//reg.SetValue(_T("address"), _T("shandong"));

	std::cout << "=== 写入注册表 EX 1. LPCTSTR ===" << std::endl;
	LPCTSTR szValueName = _T("student");
	LPCTSTR  szValueData = _T("postgraduate1234567890");
	reg.SetValueEx(szValueName, szValueData);
	reg.SetValueEx(_T("laboratory"), _T("HP-LAB at Information School Five"));

	LPCTSTR szValueName2 = _T("score");
	reg.SetValueEx(szValueName2, 1100);

	LPCTSTR szValueName3 = _T("data");
	BYTE data[5] = { 0x12, 0x34, 0x56, 0x78, 0x90 };
	reg.SetValueEx(szValueName3, data, 5);


	std::cout << "=== 读取注册表 1. LPCTSTR ===" << std::endl;
	CRegEdit reg_read;
	BOOL res_read = reg_read.OpenKey(CRegEdit::SRootKey::KEY_CURRENT_USER, szSubKey);
	if (!res_read)
	{
		std::cout << "读取注册表失败！" << std::endl;
	}
	else
	{
		CString strValue;
		//reg_read.GetValue(szKey, strValue);
		//std::wcout << strValue.GetString() << std::endl;

		//reg_read.GetValue(_T("address"), strValue);
		//std::wcout << strValue.GetString() << std::endl;

		// 读取注册表 EX 1. LPCTSTR
		reg_read.GetValueEx(szValueName, strValue);
		std::wcout << _T("Ex: REG_SZ - szValueName = ") << strValue.GetString() << std::endl;

		reg_read.GetValueEx(_T("laboratory"), strValue);
		std::wcout << _T("Ex: REG_SZ - laboratory = ") << strValue.GetString() << std::endl;

		DWORD dwData;
		reg_read.GetValueEx(_T("score"), dwData);
		std::wcout << _T("Ex: REG_DWORD - score = ") << dwData << std::endl;

		BYTE cbData[10] = { 0 };
		reg_read.GetValueEx(_T("data"), cbData, dwData);
		std::wcout << _T("Ex: REG_BINARY - dwData = ") << dwData << _T(" dwData = ");
		for (DWORD i = 0; i < dwData; i++)
			std::wcout << _T("0x") << std::hex << cbData[i] << " ";
		std::cout << std::endl;	
	}

	std::cout << "=== 删除key 1. LPCTSTR ===" << std::endl;
	//reg.DeleteValue(szKey);
	//reg.DeleteValue(_T("address"));

	std::cout << reg.DeleteValueEx(szValueName) << std::endl;

	//LPCTSTR szSubKeyTmp = _T("Software\\RegEdit");
	//reg.OpenKey(CRegEdit::SRootKey::KEY_CURRENT_USER, szSubKeyTmp);
	//reg.DeleteValue(_T("OUC"));

	std::cout << "=== 关闭注册表 1. LPCTSTR ===" << std::endl;
	reg.CloseKey();

	std::cout << "=== 写入注册表 2. CString ===" << std::endl;
	CRegEdit reg2;
	CString strSubKey = _T("Software\\RegEdit-CString\\OUC");
	BOOL res2 = reg2.OpenKey(CRegEdit::SRootKey::KEY_CURRENT_USER, strSubKey);
	if (!res2)
		reg2.CreateKey();

	CString strKey = _T("school");
	CString strValue = _T("ouc");
	reg2.SetValue(strKey, strValue);
	reg2.SetValue(CString(_T("address")), CString(_T("shandong")));

	reg2.CloseKey();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

/*** VS2017 output:
Hello World!
*** RegEdit 注册表编辑 ***
=== 写入注册表 1. LPCTSTR ===
=== 写入注册表 EX 1. LPCTSTR ===
=== 读取注册表 1. LPCTSTR ===
Ex: REG_SZ - szValueName = postgraduate1234567890
Ex: REG_SZ - laboratory = HP-LAB at Information School Five
Ex: REG_DWORD - score = 1100
Ex: REG_BINARY - dwData = 5 dwData = 0x12 0x34 0x56 0x78 0x90
=== 删除key 1. LPCTSTR ===
1
=== 关闭注册表 1. LPCTSTR ===
=== 写入注册表 2. CString ===

C:\Users\Snow-Angel\Desktop\RegEdit\x64\Debug\RegEdit.exe (进程 29868)已退出，返回代码为: 0。
按任意键关闭此窗口...
***/