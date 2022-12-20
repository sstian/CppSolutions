// CSocketClient.cpp: 实现文件
//

#include "stdafx.h"
#include "TCP_Client.h"
#include "CSocketClient.h"


// CSocketClient

CSocketClient::CSocketClient()
{
}

CSocketClient::~CSocketClient()
{
}


// CSocketClient 成员函数



void CSocketClient::OnSend(int nErrorCode)
{
	// 我也是醉了，发送字符串还得是char*，哎~
	CString text = ((CTCPClientDlg*)AfxGetMainWnd())->m_text;
	if (!text.IsEmpty())
	{
		char buf[BUFFER_SIZE];
		memset(buf, 0, BUFFER_SIZE);
		USES_CONVERSION;
		strcpy_s(buf, W2A(text));
		this->Send(buf, sizeof(buf), 0);

	}

	CSocket::OnSend(nErrorCode);
}


void CSocketClient::OnReceive(int nErrorCode)
{
	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);
	int recv = this->Receive(buf, BUFFER_SIZE, 0);

	CTCPClientDlg* pDlg = (CTCPClientDlg*)AfxGetMainWnd();
	pDlg->OnReceive(CString(buf));


	CSocket::OnReceive(nErrorCode);
}


