// 2019.04.01 
// 员工信息管理系统 SDI, 
// CFile + struct -> CArchive << >> -> CDocument.Serialize
// InfoManage.h: InfoManage 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CInfoManageApp:
// 有关此类的实现，请参阅 InfoManage.cpp
//

class CInfoManageApp : public CWinApp
{
public:
	CInfoManageApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CInfoManageApp theApp;
