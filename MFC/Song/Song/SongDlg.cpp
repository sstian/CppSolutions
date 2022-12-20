
// SongDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Song.h"
#include "SongDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSongDlg 对话框



CSongDlg::CSongDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SONG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_index = 0;
	m_left = 0;

	m_texts.Add(_T("风是穿山过水拂面而来"));
	m_texts.Add(_T("花是零落成泥常开不败"));
	m_texts.Add(_T("雪是日出消融檐上落白"));
	m_texts.Add(_T("月是咫尺天涯千秋万载"));

}

void CSongDlg::DrawColor(CRect  rect, COLORREF cofirst, COLORREF colast, CDC * pdc)
{
	CRect rt;
	m_rgns[0]->GetRgnBox(rt);
	rect.bottom = rt.bottom + 20;

	int cy = rect.Height();
	int red = GetRValue(colast) - GetRValue(cofirst);
	int green = GetGValue(colast) - GetGValue(cofirst);
	int blue = GetBValue(colast) - GetBValue(cofirst);
	int r, g, b;
	CPen* pOldPen = pdc->GetCurrentPen();
	for (int i = 0; i < cy; i++)
	{
		// 每单位像素的颜色值
		r = GetRValue(cofirst) + i * red / cy;
		g = GetGValue(cofirst) + i * green / cy;
		b = GetBValue(cofirst) + i * blue / cy;
		CPen pen(PS_SOLID, 1, RGB(r, g, b));
		pdc->SelectObject(&pen);
		pdc->MoveTo(0, i);
		pdc->LineTo(rect.right, i);
	}
	if (pOldPen)
		pdc->SelectObject(pOldPen);	//选择回去旧的笔
}

void CSongDlg::TextToRgn()
{
	int size = (int)m_texts.GetSize();

	COLORREF color = GetSysColor(COLOR_WINDOW);
	for (int i = 0; i < size; i++)
	{
		m_mdc.FillSolidRect(0, 0, m_mdc.GetWidth(), m_mdc.GetHeight(), color);
		m_mdc.TextOutW(20, 20, m_texts.GetAt(m_index));
		CRgn* pRgn = new CRgn;	
		m_mdc.MakeRgn(*pRgn, color);
		m_rgns.Add(pRgn);
	}
}

void CSongDlg::SetRgn()
{
	CRgn rgn;
	rgn.CreateRectRgn(0, 0, 0, 0);
	rgn.CopyRgn(m_rgns.GetAt(m_index));
	rgn.OffsetRgn(1, 1);
	SetWindowRgn(rgn, TRUE);
}

void CSongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSongDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CSongDlg 消息处理程序

BOOL CSongDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CFont* pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lf.lfHeight = 50;
	lf.lfWeight = 100;
	_tcscpy_s(lf.lfFaceName, _T("幼圆"));
	m_font.CreateFontIndirectW(&lf);

	CRect rect;
	GetClientRect(rect);
	m_mdc.Create(rect.Width(), rect.Height());
	m_mdc.SelectObject(m_font);

	this->TextToRgn();
	this->SetRgn();

	m_mdcFront.Create(rect.Width(), rect.Height());
	m_mdcBack.Create(rect.Width(), rect.Height());
	this->DrawColor(rect, RGB(255, 255, 0), RGB(255, 128, 0), &m_mdcFront);
	this->DrawColor(rect, RGB(255, 128, 0), RGB(255, 0, 0), &m_mdcBack);


	SetTimer(777, 1000, nullptr);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSongDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	//CRect rect;
	//GetClientRect(rect);
	//COLORREF color = GetSysColor(COLOR_WINDOW);
	//m_mdc.FillSolidRect(rect, color);
	//m_mdc.SelectObject(m_font);
	//m_mdc.TextOutW(20, 20, m_texts.GetAt(m_index));
	//CRgn rgn;
	//m_mdc.MakeRgn(rgn, color);
	//m_mdc.SelectObject(rgn);
	//m_mdc.FillSolidRect(rect, RGB(255, 0, 0));
	//dc.SelectObject(m_rgns.GetAt(m_index));
	dc.SelectObject(m_rgns[m_index]);
	dc.BitBlt(m_left , 0, m_mdc.GetWidth(), m_mdc.GetHeight(), &m_mdcFront, 0, 0, SRCCOPY);

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
HCURSOR CSongDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSongDlg::OnTimer(UINT_PTR nIDEvent)
{
	CRect rect;
	m_rgns[m_index]->GetRgnBox(rect);
	if (++m_left > rect.right)
	{
		m_left = 20;
		if (++m_index > m_texts.GetSize())
			m_index = 0;
		this->SetRgn();
		Invalidate();
		return;
	}
	Invalidate(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


LRESULT CSongDlg::OnNcHitTest(CPoint point)
{
	return HTCAPTION;

	//return CDialogEx::OnNcHitTest(point);
}
