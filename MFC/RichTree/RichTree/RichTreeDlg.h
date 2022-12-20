
// RichTreeDlg.h: 头文件
//

#pragma once


// CRichTreeDlg 对话框
class CRichTreeDlg : public CDialogEx
{
private:
	CListCtrl m_list;
	CTreeCtrl m_tree;
	CImageList m_imagelist;

// 构造
public:
	CRichTreeDlg(CWnd* pParent = nullptr);	// 标准构造函数

	// 树形深度
	int GetDepth(HTREEITEM item) const;
	// 树形路径
	CString GetPath(HTREEITEM item) const;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RICHTREE_DIALOG };
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
	virtual void OnOK();
public:
	afx_msg void OnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEndlabeleditTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnAddDept();
	afx_msg void OnBnClickedBtnDelDept();
	afx_msg void OnBnClickedBtnAddMemb();
	afx_msg void OnBnClickedBtnDelMemb();
	afx_msg void OnBnClickedBtnMove();
};
