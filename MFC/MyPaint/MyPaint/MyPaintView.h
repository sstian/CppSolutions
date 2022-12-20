
// MyPaintView.h: CMyPaintView 类的接口
//

#pragma once


class CMyPaintView : public CScrollView
{
private:
	int m_index;					//图层索引
	CArray<CLayer*> m_layers;		//图层集合

	enum ECursor 
	{ 
		CURSOR_HAND = 0, 
		CURSOR_CROSS = 1, 
		CURSOR_PENCIL = 2, 
		CURSOR_IBEAM = 3,
		
		CURSOR_COUNT = 5
	};
	HCURSOR m_cursors[CURSOR_COUNT];

protected: // 仅从序列化创建
	CMyPaintView() noexcept;
	DECLARE_DYNCREATE(CMyPaintView)

// 特性
public:
	CMyPaintDoc* GetDocument() const;

// 操作
public:
	// 选择图层
	void SelectLayer(UINT nFlags, CPoint point);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawArrow();
	afx_msg void OnUpdateDrawArrow(CCmdUI *pCmdUI);
	afx_msg void OnDrawEllipse();
	afx_msg void OnUpdateDrawEllipse(CCmdUI *pCmdUI);
	afx_msg void OnDrawLine();
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnDrawRectangle();
	afx_msg void OnUpdateDrawRectangle(CCmdUI *pCmdUI);
	afx_msg void OnDrawPencil();
	afx_msg void OnUpdateDrawPencil(CCmdUI *pCmdUI);
	afx_msg void OnDrawText();
	afx_msg void OnUpdateDrawText(CCmdUI *pCmdUI);
	afx_msg void OnDrawFront();
	afx_msg void OnUpdateDrawFront(CCmdUI *pCmdUI);
	afx_msg void OnDrawBack();
	afx_msg void OnUpdateDrawBack(CCmdUI *pCmdUI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

#ifndef _DEBUG  // MyPaintView.cpp 中的调试版本
inline CMyPaintDoc* CMyPaintView::GetDocument() const
   { return reinterpret_cast<CMyPaintDoc*>(m_pDocument); }
#endif

