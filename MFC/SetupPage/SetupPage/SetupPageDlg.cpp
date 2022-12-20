
// SetupPageDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SetupPage.h"
#include "SetupPageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSetupPageDlg 对话框



CSetupPageDlg::CSetupPageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETUPPAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_index = 0;
}

void CSetupPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetupPageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BACK, &CSetupPageDlg::OnBnClickedBack)
	ON_BN_CLICKED(IDOK, &CSetupPageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSetupPageDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetupPageDlg 消息处理程序

BOOL CSetupPageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化参数
	m_page1.Create(IDD_PAGE1, this);
	m_page2.Create(IDD_PAGE2, this);
	m_page3.Create(IDD_PAGE3, this);
	// 调整位置
	CRect rect, rt;
	GetClientRect(rect);
	GetDlgItem(IDOK)->GetWindowRect(rt);
	ScreenToClient(rt);						//将窗口坐标转换为客户区坐标
	rect.bottom = rt.top - 3;
	m_page1.MoveWindow(rect);
	m_page2.MoveWindow(rect);
	m_page3.MoveWindow(rect);

	m_page1.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BACK)->EnableWindow(m_index);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSetupPageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSetupPageDlg::OnPaint()
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
HCURSOR CSetupPageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSetupPageDlg::ShowPage()
{
	for (int i = 0; i < PAGE_COUNT; i++)
		m_pages[i]->ShowWindow(i == m_index ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BACK)->EnableWindow(m_index);
	SetDlgItemText(IDOK, m_index == PAGE_COUNT - 2 ? _T("下一步(&F)") : _T("完成(&F)"));

}

void CSetupPageDlg::OnBnClickedBack()
{
	if (m_index > 0)
		m_index--;
	this->ShowPage();

}


void CSetupPageDlg::OnBnClickedOk()
{
	if (m_index < PAGE_COUNT - 1)
		m_index++;
	this->ShowPage();

	//CDialogEx::OnOK();
}


void CSetupPageDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
