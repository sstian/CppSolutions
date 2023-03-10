// MyDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "MyDialog.h"
#include "Resource.h"
#include "afxdialogex.h"


// MyDialog 对话框

IMPLEMENT_DYNAMIC(MyDialog, CDialogEx)

MyDialog::MyDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY, pParent)
{

}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialogEx)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// MyDialog 消息处理程序


BOOL MyDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// 抓不着的按钮
	if (IDC_BTN_RUN == pWnd->GetDlgCtrlID())
	{
		CRect rect;
		pWnd->GetWindowRect(rect);			//控件区域
		this->ScreenToClient(rect);			//屏幕转为客户区，坐标系转换
		rect.OffsetRect(rect.Width(), 0);	//矩形区域移动

		CRect rectClient;
		GetClientRect(rectClient);			//客户区域
		if (rect.right > rectClient.right)	//判断是否出界
			rect.OffsetRect(-rect.left, 0);
		pWnd->MoveWindow(rect);				//控件移动
	}
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
//int GetDlgCtrlID() const;
//operator CRect::LPRECT() throw();
//operator CRect::LPCRECT() const throw();
