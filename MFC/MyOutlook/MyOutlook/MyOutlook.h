
// MyOutlook.h: MyOutlook 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMyOutlookApp:
// 有关此类的实现，请参阅 MyOutlook.cpp
//
class CLeftView;
class CTopView;
class CBottomView;

class CMyOutlookApp : public CWinApp
{
public:
	CMyOutlookApp() noexcept;

	CLeftView* m_pLeftView;
	CTopView* m_pTopView;
	CBottomView* m_pBottomView;

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyOutlookApp theApp;
