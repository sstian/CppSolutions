
// NotepadDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Notepad.h"
#include "NotepadDlg.h"
#include "CAboutDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNotepadDlg 对话框

CString CNotepadDlg::section[SECTION_NUMBER] = { _T("Rect"), _T("Setting"), _T("\0")};
CString CNotepadDlg::entry_rect[ENTRY_RECT_NUMBER] = { _T("Left"), _T("Right"), _T("Top"), _T("Bottom"), _T("\0") };
CString CNotepadDlg::entry_setting[ENTRY_SETTING_NUMBER] = { _T("Caption"), _T("Font"), _T("\0") };

CNotepadDlg::CNotepadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTEPAD_DIALOG, pParent)
{
	// 加载图标资源
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// 加载快捷键资源
	m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));	//(LPCSTR)IDR_ACCELERATOR
}
//HACCEL WINAPI LoadAcceleratorsA(_In_opt_ HINSTANCE hInstance,_In_ LPCSTR lpTableName);

void CNotepadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNotepadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_APP_EXIT, &CNotepadDlg::OnAppExit)
	ON_COMMAND(ID_APP_ABOUT, &CNotepadDlg::OnAppAbout)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_EDIT_UNDO, &CNotepadDlg::OnEditUndo)
	ON_COMMAND(ID_EDIT_CUT, &CNotepadDlg::OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CNotepadDlg::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CNotepadDlg::OnEditPaste)
	ON_COMMAND(ID_EDIT_CLEAR, &CNotepadDlg::OnEditClear)
	ON_COMMAND(ID_EDIT_DATETIME, &CNotepadDlg::OnEditDatetime)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CNotepadDlg::OnEditSelectAll)
	ON_WM_DROPFILES()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_OPEN, &CNotepadDlg::OnFileOpen)
	ON_COMMAND(ID_FORMAT_FONT, &CNotepadDlg::OnFormatFont)
	ON_COMMAND(ID_FILE_NEW, &CNotepadDlg::OnFileNew)
	ON_COMMAND(ID_FILE_SAVE, &CNotepadDlg::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CNotepadDlg::OnFileSaveAs)
	ON_MESSAGE(WM_USER_NOTIFYICON, &CNotepadDlg::OnNotifyMsg)	//自定义消息映射
END_MESSAGE_MAP()


// CNotepadDlg 消息处理程序
// 对话框专用回调函数，控件都已经按照资源模板的创建完成（可以使用）
BOOL CNotepadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//// 将“关于...”菜单项添加到系统菜单中。

	//// IDM_ABOUTBOX 必须在系统命令范围内。
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != nullptr)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 加载配置文件
	this->GetProfile();

	// 使Edit Control与窗口自适应
	CWnd* pwnd = GetDlgItem(IDC_TEXT);
	if (pwnd)
	{
		CRect rect;
		GetClientRect(&rect);
		pwnd->MoveWindow(&rect);
	}

	// 初始化并注册托盘
	this->RegisterNotify();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNotepadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	//{
	//	CAboutDlg dlgAbout;
	//	dlgAbout.DoModal();
	//}
	//else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
//// System Menu Command Values
//#define SC_SIZE         0xF000
//#define SC_MOVE         0xF010
//#define SC_MINIMIZE     0xF020
//#define SC_MAXIMIZE     0xF030
//#define SC_NEXTWINDOW   0xF040
//#define SC_PREVWINDOW   0xF050
//#define SC_CLOSE        0xF060
//#define SC_VSCROLL      0xF070
//#define SC_HSCROLL      0xF080
//#define SC_MOUSEMENU    0xF090
//#define SC_KEYMENU      0xF100
//#define SC_ARRANGE      0xF110
//#define SC_RESTORE      0xF120
//#define SC_TASKLIST     0xF130
//#define SC_SCREENSAVE   0xF140
//#define SC_HOTKEY       0xF150
//#if(WINVER >= 0x0400)
//#define SC_DEFAULT      0xF160
//#define SC_MONITORPOWER 0xF170
//#define SC_CONTEXTHELP  0xF180
//#define SC_SEPARATOR    0xF00F
//#endif 
//
//#if(WINVER >= 0x0600)
//#define SCF_ISSECURE    0x00000001
//#endif 
//
//#define GET_SC_WPARAM(wParam) ((int)wParam & 0xFFF0)
//
//// BOOL ShowWindow(int nCmdShow);
////ShowWindow() Commands
//#define SW_HIDE             0
//#define SW_SHOWNORMAL       1
//#define SW_NORMAL           1
//#define SW_SHOWMINIMIZED    2
//#define SW_SHOWMAXIMIZED    3
//#define SW_MAXIMIZE         3
//#define SW_SHOWNOACTIVATE   4
//#define SW_SHOW             5
//#define SW_MINIMIZE         6
//#define SW_SHOWMINNOACTIVE  7
//#define SW_SHOWNA           8
//#define SW_RESTORE          9
//#define SW_SHOWDEFAULT      10
//#define SW_FORCEMINIMIZE    11
//#define SW_MAX              11
//
////Identifiers for the WM_SHOWWINDOW message
//#define SW_PARENTCLOSING    1
//#define SW_OTHERZOOM        2
//#define SW_PARENTOPENING    3
//#define SW_OTHERUNZOOM      4

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNotepadDlg::OnPaint()
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
HCURSOR CNotepadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNotepadDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CNotepadDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}

