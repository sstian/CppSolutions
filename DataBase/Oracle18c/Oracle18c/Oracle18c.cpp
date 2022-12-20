// 2019.05.15
// VS2017 ADO C++ Connect Oracle Database 18c
// Oracle Database (ODP.NET, 托管驱动程序)
// Oracle18c.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
// ConnectinoString: Provider=OraOLEDB.Oracle.1;Persist Security Info=True;User ID=c##dog;Password=miaomiao;Data Source=localhost:1521/orcl
//
#include "pch.h"
#include <iostream>
#include <locale>
#include "Ado.h"

using namespace std;

void ShowResult(CAdo& ado);

int main()
{
	cout << "*** VS2017 ADO C++ Connect Oracle Database 18c ***" << endl;

	// 定义对象
	CAdo ado;								
	// 连接数据库
	BOOL result = ado.Connect(CAdo::DBT_ORACLE, _T("localhost:1521/orcl"), _T("c##dog"), _T("miaomiao"), _T("localhost"));
	if (!result)
	{
		cout << "Connect oracle database failed!" << endl;
		system("pause");
		return 0;
	}

	// 显示结果
	ShowResult(ado);

	//// 2. 增加 - 运行SQL: INSERT INTO
	//cout << "SQL = INSERT INTO info VALUES (2021, 'Zhao', 'Tianjin')" << endl;
	//ado.Select(_T("INSERT INTO info (id, name, address) VALUES (2021, 'Zhao', 'Tianjin')"));
	//ShowResult(ado);

	//// 3. 修改 - 运行SQL: UPDATE ... SET
	//cout << "SQL = UPDATE info SET name = 'Kang' WHERE name = 'Zhao'" << endl;
	//ado.ExecSQL(_T("UPDATE info SET name = 'Kang' WHERE name = 'Zhao'"));
	//ShowResult(ado);

	//// 4. 删除 - 运行SQL: DELETE FROM
	//cout << "SQL = SELECT * FROM info" << endl;
	//ado.ExecSQL(_T("DELETE FROM info WHERE id = 2021"));
	//ShowResult(ado);


	////// 未知不可期结果
	////const int SIZE = 20;
	////TCHAR tchar[SIZE];
	////ado.GetFieldByIndex(1, tchar, SIZE);
	////wcout.imbue(locale("chs"));
	////wcout << "tchar[] = " << CString(tchar) << endl;
	//////cout << ado.GetRecordCount() << endl;

	//// 析构时释放连接
	////ado.Release();

	return 0;
}

// 显示结果
void ShowResult(CAdo& ado)
{
	// 1. 查询 - 运行SQL: SELECT ... FROM
	cout << "SQL = SELECT * FROM info" << endl;
	//方式1.
	//ado.Select(_T("SELECT * FROM info"));	// 原来最后不用加分号的哎~
	//方式2.
	ado.ExecSQL(_T("SELECT * FROM info"));

	// 字段数
	int count = 0;
	cout << "FieldCount = " << (count = ado.GetFieldCount()) << endl;
	//wcout.imbue(locale("chs"));
	//wcout << ado.GetLastError().GetString() << endl;

	// 字段名
	CString field;
	for (int index = 0; index < count; index++)
	{
		ado.GetFieldName(index, field);
		wcout << field.GetString() << "\t";
	}
	cout << "\n------------------------" << endl;

	//// 字段类型
	//int type;
	//for (int ti = 0; ti < count; ti++)
	//{
	//	ado.GetFieldType(ti, type);
	//	cout << "type " << ti << " = " << type << endl;
	//}
	//// NUMBER -- DataTypeEnum::adVarNumeric = 139
	//// VARCHAR2 -- DataTypeEnum::adVarWChar = 202

	// 记录
	int id;
	CString name;
	CString address;
	ado.MoveFirst();
	while (!ado.IsEOF())
	{
		ado.GetFieldByIndex(0, id);
		ado.GetFieldByIndex(1, name);
		ado.GetFieldByIndex(2, address);
		wcout << id << "\t" << name.GetString() << "\t" << address.GetString() << endl;

		ado.MoveNext();
	}
	cout << endl;
}

/*** 在VS2017中运行结果：
*** VS2017 ADO C++ Connect Oracle Database 18c ***
SQL = SELECT * FROM info
FieldCount = 3
ID      NAME    ADDRESS
------------------------
2017    Tian    Henan
2018    Wang    Shandong
2019    Li      Beijing
2020    Sun     Shanghai

***/