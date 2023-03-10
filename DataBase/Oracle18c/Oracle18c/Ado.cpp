// Ado.cpp: Version 1.1（支持Unicode、支持VS2017和VC6编译环境）
//支持Unicode、支持Access、SQLServer和Oracle三大数据库
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "Ado.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdo::CAdo()
{
	::OleInitialize(NULL);
}

CAdo::~CAdo()
{
	this->Release();
}

BOOL CAdo::Connect(EType eType, LPCTSTR szDatabase, LPCTSTR szUser, LPCTSTR szPass, LPCTSTR szHost)
{
	CString str;
	switch (eType)
	{
	case DBT_ACCESS:
	{
		str.Format(TEXT("Provider=MSDASQL.1;Persist Security Info=False;Data Source=MS Access Database;Initial Catalog=%s;Password=%s"),
			szDatabase,szPass);
	}
	break;
	case DBT_SQLSERVER:
	{
		str = TEXT("Driver=SQL Server;Server=");
		str += szHost;
		str += TEXT(";Database=");
		str += szDatabase;
		str += TEXT(";UID=");
		str += szUser;
		str += TEXT(";PWD=");
		str += szPass;
	}
	break;
	// Provider=OraOLEDB.Oracle.1;Persist Security Info=True;User ID=c##dog;Password=miaomiao;Data Source=localhost:1521/orcl
	case DBT_ORACLE:
		str = TEXT("Provider=OraOLEDB.Oracle.1;Persist Security Info=True;User ID=");
		str += szUser;
		str += TEXT(";Password=");
		str += szPass;
		str += TEXT(";Data Source=");
		str += szDatabase;
		break;
	}

	try
	{
		m_pConn.CreateInstance(__uuidof(Connection));
		m_pConn->Open(_bstr_t(str), szUser, szPass, adModeUnknown);	//连接数据库

	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		TRACE(m_szLastError+"\n");
		return FALSE;
	}
	return TRUE;
}

