
// ExplorerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Explorer.h"
#include "ExplorerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExplorerDlg 对话框



CExplorerDlg::CExplorerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXPLORER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExplorerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_GO, &CExplorerDlg::OnBnClickedBtnGo)
END_MESSAGE_MAP()


// CExplorerDlg 消息处理程序

BOOL CExplorerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 设置背景图片。？未实现图片与控件填充比例，未实现对话框及其控件等比例缩放
	SetBackgroundImage(IDB_BITMAP);
	// 插入list标头
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_FILE);
	pList->InsertColumn(0, _T("名称"), LVCFMT_LEFT, 180);
	pList->InsertColumn(1, _T("修改日期"), LVCFMT_LEFT, 150);
	pList->InsertColumn(2, _T("类型"), LVCFMT_LEFT, 100);
	pList->InsertColumn(3, _T("大小"), LVCFMT_RIGHT, 100);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExplorerDlg::OnPaint()
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
HCURSOR CExplorerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExplorerDlg::OnBnClickedBtnGo()
{
	// C:\Users\Snow-Angel\Desktop\OUC
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST_FILE);	//CListCtrl的指针
	pList->DeleteAllItems();									//先清除所有结果
	CString strPath;											//路径
	GetDlgItemText(IDC_EDIT_PATH, strPath);

	//this->FileFindC(pList, strPath);
	//this->FileFindAPI(pList, strPath);
	this->FileFindMFC(pList, strPath);
}


// 搜索文件 C语言
BOOL CExplorerDlg::FileFindC(CListCtrl* pList, CString& strPath)
{
	_wfinddata_t cFile;
	intptr_t hFile;
	if ((hFile = _wfindfirst(strPath + _T("\\*.*"), &cFile)) == -1L)
		return FALSE;

	int item = 0;
	CString cstr;
	do
	{
		if (!CExplorerDlg::IsHidden(cFile))	//CExplorerDlg::IsHidden(cFile)	//(cFile.attrib & _A_HIDDEN)
		{
			//名称
			pList->InsertItem(item, cFile.name);
			if (cFile.attrib & _A_SUBDIR)
			{
				pList->SetItemText(item, 2, _T("文件夹"));
			}
			else
			{
				//类型
				cstr = cFile.name;
				int index = cstr.ReverseFind(_T('.'));
				if(index > 0)	
					pList->SetItemText(item, 2, cstr.Mid(index + 1) + _T(" 文件"));
				//大小，！系统计算的文件大小以KB为单位的不太对，莫名进位
				cstr.Format(_T("%u"), (unsigned long)(1.0 * cFile.size / 1024 + 0.5));
				pList->SetItemText(item, 3, cstr + _T(" KB"));
			}
			// 修改日期
			COleDateTime time(cFile.time_write);
			cstr.Format(_T("%d/%02d/%02d %02d:%02d"),
				time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute());
			pList->SetItemText(item, 1, cstr);
			item++;								//小小的item又害我找了半天bug，放在里面好使！
		}
	} while (_wfindnext(hFile, &cFile) == 0);
	_findclose(hFile);

	return TRUE;
}
//struct _wfinddata64i32_t
//{
//	unsigned   attrib;
//	__time64_t time_create;    // -1 for FAT file systems
//	__time64_t time_access;    // -1 for FAT file systems
//	__time64_t time_write;
//	_fsize_t   size;
//	wchar_t    name[260];
//};
//typedef __int64          intptr_t;
//typedef unsigned long _fsize_t;
// File attribute constants for the _findfirst() family of functions
//#define _A_NORMAL 0x00 // Normal file - No read/write restrictions
//#define _A_RDONLY 0x01 // Read only file
//#define _A_HIDDEN 0x02 // Hidden file
//#define _A_SYSTEM 0x04 // System file
//#define _A_SUBDIR 0x10 // Subdirectory
//#define _A_ARCH   0x20 // Archive file
//intptr_t __cdecl _wfindfirst64i32(
//	_In_z_ wchar_t const*            _FileName,
//	_Out_  struct _wfinddata64i32_t* _FindData
//);
//int __cdecl _wfindnext64i32(
//	_In_  intptr_t                  _FindHandle,
//	_Out_ struct _wfinddata64i32_t* _FindData
//);
//int __cdecl _findclose(_In_ intptr_t _FindHandle);


