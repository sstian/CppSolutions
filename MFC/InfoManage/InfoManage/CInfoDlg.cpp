// CInfoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "InfoManage.h"
#include "CInfoDlg.h"
#include "afxdialogex.h"


// CInfoDlg 对话框

IMPLEMENT_DYNAMIC(CInfoDlg, CDialogEx)

CInfoDlg::CInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFO, pParent)
	, m_number(_T(""))
	, m_name(_T(""))
	, m_datetime(COleDateTime::GetCurrentTime())
{
	m_title = _T("添加数据");
}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM, m_number);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME, m_datetime);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CInfoDlg 消息处理程序


BOOL CInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// 设置对话框标题
	SetWindowText(m_title);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
