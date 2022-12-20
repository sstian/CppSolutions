
// FileFolderDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FileFolder.h"
#include "FileFolderDlg.h"
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


// CFileFolderDlg 对话框



CFileFolderDlg::CFileFolderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEFOLDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFileFolderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_FILE_SINGLE, &CFileFolderDlg::OnBnClickedBtnFileSingle)
	ON_BN_CLICKED(IDC_BTN_MULTIPLE, &CFileFolderDlg::OnBnClickedBtnMultiple)
	ON_BN_CLICKED(IDC_BTN_FOLDER, &CFileFolderDlg::OnBnClickedBtnFolder)
END_MESSAGE_MAP()


// CFileFolderDlg 消息处理程序

BOOL CFileFolderDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileFolderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileFolderDlg::OnPaint()
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
HCURSOR CFileFolderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 打开单个文件
void CFileFolderDlg::OnBnClickedBtnFileSingle()
{
	// TRUE - 打开对话框，FALSE - 另存为对话框
	LPCTSTR lpszFilter =
		//_T("Worksheet Files (*.xls;*.xlsx)|*.xls;*.xlsx|Document Files (*.doc;*docx)|*.doc;*docx|PowerPoint Files (*.ppt;*.pptx)|*.ppt;*.pptx|")
		_T("配置文件 (*.ini)|*.ini|所有文件 (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, NULL, _T("image_template.ini"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);
	//CFileDialog dlgFile(FALSE, nullptr, _T("image_template.ini"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);
	dlgFile.m_ofn.lpstrTitle = _T("打开单个文件");	//修改对话框标题
	if (IDCANCEL == dlgFile.DoModal())
		return;

	CString strFile = dlgFile.GetPathName();
	AfxMessageBox(strFile);
}


// 打开多个文件
void CFileFolderDlg::OnBnClickedBtnMultiple()
{
	LPCTSTR lpszFilter =
		//_T("Worksheet Files (*.xls;*.xlsx)|*.xls;*.xlsx|Document Files (*.doc;*docx)|*.doc;*docx|PowerPoint Files (*.ppt;*.pptx)|*.ppt;*.pptx|")
		_T("Image Files(*.jpg)|*.jpg|所有文件 (*.*)|*.*||");

	CFileDialog dlgFiles(TRUE, _T("*.jpg"), NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, lpszFilter);
	dlgFiles.m_ofn.lpstrTitle = _T("选择图片");
	if (IDCANCEL == dlgFiles.DoModal())
		return;

	// 存储文件列表
	CStringArray arrFiles;		
	CString strFile;
	POSITION posFile = dlgFiles.GetStartPosition();
	while (posFile)
	{
		strFile = dlgFiles.GetNextPathName(posFile);
		arrFiles.Add(strFile);
	}
	
	/// 显示测试
	INT_PTR size = arrFiles.GetSize();
	for(INT_PTR index = 0; index < size; index++)
		AfxMessageBox(arrFiles.GetAt(index));
}
//explicit CFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
//	LPCTSTR lpszDefExt = NULL,
//	LPCTSTR lpszFileName = NULL,
//	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//	LPCTSTR lpszFilter = NULL,
//	CWnd* pParentWnd = NULL,
//	DWORD dwSize = 0,
//	BOOL bVistaStyle = TRUE);
//
//#define OFN_READONLY                 0x00000001
//#define OFN_OVERWRITEPROMPT          0x00000002
//#define OFN_HIDEREADONLY             0x00000004
//#define OFN_NOCHANGEDIR              0x00000008
//#define OFN_SHOWHELP                 0x00000010
//#define OFN_ENABLEHOOK               0x00000020
//#define OFN_ENABLETEMPLATE           0x00000040
//#define OFN_ENABLETEMPLATEHANDLE     0x00000080
//#define OFN_NOVALIDATE               0x00000100
//#define OFN_ALLOWMULTISELECT         0x00000200
//#define OFN_EXTENSIONDIFFERENT       0x00000400
//#define OFN_PATHMUSTEXIST            0x00000800
//#define OFN_FILEMUSTEXIST            0x00001000
//#define OFN_CREATEPROMPT             0x00002000
//#define OFN_SHAREAWARE               0x00004000
//#define OFN_NOREADONLYRETURN         0x00008000
//#define OFN_NOTESTFILECREATE         0x00010000
//#define OFN_NONETWORKBUTTON          0x00020000
//#define OFN_NOLONGNAMES              0x00040000     // force no long names for 4.x modules
//#if(WINVER >= 0x0400)
//#define OFN_EXPLORER                 0x00080000     // new look commdlg
//#define OFN_NODEREFERENCELINKS       0x00100000
//#define OFN_LONGNAMES                0x00200000     // force long names for 3.x modules
//// OFN_ENABLEINCLUDENOTIFY and OFN_ENABLESIZING require
//// Windows 2000 or higher to have any effect.
//#define OFN_ENABLEINCLUDENOTIFY      0x00400000     // send include message to callback
//#define OFN_ENABLESIZING             0x00800000
//#endif /* WINVER >= 0x0400 */
//#if (_WIN32_WINNT >= 0x0500)
//#define OFN_DONTADDTORECENT          0x02000000
//#define OFN_FORCESHOWHIDDEN          0x10000000    // Show All files including System and hidden files
//#endif // (_WIN32_WINNT >= 0x0500)
////FlagsEx Values
//#if (_WIN32_WINNT >= 0x0500)
//#define  OFN_EX_NOPLACESBAR         0x00000001
//#endif // (_WIN32_WINNT >= 0x0500)


// 打开目录
void CFileFolderDlg::OnBnClickedBtnFolder()
{
	BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("请选择处理结果存储路径");
	sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	sInfo.lpfn = NULL;

	// 显示文件夹选择对话框  
	LPITEMIDLIST lpidlistBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlistBrowse != NULL)
	{
		// 取得文件夹名  
		TCHAR	szFolderPath[MAX_PATH] = { 0 };
		CString	strFolderPath = _T("");
		if (::SHGetPathFromIDList(lpidlistBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
			AfxMessageBox(strFolderPath);
		}
		// 释放被分配的内存块
		::CoTaskMemFree(lpidlistBrowse);
	}
}
//1. 显示文件夹选择对话框  
//SHSTDAPI_(PIDLIST_ABSOLUTE) SHBrowseForFolderW(_In_ LPBROWSEINFOW lpbi);
//#define PIDLIST_ABSOLUTE         LPITEMIDLIST
//#define PCIDLIST_ABSOLUTE        LPCITEMIDLIST
//typedef /* [wire_marshal] */ ITEMIDLIST __unaligned *LPITEMIDLIST;
//typedef /* [wire_marshal] */ const ITEMIDLIST __unaligned *LPCITEMIDLIST;
//typedef struct _ITEMIDLIST { SHITEMID mkid; } 	ITEMIDLIST;
//typedef struct _SHITEMID { USHORT cb; BYTE abID[1]; } 	SHITEMID;
//
//typedef struct _browseinfoW {
//	HWND        hwndOwner;			// 父窗口句柄
//	PCIDLIST_ABSOLUTE pidlRoot;		// 要显示的文件夹的根(Root)		
//	LPWSTR       pszDisplayName;	// 保存被选取的文件夹路径的缓冲区
//	LPCWSTR      lpszTitle;			// 显示位于对话框左上部的标题
//	UINT         ulFlags;			// 指定对话框的外观和功能的标志			
//	BFFCALLBACK  lpfn;				// 处理事件的回调函数
//	LPARAM       lParam;			// 应用程序传给回调函数的参数
//	int          iImage;			// 保存被选取的文件夹的图片索引
//} BROWSEINFOW, *PBROWSEINFOW, *LPBROWSEINFOW;
//typedef int (CALLBACK* BFFCALLBACK)(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
//
//ulFlags:
//// Browsing for directory.
//#define BIF_RETURNONLYFSDIRS    0x00000001  // 仅仅返回文件系统的目录。
//#define BIF_DONTGOBELOWDOMAIN   0x00000002  // 在树形视窗中，不包含域名底下的网络目录结构。
//#define BIF_STATUSTEXT          0x00000004   // 在对话框中包含一个状态区域。通过给对话框发送消息使回调函数设置状态文本。
//#define BIF_RETURNFSANCESTORS   0x00000008   // 返回文件系统的一个节点。仅仅当选中的是有意义的节点时，“OK”按钮才可以使用。
//#define BIF_EDITBOX             0x00000010   // 浏览对话框中包含一个编辑框，在该编辑框中用户可以输入选中项的名字。
//#define BIF_VALIDATE            0x00000020   //当没有BIF_EDITBOX标志位时，该标志位被忽略。如果用户在编辑框中输入的名字非法，浏览对话框将发送BFFM_VALIDATEFAILED消息给回调函数。
//#define BIF_NEWDIALOGSTYLE      0x00000040   // Use the new dialog layout with the ability to resize
//#define BIF_USENEWUI            (BIF_NEWDIALOGSTYLE | BIF_EDITBOX)
//#define BIF_BROWSEINCLUDEURLS   0x00000080   // Allow URLs to be displayed or entered. (Requires BIF_USENEWUI)
//#define BIF_UAHINT              0x00000100   // Add a UA hint to the dialog, in place of the edit box. May not be combined with BIF_EDITBOX
//#define BIF_NONEWFOLDERBUTTON   0x00000200   // Do not add the "New Folder" button to the dialog.  Only applicable with BIF_NEWDIALOGSTYLE.
//#define BIF_NOTRANSLATETARGETS  0x00000400   // don't traverse target as shortcut
//#define BIF_BROWSEFORCOMPUTER   0x00001000  // 返回计算机名。除非用户选中浏览器中的一个计算机名，否则该对话框中的“OK”按钮为灰色。
//#define BIF_BROWSEFORPRINTER    0x00002000  // 返回打印机名。除非选中一个打印机名，否则“OK”按钮为灰色。
//#define BIF_BROWSEINCLUDEFILES  0x00004000  // 浏览器将显示目录，同时也显示文件。
//#define BIF_SHAREABLE           0x00008000  // sharable resources displayed (remote shares, requires BIF_USENEWUI)
//#define BIF_BROWSEFILEJUNCTIONS 0x00010000  // allow folder junctions like zip files and libraries to be browsed
//
// 2.取得文件夹名  
//SHSTDAPI_(BOOL) SHGetPathFromIDListW(_In_ PCIDLIST_ABSOLUTE pidl, _Out_writes_(MAX_PATH) LPWSTR pszPath);
//
//3. 释放被分配的内存块
//WINOLEAPI_(void) CoTaskMemFree(_Frees_ptr_opt_ LPVOID pv);


