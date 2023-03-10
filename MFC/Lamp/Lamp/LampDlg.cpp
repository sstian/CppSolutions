
// LampDlg.cpp: 实现文件
// 

#include "stdafx.h"
#include "Lamp.h"
#include "LampDlg.h"
//#include "CLampCtrl.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLampDlg 对话框



CLampDlg::CLampDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LAMP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLampDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLampDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLampDlg 消息处理程序

BOOL CLampDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 走马灯初始化
	//方法1-1
	CRect rect, rt;
	CWnd* pwnd = GetDlgItem(IDC_STATIC_LAMP);
	GetClientRect(rect);
	pwnd->GetWindowRect(rt);
	ScreenToClient(rt);
	rt.OffsetRect(rect.Width() - rt.left, 0);
	pwnd->MoveWindow(rt);

	//方法2-1
	m_szText = _T("风是穿山过水拂面而来，花是零落成泥常开不败，雪是日出消融檐上落白，月是咫尺天涯千秋万载");
	CRect rect2;
	GetClientRect(rect2);
	m_nLeft = rect2.right;

	SetTimer(TIMER_LAMP, 20, NULL);

	//方法3 自定义控件
	CRect rect3;
	GetClientRect(rect3);
	rect3.bottom = 70;
	//m_lampCtrl.Create(m_szText, rect3, this, 8888);
	m_lampCtrl.CreateEx(WS_EX_STATICEDGE, m_szText, rect3, this, 8888);
	m_lampCtrl.SetTextColor(RGB(255, 0, 0));
	m_lampCtrl.SetBackColor(RGB(0, 255, 255));
	m_lampCtrl.SetFont(GetFont());
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLampDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLampDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLampDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 方法1-2
	CRect rect, rt;
	CWnd* pwnd = GetDlgItem(IDC_STATIC_LAMP);
	GetClientRect(rect);
	pwnd->GetWindowRect(rt);
	ScreenToClient(rt);
	rt.OffsetRect(-5, 0);
	if (rt.right <= 0)
		//rt.OffsetRect(rect.Width() + rt.Width(), 0);
		rt.OffsetRect(rect.Width() - rt.left, 0);
	pwnd->MoveWindow(rt);

	// 方法2-2，存在闪烁，后续用双缓冲内存贴图？
	CRect rect2;
	GetClientRect(rect2);
	CClientDC cdc(this);
	cdc.SetBkColor(GetSysColor(COLOR_3DFACE));
	cdc.SelectObject(GetFont());
	CSize size = cdc.GetOutputTextExtent(m_szText);
	InvalidateRect(rect2);										//解决文字重影				
	UpdateWindow();												//
	cdc.TextOutW(m_nLeft, rect2.Height() - size.cy, m_szText);
	m_nLeft -= 10;
	if (m_nLeft + size.cx <= 0)
		m_nLeft = rect2.right;
	CDialogEx::OnTimer(nIDEvent);
}
//#define COLOR_DESKTOP           COLOR_BACKGROUND
//#define COLOR_3DFACE            COLOR_BTNFACE
//#define COLOR_3DSHADOW          COLOR_BTNSHADOW
//#define COLOR_3DHIGHLIGHT       COLOR_BTNHIGHLIGHT
//#define COLOR_3DHILIGHT         COLOR_BTNHIGHLIGHT
//#define COLOR_BTNHILIGHT        COLOR_BTNHIGHLIGHT