// 帮助 | 关于记事本
void CNotepadDlg::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// 使Edit Control与窗口自适应
void CNotepadDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CWnd* pwnd = GetDlgItem(IDC_TEXT);
	if (pwnd)
	{
		CRect rect;
		GetClientRect(&rect);
		pwnd->MoveWindow(&rect);
	}
}

// 关闭
void CNotepadDlg::OnClose()
{
	//EndDialog(IDCANCEL);
	//ShowWindow(SW_MINIMIZE);	
	ShowWindow(SW_HIDE);	//隐藏，设计进入托盘

	//CDialogEx::OnClose();

}

// 编辑 | 撤销
void CNotepadDlg::OnEditUndo()
{
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_TEXT);
	pedit->Undo();
}

// 编辑 | 剪切
void CNotepadDlg::OnEditCut()
{
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_TEXT);
	pedit->Cut();

	//？？？
	//if (!pedit->GetSel())
	//	return;
	//CMenu* mmenu = GetMenu();
	//CMenu* submenu = mmenu->GetSubMenu(1);
	//submenu->EnableMenuItem(ID_EDIT_CLEAR, MF_BYCOMMAND | MF_ENABLED);
}
//DWORD GetSel() const; //return: LOWORD - 起始位置，HIWORD - 结束位置
//void GetSel(int& nStartChar,int& nEndChar) const;

// 编辑 | 复制
void CNotepadDlg::OnEditCopy()
{
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_TEXT);
	pedit->Copy();
}

// 编辑 | 粘贴
void CNotepadDlg::OnEditPaste()
{
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_TEXT);
	pedit->Paste();
}

// 编辑 | 删除
void CNotepadDlg::OnEditClear()
{
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_TEXT);
	pedit->Clear();
}

// 编辑 | 时间/日期
void CNotepadDlg::OnEditDatetime()
{
	COleDateTime time = COleDateTime::GetCurrentTime();
	CString strtime = time.Format(_T("%H:%M %Y/%m/%d"));
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_TEXT);
	pedit->ReplaceSel(strtime);
}

// 编辑 | 全选
void CNotepadDlg::OnEditSelectAll()
{
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_TEXT);
	pedit->SetSel(0, -1);
}

// 支持拖拽文件
void CNotepadDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szfile[256] = { 0 };
	UINT count = DragQueryFile(hDropInfo, 0, szfile, sizeof(szfile));
	this->LoadFile(szfile);
	CDialogEx::OnDropFiles(hDropInfo);
}
//SHSTDAPI_(UINT) DragQueryFileW(_In_ HDROP hDrop, _In_ UINT iFile, _Out_writes_opt_(cch) LPWSTR lpszFile, _In_ UINT cch);