BOOL CAdo::Select(LPCTSTR szSQL)
{
	try
	{
		if (m_pRst)
			m_pRst->Close();
		m_pRst.CreateInstance(__uuidof(Recordset));
		//m_pRst ->Open(szSQL,m_pConn.GetInterfacePtr(),adOpenForwardOnly,adLockReadOnly,adCmdText);
		m_pRst->Open(szSQL, m_pConn.GetInterfacePtr(), adOpenStatic, adLockReadOnly, adCmdText);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}

int CAdo::ExecSQL(LPCTSTR szSql)
{
	_variant_t vRet;	//改变的行数
	try
	{
		m_pRst = m_pConn->Execute(szSql, &vRet, adCmdText);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return e.Error();
	}

	return (long)vRet;
}

BOOL CAdo::IsEOF()
{
	try
	{
		if (m_pRst->GetadoEOF())
			return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
	}
	return FALSE;
}

BOOL CAdo::MoveFirst()
{
	try
	{
		return m_pRst->MoveFirst() == S_OK;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::MoveLast()
{
	try
	{
		return m_pRst->MoveLast() == S_OK;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::MoveNext()
{
	try
	{
		return m_pRst->MoveNext() == S_OK;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::MovePrev()
{
	try
	{
		return m_pRst->MovePrevious() == S_OK;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

int CAdo::GetFieldCount()
{
	try
	{
		return m_pRst->Fields->Count;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return -1;
	}
	return -1;
}

int CAdo::GetRecordCount()
{
	try
	{
		return m_pRst->GetRecordCount();
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldName(long nIndex, CString &szName)
{
	try
	{
		szName = (LPCTSTR)m_pRst->Fields->Item[nIndex]->Name;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdo::GetFieldType(long nIndex, int &nType)
{
	try
	{
		nType = m_pRst->Fields->Item[nIndex]->Type;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdo::GetFieldValue(LPCTSTR szField, COleDateTime &tValue)
{
	try
	{
		tValue = (DATE)m_pRst->GetCollect(szField);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldValue(LPCTSTR szField, CString &sValue)
{
	try
	{
		sValue = m_pRst->GetCollect(szField).bstrVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldValue(LPCTSTR szField, int &iValue)
{
	try
	{
		iValue = (long)m_pRst->GetCollect(szField);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdo::GetFieldValue(LPCTSTR szField, double & fValue)
{
	try
	{
		fValue = (double)m_pRst->GetCollect(szField);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;

}

BOOL CAdo::GetFieldByIndex(long nIndex, COleDateTime &tValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			tValue = 0.0;
		else
			tValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldByIndex(long nIndex, CString &szValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			szValue.Empty();
		else
			szValue = v.bstrVal;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdo::GetFieldByIndex(long nIndex, char &cValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			cValue = 0;
		else
			cValue = v.bVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

}

BOOL CAdo::GetFieldByIndex(long nIndex, short &nValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			nValue = 0;
		else
			nValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldByIndex(long nIndex, int &iValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		iValue = (long)v;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdo::GetFieldByIndex(long nIndex, long &lValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			lValue = 0;
		else
			lValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldByIndex(long nIndex, double &fValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			fValue = 0.0;
		else
			fValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldByIndex(long nIndex, BYTE &cbValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			cbValue = 0;
		else
			cbValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldByIndex(long nIndex, WORD &wValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			wValue = 0;
		else
			wValue = v.iVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldByIndex(long nIndex, UINT &iValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			iValue = 0;
		else
			iValue = v.lVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdo::GetFieldByIndex(long nIndex, DWORD &dwValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			dwValue = 0;
		else
			dwValue = v.lVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

//LONG lVal;
//BYTE bVal;
//SHORT iVal;
//FLOAT fltVal;
//DOUBLE dblVal;

BOOL CAdo::GetFieldByIndex(long nIndex, TCHAR sValue[], int nSize)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
		{
			*sValue = 0;
			return TRUE;
		}
		CString str = v.bstrVal;
		LPCTSTR p = str;
		int i = 0;
		while (--nSize && (*sValue = *p) != 0)
		{
			sValue++;
			p++;
		}
		if (!nSize)
			*sValue = 0;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}


BOOL CAdo::CProc::Create(_ConnectionPtr &pConn, LPCTSTR szProc)
{
	try
	{
		m_pCmd.CreateInstance(__uuidof(Command));
		m_pCmd->ActiveConnection = pConn;
		m_pCmd->CommandType = adCmdStoredProc;
		m_pCmd->CommandText = _bstr_t(szProc);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdo::CProc::AddParam(LPCTSTR szVName, long lParam, ParameterDirectionEnum eDir)
{
	if (m_pCmd == NULL)
		return FALSE;
	try
	{
		_ParameterPtr pParam = m_pCmd->CreateParameter(szVName, adInteger, eDir, sizeof(long), lParam);
		m_pCmd->Parameters->Append(pParam);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}
BOOL CAdo::CProc::AddParam(LPCTSTR szVName, LPCTSTR szParam, ParameterDirectionEnum eDir)
{
	if (m_pCmd == NULL)
		return FALSE;
	try
	{
		_ParameterPtr pParam = m_pCmd->CreateParameter(_bstr_t(szVName), adVarChar, eDir, lstrlen(szParam) + 2, szParam);
		m_pCmd->Parameters->Append(pParam);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}

int CAdo::CProc::Exec()
{
	try
	{
		m_pCmd->Execute(NULL, NULL, adCmdStoredProc);

	}
	catch (_com_error& e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return e.Error();
	}
	return 0;
}

BOOL CAdo::CProc::GetValue(LPCTSTR szVName, long &lParam)
{
	try
	{
		_variant_t var = m_pCmd->Parameters->GetItem(_bstr_t(szVName))->GetValue();
		lParam = var;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdo::CProc::GetValue(LPCTSTR szVName, CString &szParam)
{
	try
	{
		_bstr_t bstr = (_bstr_t)(m_pCmd->Parameters->GetItem(_bstr_t(szVName))->GetValue());
		szParam = (LPCTSTR)bstr;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

CAdo::CProc* CAdo::CreateProc(LPCTSTR szProc)
{
	if (m_pConn == NULL)return FALSE;
	CProc* pProc = new CProc;
	if (pProc->Create(m_pConn, szProc))
		return pProc;
	delete pProc;
	return NULL;
}

//int CAdo::ExecProc(CProc* pProc)
//{
//	try
//	{
//		if(FAILED(m_pCmd.CreateInstance(__uuidof(Command))))
//		{
//			return -1;
//		}
//
//		m_pCmd->ActiveConnection   =   m_pConn;
//		m_pCmd->CommandType   =   adCmdStoredProc;
//		m_pCmd->CommandText = L"P_LOGIN";
//
//		_ParameterPtr pParam = m_pCmd->CreateParameter(_bstr_t("v_empno"), adInteger, adParamInput ,4,7839L);
//		m_pCmd ->Parameters ->Append(pParam);
//
//		pParam = m_pCmd->CreateParameter(_bstr_t("v_pass"), adVarChar, adParamInput ,20, "123456");
//		m_pCmd ->Parameters ->Append(pParam);
//
//		pParam = m_pCmd->CreateParameter(_bstr_t("v_return"), adInteger, adParamReturnValue, 0);
//		m_pCmd ->Parameters ->Append(pParam);
//
//		m_pCmd->Execute(NULL, NULL, adCmdStoredProc);
//		long nRet = m_pCmd->Parameters->GetItem("v_return")->GetValue();
//	}
//	catch(_com_error &e)
//	{
//		m_szLastError =(LPCTSTR) e.Description();
//		return e.Error();
//	}
//	return 0;
//}

/**
HRESULT CreateInstance(const CLSID& rclsid, IUnknown* pOuter = NULL, DWORD dwClsContext = CLSCTX_ALL) throw();
HRESULT Connection15::Open ( _bstr_t ConnectionString, _bstr_t UserID, _bstr_t Password, long Options );
_RecordsetPtr Connection15::Execute ( _bstr_t CommandText, VARIANT * RecordsAffected, long Options );

enum __declspec(uuid("00000521-0000-0010-8000-00aa006d2ea4"))
ConnectModeEnum
{
	adModeUnknown = 0,
	adModeRead = 1,
	adModeWrite = 2,
	adModeReadWrite = 3,
	adModeShareDenyRead = 4,
	adModeShareDenyWrite = 8,
	adModeShareExclusive = 12,
	adModeShareDenyNone = 16,
	adModeRecursive = 4194304
};

enum __declspec(uuid("0000052e-0000-0010-8000-00aa006d2ea4"))
CommandTypeEnum
{
	adCmdUnspecified = -1,
	adCmdUnknown = 8,
	adCmdText = 1,
	adCmdTable = 2,
	adCmdStoredProc = 4,
	adCmdFile = 256,
	adCmdTableDirect = 512
};
**/