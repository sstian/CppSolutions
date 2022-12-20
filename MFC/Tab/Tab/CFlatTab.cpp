// CFlatTab.cpp: 实现文件
//

#include "stdafx.h"
#include "Tab.h"
#include "CFlatTab.h"


// CFlatTab

IMPLEMENT_DYNAMIC(CFlatTab, CWnd)

CFlatTab::CFlatTab()
{
	m_index = 0;
}

CFlatTab::~CFlatTab()
{
}

BOOL CFlatTab::Create(CRect rect, CWnd * pParent, UINT id)
{
	return CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParent, id);
}

void CFlatTab::SetFont(CFont * pFont)
{
	if (!pFont)
		return;
	if (m_font.GetSafeHandle())
		m_font.DeleteObject();

	LOGFONT lf;
	pFont->GetLogFont(&lf);
	m_font.CreateFontIndirectW(&lf);
}

BEGIN_MESSAGE_MAP(CFlatTab, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()



// CFlatTab 消息处理程序





void CFlatTab::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// 改为双缓冲贴图，以减小闪烁
	CBrush brush(GetSysColor(COLOR_3DFACE));
	m_mdc.SelectObject(brush);
	m_mdc.SelectObject(m_font);
	m_mdc.SetBkMode(TRANSPARENT);

	CRect rect, textrect, selrect;	//客户区域，文本区域，选中矩形
	GetClientRect(rect);
	textrect = rect;
	m_mdc.Rectangle(rect);
	textrect.bottom--;

	int size = this->GetSize();
	int left = 0;
	for (int index = 0; index < size; index++)
	{
		CSize textsize = dc.GetTextExtent(m_attr.GetAt(index));
		textrect.left = left;
		textrect.right = left + textsize.cx + rect.Height() * 2;	//预留个矩形框做梯形处理
		m_rect.Add(textrect);	//保存矩形区域
		if (m_index != index)
		{
			POINT ps[] = {
				{textrect.left, textrect.top}, {textrect.right, textrect.top},
				{textrect.right - rect.Height(), textrect.bottom}, {textrect.left + rect.Height(), textrect.bottom}
			};
			m_mdc.Polygon(ps, 4);
			//dc.Rectangle(textrect);
			m_mdc.DrawText(m_attr.GetAt(index), textrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else
			selrect = textrect;
		
		left = textrect.right - rect.Height();
	}
	m_mdc.SelectStockObject(WHITE_BRUSH);
	LOGFONT lf;
	m_font.GetLogFont(&lf);
	lf.lfWeight = 700;
	CFont font;						//临时字体对象
	font.CreateFontIndirectW(&lf);
	m_mdc.SelectObject(font);
	POINT psel[] = {
		{selrect.left, selrect.top}, {selrect.right, selrect.top},
		{selrect.right - rect.Height(), selrect.bottom}, {selrect.left + rect.Height(), selrect.bottom}
	};
	m_mdc.Polygon(psel, 4);
	m_mdc.DrawText(m_attr.GetAt(m_index), selrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_mdc, 0, 0, SRCCOPY);
}

/***
// Stock Logical Objects
#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define NULL_BRUSH          5
#define HOLLOW_BRUSH        NULL_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define OEM_FIXED_FONT      10
#define ANSI_FIXED_FONT     11
#define ANSI_VAR_FONT       12
#define SYSTEM_FONT         13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE     15
#define SYSTEM_FIXED_FONT   16
***/

void CFlatTab::OnLButtonDown(UINT nFlags, CPoint point)
{
	for (int index = 0; index < this->GetSize(); index++)
	{
		if (m_rect.GetAt(index).PtInRect(point))
			if (m_index != index)
			{
				m_index = index;
				Invalidate();
				break;
			}
	}

	CWnd::OnLButtonDown(nFlags, point);
}


int CFlatTab::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建DC
	CRect rect;
	GetClientRect(rect);
	m_mdc.Create(rect.Width(), rect.Height());

	return 0;
}


void CFlatTab::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (!m_mdc.GetSafeHdc())
		return;
	if (m_mdc.GetWidth() >= cx && m_mdc.GetHeight() >= cy)
		return;
	// 重建DC
	m_mdc.DeleteDC();
	m_mdc.Create(cx, cy);
}


BOOL CFlatTab::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CFlatTab::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnNcPaint()
}
