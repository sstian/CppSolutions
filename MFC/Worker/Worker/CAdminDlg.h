#pragma once


// CAdminDlg 对话框

class CAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminDlg)

public:
	CAdminDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAdminDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

//protected:
//	CListCtrl m_list;

protected:
	// 关联控件变量
	CListCtrl m_ListCtrl;
	// 权限
	CComboBox m_prority;
	BOOL m_modified;
	CArray<int> m_userids;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAdminAdd();
	afx_msg void OnBnClickedBtnAdminDelete();
	afx_msg void OnBnClickedBtnAdminModify();
	afx_msg void OnBnClickedBtnAdminSave();
	//afx_msg void OnDestroy();
	virtual void OnCancel();

public:
	// 检查账户名是否存在
	BOOL Check(CString& username);
	// 加载文件
	BOOL LoadFile();
	// 保存文件
	BOOL SaveFile();
	afx_msg void OnItemchangedAdminList(NMHDR *pNMHDR, LRESULT *pResult);
};
