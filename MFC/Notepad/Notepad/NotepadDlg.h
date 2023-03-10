
// NotepadDlg.h: 头文件
//

#pragma once

// 自定义消息映射ID
#define WM_USER_NOTIFYICON	WM_USER+100

// CString 数组大小定义，多预留一个
#define SECTION_NUMBER			(2+1)
#define ENTRY_RECT_NUMBER		(4+1)
#define ENTRY_SETTING_NUMBER	(2+1)

const CString SETTING_CAPTION = _T("MyNotepad");


// CNotepadDlg 对话框
class CNotepadDlg : public CDialogEx
{
// 构造
public:
	CNotepadDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTEPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;		//图标
	HACCEL m_hAccel;	//快捷键
	CFont m_font;		//字体
	CString m_title;	//文件标题
	CString m_filePath;	//文件全路径
	NOTIFYICONDATA m_notify;	//托盘数据

	static CString section[SECTION_NUMBER];
	static CString entry_rect[ENTRY_RECT_NUMBER];
	static CString entry_setting[ENTRY_SETTING_NUMBER];
	// 段 枚举
	enum ESection
	{
		_RECT = 0,
		_SETTING
	};
	// 键 in Rect 枚举
	enum EEntry_Rect
	{
		_LEFT = 0,
		_RIGHT,
		_TOP, 
		_BOTTOM
	};
	// 键 in Setting 枚举
	enum EEntry_Setting
	{
		_CAPTION = 0,
		_FONT
	};

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAppExit();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAppAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnEditUndo();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditClear();
	afx_msg void OnEditDatetime();
	afx_msg void OnEditSelectAll();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	// 加载文件
	BOOL LoadFile(LPCTSTR szfile);
	// 读取ANSI文件
	BOOL ReadANSI(CFile& file);
	// 读取UTF-8文件
	BOOL ReadUTF8(CFile& file);
	// 读取Unicode文件
	BOOL ReadUnicode(CFile& file);
	// 读取Unicode文件 big endian
	BOOL ReadUnicodeBE(CFile& file);
	// 写入配置文件
	void WriteProfile();
	// 加载配置文件
	void GetProfile();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnFileOpen();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnFormatFont();
	afx_msg void OnFileNew();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();

	// 设置标题栏为文件名
	void SetTitle(CString& szfile)
	{
		m_filePath = szfile;
		int index = szfile.ReverseFind(_T('\\'));
		if (index > 0)
			m_title = szfile.Mid(index + 1);
		CString title = m_title.IsEmpty() ? _T("无标题") : m_title;
		SetWindowText(title + _T(" - 记事本"));
		// 托盘提示文字
		_tcscpy_s(m_notify.szTip, this->m_title);
		Shell_NotifyIcon(NIM_MODIFY, &m_notify);	//修改托盘
	}

	// 清空文件名及标题
	void ClearFile()
	{
		this->m_title.Empty();
		this->m_filePath.Empty();

		this->OnEditSelectAll();
		this->OnEditClear();
		this->SetModify(FALSE);
		SetWindowText(_T("无标题 - 记事本"));
	}

	// 设置修改标志
	void SetModify(BOOL modified)
	{
		((CEdit*)GetDlgItem(IDC_TEXT))->SetModify(modified);
	}

	// 获取修改标志
	BOOL GetModify() const
	{
		return ((CEdit*)GetDlgItem(IDC_TEXT))->GetModify();
	}

	// 检查修改标志以提示保存。
	// 返回值：TRUE - 保存/不保存；FALSE - 取消
	BOOL CheckModify()
	{
		if (this->GetModify())
		{
			CString strHint = _T("是否将更改保存到");
			strHint += this->m_filePath.IsEmpty() ? _T(" 无标题？") : _T("\r\n") + m_filePath + _T("?");
			switch (AfxMessageBox(strHint, MB_YESNOCANCEL))
			{
			case IDYES:
				this->OnFileSave();
				break;
			//case IDNO:		//无操作
			//	this->SetModify(FALSE);
			//	break;
			case IDCANCEL:	//退出函数，不结束对话框
				return FALSE;
			default:
				break;
			}
		}
		return TRUE;
	}

