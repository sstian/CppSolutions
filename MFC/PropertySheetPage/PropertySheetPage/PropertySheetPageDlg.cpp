
// PropertySheetPageDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "PropertySheetPage.h"
#include "PropertySheetPageDlg.h"
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


// CPropertySheetPageDlg 对话框



CPropertySheetPageDlg::CPropertySheetPageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROPERTYSHEETPAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPropertySheetPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CPropertySheetPageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_WIZARD, &CPropertySheetPageDlg::OnBnClickedBtnWizard)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CPropertySheetPageDlg::OnBnClickedBtnModify)
	ON_NOTIFY(LVN_HOTTRACK, IDC_LIST, &CPropertySheetPageDlg::OnHottrackList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CPropertySheetPageDlg::OnDblclkList)
END_MESSAGE_MAP()


// CPropertySheetPageDlg 消息处理程序

BOOL CPropertySheetPageDlg::OnInitDialog()
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
	m_list.InsertColumn(0, _T("帐号"), 0, 100);
	m_list.InsertColumn(1, _T("昵称"), 0, 100);
	m_list.InsertColumn(2, _T("性别"), 0, 100);
	m_list.InsertColumn(3, _T("生日"), 0, 100);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_infoDlg.Create(IDD_INFO_DIALOG, GetDesktopWindow());
	m_infoDlg.m_pList = &m_list;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPropertySheetPageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPropertySheetPageDlg::OnPaint()
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
HCURSOR CPropertySheetPageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPropertySheetPageDlg::OnBnClickedBtnWizard()
{
	CMFCPropertySheet sheet(_T("注册向导"));
	
	CPage1 page1;
	CPage2 page2;
	CPage3 page3;
	sheet.AddPage(&page1);
	sheet.AddPage(&page2);
	sheet.AddPage(&page3);

	sheet.SetWizardMode();
	if (IDCANCEL == sheet.DoModal())
		return;

	int item = m_list.GetItemCount();
	m_list.InsertItem(item, page1.m_szAccount);
	m_list.SetItemText(item, 1, page1.m_szNickname);
	m_list.SetItemText(item, 2, page1.m_sex ? _T("女") : _T("男"));
	m_list.SetItemText(item, 3, page2.m_birth.Format());

	// 不可见数据存储
	struct SInfo* pInfo = new SInfo;
	pInfo->account = page1.m_szAccount;
	pInfo->nickname = page1.m_szNickname;
	pInfo->sex = page1.m_sex;
	pInfo->birth = page2.m_birth;
	pInfo->blood = page2.m_szBlood;
	pInfo->native = page2.m_szNative;
	pInfo->phone = page3.m_szPhone;
	pInfo->address = page3.m_szAddress;
	pInfo->email = page3.m_szEmail;

	m_list.SetItemData(item, (DWORD_PTR)pInfo);
}
/***
//----- PropSheet Header related ---------
#define PSH_DEFAULT             0x00000000
#define PSH_PROPTITLE           0x00000001
#define PSH_USEHICON            0x00000002
#define PSH_USEICONID           0x00000004
#define PSH_PROPSHEETPAGE       0x00000008
#define PSH_WIZARDHASFINISH     0x00000010
#define PSH_WIZARD              0x00000020
#define PSH_USEPSTARTPAGE       0x00000040
#define PSH_NOAPPLYNOW          0x00000080
#define PSH_USECALLBACK         0x00000100
#define PSH_HASHELP             0x00000200
#define PSH_MODELESS            0x00000400
#define PSH_RTLREADING          0x00000800
#define PSH_WIZARDCONTEXTHELP   0x00001000
//----- New flags for wizard97 -----------
#define PSH_WIZARD97            0x01000000
#define PSH_WATERMARK           0x00008000
#define PSH_USEHBMWATERMARK     0x00010000  // user pass in a hbmWatermark instead of pszbmWatermark
#define PSH_USEHPLWATERMARK     0x00020000  //
#define PSH_STRETCHWATERMARK    0x00040000  // stretchwatermark also applies for the header
#define PSH_HEADER              0x00080000
#define PSH_USEHBMHEADER        0x00100000
#define PSH_USEPAGELANG         0x00200000  // use frame dialog template matched to page
//----- New flags for wizard-lite --------
#define PSH_WIZARD_LITE         0x00400000
#define PSH_NOCONTEXTHELP       0x02000000
//----------------------------------------
#define PSH_AEROWIZARD                          0x00004000
#define PSH_RESIZABLE                           0x04000000
#define PSH_HEADERBITMAP                        0x08000000
#define PSH_NOMARGIN                            0x10000000

#define PSWIZB_BACK             0x00000001
#define PSWIZB_NEXT             0x00000002
#define PSWIZB_FINISH           0x00000004
#define PSWIZB_DISABLEDFINISH   0x00000008
#define PSWIZBF_ELEVATIONREQUIRED   0x00000001
#define PSWIZB_CANCEL           0x00000010


***/

void CPropertySheetPageDlg::OnBnClickedBtnModify()
{
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (!pos)
	{
		AfxMessageBox(_T("请先选中一行再修改！"));
		return;
	}
	int item = m_list.GetNextSelectedItem(pos);

	// 填充数据
	CMFCPropertySheet sheet(_T("修改信息"));
	CPage1 page1;
	CPage2 page2;
	CPage3 page3;
	sheet.AddPage(&page1);
	sheet.AddPage(&page2);
	sheet.AddPage(&page3);
	SInfo* pInfo = (SInfo*)m_list.GetItemData(item);
	page1.m_szAccount = pInfo->account;
	page1.m_szNickname = pInfo->nickname;
	page1.m_sex = pInfo->sex;
	page2.m_birth = pInfo->birth;
	page2.m_szBlood = pInfo->blood;
	page2.m_szNative = pInfo->native;
	page3.m_szPhone = pInfo->phone;
	page3.m_szAddress = pInfo->address;
	page3.m_szEmail = pInfo->email;

	sheet.DoModal();
}

// 悬浮框
void CPropertySheetPageDlg::OnHottrackList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	LPNMLISTVIEW p = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	if (p->iItem < 0)
		return;
	// 传递数据
	m_infoDlg.m_item = p->iItem;
	m_infoDlg.MakeText();
	//m_infoDlg.m_pInfo = (SInfo*)m_list.GetItemData(p->iItem);
	// 显示窗口
	CPoint point = p->ptAction;
	m_list.ClientToScreen(&point);		//坐标转换
	point.Offset(16, 16);
	m_infoDlg.SetWindowPos(&wndTopMost, point.x, point.y, 0, 0, SWP_NOSIZE);
	m_infoDlg.ShowWindow(SW_SHOW);


}

// 释放内存
BOOL CPropertySheetPageDlg::DestroyWindow()
{
	int count = m_list.GetItemCount();
	for (int i = 0; i < count; i++)
		delete (SInfo*)m_list.GetItemData(i);

	return CDialogEx::DestroyWindow();
}


void CPropertySheetPageDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE p = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (p->iItem > -1)
		this->OnBnClickedBtnModify();
	*pResult = 0;
}
