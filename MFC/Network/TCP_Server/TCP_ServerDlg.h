
// TCP_ServerDlg.h: 头文件
//

#pragma once


// CTCPServerDlg 对话框
class CTCPServerDlg : public CDialogEx
{
// 构造
public:
	CTCPServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TCP_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 信息
	CEdit m_info;
	// IP地址
	CIPAddressCtrl m_address;
	// 端口
	int m_port;
	// 发送文本
	CString m_text;
	// 监听Socket
	CSocketListen m_socket;

	void OnReceive(CString text, CString address, UINT port);

	afx_msg void OnBnClickedBtnSend();
	virtual void OnOK();
	virtual BOOL DestroyWindow();
};