// 加载文件
BOOL CNotepadDlg::LoadFile(LPCTSTR szfile)
{
	CFile file;
	if (!file.Open(szfile, CFile::modeRead))
	{
		AfxMessageBox(_T("打开文件是失败，请检查文件名是否正确！"));
		return FALSE;
	}
	this->SetTitle(CString(szfile));
	// 编辑框显示的即是Unicode!
	wchar_t buff[5] = { 0 };
	if (3 == file.Read(buff, 3))	//按一个字节读取
	{
		switch (buff[0])
		{
		case 0xBBEF:				//UTF-8: EF BB BF  表示：英文用一个字节，中文用三个字节
			if (0x00BF == (buff[1] & 0x00FF))
				this->ReadUTF8(file);	//MultiByteToWideChar()
			break;
		case 0xFEFF:				//UTF-16 little endian: FF FE, 
			this->ReadUnicode(file);	//两个字节写入
			break;
		case 0xFFFE:				//UTF-16 big endian: FE FF  表示：低-高：00 4E
			this->ReadUnicodeBE(file);
			break;
		default:
			this->ReadANSI(file);		//单个字节写入
			break;
		}
	}

	return TRUE;
}

// 读取ANSI文件
BOOL CNotepadDlg::ReadANSI(CFile& file)
{
	file.Seek(0, CFile::begin);
	CString cstr;

	// 方法1.
	char buff[1024];
	int result = 0;
	while (result = file.Read(buff, sizeof(buff) - 1))	//result != 0
	{
		buff[result] = '\0';
		cstr += buff;
	}
	SetDlgItemText(IDC_TEXT, cstr);

	//// 方法2.
	//ULONGLONG length = file.GetLength();
	//char* pbuff = new char[length + 1];
	//UINT result = file.Read(pbuff, length);
	//pbuff[result] = '\0';
	//cstr = pbuff;
	//SetDlgItemText(IDC_TEXT, cstr);
	//delete[]pbuff;

	return TRUE;
}


// 读取UTF-8文件
BOOL CNotepadDlg::ReadUTF8(CFile& file)
{
	file.Seek(3, CFile::begin);
	ULONGLONG length = file.GetLength();
	char* pchar = new char[length + 1];
	int result = file.Read(pchar, (UINT)length);
	pchar[result] = '\0';

	wchar_t* pwchar = new wchar_t[result / 2 + 2];
	int result2 = MultiByteToWideChar(CP_UTF8, 0, pchar, -1, pwchar, result / 2 + 2);
	pwchar[result2] = _T('\0');
	SetDlgItemText(IDC_TEXT, pwchar);
	delete[]pchar;
	delete[]pwchar;

	return TRUE;
}
//int WINAPI MultiByteToWideChar(
//	_In_ UINT CodePage,
//	_In_ DWORD dwFlags,
//	_In_NLS_string_(cbMultiByte) LPCCH lpMultiByteStr,
//	_In_ int cbMultiByte,
//	_Out_writes_to_opt_(cchWideChar, return) LPWSTR lpWideCharStr,
//	_In_ int cchWideChar
//);
//int WINAPI WideCharToMultiByte(
//	_In_ UINT CodePage,
//	_In_ DWORD dwFlags,
//	_In_NLS_string_(cchWideChar) LPCWCH lpWideCharStr,
//	_In_ int cchWideChar,
//	_Out_writes_bytes_to_opt_(cbMultiByte, return) LPSTR lpMultiByteStr,
//	_In_ int cbMultiByte,
//	_In_opt_ LPCCH lpDefaultChar,
//	_Out_opt_ LPBOOL lpUsedDefaultChar
//);

// 读取Unicode文件
BOOL CNotepadDlg::ReadUnicode(CFile& file)
{
	file.Seek(2, CFile::begin);
	ULONGLONG length = file.GetLength();	//获取字节数
	wchar_t* pbuff = new wchar_t[length / 2 + 1];
	UINT result = file.Read(pbuff, (UINT)length);
	pbuff[result / 2] = _T('\0');
	SetDlgItemText(IDC_TEXT, pbuff);
	delete[]pbuff;

	return TRUE;
}


// 读取Unicode文件 big endian
BOOL CNotepadDlg::ReadUnicodeBE(CFile& file)
{
	file.Seek(2, CFile::begin);
	ULONGLONG length = file.GetLength();	//获取的是字节数
	wchar_t* pbuff = new wchar_t[length / 2 + 1];
	UINT result = file.Read(pbuff, (UINT)length);
	pbuff[result / 2] = _T('\0');

	// 高低字节调换
	wchar_t* ptext = new wchar_t[result / 2 + 1];
	unsigned char low = '\0', high = '\0';
	for (UINT i = 0; i < result / 2; i++)
	{
		low = (pbuff[i] & 0xFF00) >> 8;
		high = (pbuff[i] & 0x00FF);
		ptext[i] = (high << 8) | low;
	}
	ptext[result / 2] = _T('\0');

	SetDlgItemText(IDC_TEXT, ptext);
	delete[]pbuff;
	delete[]ptext;

	return TRUE;
}

