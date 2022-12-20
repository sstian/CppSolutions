#pragma once


// CTopView 视图

class CTopView : public CListView
{
	DECLARE_DYNCREATE(CTopView)

protected:
	CTopView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTopView();

public:
	CListCtrl& m_list;	//列表

	// 访问注册表
	// hKey : HKEY_CLASSES_ROOT, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, HKEY_USERS, HKEY_CURRENT_CONFIG
	// eg. hKey = HKEY_CURRENT_USER, 
	// eg. szSbuKey = Software\Microsoft\Internet Explorer\TypedUrls
	void RegAccess(HKEY hKey, CString szSubKey);

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


