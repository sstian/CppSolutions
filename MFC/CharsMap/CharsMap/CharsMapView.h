
// CharsMapView.h: CCharsMapView 类的接口
//

#pragma once

class CCharsMapCntrItem;

class CCharsMapDoc;

class CCharsMapView : public CRichEditView
{
protected: // 仅从序列化创建
	CCharsMapView() noexcept;
	DECLARE_DYNCREATE(CCharsMapView)

// 特性
public:
	CCharsMapDoc* GetDocument() const;

// 操作
public:
	CRichEditCtrl& m_richedit;		//编辑控件
	CCharsMapDlg m_charsdlg;		//对话框 CharsMap

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCharsMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnCipher();
	afx_msg void OnUpdateBtnCipher(CCmdUI *pCmdUI);
	afx_msg void OnBtnTocipher();
	afx_msg void OnUpdateBtnTocipher(CCmdUI *pCmdUI);
	afx_msg void OnBtnToplainUpper();
	afx_msg void OnUpdateBtnToplainUpper(CCmdUI *pCmdUI);
	afx_msg void OnBtnToplainLower();
	afx_msg void OnUpdateBtnToplainLower(CCmdUI *pCmdUI);
	afx_msg void OnBtnSeal();
	afx_msg void OnUpdateBtnSeal(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // CharsMapView.cpp 中的调试版本
inline CCharsMapDoc* CCharsMapView::GetDocument() const
   { return reinterpret_cast<CCharsMapDoc*>(m_pDocument); }
#endif

