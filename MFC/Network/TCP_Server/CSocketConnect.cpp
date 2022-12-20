// CSocketConnect.cpp: 实现文件
//

#include "stdafx.h"
#include "TCP_Server.h"
#include "CSocketConnect.h"


// CSocketConnect

CSocketConnect::CSocketConnect()
{
	
}

CSocketConnect::~CSocketConnect()
{
}


// CSocketConnect 成员函数


void CSocketConnect::OnSend(int nErrorCode)
{
	// 我也是醉了，发送字符串还得是char*，哎~
	CString text = ((CTCPServerDlg*)AfxGetMainWnd())->m_text;
	if (!text.IsEmpty())
	{
		char buf[BUFFER_SIZE];
		memset(buf, 0, BUFFER_SIZE);
		USES_CONVERSION;
		strcpy_s(buf, W2A(text));
		int len = this->Send(buf, sizeof(buf), 0);
		if (len <= 0)
		{
			POSITION pos = theApp.m_lists.Find(this);
			if (pos)
				theApp.m_lists.RemoveAt(pos);
			return;

		}
	}

	CSocket::OnSend(nErrorCode);
}


void CSocketConnect::OnReceive(int nErrorCode)
{
	CString address;	//连接客户端地址
	UINT port;		//连接客户端端口
	this->GetPeerName(address, port);

	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);
	int recv = this->Receive(buf, BUFFER_SIZE, 0);
	if (recv < 0)
	{
		memset(buf, 0, BUFFER_SIZE);

		POSITION pos = theApp.m_lists.Find(this);
		if(pos)
			theApp.m_lists.RemoveAt(pos);
		return;
	}
	
	CTCPServerDlg* pDlg = (CTCPServerDlg*)AfxGetMainWnd();
	pDlg->OnReceive(CString(buf), address, port);

	CSocket::OnReceive(nErrorCode);
}
