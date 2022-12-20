
// CalculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
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


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorDlg::OnBnClickedButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalculatorDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CCalculatorDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalculatorDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnBnClickedButtonDiv)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorDlg::OnPaint()
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
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::OnBnClickedButtonEqual()
{
	//UINT left  = GetDlgItemInt(IDC_EDIT_LEFT);	// UINT GetDlgItemInt(int nID, BOOL* lpTrans = NULL,BOOL bSigned = TRUE) const;
	//UINT right = GetDlgItemInt(IDC_EDIT_RIGHT);
	//UINT result = left + right;
	//SetDlgItemInt(IDC_EDIT_RESULT, result);	// 	void SetDlgItemInt(int nID, UINT nValue, BOOL bSigned = TRUE);
	CString strLeft, strRight, strResult;	//存放运算符左、右及结果的文本
	CString strOperator;					//四则运算符
	double dLeft, dRight, dResult;			//转换后的数值
	GetDlgItemText(IDC_EDIT_LEFT, strLeft);		//获取文本 int GetDlgItemText(int nID, CString& rString) const;
	GetDlgItemText(IDC_EDIT_RIGHT, strRight);
	dLeft   = _wtof(strLeft.GetBuffer());	//CString转double
	dRight  = _wtof(strRight.GetBuffer());

	GetDlgItemText(IDC_STATIC_OPERATOR, strOperator);
	if ("+" == strOperator)	dResult = dLeft + dRight;
	else if ("-" == strOperator)	dResult = dLeft - dRight;
	else if ("*" == strOperator)	dResult = dLeft * dRight;
	else if ("/" == strOperator)	
		if(0 != dRight) dResult = dLeft / dRight;
		else SetDlgItemText(IDC_EDIT_RESULT, _T("Divided by 0!"));	
	
	strResult.Format(_T("%lf"), dResult);	//double转CString  void CStringT<BaseType, StringTraits>::Format( PCXSTR pszFormat,...);
	SetDlgItemText(IDC_EDIT_RESULT, strResult);	//设置文本 void SetDlgItemText(int nID, LPCTSTR lpszString);	
}


/******************************************************************************
#define FAR                 far
#define NEAR                near
#define CONST               const

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef CONST void far      *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

*******************************************************************************/

void CCalculatorDlg::OnBnClickedButtonAdd()
{
	CString text;
	GetDlgItemText(IDC_BUTTON_ADD, text);
	SetDlgItemText(IDC_STATIC_OPERATOR, text.GetBuffer());
}


void CCalculatorDlg::OnBnClickedButtonSub()
{
	CString text;
	GetDlgItemText(IDC_BUTTON_SUB, text);
	SetDlgItemText(IDC_STATIC_OPERATOR, text.GetBuffer());
}


void CCalculatorDlg::OnBnClickedButtonMul()
{
	CString text;
	GetDlgItemText(IDC_BUTTON_MUL, text);
	SetDlgItemText(IDC_STATIC_OPERATOR, text.GetBuffer());
}


void CCalculatorDlg::OnBnClickedButtonDiv()
{
	CString text;
	GetDlgItemText(IDC_BUTTON_DIV, text);
	SetDlgItemText(IDC_STATIC_OPERATOR, text.GetBuffer());
}
