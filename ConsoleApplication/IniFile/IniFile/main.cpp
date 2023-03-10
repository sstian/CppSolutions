// IniFile.cpp: 定义控制台应用程序的入口点。
//
/* 2018.03.07 9:00
	C++ ini(initializing file)配置文件读写类的封装
*/
#include "stdafx.h"

int main()
{
	cout << "start test...." << endl << endl;
	CIniFile file;
	file.SetFileName(_T("./profile-tian.ini"));
	LPCTSTR section = _T("Infomation");
	file.SetProfileString(section, _T("Name"), _T("Sears Saint Tian"));
	file.SetProfileInteger(section, _T("Age"), 24);
	file.SetProfileBool(section, _T("Marriage"), false);
	file.SetProfileDouble(section, _T("Height"), 1.1234567890123);

	file.SetProfileString(_T("Hobbies"), _T("Watch"), _T("Animation"));
	file.SetProfileInteger(_T("Hobbies"), _T("TimeLength"), 365 * 12);

	file.DeleteKey(_T("Hobbies"), _T("Watch"));
	file.SetProfileString(_T("Hobbies"), _T("Watch"), _T("Animation"));
	file.DeleteSection(_T("Hobbies"));

	CString value;
	
	file.GetProfileStrings(section, _T("Name"), value);
	int age = file.GetProfileInteger(section, _T("Age"));
	bool marriage = file.GetProfileBool(section, _T("Marriage"));
	double height = file.GetProfileDouble(section, _T("Height"));
	
	wcout << "Name = " << value.GetString() << endl
		<< "Age = " << age << endl
		<< "Marriage = " << (marriage ? "True" : "False") << endl
		<< "height = " << height << endl << endl;

	file.SetProfileString(_T("Hobbies"), _T("Weight"), _T("60.1234567890"));	//实数用字符串存储，避免精度误差！
	file.SetProfileString(_T("Hobbies"), _T("Watch"), _T("Animation"));
	file.SetProfileInteger(_T("Hobbies"), _T("Deepth"), -12);
	
	CString weight;
	file.GetProfileStrings(_T("Hobbies"), _T("Weight"), weight);
	wcout << "Weight = " << weight.GetBuffer() << endl
		<< "Deepth = " << file.GetProfileInteger(_T("Hobbies"), _T("Deepth")) << endl << endl;

	CStringArray strArray;
	file.GetProfileSectionNames(strArray);
	for (int i = 0; i < strArray.GetCount(); i++)
	{
		wcout << strArray.GetAt(i).GetString() << endl;
	}


	// 改进版测试
	cout << "\nupdate2: start test...." << endl << endl;
	CIniFile file2;
	file2.SetFileName(_T("./profile2.ini"));

	file2.SetSectionName(_T("Infomation"));
	file2.SetProfileString(_T("Name"), _T("Sears Saint Tian"));
	file2.SetProfileInteger( _T("Age"), 24);
	file2.SetProfileBool(_T("Marriage"), false);
	file2.SetProfileDouble(_T("Height"), 1.1234567890123);

	CString value2;
	file2.GetProfileStrings(_T("Name"), value2);
	int age2 = file2.GetProfileInteger(_T("Age"));
	bool marriage2 = file2.GetProfileBool( _T("Marriage"));
	double height2 = file2.GetProfileDouble(_T("Height"));
	wcout << "Name = " << value2.GetString() << endl
		<< "Age = " << age2 << endl
		<< "Marriage = " << (marriage2 ? "True" : "False") << endl
		<< "height = " << height2 << endl << endl;


	file2.SetSectionName(_T("Hobbies"));
	file2.SetProfileString(_T("Watch"), _T("Animation"));
	file2.SetProfileInteger(_T("TimeLength"), 365 * 12);
	file2.DeleteKey(_T("Watch"));
	file2.SetProfileString(_T("Watch"), _T("ACG"));
	file2.DeleteSection();

	CStringArray strArray2;
	file2.GetProfileSectionNames(strArray2);
	for (int i = 0; i < strArray2.GetCount(); i++)
	{
		wcout << strArray2.GetAt(i).GetString() << endl;
	}
	
	CMapStringToString strMap;
	file2.GetProfileKeyValues(strMap, _T("Infomation"));
	POSITION pos = strMap.GetStartPosition();
	while (pos)
	{
		CString strKey, strValue;
		strMap.GetNextAssoc(pos, strKey, strValue);
		wcout << strKey.GetString() << _T("=") << strValue.GetString() << endl;
	}



    return 0;
}

/* VS2017 运行结果：
==================================================================================================================
start test....

Name = Sears Saint Tian
Age = 24
Marriage = False
height = 1.12346

Weight = 60.1234567890
Deepth = -12

Infomation
Hobbies

update2: start test....

Name = Sears Saint Tian
Age = 24
Marriage = False
height = 1.12346

Infomation
Hobbies
Marriage=False
Age=24
Name=Sears Saint Tian
Height=1.123457

C:\Users\Snow-Angel\Desktop\IniFile\x64\Debug\IniFile.exe (进程 15664)已退出，返回代码为: 0。
按任意键关闭此窗口...
==================================================================================================================
*/
