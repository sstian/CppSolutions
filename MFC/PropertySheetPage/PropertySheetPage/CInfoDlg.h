#pragma once


// CInfoDlg 对话框

class CInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	//SInfo* m_pInfo;
	CListCtrl* m_pList;		//列表控件关联变量指针
	int m_item;				//哪一项
	CString m_text;			//显示的内容

public:
	CInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFO_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void MakeText();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
};
