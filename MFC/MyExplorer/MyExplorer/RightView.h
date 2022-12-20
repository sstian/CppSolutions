#pragma once


// CRightView 视图

class CRightView : public CListView
{
	DECLARE_DYNCREATE(CRightView)
	
public:
	CListCtrl& m_list;

protected:
	CRightView();           // 动态创建所使用的受保护的构造函数
	virtual ~CRightView();

public:
	// 刷新，列出文件
	void Refresh(CString szPath);

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


