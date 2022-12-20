
// LoadImageDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LoadImage.h"
#include "LoadImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLoadImageDlg 对话框



CLoadImageDlg::CLoadImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOADIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoadImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLoadImageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOADICON, &CLoadImageDlg::OnBnClickedBtnLoadicon)
	ON_BN_CLICKED(IDC_BTN_LOADBITMAP, &CLoadImageDlg::OnBnClickedBtnLoadbitmap)
	ON_BN_CLICKED(IDC_BTN_LOADIMAGE, &CLoadImageDlg::OnBnClickedBtnLoadimage)
	ON_BN_CLICKED(IDC_BTN_CIMAGE, &CLoadImageDlg::OnBnClickedBtnCimage)
	ON_BN_CLICKED(IDC_BTN_CMEMORYDC, &CLoadImageDlg::OnBnClickedBtnCmemorydc)
	ON_BN_CLICKED(IDC_LOAD, &CLoadImageDlg::OnBnClickedLoad)
END_MESSAGE_MAP()


// CLoadImageDlg 消息处理程序

BOOL CLoadImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 只能从资源中加载
	m_hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), (LPCTSTR)IDB_BITMAP);
	m_cBitmap.LoadBitmapW(IDB_BITMAP);
	//m_cBitmap.LoadBitmapW((LPCTSTR)IDB_BITMAP);

	//m_mdc.LoadBitmapW(IDB_BITMAP);
	m_mdc.LoadBitmapW(_T("res/image_bmp.bmp"));
	//m_mdc.LoadBitmapW(_T("res/image_jpg.jpg"));
	//m_mdc.LoadBitmapW(_T("res/image_gif.gif"));

	//m_mdc2.Load(_T("./res/image_bmp.bmp"));
	//m_mdc2.Load(_T("./res/image_jpg.jpg"));
	//m_mdc2.Load(_T("./res/image_gif.gif"));
	m_mdc2.Load(_T("./res/image_png.png"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLoadImageDlg::OnPaint()
{
	//CPaintDC dc(this); // 用于绘制的设备上下文
	//CDC mdc;
	//mdc.CreateCompatibleDC(&dc);
	////mdc.SelectObject(m_hBitmap);
	//mdc.SelectObject(m_cBitmap);

	//BITMAP bitmap;
	//////::GetObject(m_hBitmap, sizeof(bitmap), &bitmap);
	////::GetObject(m_cBitmap, sizeof(bitmap), &bitmap);
	//m_cBitmap.GetBitmap(&bitmap);
	//dc.BitBlt(0, 0, bitmap.bmWidth, bitmap.bmWidth, &mdc, 0, 0, SRCCOPY);

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
HCURSOR CLoadImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLoadImageDlg::OnBnClickedBtnLoadicon()
{
	// 只能从内部资源加载
	//theApp.m_hInstance or AfxGetApp()->m_hInstance
	static HICON hIcon = ::LoadIcon(AfxGetInstanceHandle(), (LPCTSTR)IDI_ICON);
	////static HICON hIcon = ::LoadIcon(AfxGetInstanceHandle(), _T("./res/image_ico.ico"));
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);
}


void CLoadImageDlg::OnBnClickedBtnLoadbitmap()
{
	//m_hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), (LPCTSTR)IDB_BITMAP);
}


void CLoadImageDlg::OnBnClickedBtnLoadimage()
{  
	Invalidate(TRUE);

	//从内部资源加载
	//static HICON hIcon = (HICON)::LoadImage(AfxGetInstanceHandle(), (LPCTSTR)IDI_ICON, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
	//从外部文件加载
	static HICON hIcon = (HICON)::LoadImage(nullptr, _T("./res/image_ico.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);
	//DestroyIcon(hIcon);
	
	//从内部资源加载   
	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
	//从外部文件加载
	//HBITMAP hBitmap = (HBITMAP)::LoadImage(nullptr, _T("./res/image_bmp.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	CPaintDC dc(this);
	CDC mdc;
	mdc.CreateCompatibleDC(&dc);
	mdc.SelectObject(hBitmap);
	BITMAP bitmap;
	::GetObject(hBitmap, sizeof(bitmap), &bitmap);
	dc.BitBlt(0, 0, bitmap.bmWidth, bitmap.bmWidth, &mdc, 0, 0, SRCCOPY);
	DeleteObject(hBitmap);

}

/***
HANDLE WINAPI LoadImageW(
	_In_opt_ HINSTANCE hInst,
	_In_ LPCWSTR name,
	_In_ UINT type,
	_In_ int cx,
	_In_ int cy,
	_In_ UINT fuLoad);

// 释放资源
Bitmap	- DeleteObject(HGDIOBJ)
ICON	- DestroyIcon(HICON)
Cursor	- DestroyCursor(HCURSOR)

#define IMAGE_BITMAP        0
#define IMAGE_ICON          1
#define IMAGE_CURSOR        2

#define LR_DEFAULTCOLOR     0x00000000	//
#define LR_MONOCHROME       0x00000001
#define LR_COLOR            0x00000002
#define LR_COPYRETURNORG    0x00000004
#define LR_COPYDELETEORG    0x00000008
#define LR_LOADFROMFILE     0x00000010	//
#define LR_LOADTRANSPARENT  0x00000020
#define LR_DEFAULTSIZE      0x00000040	//
#define LR_VGACOLOR         0x00000080
#define LR_LOADMAP3DCOLORS  0x00001000
#define LR_CREATEDIBSECTION 0x00002000
#define LR_COPYFROMRESOURCE 0x00004000
#define LR_SHARED           0x00008000

// Ternary raster operations
#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   
#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           
#define SRCAND              (DWORD)0x008800C6 /* dest = source AND dest          
#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest         
#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   
#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             
#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) 
#define MERGECOPY           (DWORD)0x00C000CA /* dest = (source AND pattern)     
#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     
#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  
#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   
#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         
#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               
#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    
#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE                    
**/

void CLoadImageDlg::OnBnClickedBtnCimage()
{
	Invalidate(TRUE);

	// 将 BMP / JPG / GIF / PNG 转为 BMP
	CImage image;
	//从外部文件加载
	//image.Load(_T("./res/image_bmp.bmp"));
	//image.Load(_T("./res/image_jpg.jpg"));
	//image.Load(_T("./res/image_gif.gif"));
	image.Load(_T("./res/image_png.png"));
	//从资源中加载不出来，舍弃！
	//image.LoadFromResource(AfxGetInstanceHandle(), IDB_PNG);
	CBitmap* pBitmap = CBitmap::FromHandle(image.Detach());

	CPaintDC dc(this);
	CDC mdc;
	mdc.CreateCompatibleDC(&dc);
	mdc.SelectObject(pBitmap);
	BITMAP bitmap;
	pBitmap->GetBitmap(&bitmap);
	dc.BitBlt(0, 0, bitmap.bmWidth, bitmap.bmHeight, &mdc, 0, 0, SRCCOPY);

	pBitmap->DeleteObject();

}


void CLoadImageDlg::OnBnClickedBtnCmemorydc()
{
	Invalidate(TRUE);

	CPaintDC dc(this);
	dc.BitBlt(0, 0, m_mdc.GetWidth(), m_mdc.GetHeight(), &m_mdc, 0, 0, SRCCOPY);
}


void CLoadImageDlg::OnBnClickedLoad()
{
	Invalidate(TRUE);

	CPaintDC dc(this);

	dc.BitBlt(0, 0, m_mdc2.GetWidth(), m_mdc2.GetHeight(), &m_mdc2, 0, 0, SRCCOPY);
}
