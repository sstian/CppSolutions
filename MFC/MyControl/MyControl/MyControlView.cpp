
// MyControlView.cpp: CMyControlView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyControl.h"
#endif

#include "MyControlDoc.h"
#include "MyControlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyControlView

IMPLEMENT_DYNCREATE(CMyControlView, CView)

BEGIN_MESSAGE_MAP(CMyControlView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_TOOL_CUT, &CMyControlView::OnToolCut)
	ON_COMMAND(ID_TOOL_COPY, &CMyControlView::OnToolCopy)
	ON_COMMAND(ID_TOOL_PASTE, &CMyControlView::OnToolPaste)
	ON_COMMAND(ID_VIEW_SMALL, &CMyControlView::OnViewSmall)
	ON_COMMAND(ID_VIEW_ICON, &CMyControlView::OnViewIcon)
	ON_COMMAND(ID_VIEW_REPORT, &CMyControlView::OnViewReport)
	ON_COMMAND(ID_VIEW_LISTED, &CMyControlView::OnViewListed)
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CMyControlView 构造/析构

CMyControlView::CMyControlView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMyControlView::~CMyControlView()
{
}

BOOL CMyControlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyControlView 绘图

void CMyControlView::OnDraw(CDC* /*pDC*/)
{
	CMyControlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMyControlView 打印

BOOL CMyControlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyControlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyControlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMyControlView 诊断

#ifdef _DEBUG
void CMyControlView::AssertValid() const
{
	CView::AssertValid();
}

void CMyControlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyControlDoc* CMyControlView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyControlDoc)));
	return (CMyControlDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyControlView 消息处理程序


void CMyControlView::OnToolCut()
{
	// TODO: 在此添加命令处理程序代码
}


void CMyControlView::OnToolCopy()
{
	// TODO: 在此添加命令处理程序代码
}


void CMyControlView::OnToolPaste()
{
	// TODO: 在此添加命令处理程序代码
}


void CMyControlView::OnViewSmall()
{
	// TODO: 在此添加命令处理程序代码
}


void CMyControlView::OnViewIcon()
{
	// TODO: 在此添加命令处理程序代码
}


void CMyControlView::OnViewReport()
{
	// TODO: 在此添加命令处理程序代码
}


void CMyControlView::OnViewListed()
{
	// TODO: 在此添加命令处理程序代码
}

// 右键快捷菜单
// 方法一：
void CMyControlView::OnRButtonDown(UINT nFlags, CPoint point)
{
	//CMenu menu;
	//menu.LoadMenu(IDR_POPMENU);
	//CMenu* pMenu = menu.GetSubMenu(0);
	//ClientToScreen(&point);
	//pMenu->TrackPopupMenu(0, point.x, point.y, this);

	CView::OnRButtonDown(nFlags, point);
}

// 方法二：
void CMyControlView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//CMenu menu;
	//menu.LoadMenu(IDR_POPMENU);
	//CMenu* pMenu = menu.GetSubMenu(0);
	//pMenu->TrackPopupMenu(0, point.x, point.y, AfxGetMainWnd());

	//菜单自绘
	CArray<HICON> icons;
	HICON hIcon = nullptr;
	for (int index = 0; index < 3; index++)
	{
		hIcon = theApp.LoadIcon(IDI_ICON1 + index);
		//hIcon = (HICON)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1 + index),
		//	IMAGE_ICON, 16, 16, 0);
		icons.Add(hIcon);
	}
	CMyMenu mymenu;
	mymenu.CreatePopupMenu();	//创建菜单列
	mymenu.AppendMenu(0, ID_VIEW_SMALL, _T("魏无羡"), icons[0]);
	mymenu.AppendMenu(MF_SEPARATOR);
	mymenu.AppendMenu(0, ID_VIEW_ICON, _T("蓝忘机"), icons[1]);
	mymenu.AppendMenu(0, ID_VIEW_REPORT, _T("江晚吟"), icons[2]);
	mymenu.TrackPopupMenu(0, point.x, point.y, AfxGetMainWnd());


}
