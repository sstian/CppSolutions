
// CaptionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Caption.h"
#include "CaptionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCaptionDlg 对话框



CCaptionDlg::CCaptionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAPTION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCaptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCaptionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()


// CCaptionDlg 消息处理程序

BOOL CCaptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCaptionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCaptionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCaptionDlg::DrawColorTitle(CRect & rect, COLORREF cofirst, COLORREF colast, CDC* pdc)
{
	int cx = rect.Width();
	int red = GetRValue(colast) - GetRValue(cofirst);
	int green = GetGValue(colast) - GetGValue(cofirst);
	int blue = GetBValue(colast) - GetBValue(cofirst);
	int r, g, b;
	CPen* pOldPen = pdc->GetCurrentPen();
	for (int i = 0; i < cx; i++)
	{
		// 每单位像素的颜色值
		r = GetRValue(cofirst) + i * red / cx;
		g = GetGValue(cofirst) + i * green / cx;
		b = GetBValue(cofirst) + i * blue / cx;
		CPen pen(PS_SOLID, 1, RGB(r, g, b));
		pdc->SelectObject(&pen);
		pdc->MoveTo(i, 0);
		pdc->LineTo(i, rect.bottom);
	}
	if (pOldPen)
		pdc->SelectObject(pOldPen);	//选择回去旧的笔
}

// 非客户区绘制，过渡色，（效果不是很好。。。）
void CCaptionDlg::OnNcPaint()
{
	// 转换为非客户区坐标
	CWindowDC wdc(this);
	CRect rect, rt;
	GetWindowRect(rect);
	rect.OffsetRect(-rect.left, -rect.top);
	rt = rect;
	rt.bottom = 30;
	this->DrawColorTitle(rect, RGB(115, 158, 115), RGB(165, 186, 190), &wdc);			//绘制颜色
	wdc.SetTextColor(RGB(128, 255, 0));
	wdc.SetBkMode(TRANSPARENT);
	wdc.DrawText(_T("欢迎使用本软件！"), rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//绘制标题文字
	rt.right -= 5;
	rt.top += 5;
	rt.bottom -= 5;
	rt.left = rt.right - rt.Height();	
	rt.OffsetRect(-5, 4);					 // 高度收缩，宽度相同，坐标移动
	CBrush brush(RGB(255, 255, 0));
	wdc.SelectObject(brush);
	wdc.Rectangle(rt);
	wdc.MoveTo(rt.TopLeft());															//绘制交叉关闭框
	wdc.LineTo(rt.BottomRight());
	wdc.MoveTo(rt.right, rt.top);
	wdc.LineTo(rt.left, rt.bottom);

}
