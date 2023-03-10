
// ModelessDlg.h: 头文件
//

#pragma once
//#include "CChatDlg.h"

// CModelessDlg 对话框
class CModelessDlg : public CDialogEx
{
// 构造
public:
	CModelessDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODELESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CWnd m_create;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnChat();
protected:
	CChatDlg m_chatdlg;
public:
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnCreate();
	afx_msg void OnBnClickedBtnVisible();
};
