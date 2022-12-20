// 2020.05.02 20:58
// CListCtrl虚拟列表技术
// 1. CListCtrl属性：Owner Data: True, View: Report
// 2. 显示数据行数 CListCtrl::SetItemCount(_In_ int nItems)
// 3. 响应消息：
// LVN_GETDISPINFO 控件请求某个数据
// LVN_ODFINDITEM  查找某个数据
// LVN_ODCACHEHINT 缓冲某一部分数据
// 4. 自己设置复选框状态


// VirtualList.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CVirtualListApp:
// 有关此类的实现，请参阅 VirtualList.cpp
//

class CVirtualListApp : public CWinApp
{
public:
	CVirtualListApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CVirtualListApp theApp;
