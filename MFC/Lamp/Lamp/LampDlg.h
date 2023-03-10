
// LampDlg.h: 头文件
//

#pragma once

//class CLampCtrl;

// CLampDlg 对话框
class CLampDlg : public CDialogEx
{
// 构造
public:
	CLampDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAMP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CString m_szText;
	int m_nLeft;

	CLampCtrl m_lampCtrl;	//可以将使用的类的头文件包含在stdafx.h预编译处理头文件中
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
