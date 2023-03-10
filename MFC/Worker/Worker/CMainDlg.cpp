// CMainDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Worker.h"
#include "CMainDlg.h"
#include "afxdialogex.h"


// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_INFO, &CMainDlg::OnBnClickedBtnInfo)
	ON_BN_CLICKED(IDC_BTN_ADMIN, &CMainDlg::OnBnClickedBtnAdmin)
	ON_BN_CLICKED(IDC_BTN_RELOGIN, &CMainDlg::OnBnClickedBtnRelogin)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SAdmin& user = theApp.m_user;

	CString strText = _T("控制面板 - [");
	strText.Insert(7, user.sname);
	strText += !user.nprior ? _T("普通") : _T("高级");
	strText += _T("]");
	SetWindowText(strText);

	if (0 == user.nprior)
		GetDlgItem(IDC_BTN_ADMIN)->EnableWindow(FALSE);	//ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMainDlg::OnBnClickedBtnInfo()
{
	EndDialog(IDC_BTN_INFO);
}


void CMainDlg::OnBnClickedBtnAdmin()
{
	EndDialog(IDC_BTN_ADMIN);
}




void CMainDlg::OnBnClickedBtnRelogin()
{
	EndDialog(IDC_BTN_RELOGIN);
}
