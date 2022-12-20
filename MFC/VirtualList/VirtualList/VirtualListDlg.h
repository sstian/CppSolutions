
// VirtualListDlg.h: 头文件
//

#pragma once


// CVirtualListDlg 对话框
class CVirtualListDlg : public CDialogEx
{
public:
	CListCtrl m_list;

	CIniFile fileInform;
	CStringArray m_strArray;
	int m_count;				// 数据总数
	BOOL* m_pState;				// 维护记录复选框状态


// 构造
public:
	CVirtualListDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CVirtualListDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIRTUALLIST_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOdfinditemList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOdcachehintList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
