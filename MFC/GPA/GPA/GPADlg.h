
// GPADlg.h: 头文件
//

#pragma once


// CGPADlg 对话框
class CGPADlg : public CDialogEx
{
// 构造
public:
	CGPADlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CGPADlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GPA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CArray<int> m_ids;
	CListCtrl m_list;
	BOOL m_modified;

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
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCalc();
	afx_msg void OnClose();
	virtual void OnOK();
	// 根据成绩返回绩点
	float ScoreToPoint(const float& score);
	// 根据五级制返回绩点
	float FiveDegreeToPoint(const CString& degree);
};
