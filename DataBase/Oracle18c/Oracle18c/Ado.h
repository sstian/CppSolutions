// Ado.h: Version 1.1（支持Unicode、支持VS2017和VC6编译环境）
// 支持Access、SQLServer和Oracle三大数据库
//////////////////////////////////////////////////////////////////////

#pragma once
#pragma warning (disable:4146)
#import "C:\\program files\\common files\\system\\ado\\msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")

class CAdo
{
private:
	_ConnectionPtr m_pConn;	// Connection	连接对象指针
	_RecordsetPtr m_pRst;	// Recordset	记录集对象指针
	//_CommandPtr m_pCmd;		// Command		命令对象指针

	CString m_szLastError;

public:
	enum EType { DBT_ACCESS, DBT_SQLSERVER, DBT_ORACLE };

	CAdo();
	virtual ~CAdo();

	void Release() 
	{ 
		m_pConn->Release(); 
	}

	_ConnectionPtr& getConnnectionPtr() { return m_pConn; }

	// 获取错误信息
	CString GetLastError()
	{
		CString str = m_szLastError;
		m_szLastError.Empty();
		return str;
	}
	
	// 连接数据库
	BOOL Connect(EType eType, LPCTSTR szDatabase, LPCTSTR szUser = NULL, LPCTSTR szPass = NULL, LPCTSTR szHost = NULL);

	// 运行SQL
	//方式1.
	BOOL Select(LPCTSTR szSQL);
	//方式2.
	int ExecSQL(LPCTSTR szSQL);
	//int ExecProc(LPCTSTR szSQL);

	// 判断是否到末尾
	BOOL IsEOF();

	// 记录集指针移动
	BOOL MoveFirst();
	BOOL MoveLast();
	BOOL MoveNext();
	BOOL MovePrev();

	// 字段数
	int GetFieldCount();
	// 记录数?
	int GetRecordCount();

	// 字段名，字段类型
	BOOL GetFieldName(long nIndex, CString &szName);
	BOOL GetFieldType(long nIndex, int &nType);

	// 字段值：通过字段名获取
	BOOL GetFieldValue(LPCTSTR szField, COleDateTime &tValue);
	BOOL GetFieldValue(LPCTSTR szField, CString &sValue);
	BOOL GetFieldValue(LPCTSTR szField, int &iValue);
	BOOL GetFieldValue(LPCTSTR szField, double &fValue);
	//int GetFieldMoney(LPCTSTR szField, double &fValue);
	// 字段值：通过索引获取
	BOOL GetFieldByIndex(long nIndex, COleDateTime &tValue);
	BOOL GetFieldByIndex(long nIndex, CString &sValue);
	BOOL GetFieldByIndex(long nIndex, char &cValue);
	BOOL GetFieldByIndex(long nIndex, short &nValue);
	BOOL GetFieldByIndex(long nIndex, int &iValue);
	BOOL GetFieldByIndex(long nIndex, long &lValue);
	BOOL GetFieldByIndex(long nIndex, double &fValue);
	BOOL GetFieldByIndex(long nIndex, BYTE &cbValue);
	BOOL GetFieldByIndex(long nIndex, WORD &wValue);
	BOOL GetFieldByIndex(long nIndex, UINT &iValue);
	BOOL GetFieldByIndex(long nIndex, DWORD &dwValue);
	// 字段值：C语言风格?
	BOOL GetFieldByIndex(long nIndex, TCHAR sValue[], int nSize);

	// ?
	class CProc
	{
	private:
		//enum ParameterDirectionEnum
		//{
		//adParamUnknown = 0,
		//adParamInput = 1,
		//adParamOutput = 2,
		//adParamInputOutput = 3,
		//adParamReturnValue = 4
		//};

		CString m_szLastError;
		_CommandPtr m_pCmd;			// Command		命令对象指针
		//_ConnectionPtr & m_pConn;

	public:
		CProc() { }
		void Release() { delete this; }

		LPCTSTR GetLastError() const { return m_szLastError; }

		BOOL Create(_ConnectionPtr &pConn, LPCTSTR szProc);

		BOOL AddParam(LPCTSTR szVName, long lParam, ParameterDirectionEnum eDir = adParamInput);
		BOOL AddParam(LPCTSTR szVName, LPCTSTR szParam, ParameterDirectionEnum eDir = adParamInput);

		int Exec();

		BOOL GetValue(LPCTSTR szVName, long &lParam);
		BOOL GetValue(LPCTSTR szVName, CString &lParam);
	};

	CProc* CreateProc(LPCTSTR szProc);
	//int ExecProc(CProc* pProc);

};