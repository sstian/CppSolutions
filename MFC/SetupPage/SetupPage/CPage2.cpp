// CPage2.cpp: 实现文件
//

#include "stdafx.h"
#include "SetupPage.h"
#include "CPage2.h"
#include "afxdialogex.h"


// CPage2 对话框

IMPLEMENT_DYNAMIC(CPage2, CDialogEx)

CPage2::CPage2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE2, pParent)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage2, CDialogEx)
END_MESSAGE_MAP()


// CPage2 消息处理程序


void CPage2::OnOK()
{
	GetParent()->SendMessage(WM_COMMAND, IDOK);

	//CDialogEx::OnOK();
}


void CPage2::OnCancel()
{
	GetParent()->SendMessage(WM_COMMAND, IDCANCEL);

	//CDialogEx::OnCancel();
}
