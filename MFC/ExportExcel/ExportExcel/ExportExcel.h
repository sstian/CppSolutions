
// ExportExcel.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CExportExcelApp:
// 有关此类的实现，请参阅 ExportExcel.cpp
//

class CExportExcelApp : public CWinApp
{
public:
	CExportExcelApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CExportExcelApp theApp;
