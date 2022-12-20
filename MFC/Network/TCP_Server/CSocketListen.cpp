// CSocketListen.cpp: 实现文件
//

#include "stdafx.h"
#include "TCP_Server.h"
#include "CSocketListen.h"


// CSocketListen

CSocketListen::CSocketListen()
{
}

CSocketListen::~CSocketListen()
{
}


// CSocketListen 成员函数


void CSocketListen::OnAccept(int nErrorCode)
{
	CSocketConnect* pSocketConnect = new CSocketConnect;
	BOOL result = Accept(*pSocketConnect, nullptr, nullptr);
	if (!result)
	{
		AfxMessageBox(_T("CSocket Accept is failed!"));
		delete pSocketConnect;
		return;
	}
	theApp.m_lists.AddTail(pSocketConnect);		//添加客户Socket至链表中

	CSocket::OnAccept(nErrorCode);
}
