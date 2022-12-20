
// VirtualListDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "VirtualList.h"
#include "VirtualListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVirtualListDlg 对话框



CVirtualListDlg::CVirtualListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIRTUALLIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_strArray.RemoveAll();
	m_count = 0;
	m_pState = nullptr;
}

CVirtualListDlg::~CVirtualListDlg()
{
	m_strArray.RemoveAll();
	m_count = 0;
	delete[] m_pState;

}

void CVirtualListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CVirtualListDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, &CVirtualListDlg::OnGetdispinfoList)
	ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST, &CVirtualListDlg::OnOdfinditemList)
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST, &CVirtualListDlg::OnOdcachehintList)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CVirtualListDlg::OnClickList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CVirtualListDlg::OnDblclkList)
END_MESSAGE_MAP()


// CVirtualListDlg 消息处理程序

BOOL CVirtualListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 列表初始化
	m_list.InsertColumn(0, _T("通用 & 模板创建时间"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(1, _T("订货号"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(2, _T("模板图像路径"), LVCFMT_LEFT, 330);
	// LVS_EX_DOUBLEBUFFER 用来防止闪烁
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_DOUBLEBUFFER);

	fileInform.SetFileName(_T("./image_inform-100000.ini"));
	fileInform.GetProfileSectionNames(m_strArray);

	m_count = static_cast<int>(m_strArray.GetCount());
	m_pState = new BOOL[m_count]{ FALSE };
	// 设置显示数据行数
	m_list.SetItemCount(m_count);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVirtualListDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVirtualListDlg::OnPaint()
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
HCURSOR CVirtualListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVirtualListDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CWnd* pwnd = GetDlgItem(IDC_LIST);
	if (pwnd)
	{
		CRect rect;
		GetClientRect(rect);
		pwnd->MoveWindow(rect);
	}

}

// 控件请求数据
void CVirtualListDlg::OnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

	LVITEM* pItem = &(pDispInfo)->item;
	int iItemIndex = pItem->iItem;	//行号
	if (iItemIndex < 0 || iItemIndex >= m_count)
		return;

	const CString& strSection = m_strArray.GetAt(iItemIndex);
	CString text;
	text.Empty();
	if (pItem->mask & LVIF_TEXT)	//字符串缓冲区有效
	{
		switch (pItem->iSubItem)	//列号
		{
		case 0:
			fileInform.GetProfileString(strSection, _T("CreateTime"), text);
			break;
		case 1:
			text = strSection;
			break;
		case 2:
			fileInform.GetProfileString(strSection, _T("ImagePath"), text);
			break;
		}
	}
	// pItem->cchTextMax == 260
	lstrcpyn(pItem->pszText, text, pItem->cchTextMax);

	// 显示复选框
	pItem->mask |= LVIF_STATE;
	pItem->stateMask = LVIS_STATEIMAGEMASK;
	pItem->state = INDEXTOSTATEIMAGEMASK((m_pState[iItemIndex] ? 2 : 1));	// 1-未选中，2-选中
	
	*pResult = 0;
}

// 查找数据
void CVirtualListDlg::OnOdfinditemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVFINDITEM pFindInfo = reinterpret_cast<LPNMLVFINDITEM>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

// 缓冲部分数据
void CVirtualListDlg::OnOdcachehintList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCACHEHINT pCacheHint = reinterpret_cast<LPNMLVCACHEHINT>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CVirtualListDlg::OnClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	LVHITTESTINFO hitinfo;
	hitinfo.pt = pActivate->ptAction;

	int item = m_list.HitTest(&hitinfo);
	if (item != -1)
	{
		// 只单击在CheckBox上，状态切换与重绘
		if (LVHT_ONITEMSTATEICON == hitinfo.flags)
		{
			m_pState[item] = !m_pState[item];
			m_list.RedrawItems(item, item);
		}
	}
	*pResult = 0;
}


void CVirtualListDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pItemActivate->iItem != -1)
	{
		int item = pItemActivate->iItem;
		CString strModel = m_list.GetItemText(item, 1);
		CString strPath = m_list.GetItemText(item, 2);

		CString common = m_pState[item] ? _T("1") : _T("0");
		CString msg= common + _T("\\") + strPath;
		AfxMessageBox(msg);

	}
	*pResult = 0;
}

/*
LPWSTR WINAPI lstrcpynW(
	_Out_writes_(iMaxLength) LPWSTR lpString1,
	_In_ LPCWSTR lpString2,
	_In_ int iMaxLength
	);

typedef struct tagLVITEMW
{
	UINT mask;
	int iItem;
	int iSubItem;
	UINT state;
	UINT stateMask;
	LPWSTR pszText;
	int cchTextMax;
	int iImage;
	LPARAM lParam;
	int iIndent;
#if (NTDDI_VERSION >= NTDDI_WINXP)
	int iGroupId;
	UINT cColumns; // tile view columns
	PUINT puColumns;
#endif
#if (NTDDI_VERSION >= NTDDI_VISTA)
	int* piColFmt;
	int iGroup; // readonly. only valid for owner data.
#endif
} LVITEMW, *LPLVITEMW;

#define LVIF_TEXT               0x00000001
#define LVIF_IMAGE              0x00000002
#define LVIF_PARAM              0x00000004
#define LVIF_STATE              0x00000008
#define LVIF_INDENT             0x00000010
#define LVIF_NORECOMPUTE        0x00000800
#if (NTDDI_VERSION >= NTDDI_WINXP)
#define LVIF_GROUPID            0x00000100
#define LVIF_COLUMNS            0x00000200
#endif

*/
