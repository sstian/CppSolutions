
// PetDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Pet.h"
#include "PetDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPetDlg 对话框



CPetDlg::CPetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_index = 0;
	m_count = -1;

	m_texts.Add(_T("哈哈哈"));
	m_texts.Add(_T("你好啊"));
	m_texts.Add(_T("你好坏"));
	m_texts.Add(_T("拜拜咯"));
}

void CPetDlg::SetFont()
{
	CFont* pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lf.lfHeight *= 5;
	lf.lfWidth = 900;
	_tcscpy_s(lf.lfFaceName, _T("幼圆"));
	m_font.CreateFontIndirectW(&lf);
}

void CPetDlg::TextToRgn()
{
	CRect rect(0, 0, m_mdcText.GetWidth(), m_mdcText.GetHeight());
	int size = (int)m_texts.GetSize();
	for (int i = 0; i < size; i++)
	{
		m_mdcText.DrawText(m_texts.GetAt(i), rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		CRgn* pRgn = new CRgn;
		m_mdcText.MakeRgn(*pRgn, GetSysColor(COLOR_WINDOW));
		m_rgns.Add(pRgn);
	}
}

void CPetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPetDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCRBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPetDlg 消息处理程序

BOOL CPetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 加载资源
	for (int index = 0; index < BUTTER_COUNT; index++)
	{
		m_mdcButter[index].LoadBitmapW(IDB_BUTTERFLY01 + index);
		m_mdcButter[index].MakeRgn(m_rgnButter[index], RGB(255, 255, 255));
		//m_rgnButter[index].OffsetRgn(0, 50);

	}
	m_mdc.Create(m_mdcButter->GetWidth(), m_mdcButter->GetHeight());


	MoveWindow(0, 0, m_mdcButter->GetWidth(), m_mdcButter->GetHeight(), FALSE);

	CRgn rgn;
	rgn.CreateRectRgn(0, 0, 0, 0);		//拷贝前还得创建，无语
	rgn.CopyRgn(m_rgnButter);
	SetWindowRgn(rgn, FALSE);

	// 消除任务栏显示
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	this->SetFont();

	CRect rect;
	GetClientRect(rect);
	rect.bottom = 50;
	m_mdcText.Create(rect.Width(), rect.Height());
	m_mdcText.SelectObject(m_font);
	m_mdcText.FillSolidRect(rect, GetSysColor(COLOR_WINDOW));

	this->TextToRgn();
	SetTimer(TIMER_PET, 50, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPetDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rect;
	GetClientRect(rect);
	m_mdc.FillSolidRect(rect, RGB(255, 255, 255));	//GetSysColor(COLOR_3DFACE)

	m_mdcButter[m_index].BitTrans(0, 0, m_mdcButter->GetWidth(), m_mdcButter->GetHeight(),
		&m_mdc, 0, 0, RGB(255, 255, 255));
	m_mdc.BitTrans(0, 0, m_mdcButter->GetWidth(), m_mdcButter->GetHeight(),
		&dc, 0, 0, RGB(255, 255, 255));

	//rect.bottom = 50;
	//dc.FillSolidRect(rect, RGB(255, 0, 0));
	//dc.BitBlt(0, 0, m_mdcButter->GetWidth(), m_mdcButter->GetHeight(), 
	//	&m_mdc, 0, 0, SRCCOPY);

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
HCURSOR CPetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPetDlg::OnTimer(UINT_PTR nIDEvent)
{
	CRgn rgn;
	rgn.CreateRectRgn(0, 0, 0, 0);
	rgn.CopyRgn(m_rgnButter + m_index);						// => &m_rgnButter[m_index]
	
	if(m_count > -1 && m_count < m_texts.GetSize())
		rgn.CombineRgn(&rgn, m_rgns.GetAt(m_count), RGN_OR);	//组合蝴蝶与文字裁剪区

	SetWindowRgn(rgn, TRUE);								//BOOL ReDraw: TRUE / FALSE

	if (++m_index >= BUTTER_COUNT)
		m_index = 0;

	Invalidate(FALSE);

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CPetDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CPetDlg::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnNcPaint()
}


LRESULT CPetDlg::OnNcHitTest(CPoint point)
{
	return HTCAPTION;
	//return CDialogEx::OnNcHitTest(point);
}


void CPetDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	int size = (int)m_texts.GetSize();
	if (++m_count >= size)
		m_count = -1;

	CDialogEx::OnNcLButtonDblClk(nHitTest, point);
}


void CPetDlg::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	this->DestroyWindow();

	CDialogEx::OnNcRButtonDown(nHitTest, point);
}


void CPetDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 释放指针
	int size = (int)m_rgns.GetSize();
	while (size)
		delete m_rgns[--size];
}
