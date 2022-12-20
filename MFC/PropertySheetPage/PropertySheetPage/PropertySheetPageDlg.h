
// PropertySheetPageDlg.h: 头文件
//

#pragma once


// CPropertySheetPageDlg 对话框
class CPropertySheetPageDlg : public CDialogEx
{
// 构造
public:
	CPropertySheetPageDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPERTYSHEETPAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CInfoDlg m_infoDlg;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedBtnWizard();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnHottrackList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL DestroyWindow();
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
