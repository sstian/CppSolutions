
// TCP_ClientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "TCP_Client.h"
#include "TCP_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCPClientDlg 对话框



CTCPClientDlg::CTCPClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TCP_CLIENT_DIALOG, pParent)
	, m_port(0)
	, m_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INFO, m_info);
	DDX_Control(pDX, IDC_IPADDRESS, m_address);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_text);
}

BEGIN_MESSAGE_MAP(CTCPClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CTCPClientDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CTCPClientDlg 消息处理程序

BOOL CTCPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化参数
	m_address.SetAddress(10, 112, 175, 138);
	m_port = PORT;
	UpdateData(FALSE);

	AfxSocketInit();
	BOOL result = FALSE;
	result = m_socket.Create(0, SOCK_STREAM, 0);
	if (!result)
	{
		AfxMessageBox(_T("Client: CSocket Create is failed!"));
		return FALSE;
	}
	result = m_socket.Connect(ADDRESS, PORT);
	if (!result)
	{
		AfxMessageBox(_T("Client: CSocket Connect is failed!"));
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTCPClientDlg::OnPaint()
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
HCURSOR CTCPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCPClientDlg::OnBnClickedBtnSend()
{
	UpdateData(TRUE);
	if (m_text.IsEmpty())
	{
		AfxMessageBox(_T("发送文本不能为空！"));
		return;
	}
	int length = m_info.GetWindowTextLength();
	m_info.SetSel(length, -1);

	CString str;
	COleDateTime datetime = COleDateTime::GetCurrentTime();
	str.Format(_T("<-Send to Server [%ws:%d] Time="), ADDRESS, PORT);
	str += datetime.Format() + _T(" :\r\n");
	str += m_text + _T("\r\n");

	m_info.ReplaceSel(str);

	m_socket.OnSend(0);

}

void CTCPClientDlg::OnReceive(CString text)
{
	int length = m_info.GetWindowTextLength();
	m_info.SetSel(length, -1);

	CString str;
	COleDateTime datetime = COleDateTime::GetCurrentTime();
	str.Format(_T("<-Receive from Server [%ws:%d] Time="), ADDRESS, PORT);
	str += datetime.Format() + _T(" :\r\n");
	str += text + _T("\r\n");

	m_info.ReplaceSel(str);

}


void CTCPClientDlg::OnOK()
{
	this->OnBnClickedBtnSend();

	//CDialogEx::OnOK();
}
