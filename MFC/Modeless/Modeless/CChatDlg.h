#pragma once


// CChatDlg 对话框

class CChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChatDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
