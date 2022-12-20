// CAddrBar.cpp: 实现文件
//

#include "stdafx.h"
#include "MyControl.h"
#include "CAddrBar.h"
#include "afxdialogex.h"


// CAddrBar 对话框

IMPLEMENT_DYNAMIC(CAddrBar, CDialogBar)

CAddrBar::CAddrBar(CWnd* pParent /*=nullptr*/)
	//: CDialogBar(IDD_ADDR_BAR, pParent)
{

}

CAddrBar::~CAddrBar()
{
}

void CAddrBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddrBar, CDialogBar)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CAddrBar 消息处理程序

// 调整控件大小
void CAddrBar::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	CWnd* pBtn = GetDlgItem(IDOK);
	CWnd* pCombo = GetDlgItem(IDC_COMBO_ADDR);
	if (!pBtn || !pCombo)
		return;

	CRect rect, rt, rt2;
	GetClientRect(rect);
	pBtn->GetWindowRect(rt);
	ScreenToClient(rt);
	rt.OffsetRect(rect.right - rt.right, 0);
	pBtn->MoveWindow(rt);

	pCombo->GetWindowRect(rt2);
	ScreenToClient(rt2);
	rt2.right = rt.left - 2;
	pCombo->MoveWindow(rt2);

}
