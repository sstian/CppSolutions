// LinkDBForHX.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

#include <string>
#include <atlstr.h>	//Active Template Library
using namespace ADODB;
using namespace std;

class AdoAccess 
{
public:
	_ConnectionPtr   HX_pConnection;	// 数据库指针
	_RecordsetPtr    HX_pRecordset;		// 记录指针
	_CommandPtr      HX_pCommand;		// 命令指针
	//初始化ADO方式数据库连接
	void OnInitADOConn() {
		::CoInitialize(NULL);
		try
		{
			HX_pConnection.CreateInstance(__uuidof(Connection));//等价于 //HX_pConnection.CreateInstance("ADODB.Connection");
																//此句包含定位你数据库的所需的访问信息
			_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=test.accdb;Persist Security Info=False ";
			//测试//_bstr_t strConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=test.accdb;Persist Security Info=False";//此句包含定位你数据库的所需的访问信息
			//测试//_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Driver = { Microsoft Access Driver(*.mdb, *.accdb) }; DBQ =test.accdb;Persist Security Info=False ";
			//此句包含定位你数据库的所需的访问信息
			//连接master数据库，无密码。
			HX_pConnection->Open(strConnect, "", "", adModeUnknown);	//连接数据库

			cout << "Connect succeed and acquire intelligent pointer!" << endl;
		}
		catch (_com_error e)
		{
			cout << e.Description() << endl;
		}
	}
	//断开连接：关闭记录、命令指针
	void ExitConnect() {
		if (HX_pRecordset != NULL)
			HX_pRecordset->Close();
		HX_pConnection->Close();
		::CoUninitialize();
	}
};

int main()
{
	AdoAccess dataBase;

	//初始化
	dataBase.OnInitADOConn();
	dataBase.HX_pRecordset.CreateInstance("ADODB.Recordset");

	//选择名为table的表格
	dataBase.HX_pRecordset->Open("select *  from [table]",
		dataBase.HX_pConnection.GetInterfacePtr(),
		adOpenDynamic,
		adLockOptimistic,
		adCmdText);

	int i = 0;
	//读取其中的sname字段所有数据，并显示
	while (!dataBase.HX_pRecordset->adoEOF)
	{
		_variant_t var;
		string strValue;
		var = dataBase.HX_pRecordset->GetCollect("sname");
		//其他类似，都是通过HX_pRecordset传递SQL语句执行查找、添加、删除等命令

		if (var.vt != VT_NULL)
			strValue = _com_util::ConvertBSTRToString((_bstr_t)var);

		++i;
		cout << "sname " << i << "  " << strValue << endl;

		dataBase.HX_pRecordset->MoveNext();
	}

	//卸载com组件
	dataBase.ExitConnect();
	int xxxx = 0;
	cout << "Input a number to over:\n";
	cin >> xxxx;
	return 0;
}