// 搜索文件 Windows API
BOOL CExplorerDlg::FileFindAPI(CListCtrl* pList, CString& strPath)
{
	WIN32_FIND_DATA cFile;
	HANDLE hFile;
	if ((hFile = FindFirstFile(strPath + _T("\\*.*"), &cFile)) == INVALID_HANDLE_VALUE)
		return FALSE;

	int item = 0;
	CString cstr;
	do
	{
		if (!CExplorerDlg::IsHidden(cFile))	
		{
			//名称
			pList->InsertItem(item, cFile.cFileName);
			if (cFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				pList->SetItemText(item, 2, _T("文件夹"));
			}
			else
			{
				//类型
				cstr = cFile.cFileName;
				int index = cstr.ReverseFind(_T('.'));
				if (index > 0)
					pList->SetItemText(item, 2, cstr.Mid(index + 1) + _T(" 文件"));
				//大小，！系统计算的文件大小以KB为单位的不太对，莫名进位
				cstr.Format(_T("%u"), (unsigned long)(1.0 * cFile.nFileSizeLow / 1024 + 0.5));
				pList->SetItemText(item, 3, cstr + _T(" KB"));
			}
			// 修改日期
			COleDateTime time(cFile.ftLastWriteTime);
			cstr.Format(_T("%d/%02d/%02d %02d:%02d"),
				time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute());
			pList->SetItemText(item, 1, cstr);
			item++;								//小小的item又害我找了半天bug，放在里面好使！
		}
	} while (FindNextFile(hFile, &cFile));
	FindClose(hFile);

	return TRUE;
}
//#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
//typedef struct _WIN32_FIND_DATAW {
//	DWORD dwFileAttributes;
//	FILETIME ftCreationTime;
//	FILETIME ftLastAccessTime;
//	FILETIME ftLastWriteTime;
//	DWORD nFileSizeHigh;
//	DWORD nFileSizeLow;
//	DWORD dwReserved0;
//	DWORD dwReserved1;
//	_Field_z_ WCHAR  cFileName[MAX_PATH];
//	_Field_z_ WCHAR  cAlternateFileName[14];
//#ifdef _MAC
//	DWORD dwFileType;
//	DWORD dwCreatorType;
//	WORD  wFinderFlags;
//#endif
//} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;
//typedef struct _FILETIME {
//	DWORD dwLowDateTime;
//	DWORD dwHighDateTime;
//} FILETIME, *PFILETIME, *LPFILETIME;
//// end_access
//#define FILE_SHARE_READ                 0x00000001  
//#define FILE_SHARE_WRITE                0x00000002  
//#define FILE_SHARE_DELETE               0x00000004  
//#define FILE_ATTRIBUTE_READONLY             0x00000001  
//#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
//#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
//#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
//#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
//#define FILE_ATTRIBUTE_DEVICE               0x00000040  
//#define FILE_ATTRIBUTE_NORMAL               0x00000080  
//#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
//#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
//#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
//#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
//#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
//#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
//#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000  
//#define FILE_ATTRIBUTE_INTEGRITY_STREAM     0x00008000  
//#define FILE_ATTRIBUTE_VIRTUAL              0x00010000  
//#define FILE_ATTRIBUTE_NO_SCRUB_DATA        0x00020000  
//#define FILE_ATTRIBUTE_EA                   0x00040000  
//#define FILE_ATTRIBUTE_PINNED               0x00080000  
//#define FILE_ATTRIBUTE_UNPINNED             0x00100000  
//#define FILE_ATTRIBUTE_RECALL_ON_OPEN       0x00040000  
//#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 0x00400000 
//HANDLE WINAPI FindFirstFileW(
//	_In_ LPCWSTR lpFileName,
//	_Out_ LPWIN32_FIND_DATAW lpFindFileData
//);
//BOOL WINAPI FindNextFileW(
//	_In_ HANDLE hFindFile,
//	_Out_ LPWIN32_FIND_DATAW lpFindFileData
//);
//BOOL WINAPI FindClose(
//	_Inout_ HANDLE hFindFile
//);


// 搜索文件 MFC, CFileFind封装了Windows API FindFirstFile()...等函数
BOOL CExplorerDlg::FileFindMFC(CListCtrl* pList, CString& strPath)
{
	int item = 0;
	CString cstr;

	CFileFind cFile;
	BOOL finished = cFile.FindFile(strPath + _T("\\*.*"));
	while(finished)
	{
		finished = cFile.FindNextFileW();
		if (!(cFile.IsHidden() || cFile.IsDots()))	
		{
			//名称
			pList->InsertItem(item, cFile.GetFileName());
			if (cFile.IsDirectory())
			{
				pList->SetItemText(item, 2, _T("文件夹"));
			}
			else
			{
				//类型
				cstr = cFile.GetFileName();
				int index = cstr.ReverseFind(_T('.'));
				if (index > 0)
					pList->SetItemText(item, 2, cstr.Mid(index + 1) + _T(" 文件"));
				//大小，！系统计算的文件大小以KB为单位的不太对，莫名进位
				cstr.Format(_T("%u"), (unsigned long)(1.0 * cFile.GetLength() / 1024 + 0.5));
				pList->SetItemText(item, 3, cstr + _T(" KB"));
			}
			// 修改日期
			FILETIME filetime;
			cFile.GetLastWriteTime(&filetime);
			COleDateTime time(filetime);
			cstr.Format(_T("%d/%02d/%02d %02d:%02d"),
				time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute());
			pList->SetItemText(item, 1, cstr);
			item++;								//小小的item又害我找了半天bug，放在里面好使！
		}
	}
	cFile.Close();

	return TRUE;
}
//文件c : \myhtml\myfile.txt的用户信息
//CString GetFileName() 返回文件名，包括扩展文件名。返回文件名myfile.txt。
//CString GetFilePath() 返回全部文件的路径。返回文件路径c:\myhtml\myfile.txt。
//CString GetFileTitle() 返回文件名，不包括扩展名。返回文件标题myfile。
//CString GetFileURL() 调用之前必须至少调用一次FindNextFile。URL的形式为 file :// path。返回URL：file://c:\myhtml\myfile.txt。


