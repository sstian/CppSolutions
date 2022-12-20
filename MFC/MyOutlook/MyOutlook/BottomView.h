#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CHtmlView。"
#endif 

// CBottomView HTML 视图

class CBottomView : public CHtmlView
{
	DECLARE_DYNCREATE(CBottomView)

protected:
	CBottomView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBottomView();

public:
	

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


