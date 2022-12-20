// 2019.04.05
// MFC Socket TCP Server+Client
// TCP_Server.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

//const CString ADDRESS = _T("10.112.175.138");
//int PORT = 8086;
constexpr auto ADDRESS = _T("10.112.175.138");
constexpr int PORT = 8086;

constexpr int BUFFER_SIZE = 1024;

// CTCPServerApp:
// 有关此类的实现，请参阅 TCP_Server.cpp
//

class CTCPServerApp : public CWinApp
{
public:
	CList<CSocketConnect*> m_lists;	//连接客户Socket

public:
	CTCPServerApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CTCPServerApp theApp;
