
// CaptionDlg.h: 头文件
//

#pragma once


// CCaptionDlg 对话框
class CCaptionDlg : public CDialogEx
{
// 构造
public:
	CCaptionDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAPTION_DIALOG };
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
	// 绘制标题栏
	void DrawColorTitle(CRect& rect, COLORREF cofirst, COLORREF colast, CDC* pdc);

	afx_msg void OnNcPaint();
};