void CNotepadDlg::WriteProfile()
{
	CRect rect;
	GetWindowRect(&rect);
	//CString section = _T("Rect");
	//CString entry[5] = { _T("Left"), _T("Right"), _T("Top"), _T("Bottom"), _T('\0') };
	theApp.WriteProfileInt(section[_RECT], entry_rect[_LEFT], rect.left);
	theApp.WriteProfileInt(section[_RECT], entry_rect[_RIGHT], rect.right);
	theApp.WriteProfileInt(section[_RECT], entry_rect[_TOP], rect.top);
	theApp.WriteProfileInt(section[_RECT], entry_rect[_BOTTOM], rect.bottom);

	theApp.WriteProfileStringW(section[_SETTING], entry_setting[_CAPTION], SETTING_CAPTION);

	if (m_font.GetSafeHandle())
	{
		LOGFONT logfont;
		m_font.GetLogFont(&logfont);
		theApp.WriteProfileBinary(section[_SETTING], entry_setting[_FONT], (LPBYTE)&logfont, sizeof(logfont));
	}
}

void CNotepadDlg::GetProfile()
{
	CRect rect;
	rect.left = theApp.GetProfileIntW(CNotepadDlg::section[ESection::_RECT], CNotepadDlg::entry_rect[EEntry_Rect::_LEFT], 0);
	rect.right = theApp.GetProfileIntW(CNotepadDlg::section[ESection::_RECT], CNotepadDlg::entry_rect[EEntry_Rect::_RIGHT], 0);
	rect.top = theApp.GetProfileIntW(CNotepadDlg::section[ESection::_RECT], CNotepadDlg::entry_rect[EEntry_Rect::_TOP], 0);
	rect.bottom = theApp.GetProfileIntW(CNotepadDlg::section[ESection::_RECT], CNotepadDlg::entry_rect[EEntry_Rect::_BOTTOM], 0);

	CString caption = theApp.GetProfileStringW(CNotepadDlg::section[ESection::_SETTING], CNotepadDlg::entry_setting[EEntry_Setting::_CAPTION]);
	MoveWindow(&rect);
	SetWindowText(caption);

	LPBYTE pdata = nullptr;
	UINT bytes = 0;
	theApp.GetProfileBinary(CNotepadDlg::section[ESection::_SETTING], CNotepadDlg::entry_setting[_FONT], &pdata, &bytes);
	m_font.CreateFontIndirectW((LOGFONT*)pdata);
	GetDlgItem(IDC_TEXT)->SetFont(&m_font);
	if (bytes > 0)
		delete[]pdata;
}

// 所有窗口通用的初始化消息，子窗口和控件还没有出现
int CNotepadDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CNotepadDlg::OnDestroy()
{
	// 保存配置文件
	this->WriteProfile();

	CDialogEx::OnDestroy();
}


