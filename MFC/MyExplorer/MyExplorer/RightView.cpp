// RightView.cpp: 实现文件
//

#include "stdafx.h"
#include "MyExplorer.h"
#include "MyExplorerDoc.h"
#include "RightView.h"


// CRightView

IMPLEMENT_DYNCREATE(CRightView, CListView)

CRightView::CRightView() : m_list(GetListCtrl())
{

}

CRightView::~CRightView()
{
}

void CRightView::Refresh(CString szPath)
{
	if (szPath.IsEmpty())
		return;
	m_list.DeleteAllItems();

	CFileFind ff;
	BOOL result = ff.FindFile(szPath + _T("\\*.*"));
	int item = 0;
	while (result)
	{
		result = ff.FindNextFile();
		if (ff.IsHidden())
			continue;

		m_list.InsertItem(item, ff.GetFileName());

		if (ff.IsDirectory())
			m_list.SetItemText(item, 2, _T("文件夹"));
		else
		{
			int length = (int)ff.GetLength();
			CString str;
			str.Format(_T("%d Bytes"), length);
			m_list.SetItemText(item, 1, str);
			
			CString name = ff.GetFileName();
			int ext = name.ReverseFind(_T('.'));
			CString extend = name.Right(name.GetLength() - ext - 1);			
			m_list.SetItemText(item, 2, extend + _T(" 文件"));
		}

		FILETIME filetime;
		ff.GetLastWriteTime(&filetime);
		COleDateTime time(filetime);
		m_list.SetItemText(item, 3, time.Format(_T("%Y-%m-%d %H:%M:%S")));

		// ...
	}
}

BEGIN_MESSAGE_MAP(CRightView, CListView)
END_MESSAGE_MAP()


// CRightView 诊断

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView 消息处理程序


void CRightView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	m_list.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS);
	m_list.InsertColumn(0, _T("名称"), 0, 150);
	m_list.InsertColumn(1, _T("大小"), 0, 150);
	m_list.InsertColumn(2, _T("类型"), 0, 150);
	m_list.InsertColumn(3, _T("修改时间"), 0, 200);


}
