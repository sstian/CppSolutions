
// ArrowHeartsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ArrowHearts.h"
#include "ArrowHeartsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPoint CArrowHeartsDlg::m_move = {200, 100 };

// CArrowHeartsDlg 对话框



CArrowHeartsDlg::CArrowHeartsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARROWHEARTS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArrowHeartsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CArrowHeartsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CArrowHeartsDlg 消息处理程序

BOOL CArrowHeartsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 加载背景
	m_mdcBack.LoadBitmapW(IDB_BITMAP_BACK);

	SetWindowPos(nullptr, 0, 0, m_mdcBack.GetWidth(), m_mdcBack.GetHeight(), SWP_NOMOVE);

	SetTimer(TIMER_DELAY, 2000, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CArrowHeartsDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rect;
	GetClientRect(rect);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_mdcBack, 0, 0, SRCCOPY);

	this->DrawHeartHalf(&dc);
	this->DrawHeart(&dc);
	this->DrawArrow(&dc);

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
HCURSOR CArrowHeartsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CArrowHeartsDlg::DrawHeartHalf(CDC * pDC)
{
	Sleep(1000);
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(255, 128, 255));
	pDC->SelectObject(pen);

	CRect rect;
	GetClientRect(rect);
	CPoint point = rect.CenterPoint();
	point.Offset(200, 0);
	point -= m_move;

	pDC->MoveTo(point.x - 4, point.y + 160 - 4);

	//pen.DeleteObject();
	//pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	//pDC->SelectObject(pen);
	// 画左心线
	//pDC->MoveTo(point.x - 100 + 20, point.y + 60);
	//pDC->LineTo(point.x + 100, point.y + 100 + 160);
	CPoint pos = pDC->GetCurrentPosition();
	for (int i = 1; i <= 20; i += 2)
	{
		Sleep(20);
		pDC->MoveTo(pos);
		pDC->LineTo(pos.x + 5 * i, pos.y + 5 * i);
	}
	pDC->LineTo(point.x + 100, point.y + 100 + 160);

	// 画右心线
	pDC->MoveTo(point.x + 100, point.y + 100 + 160);
	//pDC->LineTo(point.x + 300 - 20, point.y + 60);
	pos = pDC->GetCurrentPosition();
	for (int i = 1; i <= 20; i += 2)
	{
		Sleep(20);
		pDC->MoveTo(pos);
		pDC->LineTo(pos.x + 9 * i, pos.y - 10 * i);
	}

	// 画右心圆弧
	pos = pDC->GetCurrentPosition();
	for (int a = 0; a < 180 + 45; a += 2)
	{
		Sleep(10);
		pDC->MoveTo(pos);
		pDC->AngleArc(point.x + 200, point.y, 100, -45.0f, a*1.0f);
	}

}


void CArrowHeartsDlg::DrawHeart(CDC* pDC)
{
	Sleep(500);
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(255, 128, 255));
	pDC->SelectObject(pen);

	CRect rect;
	GetClientRect(rect);
	CPoint point = rect.CenterPoint();
	point -= m_move;
	pDC->MoveTo(point);

	// 画右心线
	pDC->MoveTo(point.x + 100, point.y + 100 + 160);
	//pDC->LineTo(point.x + 300 - 20, point.y + 60);
	CPoint pos = pDC->GetCurrentPosition();
	for (int i = 1; i <= 20; i += 2)
	{
		Sleep(20);
		pDC->MoveTo(pos);
		pDC->LineTo(pos.x + 9 * i, pos.y - 10 * i);
	}
	// 画右心圆弧
	pos = pDC->GetCurrentPosition();
	for (int a = 0; a < 180 + 45; a += 2)
	{
		Sleep(10);
		pDC->MoveTo(pos);
		pDC->AngleArc(point.x + 200, point.y, 100, -45.0f, a*1.0f);
	}
	// 画左心圆弧
	pos = pDC->GetCurrentPosition();
	for (int a = 0; a < 180 + 45; a += 2)
	{
		Sleep(10);
		pDC->MoveTo(pos);
		pDC->AngleArc(point.x, point.y, 100, 0.0f, a*1.0f);
	}
	pDC->MoveTo(point.x - 100 + 20, point.y + 60);
	//pDC->LineTo(point.x + 100, point.y + 100 + 160);
	pos = pDC->GetCurrentPosition();
	for (int i = 1; i <= 20; i += 2)
	{
		Sleep(20);
		pDC->MoveTo(pos);
		pDC->LineTo(pos.x + 9 * i, pos.y + 10 * i);
	}
	pDC->LineTo(point.x + 100, point.y + 100 + 160);
	// 填充颜色
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 0, 0));
	pDC->SelectObject(brush);
	pDC->ExtFloodFill(point.x , point.y, RGB(255, 128, 255), FLOODFILLBORDER);
	pDC->ExtFloodFill(point.x + 400, point.y, RGB(255, 128, 255), FLOODFILLBORDER);

}

void CArrowHeartsDlg::DrawArrow(CDC * pDC)
{
	Sleep(500);
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	pDC->SelectObject(pen);

	CRect rect;
	GetClientRect(rect);
	CPoint point = rect.CenterPoint();
	point -= m_move;
	// 画箭
	pDC->MoveTo(point.x - 300, point.y + 200);
	//pDC->LineTo(point.x + 700, point.y - 50);
	CPoint pos = pDC->GetCurrentPosition();
	for (int i = 1; i <= 250; i += 10)
	{
		if(i <= 100)
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
}


//void CArrowHeartsDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	//this->DrawHeats();
//	//KillTimer(TIMER_DELAY);
//
//	CDialogEx::OnTimer(nIDEvent);
//}