// 快捷键的翻译消息
BOOL CNotepadDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_hAccel)
	{
		if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
//int WINAPI TranslateAcceleratorW(
//	_In_ HWND hWnd,
//	_In_ HACCEL hAccTable,
//	_In_ LPMSG lpMsg);

// 格式 | 字体...
void CNotepadDlg::OnFormatFont()
{
	// 获取初始化CFontDialog的LOGFONT
	LOGFONT logfont;
	CFont* pFont = nullptr;
	m_font.GetSafeHandle() ? pFont = &m_font : pFont = GetFont();
	pFont->GetLogFont(&logfont);
	// 获取选择的字体
	CFontDialog fontDialog(&logfont);
	if (IDCANCEL == fontDialog.DoModal())
		return;	
	fontDialog.GetCurrentFont(&logfont);
	// 创建字体样式并设置文本
	m_font.DeleteObject();
	m_font.CreateFontIndirectW(&logfont);
	GetDlgItem(IDC_TEXT)->SetFont(&m_font);

	///// 颜色对话框
	//CColorDialog colorDialog;
	//colorDialog.DoModal();
	//COLORREF colorref = colorDialog.GetColor();
	
}
//typedef struct tagLOGFONTW
//{
//	LONG      lfHeight;
//	LONG      lfWidth;
//	LONG      lfEscapement;
//	LONG      lfOrientation;
//	LONG      lfWeight;
//	BYTE      lfItalic;
//	BYTE      lfUnderline;
//	BYTE      lfStrikeOut;
//	BYTE      lfCharSet;
//	BYTE      lfOutPrecision;
//	BYTE      lfClipPrecision;
//	BYTE      lfQuality;
//	BYTE      lfPitchAndFamily;
//	WCHAR     lfFaceName[LF_FACESIZE];
//} LOGFONTW, *PLOGFONTW, NEAR *NPLOGFONTW, FAR *LPLOGFONTW;
//typedef LOGFONTW LOGFONT;

// 文件 | 新建
void CNotepadDlg::OnFileNew()
{
	// 与打开文件同理
	if (!this->CheckModify())
		return;

	this->ClearFile();
}

// 文件 | 打开...
//文件数据读取在软件中不需要前面的标识符，保存写入到文件中要加上前面的标识符以区分文件格式
void CNotepadDlg::OnFileOpen()
{
	// 是否存在修改过需要保存的文件
	if (!this->CheckModify())
		return;
	
	// 保存或不保存或没修改过则打开文件
	LPCTSTR lpszFilter =
		//_T("Worksheet Files (*.xls;*.xlsx)|*.xls;*.xlsx|Document Files (*.doc;*docx)|*.doc;*docx|PowerPoint Files (*.ppt;*.pptx)|*.ppt;*.pptx|")
		_T("文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*||");
	CFileDialog fileDialog(TRUE, nullptr, nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);
	//fileDialog.AddComboBox(IDOK);	//?
	if (IDCANCEL == fileDialog.DoModal())
		return;
	CString strPath = fileDialog.GetPathName();

	this->LoadFile(strPath);

}
//explicit CFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
//	LPCTSTR lpszDefExt = NULL,
//	LPCTSTR lpszFileName = NULL,
//	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//	LPCTSTR lpszFilter = NULL,
//	CWnd* pParentWnd = NULL,
//	DWORD dwSize = 0,
//	BOOL bVistaStyle = TRUE);
//typedef struct tagOFNW {
//	DWORD        lStructSize;
//	HWND         hwndOwner;
//	HINSTANCE    hInstance;
//	LPCWSTR      lpstrFilter;
//	LPWSTR       lpstrCustomFilter;
//	DWORD        nMaxCustFilter;
//	DWORD        nFilterIndex;
//	LPWSTR       lpstrFile;
//	DWORD        nMaxFile;
//	LPWSTR       lpstrFileTitle;
//	DWORD        nMaxFileTitle;
//	LPCWSTR      lpstrInitialDir;
//	LPCWSTR      lpstrTitle;
//	DWORD        Flags;
//	WORD         nFileOffset;
//	WORD         nFileExtension;
//	LPCWSTR      lpstrDefExt;
//	LPARAM       lCustData;
//	LPOFNHOOKPROC lpfnHook;
//	LPCWSTR      lpTemplateName;
//#ifdef _MAC
//	LPEDITMENU   lpEditInfo;
//	LPCSTR       lpstrPrompt;
//#endif
//#if (_WIN32_WINNT >= 0x0500)
//	void *        pvReserved;
//	DWORD        dwReserved;
//	DWORD        FlagsEx;
//#endif // (_WIN32_WINNT >= 0x0500)
//} OPENFILENAMEW, *LPOPENFILENAMEW;
//#ifdef UNICODE
//typedef OPENFILENAMEW OPENFILENAME;
//typedef LPOPENFILENAMEW LPOPENFILENAME;
//#else
//typedef OPENFILENAMEA OPENFILENAME;
//typedef LPOPENFILENAMEA LPOPENFILENAME;
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
//#endif 
//#if (_WIN32_WINNT >= 0x0500)
//#define OFN_DONTADDTORECENT          0x02000000
//#define OFN_FORCESHOWHIDDEN          0x10000000    // Show All files including System and hidden files
//#endif // (_WIN32_WINNT >= 0x0500)

// 文件 | 保存
void CNotepadDlg::OnFileSave()
{
	// 对于新建的文件
	if (this->m_filePath.IsEmpty())
	{
		this->OnFileSaveAs();
		return;
	}

	// 对于打开的文件
	this->WriteUnicode(this->m_filePath);
	this->SetModify(FALSE);
}

// 文件 | 另存为...
void CNotepadDlg::OnFileSaveAs()
{
	LPCTSTR lpszFilter =
		//_T("Worksheet Files (*.xls;*.xlsx)|*.xls;*.xlsx|Document Files (*.doc;*docx)|*.doc;*docx|PowerPoint Files (*.ppt;*.pptx)|*.ppt;*.pptx|")
		_T("文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*||");
	CFileDialog fileDialog(FALSE, _T("txt"), nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter);
	if (IDCANCEL == fileDialog.DoModal())
		return;
	
	this->WriteUnicode(fileDialog.GetPathName());
}

// 文件 | 退出
void CNotepadDlg::OnAppExit()
{
	if (this->CheckModify())
	{
		Shell_NotifyIcon(NIM_DELETE, &m_notify);	//删除托盘
		EndDialog(ID_APP_EXIT);
	}
	
	//SendMessage(WM_CLOSE);
}


// 写入Unicode
BOOL CNotepadDlg::WriteUnicode(CString& filePath)
{
	CString strText;
	GetDlgItemText(IDC_TEXT, strText);
	CFile file;
	if (!file.Open(filePath, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox(_T("文件无法保存至此处，请选择其它位置！"));
		return FALSE;
	}
	wchar_t endian = 0xFEFF;									//暂时均保存为Unicode little endian...
	file.Write(&endian, sizeof(endian));
	file.Write(strText, strText.GetLength() * sizeof(TCHAR));
	file.Close();

	return TRUE;
}


void CNotepadDlg::RegisterNotify()
{
	// 初始化
	m_notify.cbSize = sizeof(NOTIFYICONDATA);
	m_notify.hWnd = this->GetSafeHwnd();
	m_notify.uID = IDR_MAINFRAME;
	m_notify.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_notify.uCallbackMessage = WM_USER_NOTIFYICON;
	m_notify.hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);	//OR m_notify.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	_tcscpy_s(m_notify.szTip, this->m_title);
	// 注册
	Shell_NotifyIcon(NIM_ADD, &m_notify);
}

// 托盘 - 方法一：自定义消息处理函数
// 自定义消息响应函数的实现
//wParam接收的是图标的ID，而lParam接收的是鼠标的行为 
LRESULT CNotepadDlg::OnNotifyMsg(WPARAM wParam, LPARAM lParam)
{
	if (IDR_MAINFRAME != wParam)
		return 1;

	switch (lParam)
	{
	case WM_RBUTTONDOWN:		//	Windows Message _ Right Button Down
	{
		// 方法1.
		//POINT point;
		//GetCursorPos(&point);										//鼠标的位置
		//CMenu menu;
		//menu.CreatePopupMenu();										//创建弹出式菜单
		//menu.AppendMenuW(MF_STRING, ID_APP_ABOUT, _T("关于"));
		//menu.AppendMenuW(MF_STRING, ID_APP_EXIT, _T("退出"));		//添加菜单项，映射到相应的响应函数ID上
		//menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);	//确定弹出式菜单的位置
		//HMENU hMenu = menu.Detach();								//资源回收
		//menu.DestroyMenu();

		// 方法2.
		CPoint pos2;
		GetCursorPos(&pos2);
		CMenu menu2;
		menu2.LoadMenu(IDR_MENU_TRAY);			//载入事先定义的选单 
		CMenu* pMenu2 = menu2.GetSubMenu(0);
		pMenu2->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos2.x, pos2.y, AfxGetMainWnd());	//this

		break;
	}
	case WM_LBUTTONDBLCLK:	// Windows Message _ Left Button Double Click
		//切换显示/隐藏主窗口
		//AfxGetApp()->m_pMainWnd->IsWindowVisible();
		IsWindowVisible() ? ShowWindow(SW_HIDE) : (ShowWindow(SW_SHOW), ShowWindow(SW_RESTORE));
		(IsIconic() || IsZoomed()) ? ShowWindow(SW_RESTORE) : FALSE;
		break;
	default:
		break;
	}
	return 0;
}

