// RightFrame.cpp: 实现文件
//

#include "stdafx.h"
#include "MyOutlook.h"
#include "RightFrame.h"


// CRightFrame

IMPLEMENT_DYNCREATE(CRightFrame, CFrameWnd)

CRightFrame::CRightFrame()
{

}

CRightFrame::~CRightFrame()
{
}


BEGIN_MESSAGE_MAP(CRightFrame, CFrameWnd)
END_MESSAGE_MAP()


// CRightFrame 消息处理程序


BOOL CRightFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	m_rightSplitter.CreateStatic(this, 2, 1);
	m_rightSplitter.CreateView(0, 0, RUNTIME_CLASS(CTopView), CSize(0, 200), pContext);
	m_rightSplitter.CreateView(1, 0, RUNTIME_CLASS(CBottomView), CSize(0, 0), pContext);


	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;

}
