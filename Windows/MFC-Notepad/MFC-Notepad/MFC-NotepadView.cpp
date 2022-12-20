
// MFC-NotepadView.cpp: CMFCNotepadView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC-Notepad.h"
#endif

#include "MFC-NotepadDoc.h"
#include "MFC-NotepadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCNotepadView

IMPLEMENT_DYNCREATE(CMFCNotepadView, CView)

BEGIN_MESSAGE_MAP(CMFCNotepadView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCNotepadView 构造/析构

CMFCNotepadView::CMFCNotepadView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCNotepadView::~CMFCNotepadView()
{
}

BOOL CMFCNotepadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCNotepadView 绘图

void CMFCNotepadView::OnDraw(CDC* /*pDC*/)
{
	CMFCNotepadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCNotepadView 打印

BOOL CMFCNotepadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCNotepadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCNotepadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCNotepadView 诊断

#ifdef _DEBUG
void CMFCNotepadView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCNotepadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCNotepadDoc* CMFCNotepadView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCNotepadDoc)));
	return (CMFCNotepadDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCNotepadView 消息处理程序