//// Menu flags for Add/Check/EnableMenuItem()
//#define MF_INSERT           0x00000000L
//#define MF_CHANGE           0x00000080L
//#define MF_APPEND           0x00000100L
//#define MF_DELETE           0x00000200L
//#define MF_REMOVE           0x00001000L
//#define MF_BYCOMMAND        0x00000000L
//#define MF_BYPOSITION       0x00000400L
//#define MF_SEPARATOR        0x00000800L
//#define MF_ENABLED          0x00000000L
//#define MF_GRAYED           0x00000001L
//#define MF_DISABLED         0x00000002L
//#define MF_UNCHECKED        0x00000000L
//#define MF_CHECKED          0x00000008L
//#define MF_USECHECKBITMAPS  0x00000200L
//#define MF_STRING           0x00000000L
//#define MF_BITMAP           0x00000004L
//#define MF_OWNERDRAW        0x00000100L
//#define MF_POPUP            0x00000010L
//#define MF_MENUBARBREAK     0x00000020L
//#define MF_MENUBREAK        0x00000040L
//#define MF_UNHILITE         0x00000000L
//#define MF_HILITE           0x00000080L
//#define MF_DEFAULT          0x00001000L
//#define MF_SYSMENU          0x00002000L
//#define MF_HELP             0x00004000L
//#define MF_RIGHTJUSTIFY     0x00004000L
//#define MF_MOUSESELECT      0x00008000L
//#define MF_END              0x00000080L 
//// Flags for TrackPopupMenu
//#define TPM_LEFTBUTTON  0x0000L
//#define TPM_RIGHTBUTTON 0x0002L
//#define TPM_LEFTALIGN   0x0000L
//#define TPM_CENTERALIGN 0x0004L
//#define TPM_RIGHTALIGN  0x0008L
//#define TPM_TOPALIGN        0x0000L
//#define TPM_VCENTERALIGN    0x0010L
//#define TPM_BOTTOMALIGN     0x0020L
//#define TPM_HORIZONTAL      0x0000L     /* Horz alignment matters more */
//#define TPM_VERTICAL        0x0040L     /* Vert alignment matters more */
//#define TPM_NONOTIFY        0x0080L     /* Don't send any notification msgs */
//#define TPM_RETURNCMD       0x0100L
//#define TPM_RECURSE         0x0001L
//#define TPM_HORPOSANIMATION 0x0400L
//#define TPM_HORNEGANIMATION 0x0800L
//#define TPM_VERPOSANIMATION 0x1000L
//#define TPM_VERNEGANIMATION 0x2000L
//#define TPM_NOANIMATION     0x4000L
//#define TPM_LAYOUTRTL       0x8000L
//#define TPM_WORKAREA        0x10000L


 //托盘 - 方法二：重载虚函数WindowProc()
