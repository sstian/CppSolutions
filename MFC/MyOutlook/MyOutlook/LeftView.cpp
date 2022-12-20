
// LeftView.cpp: CLeftView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyOutlook.h"
#endif

#include "MyOutlookDoc.h"
#include "LeftView.h"

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
END_MESSAGE_MAP()

// CLeftView 构造/析构

CLeftView::CLeftView() noexcept : m_tree(GetTreeCtrl())
{
	theApp.m_pLeftView = this;

}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.dwExStyle = 0;
	return CTreeView::PreCreateWindow(cs);
}


void CLeftView::OnDraw(CDC* /*pDC*/)
{
	CMyOutlookDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 在此处为本机数据添加绘制代码
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
//#define TVS_HASBUTTONS          0x0001
//#define TVS_HASLINES            0x0002
//#define TVS_LINESATROOT         0x0004
//#define TVS_EDITLABELS          0x0008
//#define TVS_DISABLEDRAGDROP     0x0010
//#define TVS_SHOWSELALWAYS       0x0020
	m_tree.ModifyStyle(0, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT
		| TVS_EDITLABELS  | TVS_SHOWSELALWAYS);
	HTREEITEM hItem = m_tree.InsertItem(_T("本地文件夹"));
	m_tree.InsertItem(_T("收件箱"), hItem);
	m_tree.InsertItem(_T("发件箱"), hItem);
	m_tree.InsertItem(_T("已发送邮件"), hItem);
	m_tree.InsertItem(_T("已删除邮件"), hItem);
	m_tree.InsertItem(_T("草稿"), hItem);
	m_tree.Expand(hItem, TVE_EXPAND);
}


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

CMyOutlookDoc* CLeftView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyOutlookDoc)));
	return (CMyOutlookDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView 消息处理程序
