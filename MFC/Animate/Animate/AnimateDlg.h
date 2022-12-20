
// AnimateDlg.h: 头文件
//

#pragma once

#define TIMER_BUTTER	1
#define TIMER_FLY		2

// CAnimateDlg 对话框
class CAnimateDlg : public CDialogEx
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
private:
	CMemoryDC m_mdc;						//内存缓冲DC
	CMemoryDC m_mdcBack;					//加载背景DC
	CMemoryDC m_mdcButter[FRAME_COUNT];		//加载图片DC，得保证每张图片分辨率一致
	// 方案一：一只蝴蝶
	CSize m_solo;							//蝴蝶尺寸
	//int m_index;							//帧数索引
	//CPoint m_pos;							//移动距离
	//CPoint m_dir;							//移动方向
	//CSize m_size;							//蝴蝶缩放
	//int m_angle;							//旋转角度
	struct SButter m_bu;
	// 方案二：点击出现蝴蝶
	CArray<SButter> m_butters;				//一群蝴蝶

// 构造
public:
	CAnimateDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CAnimateDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATE_DIALOG };
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
//	afx_msg void OnNcPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
