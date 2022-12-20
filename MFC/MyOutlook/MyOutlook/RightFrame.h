#pragma once


// CRightFrame 框架

class CRightFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CRightFrame)
public:
	CSplitterWnd m_rightSplitter;

protected:
	CRightFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CRightFrame();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


