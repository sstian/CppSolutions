
// LeftView.cpp: CLeftView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyExplorer.h"
#endif

#include "MainFrm.h"
#include "MyExplorerDoc.h"
#include "LeftView.h"
#include "RightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTreeView::OnFilePrintPreview)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CLeftView::OnTvnSelchanged)
END_MESSAGE_MAP()

// CLeftView 构造/析构

CLeftView::CLeftView()  noexcept : m_tree(GetTreeCtrl())
{
	// TODO: 在此处添加构造代码
	
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}


void CLeftView::OnDraw(CDC* /*pDC*/)
{
	CMyExplorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 在此处为本机数据添加绘制代码
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	// 初始化参数
	//static int i = 0; 
	//if (i++)
	//	return;
	m_tree.ModifyStyle(0, TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_EDITLABELS | TVS_SHOWSELALWAYS);
	HTREEITEM hItem = m_tree.InsertItem(_T("计算机"));

	//m_tree.InsertItem(_T("C:"), hItem);
	//m_tree.InsertItem(_T("D:"), hItem);
	//m_tree.InsertItem(_T("E:"), hItem);

	TCHAR str[256];
	GetLogicalDriveStrings(sizeof(str), str);
	LPTSTR p = str;
	CString cstr;
	while (*p)
	{
		cstr = p;
		int length = cstr.GetLength();
		if (length < 1)
			break;
		if (cstr.GetAt(length - 1) == _T('\\'))
			cstr = cstr.Left(length - 1);
		m_tree.InsertItem(cstr, hItem);
		p += length + 1;
	}
	m_tree.Expand(hItem, TVE_EXPAND);



}
//#define TVE_COLLAPSE            0x0001
//#define TVE_EXPAND              0x0002
//#define TVE_TOGGLE              0x0003
//#define TVE_EXPANDPARTIAL       0x4000
//#define TVE_COLLAPSERESET       0x8000

//// begin_r_commctrl
//#define TVS_HASBUTTONS          0x0001
//#define TVS_HASLINES            0x0002
//#define TVS_LINESATROOT         0x0004
//#define TVS_EDITLABELS          0x0008
//#define TVS_DISABLEDRAGDROP     0x0010
//#define TVS_SHOWSELALWAYS       0x0020
//#define TVS_RTLREADING          0x0040
//
//#define TVS_NOTOOLTIPS          0x0080
//#define TVS_CHECKBOXES          0x0100
//#define TVS_TRACKSELECT         0x0200
//#define TVS_SINGLEEXPAND        0x0400
//#define TVS_INFOTIP             0x0800
//#define TVS_FULLROWSELECT       0x1000
//#define TVS_NOSCROLL            0x2000
//#define TVS_NONEVENHEIGHT       0x4000
//#define TVS_NOHSCROLL           0x8000  // TVS_NOSCROLL overrides this


// CLeftView 打印

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CLeftView 诊断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMyExplorerDoc* CLeftView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyExplorerDoc)));
	return (CMyExplorerDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView 消息处理程序


void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW p = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	HTREEITEM hItem = p->itemNew.hItem;
	CString text = m_tree.GetItemText(hItem);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SetWindowText(text);
	if (m_tree.GetRootItem() != hItem)
		pFrame->m_pRightView->Refresh(text);


	*pResult = 0;
}
