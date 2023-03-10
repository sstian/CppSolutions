
// Worker.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#define WORKER_SIZE		(7+1)	//SWorker变量个数	
#define PRORITY_SIZE	(2+1)	//权限数量

// CWorkerApp:
// 有关此类的实现，请参阅 Worker.cpp
//

class CWorkerApp : public CWinApp
{
public:
	CWorkerApp();

public:
	SAdmin m_user;		//登录的用户
public:
	// Worker
	static CString m_szWorker[WORKER_SIZE];		//作为List Control的标题栏
	// CAdminDlg
	static CString m_szPrority[];	//权限字符串	//PRORITY_SIZE
	enum EPrority
	{
		Normal = 0,
		Advance
	};
	// CInputDlg
	static LPCTSTR m_szSex[];
	enum ESex
	{
		Female = 0,
		Male
	};
	static CString m_szGraduate[];
	static LPCTSTR m_szLanguage[];
	static DWORD m_dwordLangs[];
	enum ELang
	{
		English = 0,
		Japanese,
		Korean, 
		French,
		Russian
	};

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CWorkerApp theApp;
