/*
	2019.04.13 16:15 - 2019.04.14 01:10
	一箭穿心2 ExpressHearts
	代码重构，利用定时器触发，克服Sleep()造成的阻塞状态
完善工作：添加背景音乐，Wave格式，但使得exe文件体积达到几十兆，实际上Release版本生成后有4兆左右
*/
// ExpressHearts.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CExpressHeartsApp:
// 有关此类的实现，请参阅 ExpressHearts.cpp
//

class CExpressHeartsApp : public CWinApp
{
public:
	CExpressHeartsApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CExpressHeartsApp theApp;
