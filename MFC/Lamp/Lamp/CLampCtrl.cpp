#include "stdafx.h"
#include "CLampCtrl.h"


CLampCtrl::CLampCtrl()
{
	m_coText = GetSysColor(COLOR_WINDOWTEXT);
	m_coBack = GetSysColor(COLOR_3DFACE);
	m_nLeft2 = 0;
}


CLampCtrl::~CLampCtrl()
{
}

BOOL CLampCtrl::Create(CString& szText, CRect& rect, CWnd* pParent, UINT nID)
{
	m_szText = szText;
	return CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParent, nID);
}

BOOL CLampCtrl::CreateEx(DWORD dwExStyle , CString & szText, CRect & rect, CWnd * pParent, UINT nID)
{
	m_szText = szText;
	return CWnd::CreateEx(dwExStyle, NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParent, nID);
}

void CLampCtrl::SetFont(CFont * pFont)
{
	if (!pFont)
		return;
	LOGFONT logfont;
	pFont->GetLogFont(&logfont);
	m_font.CreateFontIndirectW(&logfont);
}

BEGIN_MESSAGE_MAP(CLampCtrl, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()

int CLampCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(rect);
	m_nLeft = rect.right;
	m_mdc.Create(rect.Width(), rect.Height());	//创建空白
	this->Start();

	return 0;
}

void CLampCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect2;
	GetClientRect(rect2);
	//CClientDC cdc(this);
	m_mdc.SetTextColor(m_coText);
	//cdc.SetBkColor(m_coBack);
	m_mdc.SetBkMode(TRANSPARENT);
	m_mdc.FillSolidRect(rect2, m_coBack);
	if (m_font.GetSafeHandle())
		m_mdc.SelectObject(&m_font);
	CSize size = m_mdc.GetOutputTextExtent(m_szText);
	//InvalidateRect(rect2);										//解决文字重影				
	//UpdateWindow();												//
	//cdc.TextOutW(m_nLeft, rect2.Height() - size.cy, m_szText);

	//// 单串
	//rect2.left = m_nLeft;
	//cdc.DrawText(m_szText, rect2, DT_VCENTER | DT_SINGLELINE);
	//m_nLeft -= 1;
	//if (m_nLeft + size.cx <= 0)
	//	m_nLeft = rect2.right;

	// 两串首尾
	// rect2.right == rect2.Width(); because rect2.left == 0;
	rect2.left = m_nLeft;
	m_nLeft -= 1;
	m_mdc.DrawText(m_szText, rect2, DT_VCENTER | DT_SINGLELINE);
	if (m_nLeft2 > 0)
	{
		rect2.left = m_nLeft2;
		m_nLeft2 -= 1;
		m_mdc.DrawText(m_szText, rect2, DT_VCENTER | DT_SINGLELINE);
	}
	dc.BitBlt(0, 0, m_mdc.GetWidth(), m_mdc.GetHeight(), &m_mdc, 0, 0, SRCCOPY);

	int right = m_nLeft + size.cx;
	if (right <= 0)
	{
		m_nLeft = m_nLeft2;
		m_nLeft2 = 0;
	}
	else if (right < rect2.Width() / 2 && !m_nLeft2)
		m_nLeft2 = rect2.right;
}

void CLampCtrl::OnTimer(UINT_PTR nIDEvent)
{
	//在OnPaint()里绘图
	Invalidate(TRUE);

	CWnd::OnTimer(nIDEvent);
}


