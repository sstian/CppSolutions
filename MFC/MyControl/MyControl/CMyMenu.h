#pragma once
#include <afxwin.h>
class CMyMenu :
	public CMenu
{
public:
	CMyMenu();
	virtual ~CMyMenu();

	// 菜单项属性：包括分隔符
	struct SItem
	{
		HICON icon;
		TCHAR text[30];
		int height;
	};
	CMap<DWORD, DWORD, SItem, SItem> m_map;

	// 自绘函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	BOOL AppendMenu(UINT nFlags, UINT_PTR nIDNewItem = 0,
		LPCTSTR lpszNewItem = NULL, HICON hIcon = NULL);
};

