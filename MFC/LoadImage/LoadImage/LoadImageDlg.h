
// LoadImageDlg.h: 头文件
//

#pragma once


// CLoadImageDlg 对话框
class CLoadImageDlg : public CDialogEx
{
// 构造
public:
	CLoadImageDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOADIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	HBITMAP m_hBitmap;
	CBitmap m_cBitmap;

	CMemoryDC m_mdc;
	CMemoryDC m_mdc2;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLoadicon();
	afx_msg void OnBnClickedBtnLoadbitmap();
	afx_msg void OnBnClickedBtnLoadimage();
	afx_msg void OnBnClickedBtnCimage();
	afx_msg void OnBnClickedBtnCmemorydc();
	afx_msg void OnBnClickedLoad();
};
