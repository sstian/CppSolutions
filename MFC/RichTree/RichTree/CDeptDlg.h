#pragma once


// CDeptDlg 对话框

class CDeptDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeptDlg)

public:
	CDeptDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDeptDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEPT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboComp;
	CComboBox m_comboDept;

	
	void FillCombo(CString strPath, CComboBox& combo);
	void SetCombo(CString strText, CComboBox& combo);

	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboComp();
};
