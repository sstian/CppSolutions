
// MainFrm.cpp: CMainFrame 类的实现
//

#include "stdafx.h"
#include "MyControl.h"
//#include "CAddrBar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnDropToolBar)
	ON_COMMAND(IDOK, OnOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	IDS_STATUS_CLOCK,		// 添加时钟显示，通过WM_TIMER触发
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 工具栏
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	// 状态栏
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	//m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(IDS_STATUS_CLOCK), 
	//	IDS_STATUS_CLOCK, SBPS_POPOUT, 150);	//似乎效果没有哎
	// 设置状态栏触发定时器
	SetTimer(CLOCK, 1000, nullptr);

	// 下拉列表
	CToolBarCtrl& toolbar = m_wndToolBar.GetToolBarCtrl();
	toolbar.SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	m_wndToolBar.SetButtonStyle(9, TBSTYLE_DROPDOWN | TBSTYLE_AUTOSIZE);
	//m_wndToolBar.SetButtonStyle(2, BTNS_WHOLEDROPDOWN | TBSTYLE_AUTOSIZE);

	// 地址栏
	// ！需要更改对话框属性：Style: Child
	m_addrbar.Create(this, IDD_ADDR_BAR, CBRS_ALIGN_TOP, 8912);
	m_addrbar.EnableDocking(CBRS_ALIGN_ANY);


	// 自定义控制栏-工具箱
	//// 方法一：m_wndToolBox.LoadToolBar(IDR_TOOLBOX)
	//if (!m_wndToolBox.CreateEx(this, TBSTYLE_FLAT, 
	//	WS_CHILD | WS_VISIBLE |
	//	CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBox.LoadToolBar(IDR_TOOLBOX))
	//{
	//	TRACE0("未能创建工具栏\n");
	//	return -1;      // 未能创建
	//}

	// 方法二：m_wndToolBox.SetBitmap(bmp)
	if (!m_wndToolBox.CreateEx(this, TBSTYLE_FLAT,
		WS_CHILD | WS_VISIBLE |
		CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED))	//CBRS_SIZE_DYNAMIC
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	static CBitmap bmp;
	bmp.LoadBitmap(IDB_TOOLBOX);
	m_wndToolBox.SetBitmap(bmp);
	UINT ids[] = 
	{
		ID_TOOL_CUT, 
		ID_TOOL_COPY, 
		ID_TOOL_PASTE,
	};
	m_wndToolBox.SetButtons(ids, sizeof(ids) / sizeof(ids[0]));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//设置工具箱文字
	m_wndToolBox.SetWindowText(_T("工具箱"));
	m_wndToolBox.SetButtonText(0, _T("剪切"));
	m_wndToolBox.SetButtonText(1, _T("复制"));
	m_wndToolBox.SetButtonText(2, _T("粘贴"));
	CRect rect;
	m_wndToolBox.GetItemRect(0, rect);
	m_wndToolBox.SetSizes(rect.Size(), CSize(16, 15));

	m_wndToolBox.EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBox);
	GetWindowRect(rect);
	rect.OffsetRect(10, 80);
	FloatControlBar(&m_wndToolBox, rect.TopLeft());


	return 0;
}
//#define TBSTYLE_BUTTON          0x0000  // obsolete; use BTNS_BUTTON instead
//#define TBSTYLE_SEP             0x0001  // obsolete; use BTNS_SEP instead
//#define TBSTYLE_CHECK           0x0002  // obsolete; use BTNS_CHECK instead
//#define TBSTYLE_GROUP           0x0004  // obsolete; use BTNS_GROUP instead
//#define TBSTYLE_CHECKGROUP      (TBSTYLE_GROUP | TBSTYLE_CHECK)     // obsolete; use BTNS_CHECKGROUP instead
//#define TBSTYLE_DROPDOWN        0x0008  // obsolete; use BTNS_DROPDOWN instead
//#define TBSTYLE_AUTOSIZE        0x0010  // obsolete; use BTNS_AUTOSIZE instead
//#define TBSTYLE_NOPREFIX        0x0020  // obsolete; use BTNS_NOPREFIX instead
//
//#define TBSTYLE_TOOLTIPS        0x0100
//#define TBSTYLE_WRAPABLE        0x0200
//#define TBSTYLE_ALTDRAG         0x0400
//#define TBSTYLE_FLAT            0x0800
//#define TBSTYLE_LIST            0x1000
//#define TBSTYLE_CUSTOMERASE     0x2000
//#define TBSTYLE_REGISTERDROP    0x4000
//#define TBSTYLE_TRANSPARENT     0x8000
//#define TBSTYLE_EX_DRAWDDARROWS 0x00000001
//
//// ControlBar styles
//#define CBRS_ALIGN_LEFT     0x1000L
//#define CBRS_ALIGN_TOP      0x2000L
//#define CBRS_ALIGN_RIGHT    0x4000L
//#define CBRS_ALIGN_BOTTOM   0x8000L
//#define CBRS_ALIGN_ANY      0xF000L
//
//#define CBRS_BORDER_LEFT    0x0100L
//#define CBRS_BORDER_TOP     0x0200L
//#define CBRS_BORDER_RIGHT   0x0400L
//#define CBRS_BORDER_BOTTOM  0x0800L
//#define CBRS_BORDER_ANY     0x0F00L
//
//#define CBRS_TOOLTIPS       0x0010L
//#define CBRS_FLYBY          0x0020L
//#define CBRS_FLOAT_MULTI    0x0040L
//#define CBRS_BORDER_3D      0x0080L
//#define CBRS_HIDE_INPLACE   0x0008L
//#define CBRS_SIZE_DYNAMIC   0x0004L
//#define CBRS_SIZE_FIXED     0x0002L
//#define CBRS_FLOATING       0x0001L
//
//#define CBRS_GRIPPER        0x00400000L

//// Styles for status bar panes
//#define SBPS_NORMAL     0x0000
//#define SBPS_NOBORDERS  SBT_NOBORDERS
//#define SBPS_POPOUT     SBT_POPOUT
//#define SBPS_OWNERDRAW  SBT_OWNERDRAW
//#define SBPS_DISABLED   0x04000000
//#define SBPS_STRETCH    0x08000000  // stretch to fill status bar

// 反射消息
void CMainFrame::OnDropToolBar(NMHDR * pNMHDR, LRESULT * pResult)
{
	*pResult = 0;
	LPNMTOOLBAR p = reinterpret_cast<LPNMTOOLBAR>(pNMHDR);
	CPoint point;
	CRect rect;
	switch (p->iItem)
	{
	case ID_APP_ABOUT:
	{
		m_wndToolBar.GetWindowRect(rect);
		point.x = rect.left;
		point.y = rect.bottom;
		m_wndToolBar.GetItemRect(9, rect);
		point.x += rect.left + 6;

		CMenu menu;
		menu.LoadMenu(IDR_POPMENU);
		menu.GetSubMenu(0)->TrackPopupMenu(0, point.x, point.y, this);
	}
		break;
	default:
		break;
	}

}

void CMainFrame::OnOk()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	COleDateTime datetime = COleDateTime::GetCurrentTime();
	
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(IDS_STATUS_CLOCK),
		datetime.Format());

	CFrameWnd::OnTimer(nIDEvent);
}


BOOL CMainFrame::DestroyWindow()
{
	// 摧毁定时器
	KillTimer(CLOCK);

	return CFrameWnd::DestroyWindow();
}
