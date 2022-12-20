
// InfoManageView.h: CInfoManageView 类的接口
//

#pragma once

class CInfoManageDoc;

class CInfoManageView : public CListView
{
public: // 仅从序列化创建
	CInfoManageView() noexcept;
	DECLARE_DYNCREATE(CInfoManageView)

// 特性
public:
	CInfoManageDoc* GetDocument() const;

	CListCtrl& m_list;
	CString m_file;
	CInfoManageDoc m_doc;

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
	virtual ~CInfoManageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	BOOL CheckExit();

	afx_msg void OnEditAdd();
	afx_msg void OnEditDel();
	afx_msg void OnEditMod();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void Serialize(CArchive& ar);
	void DeleteContents();
};

#ifndef _DEBUG  // InfoManageView.cpp 中的调试版本
inline CInfoManageDoc* CInfoManageView::GetDocument() const
   { return reinterpret_cast<CInfoManageDoc*>(m_pDocument); }
#endif

