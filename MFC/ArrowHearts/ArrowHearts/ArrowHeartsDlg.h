// 2019.03.13
// 一箭穿心
// ArrowHeartsDlg.h: 头文件
//

#pragma once

#define TIMER_DELAY		7

// CArrowHeartsDlg 对话框
class CArrowHeartsDlg : public CDialogEx
{
private:
	CMemoryDC m_mdcBack;
	static CPoint m_move;		//坐标偏移修正

// 构造
public:
	CArrowHeartsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARROWHEARTS_DIALOG };
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
	// 画半心
	void DrawHeartHalf(CDC* pDC = nullptr);
	// 画心
	void DrawHeart(CDC* pDC = nullptr);
	// 画箭
	void DrawArrow(CDC* pDC = nullptr);

public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
