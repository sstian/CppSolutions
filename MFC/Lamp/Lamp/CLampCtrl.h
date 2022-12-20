// 自定义控件
#pragma once
#define TIMER_LAMPCTRL	0x0010

class CLampCtrl : public CWnd
{
public:
	CLampCtrl();
	virtual ~CLampCtrl();
	// 创建
	BOOL Create(CString& szText, CRect& rect, CWnd* pParent, UINT nID);
	BOOL CreateEx(DWORD dwExStyle, CString& szText, CRect& rect, CWnd* pParent, UINT nID);
	// 启动
	void Start()
	{
		SetTimer(TIMER_LAMPCTRL, 15, NULL);
	}
	// 暂停
	void Pause()
	{
		KillTimer(TIMER_LAMPCTRL);
	}
	// 重设（待定。。。）
	void Reset();

	void SetTextColor(COLORREF coText) { m_coText = coText; }
	void SetBackColor(COLORREF coBack) { m_coBack = coBack; }
	void SetFont(CFont* pFont);

public:
	CString m_szText;	//文本内容
	int m_nLeft;		//文本位置
	int m_nLeft2;		//文本位置2
	COLORREF m_coText;	//文本颜色
	COLORREF m_coBack;	//背景颜色
	CFont m_font;		//字体

	CMemoryDC m_mdc;		//内存缓冲DC

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

