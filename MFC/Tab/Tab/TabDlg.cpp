
// TabDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Tab.h"
#include "TabDlg.h"
//#include "CFlatTab.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTabDlg 对话框

int CTabDlg::m_tabwidth = 24;

CTabDlg::CTabDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTabDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
//	ON_WM_NCPAINT()
END_MESSAGE_MAP()


// CTabDlg 消息处理程序

BOOL CTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CRect rect;
	GetClientRect(rect);
	rect.top = rect.bottom - m_tabwidth;
	rect.bottom++;
	m_flattab.Create(rect, this, 9958);
	m_flattab.SetFont(GetFont());
	m_flattab.InsertItem(0, _T("Build"));
	m_flattab.InsertItem(1, _T("Debug"));
	m_flattab.InsertItem(2, _T("Open in files 1"));
	m_flattab.InsertItem(3, _T("Results"));
	m_flattab.InsertItem(4, _T("SQL Debugging"));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTabDlg::OnPaint()
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
HCURSOR CTabDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTabDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_flattab)
		m_flattab.MoveWindow(0, cy - m_tabwidth, cx, m_tabwidth);
}


BOOL CTabDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	rect.bottom -= m_tabwidth;
	pDC->FillSolidRect(rect, GetSysColor(COLOR_3DFACE));

	//return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


//void CTabDlg::OnNcPaint()
//{
//	// TODO: 在此处添加消息处理程序代码
//	// 不为绘图消息调用 CDialogEx::OnNcPaint()
//}
