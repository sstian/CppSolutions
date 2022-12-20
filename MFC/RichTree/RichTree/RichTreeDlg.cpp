
// RichTreeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "RichTree.h"
#include "RichTreeDlg.h"
#include "CDeptDlg.h"
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


// CRichTreeDlg 对话框



CRichTreeDlg::CRichTreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RICHTREE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

int CRichTreeDlg::GetDepth(HTREEITEM item) const
{
	int depth = 1;
	HTREEITEM root = m_tree.GetRootItem();
	while (item != root)
	{
		item = m_tree.GetParentItem(item);
		depth++;
	}
	return depth;
}

CString CRichTreeDlg::GetPath(HTREEITEM item) const
{
	CString strPath;
	while (item)
	{
		// 向上遍历
		strPath = m_tree.GetItemText(item) + _T("\\") + strPath;
		item = m_tree.GetParentItem(item);
	}
	return strPath;
}

void CRichTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_TREE, m_tree);
}

BEGIN_MESSAGE_MAP(CRichTreeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CRichTreeDlg::OnSelchangedTree)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE, &CRichTreeDlg::OnEndlabeleditTree)
	ON_BN_CLICKED(IDC_BTN_ADD_DEPT, &CRichTreeDlg::OnBnClickedBtnAddDept)
	ON_BN_CLICKED(IDC_BTN_DEL_DEPT, &CRichTreeDlg::OnBnClickedBtnDelDept)
	ON_BN_CLICKED(IDC_BTN_ADD_MEMB, &CRichTreeDlg::OnBnClickedBtnAddMemb)
	ON_BN_CLICKED(IDC_BTN_DEL_MEMB, &CRichTreeDlg::OnBnClickedBtnDelMemb)
	ON_BN_CLICKED(IDC_BTN_MOVE, &CRichTreeDlg::OnBnClickedBtnMove)
END_MESSAGE_MAP()


// CRichTreeDlg 消息处理程序

BOOL CRichTreeDlg::OnInitDialog()
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

	// 初始化参数

	m_imagelist.Create(16, 16, ILC_COLOR32 | ILC_MASK, 8, 8);
	m_imagelist.Add(theApp.LoadIcon(IDI_ICON1));
	m_imagelist.Add(theApp.LoadIcon(IDI_ICON2));
	m_imagelist.Add(theApp.LoadIcon(IDI_ICON3));
	m_imagelist.Add(theApp.LoadIcon(IDI_ICON4));
	m_imagelist.Add(theApp.LoadIcon(IDI_ICON5));
	m_imagelist.Add(theApp.LoadIcon(IDI_ICON6));

	//m_list.SetImageList(&m_imagelist, LVSIL_SMALL);		//设置图标
	m_list.InsertColumn(0, _T("工号"), 0, 100);
	m_list.InsertColumn(1, _T("姓名"), 0, 100);
	m_list.InsertColumn(2, _T("工资"), 0, 100);

	m_list.InsertItem(0, _T("孙悟空"), 2);

	
	m_tree.SetBkColor(RGB(200, 255, 255));				//设置背景色
	m_tree.SetImageList(&m_imagelist, TVSIL_NORMAL);	//设置图标
	HTREEITEM root = m_tree.InsertItem(_T("总公司"), 5, 5);
	HTREEITEM item = m_tree.InsertItem(_T("www.snowflake.com"), 1, 4, root);
	m_tree.InsertItem(_T("行政部"), 2, 3, item);
	m_tree.InsertItem(_T("人事部"), 2, 3, item);
	m_tree.InsertItem(_T("财务部"), 2, 3, item);
	m_tree.Expand(item, TVE_EXPAND);					//展开

	HTREEITEM item2 = m_tree.InsertItem(_T("study.163.com"),1, 4,  root);
	m_tree.InsertItem(_T("办事处"), 2, 3, item2);
	m_tree.InsertItem(_T("国资处"), 2, 3, item2);
	m_tree.InsertItem(_T("设备处"), 2, 3, item2);
	m_tree.Expand(item2, TVE_EXPAND);

	m_tree.Expand(root, TVE_EXPAND);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
//#define LVSIL_NORMAL            0
//#define LVSIL_SMALL             1
//#define LVSIL_STATE             2
//#define LVSIL_GROUPHEADER       3

//#define TVSIL_NORMAL            0
//#define TVSIL_STATE             2



void CRichTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRichTreeDlg::OnPaint()
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
HCURSOR CRichTreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRichTreeDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CRichTreeDlg::OnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW p = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	HTREEITEM item = p->itemNew.hItem;
	int depth = this->GetDepth(item);
	GetDlgItem(IDC_BTN_ADD_DEPT)->EnableWindow(2 == depth);
	GetDlgItem(IDC_BTN_DEL_DEPT)->EnableWindow(3 == depth);
	GetDlgItem(IDC_BTN_ADD_MEMB)->EnableWindow(3 == depth);
	GetDlgItem(IDC_BTN_DEL_MEMB)->EnableWindow(3 == depth);
	SetDlgItemText(IDC_STATUS, this->GetPath(item));

	*pResult = 0;
}


void CRichTreeDlg::OnEndlabeleditTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO p = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	
	HTREEITEM item = p->item.hItem;
	CEdit* pEdit = m_tree.GetEditControl();
	CString str;
	pEdit->GetWindowText(str);
	m_tree.SetItemText(item, str);

	*pResult = 0;
}
//typedef struct tagTVDISPINFOW {
//	NMHDR hdr;
//	TVITEMW item;
//} NMTVDISPINFOW, *LPNMTVDISPINFOW;


void CRichTreeDlg::OnBnClickedBtnAddDept()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CRichTreeDlg::OnBnClickedBtnDelDept()
{
	HTREEITEM item = m_tree.GetSelectedItem();
	CString str = m_tree.GetItemText(item);
	if (IDYES == AfxMessageBox(_T("确定删除 ") + str + _T(" 吗？"), MB_YESNO))
		m_tree.DeleteItem(item);
}


void CRichTreeDlg::OnBnClickedBtnAddMemb()
{
	CString str;
	GetDlgItemText(IDC_EDIT_NUMB, str);
	int count = m_list.GetItemCount();
	m_list.InsertItem(count, str);
	GetDlgItemText(IDC_EDIT_NAME, str);
	m_list.SetItemText(count, 1, str);
	GetDlgItemText(IDC_EDIT_SALA, str);
	m_list.SetItemText(count, 2, str);
}


void CRichTreeDlg::OnBnClickedBtnDelMemb()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CRichTreeDlg::OnBnClickedBtnMove()
{
	CDeptDlg dept;
	dept.DoModal();
}
