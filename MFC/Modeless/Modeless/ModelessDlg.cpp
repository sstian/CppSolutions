
// ModelessDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Modeless.h"
#include "ModelessDlg.h"
//#include "CChatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CModelessDlg 对话框



CModelessDlg::CModelessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODELESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CModelessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CModelessDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CHAT, &CModelessDlg::OnBnClickedBtnChat)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CModelessDlg::OnBnClickedBtnConnect)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_CREATE, &CModelessDlg::OnBnClickedBtnCreate)
	ON_BN_CLICKED(IDC_BTN_VISIBLE, &CModelessDlg::OnBnClickedBtnVisible)
END_MESSAGE_MAP()


// CModelessDlg 消息处理程序

BOOL CModelessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CModelessDlg::OnPaint()
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
HCURSOR CModelessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CModelessDlg::OnBnClickedBtnChat()
{
	//// 单例模式
	//if (!m_chatdlg.m_hWnd)
	//	m_chatdlg.Create(IDD_CHAT_DIALOG);
	//m_chatdlg.ShowWindow(SW_SHOW);

	// 多例模式
	CChatDlg* pdlg = new CChatDlg;
	pdlg->Create(IDD_CHAT_DIALOG, GetDesktopWindow());
	//属性：Visible: True - 指定对话框最初可见
}


void CModelessDlg::OnBnClickedBtnConnect()
{
	//// 方法1.
	////1.1
	//AfxGetApp()->DoWaitCursor(1);	//出现等待光标
	////1.2
	////CWinApp* pApp = AfxGetApp();
	////pApp->DoWaitCursor(1);
	////1.3
	////theApp.DoWaitCursor(1);
	//Sleep(3000);
	//AfxGetApp()->DoWaitCursor(0);	//清除等待光标

	// 方法2.
	CWaitCursor wait;	//构造时显示等待光标，析构时清除等待光标
	CWnd* pwnd = GetDlgItem(IDC_BTN_CONNECT);
	pwnd->EnableWindow(FALSE);
	Sleep(3000);
	pwnd->EnableWindow(TRUE);
	//wait.Restore();
}


void CModelessDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

}


void CModelessDlg::OnClose()
{
	// 动画窗口
	AnimateWindow(300, AW_HIDE | AW_HOR_POSITIVE | AW_SLIDE);

	CDialogEx::OnClose();
}

void CModelessDlg::OnBnClickedBtnCreate()
{
	if(!m_create)	//operator HWND
		m_create.Create(_T("Button"), _T("OK"), WS_CHILD | WS_VISIBLE, CRect(200, 200, 250, 250), this, IDOK);	//GetDesktopWindow()

	CWnd* pWnd = GetDlgItem(IDC_BTN_VISIBLE);
	//HWND hWnd = pWnd->GetSafeHwnd();
	//pWnd->IsWindowVisible() ? pWnd->ShowWindow(SW_HIDE) : pWnd->ShowWindow(SW_SHOW);
	pWnd->ShowWindow(pWnd->IsWindowVisible() ? SW_HIDE : SW_SHOW);
	
	//HWND hwnd = ::GetDlgItem(m_hWnd, IDC_BTN_VISIBLE);
	//CWnd* pwnd = CWnd::FromHandle(hwnd);
	//pwnd->SetWindowTextW(_T("Handle"));

}

void CModelessDlg::OnBnClickedBtnVisible()
{
	if (m_create.m_hWnd)
		m_create.DestroyWindow();
}

//// AnimateWindow() Commands
//#define AW_HOR_POSITIVE             0x00000001
//#define AW_HOR_NEGATIVE             0x00000002
//#define AW_VER_POSITIVE             0x00000004
//#define AW_VER_NEGATIVE             0x00000008
//#define AW_CENTER                   0x00000010
//#define AW_HIDE                     0x00010000
//#define AW_ACTIVATE                 0x00020000
//#define AW_SLIDE                    0x00040000
//#define AW_BLEND                    0x00080000

////Window Styles
//#define WS_OVERLAPPED       0x00000000L
//#define WS_POPUP            0x80000000L
//#define WS_CHILD            0x40000000L
//#define WS_MINIMIZE         0x20000000L
//#define WS_VISIBLE          0x10000000L
//#define WS_DISABLED         0x08000000L
//#define WS_CLIPSIBLINGS     0x04000000L
//#define WS_CLIPCHILDREN     0x02000000L
//#define WS_MAXIMIZE         0x01000000L
//#define WS_CAPTION          0x00C00000L    //WS_BORDER | WS_DLGFRAME
//#define WS_BORDER           0x00800000L
//#define WS_DLGFRAME         0x00400000L
//#define WS_VSCROLL          0x00200000L
//#define WS_HSCROLL          0x00100000L
//#define WS_SYSMENU          0x00080000L
//#define WS_THICKFRAME       0x00040000L
//#define WS_GROUP            0x00020000L
//#define WS_TABSTOP          0x00010000L
//#define WS_MINIMIZEBOX      0x00020000L
//#define WS_MAXIMIZEBOX      0x00010000L
//#define WS_TILED            WS_OVERLAPPED
//#define WS_ICONIC           WS_MINIMIZE
//#define WS_SIZEBOX          WS_THICKFRAME
//#define WS_TILEDWINDOW      WS_OVERLAPPEDWINDOW