//LRESULT CNotepadDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message) //判断消息类型
//	{
//	case WM_SYSCOMMAND:			//如果是系统消息 
//		switch (wParam)
//		{
//		case SC_MINIMIZE:			//接收到最小化消息时主窗口隐藏 
//			//AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);
//			ShowWindow(SW_HIDE);
//			break;
//		default:
//			break;
//		}
//		break;
//
//	//case WM_USER_NOTIFYICON:	//如果是用户定义的消息 
//	//	switch (lParam)
//	//	{
//	//	case WM_RBUTTONDOWN:		//鼠标右键单击弹出选单
//	//	{
//	//		CMenu menu;
//	//		menu.LoadMenu(IDR_MENU_TRAY);			//载入事先定义的选单 
//	//		CMenu *pMenu = menu.GetSubMenu(0);
//	//		CPoint pos;
//	//		GetCursorPos(&pos);
//	//		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, AfxGetMainWnd());
//	//		break;
//	//	}
//	//	case WM_LBUTTONDBLCLK:		//鼠标左键双击时主窗口出现 
//	//		AfxGetApp()->m_pMainWnd->IsWindowVisible() ? 
//	//			AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE) : 
//	//			AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
//	//		break;
//	//	default:
//	//		break;
//	//	}
//	//	break;
//	}
//
//	return CDialogEx::WindowProc(message, wParam, lParam);
//}
