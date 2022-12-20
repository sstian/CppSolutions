
// LeftView.h: CLeftView 类的接口
//

#pragma once

class CMyExplorerDoc;

class CLeftView : public CTreeView
{
protected: // 仅从序列化创建
	CLeftView() noexcept;
	DECLARE_DYNCREATE(CLeftView)

// 特性
public:
	CMyExplorerDoc* GetDocument() const;

	CTreeCtrl& m_tree;

// 操作
public:

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
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // LeftView.cpp 中的调试版本
inline CMyExplorerDoc* CLeftView::GetDocument() const
   { return reinterpret_cast<CMyExplorerDoc*>(m_pDocument); }
#endif

