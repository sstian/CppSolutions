
// PageDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Page.h"
#include "PageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPageDlg 对话框



CPageDlg::CPageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hCursor = theApp.LoadStandardCursor(IDC_HAND);	//手形光标
	m_index = 0;

	CString strNumber;
	for (int i = 0; i < PAGE_COUNT; i++)
	{
		// "xbox_1.jpg"
		strNumber.Format(_T("%d"), i + 1);
		m_strImages[i] = _T("./res/xbox_") + strNumber + _T(".jpg");

		m_pBitmaps[i] = new CBitmap;

	}
}

CPageDlg::~CPageDlg()
{
	for (int i = 0; i < PAGE_COUNT; i++)
		delete m_pBitmaps[i];
}

void CPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CPageDlg 消息处理程序

BOOL CPageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 方法1.2 加载位图
	for (int index = 0; index < PAGE_COUNT; index++)
		m_bitmaps[index].LoadBitmapW(IDB_BITMAP_XBOX_100 + index);
	BITMAP bitmap;
	m_bitmaps[0].GetBitmap(&bitmap);
	SetWindowPos(nullptr, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SWP_NOMOVE);

	//// 方法2.2 加载jpg
	//CImage image;
	//for (int index = 0; index < PAGE_COUNT; index++)
	//{
	//	image.Load(m_strImages[index]);//m_strImages[index]
	//	//image.LoadFromResource(AfxGetInstanceHandle(), IDR_IMAGE_XBOX_1 + index);	//？为什么不行哎
	//	m_pBitmaps[index] = CBitmap::FromHandle(image.Detach());	//HBITMAP
	//}

	// 设置切换矩形区域
	CRect rect(800, 650, 850, 700);
	for (int i = 0; i < PAGE_COUNT; i++)
	{
		m_rects[i] = rect;
		rect.OffsetRect(70, 0);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPageDlg::OnPaint()
{
	// 绘制图片
	//防止数组下标越界
	if (m_index < 0 || m_index >= PAGE_COUNT)
		return;
	CPaintDC dc(this); // 用于绘制的设备上下文
	CDC mdc;
	mdc.CreateCompatibleDC(&dc);
	mdc.SelectObject(m_bitmaps + m_index);	//m_bitmaps[m_index]
	//mdc.SelectObject(*(m_pBitmaps + m_index));	//m_pBitmaps[m_index]
	CRect rectClient;
	GetClientRect(rectClient);
	dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &mdc, 0, 0, SRCCOPY);

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
HCURSOR CPageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPageDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	for (int index = 0; index < PAGE_COUNT; index++)
	{
		if (m_rects[index].PtInRect(point))
		{
			SetCursor(m_hCursor);
			if (m_index != index)
			{
				m_index = index;
				Invalidate(FALSE);
				break;
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


//void CPageDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	for (int index = 0; index < PAGE_COUNT; index++)
//	{
//		if(m_rects[index].PtInRect(point) && m_index != index)
//		{ 
//			m_index = index;
//			Invalidate(FALSE);
//			break;
//		}
//	}
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//}
