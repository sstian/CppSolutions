
// SongDlg.h: 头文件
//

#pragma once


// CSongDlg 对话框
class CSongDlg : public CDialogEx
{
private:
	CMemoryDC m_mdc;
	CMemoryDC m_mdcFront;
	CMemoryDC m_mdcBack;
	int m_index;
	int m_left;
	CRgn m_rgn;
	CStringArray m_texts;
	CArray<CRgn*> m_rgns;
	CFont m_font;
// 构造
public:
	CSongDlg(CWnd* pParent = nullptr);	// 标准构造函数

	void DrawColor(CRect  rect, COLORREF cofirst, COLORREF colast, CDC* pdc);
	void TextToRgn();
	void SetRgn();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SONG_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
