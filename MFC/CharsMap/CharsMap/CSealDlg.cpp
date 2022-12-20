// CSealDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CharsMap.h"
#include "CSealDlg.h"
#include "afxdialogex.h"


// CSealDlg 对话框

IMPLEMENT_DYNAMIC(CSealDlg, CDialogEx)

CSealDlg::CSealDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEAL, pParent)
{
	m_pt1.RemoveAll();
	m_pt2.RemoveAll();
}

CSealDlg::~CSealDlg()
{
	m_pt1.RemoveAll();
	m_pt2.RemoveAll();

}

void CSealDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSealDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSealDlg 消息处理程序


BOOL CSealDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 加载背景图片
	m_mdcBack.LoadBitmap(IDB_SEAL);
	SetWindowPos(nullptr, 0, 0, m_mdcBack.GetWidth(), m_mdcBack.GetHeight(), SWP_NOMOVE);

	// 双缓冲
	m_mdc.Create(m_mdcBack.GetWidth(), m_mdcBack.GetHeight());

	SetTimer(TIMER_INNER, 10, nullptr);
	m_inner = 0;
	m_seal = 0;
	m_index = 0;
	m_radius = 0;
	m_outer = 0;

	CRect rect;
	GetClientRect(rect);
	CPoint center = rect.CenterPoint();

	m_pt1.Add(center);
	m_pt1.Add(center + CPoint((int)(sqrt(3) / 2 * RADIUS), -RADIUS / 2));
	m_pt1.Add(center + CPoint(0, RADIUS));
	m_pt1.Add(center + CPoint((int)(-sqrt(3) / 2 * RADIUS), -RADIUS / 2));
	m_pt1.Add(center);

	m_pt2.Add(center);
	m_pt2.Add(center + CPoint((int)(-sqrt(3) / 2 * RADIUS), RADIUS / 2));
	m_pt2.Add(center + CPoint(0, -RADIUS));
	m_pt2.Add(center + CPoint((int)(sqrt(3) / 2 * RADIUS), RADIUS / 2));
	m_pt2.Add(center);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSealDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);
	m_mdc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_mdcBack, 0, 0, SRCCOPY);

	CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(255, 128, 255));
	m_mdc.SelectObject(pen);

	this->DrawCircleInner(&m_mdc);
	this->DrawLineSeal(&m_mdc);
	this->DrawCircleOuter(&m_mdc);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_mdc, 0, 0, SRCCOPY);

}

void CSealDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case TIMER_INNER:
		m_inner += 3;
		if (m_inner > 450)
		{
			KillTimer(TIMER_INNER);
			SetTimer(TIMER_SEAL, 10, nullptr);
		}
		break;
	case TIMER_SEAL:
		m_seal += 10;
		if (m_seal >= m_radius)
		{
			m_seal = 0;
			m_index++;
			if (m_index > 3)
			{
				KillTimer(TIMER_SEAL);
				SetTimer(TIMER_OUTER, 10, nullptr);
			}
		}
		break;
	case TIMER_OUTER:
		m_outer -= 3;
		if (m_outer < -360)
		{
			KillTimer(TIMER_OUTER);
		}
		break;
	default:
		break;
	}

	Invalidate(FALSE);	//引起重绘


	CDialogEx::OnTimer(nIDEvent);
}

void CSealDlg::DrawCircleInner(CDC * pDC)
{
	//CPen pen;
	//pen.CreatePen(PS_SOLID, 3, RGB(255, 128, 255));
	//pDC->SelectObject(pen);

	CRect rect;
	GetClientRect(rect);
	CPoint center = rect.CenterPoint();
	CPoint origin = center + CPoint(0, -RADIUS);

	pDC->MoveTo(origin);
	pDC->AngleArc(center.x, center.y, RADIUS, 90.0f, m_inner*1.0f);
	
}

