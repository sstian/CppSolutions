
// MyPaintView.cpp: CMyPaintView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyPaint.h"
#endif

#include "MyPaintDoc.h"
#include "MyPaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPaintView

IMPLEMENT_DYNCREATE(CMyPaintView, CScrollView)

BEGIN_MESSAGE_MAP(CMyPaintView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_ARROW, &CMyPaintView::OnDrawArrow)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ARROW, &CMyPaintView::OnUpdateDrawArrow)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CMyPaintView::OnDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &CMyPaintView::OnUpdateDrawEllipse)
	ON_COMMAND(ID_DRAW_LINE, &CMyPaintView::OnDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CMyPaintView::OnUpdateDrawLine)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CMyPaintView::OnDrawRectangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECTANGLE, &CMyPaintView::OnUpdateDrawRectangle)
	ON_COMMAND(ID_DRAW_PENCIL, &CMyPaintView::OnDrawPencil)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PENCIL, &CMyPaintView::OnUpdateDrawPencil)
	ON_COMMAND(ID_DRAW_TEXT, &CMyPaintView::OnDrawText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_TEXT, &CMyPaintView::OnUpdateDrawText)
	ON_COMMAND(ID_DRAW_FRONT, &CMyPaintView::OnDrawFront)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FRONT, &CMyPaintView::OnUpdateDrawFront)
	ON_COMMAND(ID_DRAW_BACK, &CMyPaintView::OnDrawBack)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BACK, &CMyPaintView::OnUpdateDrawBack)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CMyPaintView 构造/析构


CMyPaintView::CMyPaintView() noexcept
{
	m_index = ID_DRAW_ARROW;
	m_cursors[CURSOR_HAND] = AfxGetApp()->LoadStandardCursor(IDC_HAND);
	m_cursors[CURSOR_CROSS] = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	m_cursors[CURSOR_PENCIL] = AfxGetApp()->LoadCursor(IDC_PENCIL);
	m_cursors[CURSOR_IBEAM] = AfxGetApp()->LoadStandardCursor(IDC_IBEAM);

}

CMyPaintView::~CMyPaintView()
{
	int size = (int)m_layers.GetSize();
	for (int index = 0; index < size; index++)
	{
		delete m_layers.GetAt(index);
	}
	m_layers.RemoveAll();
}

BOOL CMyPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CMyPaintView 绘图

void CMyPaintView::SelectLayer(UINT nFlags, CPoint point)
{
	int size = (int)m_layers.GetSize();
	for (int index = 0; index < size; index++)
		m_layers.GetAt(index)->SelectLayer(nFlags, point);
	Invalidate(TRUE);
}

void CMyPaintView::OnDraw(CDC* pDC)
{
	CMyPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 绘制图形
	int size = (int)m_layers.GetSize();
	for (int index = 0; index < size; index++)
	{
		m_layers.GetAt(index)->OnDraw(pDC);
	}
}

void CMyPaintView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMyPaintView 打印

BOOL CMyPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMyPaintView 诊断

#ifdef _DEBUG
void CMyPaintView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMyPaintView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMyPaintDoc* CMyPaintView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPaintDoc)));
	return (CMyPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyPaintView 消息处理程序


void CMyPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (ID_DRAW_ARROW == m_index)
	{
		this->SelectLayer(nFlags, point);
		return;
	}

	if (m_index > ID_DRAW_ARROW && m_index <= ID_DRAW_TEXT)
	{
		CLayer* pLayer = nullptr;
		switch (m_index)
		{
		case ID_DRAW_LINE:
			pLayer = new CLine;
			break;
		case ID_DRAW_RECTANGLE:
			pLayer = new CRectangle;
			break;
		case ID_DRAW_ELLIPSE:
			pLayer = new CEllipse;
			break;
		case ID_DRAW_PENCIL:
			pLayer = new CPencil;
			break;
		default:
			break;
		}
		
		if (pLayer)
		{
			pLayer->m_clFront = theApp.m_clFront;
			pLayer->m_clBack = theApp.m_clBack;

			pLayer->OnLButtonDown(nFlags, point);
			m_layers.Add(pLayer);
		}
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMyPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (ID_DRAW_ARROW == m_index)
		return;

	int size = (int)m_layers.GetSize();
	if (size <= 0)
		return;

	m_layers.GetAt(size - 1)->OnLButtonUp(nFlags, point);

	Invalidate(FALSE);

	CScrollView::OnLButtonUp(nFlags, point);
}


void CMyPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (ID_DRAW_ARROW == m_index)
		return;

	int size = (int)m_layers.GetSize();
	if (size <= 0)
		return;

	if (m_index > ID_DRAW_ARROW && m_index <= ID_DRAW_TEXT)
	{
		CClientDC dc(this);
		m_layers.GetAt(size - 1)->OnMouseMove(nFlags, point, &dc);
	}
	Invalidate(FALSE);

	CScrollView::OnMouseMove(nFlags, point);
}


void CMyPaintView::OnDrawArrow()
{
	m_index = ID_DRAW_ARROW;
}


void CMyPaintView::OnUpdateDrawArrow(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(ID_DRAW_ARROW == m_index);
}


void CMyPaintView::OnDrawEllipse()
{
	m_index = ID_DRAW_ELLIPSE;
}


void CMyPaintView::OnUpdateDrawEllipse(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(ID_DRAW_ELLIPSE == m_index);
}


void CMyPaintView::OnDrawLine()
{
	m_index = ID_DRAW_LINE;
}


void CMyPaintView::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(ID_DRAW_LINE == m_index);
}


void CMyPaintView::OnDrawRectangle()
{
	m_index = ID_DRAW_RECTANGLE;
}


void CMyPaintView::OnUpdateDrawRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(ID_DRAW_RECTANGLE == m_index);
}


void CMyPaintView::OnDrawPencil()
{
	m_index = ID_DRAW_PENCIL;
}


void CMyPaintView::OnUpdateDrawPencil(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(ID_DRAW_PENCIL == m_index);
}


void CMyPaintView::OnDrawText()
{
	m_index = ID_DRAW_TEXT;
}


void CMyPaintView::OnUpdateDrawText(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(ID_DRAW_TEXT == m_index);
}


void CMyPaintView::OnDrawFront()
{
	CColorDialog dialog(theApp.m_clFront);
	if (dialog.DoModal() == IDCANCEL)
		return;
	theApp.m_clFront = dialog.GetColor();

}


void CMyPaintView::OnUpdateDrawFront(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMyPaintView::OnDrawBack()
{
	CColorDialog dialog(theApp.m_clBack);
	if (dialog.DoModal() == IDCANCEL)
		return;
	theApp.m_clBack = dialog.GetColor();
}


void CMyPaintView::OnUpdateDrawBack(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

// 设置光标
BOOL CMyPaintView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	switch (m_index)
	{
	case ID_DRAW_ARROW:
		SetCursor(m_cursors[CURSOR_HAND]);
		break;

	case ID_DRAW_LINE:
	case ID_DRAW_RECTANGLE:
	case ID_DRAW_ELLIPSE:
		SetCursor(m_cursors[CURSOR_CROSS]);
		break;

	case ID_DRAW_PENCIL:
		SetCursor(m_cursors[CURSOR_PENCIL]);
		break;

	case ID_DRAW_TEXT:
		SetCursor(m_cursors[CURSOR_IBEAM]);
		break;
	default:
		break;
	}
	return TRUE;

	//return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}
