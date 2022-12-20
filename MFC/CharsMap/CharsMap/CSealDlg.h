// 奥利哈刚结界

#pragma once

constexpr int RADIUS = 160;		//内圆半径
// 定时器
constexpr int TIMER_INNER = 4;	
constexpr int TIMER_SEAL = 5;
constexpr int TIMER_OUTER = 6;

constexpr int SEG = 20;			//分段

// CSealDlg 对话框

class CSealDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSealDlg)

public:
	CSealDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSealDlg();

	CMemoryDC m_mdc;					//双缓冲
	CMemoryDC m_mdcBack;				//背景图片
	// 内圆、结界、结界点索引、结界半径、外圆 计数器
	int m_inner;
	int m_seal;
	int m_index;
	int m_radius;
	int m_outer;
	// 结界点
	CArray<CPoint> m_pt1;
	CArray<CPoint> m_pt2;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// 画内圆
	void DrawCircleInner(CDC* pDC = nullptr);
	// 画结界线
	void DrawLineSeal(CDC* pDC = nullptr);
	// 画外圆
	void DrawCircleOuter(CDC* pDC = nullptr);

};