void CSealDlg::DrawLineSeal(CDC * pDC)
{
	//CRect rect;
	//GetClientRect(rect);
	//CPoint center = rect.CenterPoint();

	//CPoint pt1[5] = {
	//	center,
	//	center + CPoint((int)(sqrt(3) / 2 * RADIUS), -RADIUS / 2),
	//	center + CPoint(0, RADIUS),
	//	center + CPoint((int)(-sqrt(3) / 2 * RADIUS), -RADIUS / 2),
	//	center
	//};
	//CPoint pt2[5] = {
	//	center,
	//	center + CPoint((int)(-sqrt(3) / 2 * RADIUS), RADIUS / 2),
	//	center + CPoint(0, -RADIUS),
	//	center + CPoint((int)(sqrt(3) / 2 * RADIUS), RADIUS / 2),
	//	center
	//};

	//// 绘制已画好的
	//pDC->MoveTo(pt1[0]);
	//pDC->Polyline(pt1, m_index + 1);

	//CPen pen2;
	//pen2.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	//pDC->SelectObject(pen2);

	//// 动态绘图
	//pDC->MoveTo(pt1[m_index]);
	//CPoint t1 = pt1[m_index];
	//CPoint t2 = pt1[m_index + 1];
	//int r = (int)sqrt((t1.x - t2.x) * ((t1.x - t2.x)) + (t1.y - t2.y) * (t1.y - t2.y));
	//m_radius = r;
	//int m = (pt1[m_index + 1].x - pt1[m_index].x);
	//int n = (pt1[m_index + 1].y - pt1[m_index].y);
	//pDC->LineTo(pt1[m_index] + CPoint((int)(1.0*m / r * m_seal), (int)(1.0*n / r * m_seal)));
	//
	//TRACE(_T("r = %d, m = %d, n = %d, m_index = %d, m_seal = %d\n"), r, m, n, m_index, m_seal);
	// //finally, m_index = 4, out of range!

	//// 绘制已画好的 2
	//pDC->MoveTo(pt2[0]);
	//pDC->Polyline(pt2, m_index + 1);

	//// 动态绘图 2
	//t1 = pt2[m_index];
	//t2 = pt2[m_index + 1];
	//r = (int)sqrt((t1.x - t2.x) * ((t1.x - t2.x)) + (t1.y - t2.y) * (t1.y - t2.y));
	//pDC->MoveTo(pt2[m_index]);
	//m = (pt2[m_index + 1].x - pt2[m_index].x);
	//n = (pt2[m_index + 1].y - pt2[m_index].y);
	//pDC->LineTo(pt2[m_index] + CPoint((int)(1.0*m / r * m_seal), (int)(1.0*n / r * m_seal)));


	//////////////////
	// 绘制已画好的
	pDC->MoveTo(m_pt1[0]);
	pDC->Polyline(m_pt1.GetData(), m_index + 1);

	//交错颜色输入，注释掉可表现为同种颜色
	CPen pen2;
	pen2.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	pDC->SelectObject(pen2);

	// 绘制已画好的 2
	pDC->MoveTo(m_pt2[0]);
	pDC->Polyline(m_pt2.GetData(), m_index + 1);

	// 动态绘图
	if (4 == m_index)
		return;
	pDC->MoveTo(m_pt1[m_index]);
	CPoint t1 = m_pt1[m_index];
	CPoint t2 = m_pt1[m_index + 1];
	int r = (int)sqrt((t1.x - t2.x) * ((t1.x - t2.x)) + (t1.y - t2.y) * (t1.y - t2.y));
	m_radius = r;
	int m = (m_pt1[m_index + 1].x - m_pt1[m_index].x);
	int n = (m_pt1[m_index + 1].y - m_pt1[m_index].y);
	pDC->LineTo(m_pt1[m_index] + CPoint((int)(1.0*m / r * m_seal), (int)(1.0*n / r * m_seal)));


	// 动态绘图 2
	t1 = m_pt2[m_index];
	t2 = m_pt2[m_index + 1];
	r = (int)sqrt((t1.x - t2.x) * ((t1.x - t2.x)) + (t1.y - t2.y) * (t1.y - t2.y));

	pDC->MoveTo(m_pt2[m_index]);
	m = (m_pt2[m_index + 1].x - m_pt2[m_index].x);
	n = (m_pt2[m_index + 1].y - m_pt2[m_index].y);
	pDC->LineTo(m_pt2[m_index] + CPoint((int)(1.0*m / r * m_seal), (int)(1.0*n / r * m_seal)));

}

void CSealDlg::DrawCircleOuter(CDC * pDC)
{
	CRect rect;
	GetClientRect(rect);
	int ro = RADIUS + 40;
	CPoint center = rect.CenterPoint();
	CPoint origin = center + CPoint(0, -ro);

	pDC->MoveTo(origin);
	//pDC->MoveTo(rect.CenterPoint() + CPoint(0, -ro));
	pDC->AngleArc(center.x, center.y, ro, 90.0f, m_outer*1.0f);

}