	// 写入Unicode文件
	BOOL WriteUnicode(CString& filePath);
protected:
	// 初始化并注册NOTIFYICON
	void RegisterNotify();	
	// 自定义消息响应函数的声明
	afx_msg LRESULT OnNotifyMsg(WPARAM wParam, LPARAM lParam);
	//virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

//typedef struct _NOTIFYICONDATAW {
//	DWORD cbSize;			// 结构的大小，必须在程序中给出
//	HWND hWnd;				// 程序中将要接收托盘消息的窗口句柄
//	UINT uID;				// 应用程序中定义的托盘图标ID，此参数用作标识
//	UINT uFlags;			// 设置属性 标记下边3个参数是否有效。NIF_ICON|NIF_MESSAGE|NIF_TIP
//	UINT uCallbackMessage;	// 自定义的消息ID值
//	HICON hIcon;			// 显示在系统托盘上的Icon的句柄
//#if (NTDDI_VERSION < NTDDI_WIN2K)
//	WCHAR  szTip[64];		
//#endif
//#if (NTDDI_VERSION >= NTDDI_WIN2K)
//	WCHAR  szTip[128];		// 用于图标显示的提示字符串
//	DWORD dwState;
//	DWORD dwStateMask;
//	WCHAR  szInfo[256];
//#ifndef _SHELL_EXPORTS_INTERNALAPI_H_
//	union {
//		UINT  uTimeout;
//		UINT  uVersion;  // used with NIM_SETVERSION, values 0, 3 and 4
//	} DUMMYUNIONNAME;
//#endif
//	WCHAR  szInfoTitle[64];
//	DWORD dwInfoFlags;
//#endif
//#if (NTDDI_VERSION >= NTDDI_WINXP)
//	GUID guidItem;
//#endif
//#if (NTDDI_VERSION >= NTDDI_VISTA)
//	HICON hBalloonIcon;
//#endif
//} NOTIFYICONDATAW, *PNOTIFYICONDATAW;
//typedef NOTIFYICONDATAW NOTIFYICONDATA;
//typedef PNOTIFYICONDATAW PNOTIFYICONDATA;
//
//SHSTDAPI_(BOOL) Shell_NotifyIconW(DWORD dwMessage, _In_ PNOTIFYICONDATAW lpData);
//
//#define NIM_ADD         0x00000000
//#define NIM_MODIFY      0x00000001
//#define NIM_DELETE      0x00000002
//#define NIM_SETFOCUS    0x00000003
//#define NIM_SETVERSION  0x00000004
// Notify Icon Flag
//#define NIF_MESSAGE     0x00000001
//#define NIF_ICON        0x00000002
//#define NIF_TIP         0x00000004
//#define NIF_STATE       0x00000008
//#define NIF_INFO        0x00000010
//#define NIF_GUID        0x00000020
//#define NIF_REALTIME    0x00000040
//#define NIF_SHOWTIP     0x00000080
//#define NIS_HIDDEN              0x00000001
//#define NIS_SHAREDICON          0x00000002
//// Notify Icon Infotip flags
//#define NIIF_NONE       0x00000000
//// icon flags are mutually exclusive and take only the lowest 2 bits
//#define NIIF_INFO       0x00000001
//#define NIIF_WARNING    0x00000002
//#define NIIF_ERROR      0x00000003
//#define NIIF_USER       0x00000004
//#define NIIF_ICON_MASK  0x0000000F
//#define NIIF_NOSOUND    0x00000010
//#define NIIF_LARGE_ICON 0x00000020
//#define NIIF_RESPECT_QUIET_TIME 0x00000080
//

