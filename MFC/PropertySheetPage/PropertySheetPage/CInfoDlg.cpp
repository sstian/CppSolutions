// CInfoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "PropertySheetPage.h"
#include "CInfoDlg.h"
#include "afxdialogex.h"


// CInfoDlg 对话框

IMPLEMENT_DYNAMIC(CInfoDlg, CDialogEx)

CInfoDlg::CInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFO_DIALOG, pParent)
{
	
}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()


// CInfoDlg 消息处理程序




void CInfoDlg::MakeText()
{
	SInfo* m_pInfo = (SInfo*)m_pList->GetItemData(m_item);
	m_text.Empty();
	m_text = _T("帐号：") + m_pInfo->account + _T("\r\n");
	m_text += _T("昵称：") + m_pInfo->nickname + _T("\r\n");
	m_text += CString("性别：") + (m_pInfo->sex ? _T("女") : _T("男")) + _T("\r\n");
	m_text += _T("生日：") + m_pInfo->birth.Format() + _T("\r\n");
	m_text += _T("血型：") + m_pInfo->blood + _T("\r\n");
	m_text += _T("籍贯：") + m_pInfo->native + _T("\r\n");
	m_text += _T("联系电话：") + m_pInfo->phone + _T("\r\n");
	m_text += _T("联系地址：") + m_pInfo->address + _T("\r\n");
	m_text += _T("电子邮件：") + m_pInfo->email + _T("\r\n");


}

int CInfoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// 窗口样式
	//this->MakeText();
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	SetTimer(1, 500, nullptr);

	return 0;
}


void CInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	CPoint point;
	GetCursorPos(&point);
	m_pList->ScreenToClient(&point);		//坐标转换
	int item = m_pList->HitTest(point);
	if (item != m_item)
		ShowWindow(SW_HIDE);

	TRACE("item = %d", item);

	CDialogEx::OnTimer(nIDEvent);
}


void CInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	dc.SelectObject(GetFont());

	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, GetSysColor(COLOR_INFOBK));

	//dc.TextOut(2, 2, m_text);
	dc.DrawText(m_text, rect, DT_LEFT);
}


BOOL CInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CInfoDlg::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnNcPaint()
}
