#include "stdafx.h"
#include "CMyMenu.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
}
//typedef struct tagDRAWITEMSTRUCT {
//	UINT        CtlType;
//	UINT        CtlID;
//	UINT        itemID;
//	UINT        itemAction;
//	UINT        itemState;
//	HWND        hwndItem;
//	HDC         hDC;
//	RECT        rcItem;
//	ULONG_PTR   itemData;
//} DRAWITEMSTRUCT, NEAR *PDRAWITEMSTRUCT, FAR *LPDRAWITEMSTRUCT;

void CMyMenu::DrawItem(LPDRAWITEMSTRUCT lpdis)
{
	CDC* pDC = CDC::FromHandle(lpdis->hDC);
	CRect rect(lpdis->rcItem);

	SItem& it = m_map[lpdis->itemID];
	CString str;
	if (lpdis->itemID)
		str = it.text;
	// 选中状态
	if ((lpdis->itemState & ODS_SELECTED) && (lpdis->itemAction & ODA_SELECT))
	{
		pDC->FillSolidRect(&rect, GetSysColor(COLOR_MENU));
		rect.DeflateRect(1, 1);
		static CPen pen(PS_SOLID, 1, GetSysColor(COLOR_HIGHLIGHT));
		static CBrush brush(RGB(182, 189, 210));
		pDC->SelectObject(pen);
		pDC->SelectObject(brush);
		pDC->Rectangle(rect);
		rect.InflateRect(1, 1);
	}
	else
	{
		pDC->FillSolidRect(&rect, GetSysColor(COLOR_MENU));
		if (rect.Height() == 10)	//分隔栏
		{
			static CPen pen1(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW));
			pDC->SelectObject(&pen1);
			pDC->MoveTo(rect.left + 2, rect.top + 4);
			pDC->LineTo(rect.right - 2, rect.top + 4);
			
			static CPen pen2(PS_SOLID, 1, GetSysColor(COLOR_HIGHLIGHTTEXT));
			pDC->SelectObject(&pen2);
			pDC->MoveTo(rect.left + 2, rect.top + 5);
			pDC->LineTo(rect.right - 2, rect.top + 5);

			return;

		}
	}
	// 绘制图标和文字
	pDC->DrawIcon(rect.left + 3, rect.top + 3, it.icon);
	pDC->SetBkMode(TRANSPARENT);
	rect.left += 22;
	pDC->DrawText(str, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

}

void CMyMenu::MeasureItem(LPMEASUREITEMSTRUCT lpmis)
{
	lpmis->itemWidth = 80;
	lpmis->itemHeight = lpmis->itemID ? 20 : 10;
}

BOOL CMyMenu::AppendMenu(UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem, HICON hIcon)
{
	SItem it = { hIcon };
	if (lpszNewItem)
		_tcscpy_s(it.text, lpszNewItem);
	//if (nFlags & MF_SEPARATOR)
	//	it.height = 10;
	//else
	//	it.height = 20;
	it.height = (nFlags & MF_SEPARATOR) ? 10 : 20;

	m_map[(DWORD)nIDNewItem] = it;

	return CMenu::AppendMenu(nFlags | MF_OWNERDRAW, nIDNewItem, lpszNewItem);
}
