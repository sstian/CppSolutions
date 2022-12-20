
// ExpressHeartsDlg.h: 头文件
//

#pragma once

// 蝴蝶定时器
#define TIMER_BUTTER	1
#define TIMER_FLY		2
#define CLOSE_WINDOW	10

// 定时器触发ID们
constexpr int TIMER_START_HEARTHALF = 2019;
constexpr int TIMER_LEFTHEARTLINE = TIMER_START_HEARTHALF + 1;
constexpr int TIMER_RIGHTHEARTLINE = TIMER_START_HEARTHALF + 2;
constexpr int TIMER_RIGHTHEARTARCH = TIMER_START_HEARTHALF + 3;

constexpr int TIMER_START_HEART = 2119;
constexpr int TIMER_RIGHTHEARTLINE2 = TIMER_START_HEART + 1;
constexpr int TIMER_RIGHTHEARTARCH2 = TIMER_START_HEART + 2;
constexpr int TIMER_LEFTHEARTARCH2 = TIMER_START_HEART + 3;
constexpr int TIMER_LEFTHEARTLINE2 = TIMER_START_HEART + 4;

constexpr int TIMER_START_ARROW = 2219;
constexpr int TIMER_END = 3000;

constexpr int TIMER_TEXT_SHE = 7000;
constexpr int TIMER_TEXT_HE = 8000;

// 文字常量
const CString g_strShe = _T("小双双");
const CString g_strHe = _T("小田田");


// CExpressHeartsDlg 对话框
class CExpressHeartsDlg : public CDialogEx
{
public:
	enum FRAME { FRAME_COUNT = 6 };				//蝴蝶帧数
	struct SButter
	{
		int index;		//第几帧
		CPoint pos;		//移动点数
		CPoint dir;		//移动方向
		CSize size;		//缩放大小
		CSize wing;		//缩放方向
		int angle;		//旋转角度（待定）
	};
	CSize m_solo;							//蝴蝶尺寸
	struct SButter m_bu;					//蝴蝶参数
	CArray<SButter> m_butters;				//一群蝴蝶

	CMemoryDC m_mdc;						//内存缓冲DC
	CMemoryDC m_mdcBack;					//加载背景DC
	CMemoryDC m_mdcButter[FRAME_COUNT];		//加载图片DC，得保证每张图片分辨率一致
	static CPoint m_move;					//坐标偏移修正

	CFont m_font;							//字体
	CArray<CRect> m_rectShe;				//文字矩形区域：她
	CArray<CRect> m_rectHe;					//文字矩形区域：他

	// 计数器们
	bool m_startHeartHalf;
	int m_leftHeartLine;
	int m_rightHeartLine;
	int m_rightHeartArch;

	bool m_startHeart;
	int m_rightHeartLine2;
	int m_rightHeartArch2;
	int m_leftHeartArch2;
	int m_leftHeartLine2;

	bool m_startArrow;
	bool m_end;

	bool m_textShe;
	bool m_textHe;

	double m_start;
	double m_over;

// 构造
public:
	CExpressHeartsDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual~CExpressHeartsDlg();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXPRESSHEARTS_DIALOG };
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
	// 参数初始化
	void InitParams();
	// 画半心
	void DrawHeartHalf(CPoint point, CDC* pDC = nullptr);
	// 画心
	void DrawHeart(CPoint point, CDC* pDC = nullptr);
	// 文本 She
	void DrawTextShe(CDC* pDC = nullptr);
	// 画箭
	void DrawArrow(CPoint point, CDC* pDC = nullptr);
	// 文本 He
	void DrawTextHe(CDC* pDC = nullptr);


public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
