#pragma once


// CInfoDlg 对话框

class CInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	CInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInfoDlg();

	CString m_title;	//对话框标题
	CString m_number;
	CString m_name;
	COleDateTime m_datetime;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
