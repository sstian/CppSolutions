
// MyControlView.h: CMyControlView 类的接口
//

#pragma once

class CMyControlDoc;

class CMyControlView : public CView
{
protected: // 仅从序列化创建
	CMyControlView() noexcept;
	DECLARE_DYNCREATE(CMyControlView)

// 特性
public:
	CMyControlDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyControlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnToolCut();
	afx_msg void OnToolCopy();
	afx_msg void OnToolPaste();
	afx_msg void OnViewSmall();
	afx_msg void OnViewIcon();
	afx_msg void OnViewReport();
	afx_msg void OnViewListed();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

#ifndef _DEBUG  // MyControlView.cpp 中的调试版本
inline CMyControlDoc* CMyControlView::GetDocument() const
   { return reinterpret_cast<CMyControlDoc*>(m_pDocument); }
#endif

