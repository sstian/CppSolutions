// CPage3.cpp: 实现文件
//

#include "stdafx.h"
#include "SetupPage.h"
#include "CPage3.h"
#include "afxdialogex.h"


// CPage3 对话框

IMPLEMENT_DYNAMIC(CPage3, CDialogEx)

CPage3::CPage3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE3, pParent)
{

}

CPage3::~CPage3()
{
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage3, CDialogEx)
END_MESSAGE_MAP()


// CPage3 消息处理程序


void CPage3::OnOK()
{
	GetParent()->SendMessage(WM_COMMAND, IDOK);

	//CDialogEx::OnOK();
}


void CPage3::OnCancel()
{
	GetParent()->SendMessage(WM_COMMAND, IDCANCEL);

	//CDialogEx::OnCancel();
}
