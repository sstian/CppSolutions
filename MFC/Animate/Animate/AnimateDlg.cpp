
// AnimateDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Animate.h"
#include "AnimateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnimateDlg 对话框



CAnimateDlg::CAnimateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANIMATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_butters.RemoveAll();
}

CAnimateDlg::~CAnimateDlg()
{
	m_butters.RemoveAll();
}

void CAnimateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAnimateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
//	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CAnimateDlg 消息处理程序

BOOL CAnimateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 窗口全屏
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	SetWindowPos(nullptr, 0, 0, cx, cy, SWP_NOMOVE);


	// 初始化图片加载
	CString strFile;
	for (int index = 0; index < FRAME_COUNT; index++)
	{
		strFile.Format(_T("./images/butterfly%02d.bmp"), index + 1);
		m_mdcButter[index].LoadBitmapW(strFile);
	}

	//CRect rect;
	//GetClientRect(rect);
	//m_mdc.Create(rect.Width(), rect.Height());
	////m_mdc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
	m_mdcBack.LoadBitmapW(_T("./images/back.bmp"));

	m_mdc.Create(cx, cy);

	// 初始化参数
	m_bu.index = 0;
	m_bu.pos.SetPoint(cx / 2, cy / 2);
	m_bu.dir.SetPoint(30, 30);				//每次移动距离
	m_solo.cx = m_mdcButter->GetWidth();
	m_solo.cy = m_mdcButter->GetHeight();
	m_bu.size.SetSize(0, 0);
	m_bu.wing.SetSize(10, 10);				//每次缩放大小
	m_bu.angle = 0;

	// 随机数
	srand((unsigned int)time(NULL));
	// 设置定时器
	SetTimer(TIMER_BUTTER, 70, nullptr);	//控制移动
	SetTimer(TIMER_FLY, 50, nullptr);		//控制远近
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAnimateDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文，界面DC
	// 双缓冲，内存绘制，一次性输出，解决闪烁
	CRect rect;
	GetClientRect(rect);
	//m_mdc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
	m_mdc.StretchBlt(0, 0, rect.Width()+10, rect.Height(), &m_mdcBack, 0, 0, m_mdcBack.GetWidth(), m_mdcBack.GetHeight(), SRCCOPY);

	CMemoryDC& mdcButter = m_mdcButter[m_bu.index++];
	//mdcBack.BitTrans(0, 0, mdcBack.GetWidth(), mdcBack.GetHeight(), &, 0, 0, RGB(255, 255, 255));
	////mdcBack.StretchTrans(10, 10, mdcBack.GetWidth() - 300, mdcBack.GetWidth(), &dc, 0, 0, mdcBack.GetWidth(), mdcBack.GetHeight(), RGB(255, 255, 255));
	//dc.BitBlt(0, 0, m_mdc.GetWidth(), m_mdc.GetHeight(), &m_mdc, 0, 0, SRCCOPY);
	////dc.StretchBlt(0, 0, m_mdc.GetWidth(), m_mdc.GetHeight(), &m_mdc, 0, 0, m_mdc.GetWidth(), m_mdc.GetHeight(), SRCCOPY);
	//mdcButter.BitTrans(m_bu.pos.x, m_bu.pos.y, mdcButter.GetWidth(), mdcButter.GetHeight(), &m_mdc, 0, 0, RGB(255, 255, 255));
	mdcButter.StretchTrans(m_bu.pos.x, m_bu.pos.y, 
		m_bu.size.cx, m_bu.size.cy,
		&m_mdc, 0, 0, m_solo.cx, m_solo.cy, RGB(255, 255, 255));//mdcButter.GetWidth(), mdcButter.GetHeight()

	int size = (int)m_butters.GetSize();
	for (int i = 0; i < size; i++)
	{
		struct SButter& sbutter = m_butters.GetAt(i);

		CMemoryDC& mdcButter = m_mdcButter[sbutter.index];
		//mdcButter.BitTrans(sbutter.pos.x, sbutter.pos.y, mdcButter.GetWidth(), mdcButter.GetHeight(), &m_mdc, 0, 0, RGB(255, 255, 255));
		mdcButter.StretchTrans(sbutter.pos.x, sbutter.pos.y,
			mdcButter.GetWidth() - sbutter.size.cx, mdcButter.GetHeight() - sbutter.size.cy,
			//sbutter.size.cx, sbutter.size.cy,
			&m_mdc, 0, 0, mdcButter.GetWidth(), mdcButter.GetHeight(), RGB(255, 255, 255));

		if (++sbutter.index >= 6)
			sbutter.index = 0;

		sbutter.pos.Offset(sbutter.dir);
		if (sbutter.pos.x >= rect.right || sbutter.pos.x <= m_solo.cx / 2)
			sbutter.dir.x *= -1;
		if (sbutter.pos.y >= rect.bottom || sbutter.pos.y <= m_solo.cy / 2)
			sbutter.dir.y *= -1;

		sbutter.size += sbutter.wing;
		if (sbutter.size.cx >= m_solo.cx || sbutter.size.cy >= m_solo.cy
			|| sbutter.size.cx <= 0 || sbutter.size.cy <= 0)
		{
			sbutter.wing.cx *= -1;
			sbutter.wing.cy *= -1;
		}

	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_mdc, 0, 0, SRCCOPY);
	
	//if (IsIconic())
	//{
	//	CPaintDC dc(this); // 用于绘制的设备上下文

	//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	//	// 使图标在工作区矩形中居中
	//	int cxIcon = GetSystemMetrics(SM_CXICON);
	//	int cyIcon = GetSystemMetrics(SM_CYICON);
	//	CRect rect;
	//	GetClientRect(&rect);
	//	int x = (rect.Width() - cxIcon + 1) / 2;
	//	int y = (rect.Height() - cyIcon + 1) / 2;

	//	// 绘制图标
	//	dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	//{
	//	CDialogEx::OnPaint();
	//}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAnimateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAnimateDlg::OnTimer(UINT_PTR nIDEvent)
{
	//CClientDC dc(this);		//客户区临时绘图DC，界面DC
	//CRect rect;
	//GetClientRect(rect);
	//m_mdc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));

	//CMemoryDC& mdcBack = m_mdcBack[m_index++];
	//mdcBack.BitTrans(0, 0, mdcBack.GetWidth(), mdcBack.GetHeight(), &m_mdc, 0, 0, RGB(255, 255, 255));
	////mdcBack.StretchTrans(10, 10, mdcBack.GetWidth() - 300, mdcBack.GetWidth(), &dc, 0, 0, mdcBack.GetWidth(), mdcBack.GetHeight(), RGB(255, 255, 255));
	//dc.BitBlt(0, 0, m_mdc.GetWidth(), m_mdc.GetHeight(), &m_mdc, 0, 0, SRCCOPY);
	////dc.StretchBlt(0, 0, m_mdc.GetWidth(), m_mdc.GetHeight(), &m_mdc, 0, 0, m_mdc.GetWidth(), m_mdc.GetHeight(), SRCCOPY);
	
	if (++m_bu.index >= 6)
		m_bu.index = 0;
	CRect rect;
	GetClientRect(rect);

	switch (nIDEvent)
	{
	case TIMER_BUTTER:
	{
		m_bu.pos.Offset(m_bu.dir);
		if (m_bu.pos.x >= rect.right || m_bu.pos.x <= m_solo.cx / 2)
			m_bu.dir.x *= -1;
		if (m_bu.pos.y >= rect.bottom || m_bu.pos.y <= m_solo.cy / 2)
			m_bu.dir.y *= -1;
	}
		break;
	case TIMER_FLY:
	{
		m_bu.size += m_bu.wing;
		if (m_bu.size.cx >= m_solo.cx || m_bu.size.cy >= m_solo.cy
			|| m_bu.size.cx <= 0 || m_bu.size.cy <= 0)
		{
			m_bu.wing.cx *= -1;
			m_bu.wing.cy *= -1;
		}
	}
		break;
	default:
		break;
	}		

	Invalidate(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


//void CAnimateDlg::OnNcPaint()
//{
//	// TODO: 在此处添加消息处理程序代码
//	// 不为绘图消息调用 CDialogEx::OnNcPaint()
//}


BOOL CAnimateDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


// 点击鼠标左键可生成新的蝴蝶
void CAnimateDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//使点击时蝴蝶出现在中心
	//point.x -= m_mdcButter->GetWidth() / 2;
	//point.y -= m_mdcButter->GetHeight() / 2;
	point.x -= m_solo.cx / 2;
	point.y -= m_solo.cy / 2;
	struct SButter sbutter = { 0, point, m_bu.dir, m_bu.size, m_bu.wing, 0 };
	// 随机方向
	if (rand() % 2)			//奇数 或 偶数
		sbutter.dir.x *= -1;
	if (rand() % 2)
		sbutter.dir.y *= -1;
	m_butters.Add(sbutter);

	CDialogEx::OnLButtonDown(nFlags, point);
}
