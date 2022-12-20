// 会动不会讲话的宠物蝴蝶
// PetDlg.h: 头文件
//

#pragma once

#define TIMER_PET	6

// CPetDlg 对话框
class CPetDlg : public CDialogEx
{
private:
	enum BUTTER{ BUTTER_COUNT = 6 };
	int m_index;							//帧数索引
	CMemoryDC m_mdc;						//内存缓冲DC
	CMemoryDC m_mdcButter[BUTTER_COUNT];	//加载图片DC
	CRgn m_rgnButter[BUTTER_COUNT];			//蝴蝶裁剪区RGN

	int m_count;							//文字索引
	CMemoryDC m_mdcText;					//加载文本背景DC
	CFont m_font;							//字体
	CStringArray m_texts;					//文字
	CArray<CRgn*> m_rgns;					//位子裁剪区

// 构造
public:
	CPetDlg(CWnd* pParent = nullptr);	// 标准构造函数

	// 设置字体
	void SetFont();
	// 文本到裁剪区
	void TextToRgn();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PET_DIALOG };
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnDestroy();
};
