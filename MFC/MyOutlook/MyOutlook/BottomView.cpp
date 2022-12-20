// BottomView.cpp: 实现文件
//

#include "stdafx.h"
#include "MyOutlook.h"
#include "BottomView.h"


// CBottomView

IMPLEMENT_DYNCREATE(CBottomView, CHtmlView)

CBottomView::CBottomView()
{
	theApp.m_pBottomView = this;
}

CBottomView::~CBottomView()
{
}

void CBottomView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBottomView, CHtmlView)
END_MESSAGE_MAP()


// CBottomView 诊断

#ifdef _DEBUG
void CBottomView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBottomView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CBottomView 消息处理程序


BOOL CBottomView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle = 0;

	return CHtmlView::PreCreateWindow(cs);
}
