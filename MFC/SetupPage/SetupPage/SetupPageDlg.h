
// SetupPageDlg.h: 头文件
//

#pragma once


// CSetupPageDlg 对话框
class CSetupPageDlg : public CDialogEx
{
private:
	int m_index;
	enum EPage { PAGE_COUNT = 3 };
	CPage1 m_page1;
	CPage2 m_page2;
	CPage3 m_page3;
	CWnd* m_pages[PAGE_COUNT] = { &m_page1, &m_page2, &m_page3 };

// 构造
public:
	CSetupPageDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETUPPAGE_DIALOG };
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
	// 显示页面
	void ShowPage();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
