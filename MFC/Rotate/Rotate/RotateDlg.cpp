
// RotateDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Rotate.h"
#include "RotateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRotateDlg 对话框



CRotateDlg::CRotateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROTATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_left = 0;
	m_dir = 5;
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRotateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRotateDlg 消息处理程序

BOOL CRotateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 加载图像
	//m_bitmap.LoadBitmapW(IDB_BITMAP_XBOX_200);
	//BITMAP bitmap;
	//m_bitmap.GetBitmap(&bitmap);
	//SetWindowPos(nullptr, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SWP_NOMOVE);

	m_mdcBack.LoadBitmapW(IDB_BITMAP_XBOX_200);
	SetWindowPos(nullptr, 0, 0, m_mdcBack.GetWidth(), m_mdcBack.GetHeight(), SWP_NOMOVE);

	m_mdc.Create(m_mdcBack.GetWidth(), m_mdcBack.GetHeight());

	SetTimer(3, 12, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRotateDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	//CDC mdc;
	//mdc.CreateCompatibleDC(&dc);
	//mdc.SelectObject(m_bitmap);
	//CRect rectClient;
	//GetClientRect(rectClient);
	//dc.SetStretchBltMode(COLORONCOLOR);
	//dc.StretchBlt(m_left, 0, rectClient.Width() - m_left * 2, rectClient.Height(), 
	//	&mdc, 0, 0, rectClient.Width(), rectClient.Height(), SRCCOPY);
	//// 分三块区域绘制，以消除闪烁
	//CRect rect = rectClient;
	//if (m_dir > 0)		//正向
	//{
	//	// m_left逐渐递增，空白区域也增加
	//	if (m_left <= rectClient.Width() / 2)
	//	{
	//		rect.left = 0;
	//		rect.right = m_left;
	//		dc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));

	// 方案二：双缓冲
	//CRect rect(0, 0, m_mdcBack.GetWidth(), m_mdcBack.GetHeight());
	//背景DC m_mdc
	CRect rect;
	GetClientRect(rect);
	m_mdc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
	//图片DC m_mdcBack -> m_mdc
	m_mdc.SetStretchBltMode(COLORONCOLOR);
	m_mdc.StretchBlt(m_left, 0, rect.Width() - m_left * 2, rect.Height(),
		&m_mdcBack, 0, 0, m_mdcBack.GetWidth(), m_mdcBack.GetHeight(), SRCCOPY);
	//界面DC m_mdc -> dc
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_mdc, 0, 0, SRCCOPY);

	//		rect.left = rectClient.Width() - m_left;
	//		rect.right = rectClient.right;
	//		dc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
	//	}
	//	//缩小至中轴线，然后扩展直接用图像填充，故不需要填充底色
	//}
	//else			//反向
	//{
	//	// m_left逐渐减小，但空白区域增加
	//	if (m_left >= rectClient.Width() / 2)
	//	{
	//		rect.left = 0;
	//		rect.right = rectClient.Width() - m_left;
	//		dc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));

	//		rect.left = m_left;
	//		rect.right = rectClient.right;
	//		dc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
	//	}
	//}

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
HCURSOR CRotateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRotateDlg::OnTimer(UINT_PTR nIDEvent)
{
	//触发重绘
	m_left += m_dir;
	//Invalidate(TRUE);	//TRUE - 窗口原本颜色清理
	Invalidate(FALSE);//TRUE - 窗口原本颜色清理

	//反向
	CRect rectClient;
	GetClientRect(rectClient);
	if (m_left >= rectClient.Width() || m_left <= 0)
		m_dir = -m_dir;

	TRACE("m_left = %d, rect.Width() = %d\n", m_left, rectClient.Width());
	CDialogEx::OnTimer(nIDEvent);
}
