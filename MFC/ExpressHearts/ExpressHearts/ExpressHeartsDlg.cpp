
// ExpressHeartsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ExpressHearts.h"
#include "ExpressHeartsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPoint CExpressHeartsDlg::m_move = { 200, 100 };

// CExpressHeartsDlg 对话框



CExpressHeartsDlg::CExpressHeartsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXPRESSHEARTS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_butters.RemoveAll();
}

CExpressHeartsDlg::~CExpressHeartsDlg()
{
	m_butters.RemoveAll();
}

void CExpressHeartsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExpressHeartsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CExpressHeartsDlg 消息处理程序

BOOL CExpressHeartsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化成员变量参数
	this->InitParams();

	// 窗口全屏
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	SetWindowPos(nullptr, 0, 0, cx, cy, SWP_NOMOVE);

	// 加载背景
	//m_mdcBack.LoadBitmap(IDB_BITMAP_BACK);
	m_mdcBack.LoadBitmap(IDB_BITMAP_SCENE);

	//m_mdc.Create(m_mdcBack.GetWidth(), m_mdcBack.GetHeight());
	m_mdc.Create(cx, cy);

	// 初始化图片加载
	CString strFile;
	for (int index = 0; index < FRAME_COUNT; index++)
	{
		//strFile.Format(_T("./images/butterfly%02d.bmp"), index + 1);
		m_mdcButter[index].LoadBitmap(IDB_BUTTERFLY01 + index);
	}

	// 设置字体
	CFont* pFont = GetFont();
	LOGFONT lg;
	pFont->GetLogFont(&lg);
	_tcscpy_s(lg.lfFaceName, _T("方正舒体"));
	lg.lfHeight = 100;
	lg.lfWidth = 60;
	//lg.lfWeight = 50;
	m_font.CreateFontIndirect(&lg);
	m_mdc.SelectObject(m_font);

	// 文字矩形区域
	CRect rect;
	GetClientRect(rect);
	CRect rectShe1(rect.left + 20, rect.Height() / 2 - 100, rect.left + 140, rect.Height() / 2 + 20);
	CRect rectShe2(rect.left + 20, rect.Height() / 2 + 20, rect.left + 140, rect.Height() / 2 + 140);
	CRect rectShe3(rect.left + 20, rect.Height() / 2 + 140, rect.left + 140, rect.Height() / 2 + 260);
	m_rectShe.Add(rectShe1);
	m_rectShe.Add(rectShe2);
	m_rectShe.Add(rectShe3);

	CRect rectHe1(rect.right - 140, rect.Height() / 2 - 340, rect.right - 20, rect.Height() / 2 - 220);
	CRect rectHe2(rect.right - 140, rect.Height() / 2 - 220, rect.right - 20, rect.Height() / 2 - 100);
	CRect rectHe3(rect.right - 140, rect.Height() / 2 - 100, rect.right - 20, rect.Height() / 2 + 20);
	m_rectHe.Add(rectHe1);
	m_rectHe.Add(rectHe2);
	m_rectHe.Add(rectHe3);


	// 初始化蝴蝶参数
	m_bu.index = 0;
	m_bu.pos.SetPoint(cx / 2, cy / 2);
	m_bu.dir.SetPoint(30, 30);				//每次移动距离
	m_solo.cx = m_mdcButter->GetWidth();
	m_solo.cy = m_mdcButter->GetHeight();
	m_bu.size.SetSize(0, 0);
	m_bu.wing.SetSize(10, 10);				//每次缩放大小
	m_bu.angle = 0;

	//SetWindowPos(nullptr, 0, 0, m_mdcBack.GetWidth(), m_mdcBack.GetHeight(), SWP_NOMOVE);

	// 随机数
	srand((unsigned int)time(NULL));

	// 定时器
	SetTimer(TIMER_START_HEARTHALF, 1000, nullptr);
	//// Sleep(20); 沉睡20秒 VS 每隔20秒触发
	//SetTimer(TIMER_LEFTHEARTLINE, 20, nullptr);
	SetTimer(TIMER_BUTTER, 70, nullptr);	//控制移动
	SetTimer(TIMER_FLY, 50, nullptr);		//控制远近
	SetTimer(CLOSE_WINDOW, 2000, nullptr);	//关闭窗口

	// 播放背景音乐
	PlaySound((LPCWSTR)IDR_WAVE_BGM, NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);

	m_start = clock();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExpressHeartsDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rect;
	GetClientRect(rect);
	//m_mdc.BitBlt(0, 0, m_mdcBack.GetWidth(), m_mdcBack.GetHeight(), &m_mdcBack, 0, 0, SRCCOPY);
	m_mdc.StretchBlt(0, 0, rect.Width(), rect.Height(), &m_mdcBack, 0, 0, m_mdcBack.GetWidth(), m_mdcBack.GetHeight(), SRCCOPY);

	// 箭心动画
	// 线条颜色
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(255, 128, 255));
	m_mdc.SelectObject(pen);
	// 坐标偏移校准点
	CPoint point = rect.CenterPoint();
	point -= m_move;
	// 绘制函数
	this->DrawHeartHalf(point, &m_mdc);
	this->DrawHeart(point, &m_mdc);
	this->DrawTextShe(&m_mdc);
	this->DrawArrow(point, &m_mdc);
	this->DrawTextHe(&m_mdc);

	// 蝴蝶动画
	CMemoryDC& mdcButter = m_mdcButter[m_bu.index++];
	mdcButter.StretchTrans(m_bu.pos.x, m_bu.pos.y,
		m_bu.size.cx, m_bu.size.cy,
		&m_mdc, 0, 0, m_solo.cx, m_solo.cy, RGB(255, 255, 255));

	int size = (int)m_butters.GetSize();
	for (int i = 0; i < size; i++)
	{
		struct SButter& sbutter = m_butters.GetAt(i);

		CMemoryDC& mdcButter = m_mdcButter[sbutter.index];
		mdcButter.StretchTrans(sbutter.pos.x, sbutter.pos.y,
			mdcButter.GetWidth() - sbutter.size.cx, mdcButter.GetHeight() - sbutter.size.cy,
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

	// 全部输出显示
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
HCURSOR CExpressHeartsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CExpressHeartsDlg::InitParams()
{
	m_startHeartHalf = false;
	m_leftHeartLine = 0;
	m_rightHeartLine = 0;
	m_rightHeartArch = 0;

	m_startHeart = false;
	m_rightHeartLine2 = 0;
	m_rightHeartArch2 = 0;
	m_leftHeartArch2 = 0;
	m_leftHeartLine2 = 0;

	m_startArrow = false;
	m_end = false;

	m_textShe = false;
	m_textHe = false;

}

void CExpressHeartsDlg::DrawHeartHalf(CPoint point, CDC* pDC)
{
	// 开始
	//Sleep(1000);
	if (!m_startHeartHalf)
		return;

	//CPen pen;
	//pen.CreatePen(PS_SOLID, 5, RGB(255, 128, 255));
	//pDC->SelectObject(pen);

	//CRect rect;
	//GetClientRect(rect);
	//CPoint point = rect.CenterPoint();
	//point.Offset(200, 0);
	//point -= m_move;

	point.Offset(200, 0);
	pDC->MoveTo(point.x - 4, point.y + 160 - 4);

	// 画左心线
	CPoint pos = pDC->GetCurrentPosition();
	//for (int i = 1; i <= 20; i += 2)
	{
		//Sleep(20);
		pDC->MoveTo(pos);
		pDC->LineTo(pos.x + 5 * m_leftHeartLine, pos.y + 5 * m_leftHeartLine);
	}
	if(m_leftHeartLine >= 20)
		pDC->LineTo(point.x + 100, point.y + 100 + 160);

	// 画右心线
	if (!m_rightHeartLine)
		return;
	pDC->MoveTo(point.x + 100, point.y + 100 + 160);
	pos = pDC->GetCurrentPosition();
	//for (int i = 1; i <= 20; i += 2)
	{
		//Sleep(20);
		pDC->MoveTo(pos);
		pDC->LineTo(pos.x + 9 * m_rightHeartLine, pos.y - 10 * m_rightHeartLine);
	}

	// 画右心圆弧
	if (!m_rightHeartArch)
		return;
	pos = pDC->GetCurrentPosition();
	//for (int a = 0; a < 180 + 45; a += 2)
	{
		//Sleep(10);
		pDC->MoveTo(pos);
		pDC->AngleArc(point.x + 200, point.y, 100, -45.0f, m_rightHeartArch*1.0f);
	}

}

void CExpressHeartsDlg::DrawHeart(CPoint point, CDC* pDC)
{
	// 开始
	if (!m_startHeart)
		return;

	pDC->MoveTo(point);

	// 画右心线
	if (!m_rightHeartLine2)
		return;
	pDC->MoveTo(point.x + 100, point.y + 100 + 160);
	CPoint pos = pDC->GetCurrentPosition();
	pDC->MoveTo(pos);
	pDC->LineTo(pos.x + 9 * m_rightHeartLine2, pos.y - 10 * m_rightHeartLine2);

	// 画右心圆弧
	if (!m_rightHeartArch2)
		return;
	pos = pDC->GetCurrentPosition();
	pDC->MoveTo(pos);
	pDC->AngleArc(point.x + 200, point.y, 100, -45.0f, m_rightHeartArch2*1.0f);

	// 画左心圆弧
	if (!m_leftHeartArch2)
		return;
	pos = pDC->GetCurrentPosition();
	pDC->MoveTo(pos);
	pDC->AngleArc(point.x, point.y, 100, 0.0f, m_leftHeartArch2*1.0f);

	// 画左心线
	if (!m_leftHeartLine2)
		return;
	pDC->MoveTo(point.x - 100 + 20, point.y + 60);
	pos = pDC->GetCurrentPosition();
	pDC->MoveTo(pos);
	pDC->LineTo(pos.x + 9 * m_leftHeartLine2, pos.y + 10 * m_leftHeartLine2);

	if (m_leftHeartLine2 >= 20)
	{
		pDC->LineTo(point.x + 100, point.y + 100 + 160);
		// 填充颜色
		CBrush brush;
		brush.CreateSolidBrush(RGB(255, 0, 0));
		pDC->SelectObject(brush);
		pDC->ExtFloodFill(point.x, point.y, RGB(255, 128, 255), FLOODFILLBORDER);
		pDC->ExtFloodFill(point.x + 400, point.y, RGB(255, 128, 255), FLOODFILLBORDER);
	}
}

void CExpressHeartsDlg::DrawTextShe(CDC * pDC)
{
	if (!m_textShe)
		return;

	// 先画白的再画其它色的，以表现立体感
	m_mdc.SetBkMode(TRANSPARENT);

	m_mdc.SetTextColor(RGB(255, 255, 255));
	int count = (int)m_rectShe.GetCount();
	CString str;
	for (int index = 0; index < count; index++)
	{
		str.Format(_T("%wc"), g_strShe[index]);
		m_mdc.DrawText(str, m_rectShe[index], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	m_mdc.SetTextColor(RGB(255, 128, 255));
	CRect rect;
	for (int index = 0; index < count; index++)
	{
		str.Format(_T("%wc"), g_strShe[index]);
		rect = m_rectShe[index];
		rect.OffsetRect(-4, 0);
		m_mdc.DrawText(str, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

}

void CExpressHeartsDlg::DrawArrow(CPoint point, CDC* pDC)
{
	if (!m_startArrow)
		return;

	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	pDC->SelectObject(pen);

	// 画箭
	pDC->MoveTo(point.x - 300, point.y + 200);
	CPoint pos = pDC->GetCurrentPosition();
	for (int i = 1; i <= 250; i += 10)
	{
		if (i <= 100)
		{
			pDC->MoveTo(pos);
			pDC->LineTo(pos.x + 4 * i, pos.y - i);
		}
		if (i >= 175)
		{
			pDC->MoveTo(pos.x + 700, pos.y - 175);
			pDC->LineTo(pos.x + 4 * i, pos.y - i);
		}
	}
	pos = pDC->GetCurrentPosition();
	// 画箭头
	CPoint ps[] = {
		pos, {pos.x - 100, pos.y}, {pos.x - 40, pos.y + 10}, {pos.x - 80, pos.y + 50}
	};
	pDC->Polygon(ps, _countof(ps));

	if (!m_end)
		return;
	this->InitParams();
	SetTimer(TIMER_START_HEARTHALF, 1000, nullptr);
	Invalidate(FALSE);

}

void CExpressHeartsDlg::DrawTextHe(CDC * pDC)
{
	if (!m_textHe)
		return;

	// 先画白的再画其它色的，以表现立体感
	m_mdc.SetBkMode(TRANSPARENT);

	m_mdc.SetTextColor(RGB(255, 255, 255));
	int count = (int)m_rectHe.GetCount();
	CString str;
	for (int index = 0; index < count; index++)
	{
		str.Format(_T("%wc"), g_strHe[index]);
		m_mdc.DrawText(str, m_rectHe[index], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	m_mdc.SetTextColor(RGB(0, 255, 255));
	CRect rect;
	for (int index = 0; index < count; index++)
	{
		str.Format(_T("%wc"), g_strHe[index]);
		rect = m_rectHe[index];
		rect.OffsetRect(-4, 0);
		m_mdc.DrawText(str, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

}

void CExpressHeartsDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (++m_bu.index >= 6)
		m_bu.index = 0;
	CRect rect;
	GetClientRect(rect);

	double span = 0.0;

	switch (nIDEvent)
	{
		// Butterflies
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
	case CLOSE_WINDOW:
	{
		m_over = clock();
		span = 1.0 * (m_over - m_start) / CLOCKS_PER_SEC;
		if (span >= 276)
			exit(1);
	}
		break;
		// DrawHeartHalf()
	case TIMER_START_HEARTHALF:
		m_startHeartHalf = true;
		KillTimer(TIMER_START_HEARTHALF);
		SetTimer(TIMER_LEFTHEARTLINE, 20, nullptr);
		break;
	case TIMER_LEFTHEARTLINE:
		m_leftHeartLine += 2;
		if (m_leftHeartLine >= 20)
		{
			KillTimer(TIMER_LEFTHEARTLINE);
			SetTimer(TIMER_RIGHTHEARTLINE, 20, nullptr);
		}
		break;
	case TIMER_RIGHTHEARTLINE:
		m_rightHeartLine += 2;
		if (m_rightHeartLine >= 20)
		{
			KillTimer(TIMER_RIGHTHEARTLINE);
			SetTimer(TIMER_RIGHTHEARTARCH, 10, nullptr);
		}
		break;
	case TIMER_RIGHTHEARTARCH:
		m_rightHeartArch += 2;
		if (m_rightHeartArch >= 180 + 45)
		{
			KillTimer(TIMER_RIGHTHEARTARCH);
			SetTimer(TIMER_START_HEART, 500, nullptr);
		}
		break;

		// DrawHeart()
	case TIMER_START_HEART:
		m_startHeart = true;
		KillTimer(TIMER_START_HEART);
		SetTimer(TIMER_RIGHTHEARTLINE2, 20, nullptr);
		break;
	case TIMER_RIGHTHEARTLINE2:
		m_rightHeartLine2 += 2;
		if (m_rightHeartLine2 >= 20)
		{
			KillTimer(TIMER_RIGHTHEARTLINE2);
			SetTimer(TIMER_RIGHTHEARTARCH2, 10, nullptr);
		}
		break;
	case TIMER_RIGHTHEARTARCH2:
		m_rightHeartArch2 += 2;
		if (m_rightHeartArch2 >= 180 + 45)
		{
			KillTimer(TIMER_RIGHTHEARTARCH2);
			SetTimer(TIMER_LEFTHEARTARCH2, 10, nullptr);
		}
		break;
	case TIMER_LEFTHEARTARCH2:
		m_leftHeartArch2 += 2;
		if (m_leftHeartArch2 >= 180 + 45)
		{
			KillTimer(TIMER_LEFTHEARTARCH2);
			SetTimer(TIMER_LEFTHEARTLINE2, 20, nullptr);
		}
		break;
	case TIMER_LEFTHEARTLINE2:
		m_leftHeartLine2 += 2;
		if (m_leftHeartLine2 >= 20)
		{
			KillTimer(TIMER_LEFTHEARTLINE2);
			SetTimer(TIMER_TEXT_SHE, 500, nullptr);
		}
		break;

		// DrawTextShe()
	case TIMER_TEXT_SHE:
		m_textShe = true;
		KillTimer(TIMER_TEXT_SHE);
		SetTimer(TIMER_START_ARROW, 500, nullptr);
		break;

		// DrawArrow()
	case TIMER_START_ARROW:
		m_startArrow = true;
		KillTimer(TIMER_START_ARROW);
		SetTimer(TIMER_TEXT_HE, 500, nullptr);
		break;

		// DrawTextHe()
	case TIMER_TEXT_HE:
		m_textHe = true;
		KillTimer(TIMER_TEXT_HE);
		SetTimer(TIMER_END, 1000, nullptr);
		break;

	case TIMER_END:
		m_end = true;
		KillTimer(TIMER_END);
	default:
		break;
	}

	Invalidate(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}



BOOL CExpressHeartsDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CExpressHeartsDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//使点击时蝴蝶出现在中心
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
