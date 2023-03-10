
// MFC-VSView.cpp: CMFCVSView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC-VS.h"
#endif

#include "MFC-VSDoc.h"
#include "MFC-VSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCVSView

IMPLEMENT_DYNCREATE(CMFCVSView, CView)

BEGIN_MESSAGE_MAP(CMFCVSView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCVSView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCVSView 构造/析构

CMFCVSView::CMFCVSView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCVSView::~CMFCVSView()
{
}

BOOL CMFCVSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCVSView 绘图

void CMFCVSView::OnDraw(CDC* /*pDC*/)
{
	CMFCVSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCVSView 打印


void CMFCVSView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCVSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCVSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCVSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCVSView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCVSView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCVSView 诊断

#ifdef _DEBUG
void CMFCVSView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCVSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCVSDoc* CMFCVSView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCVSDoc)));
	return (CMFCVSDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCVSView 消息处理程序
