#pragma once


// CAddrBar 对话框

class CAddrBar : public CDialogBar
{
	DECLARE_DYNAMIC(CAddrBar)

public:
	CAddrBar(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddrBar();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDR_BAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
