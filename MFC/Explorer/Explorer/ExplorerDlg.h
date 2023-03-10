
// ExplorerDlg.h: 头文件
//

#pragma once


// CExplorerDlg 对话框
class CExplorerDlg : public CDialogEx
{
// 构造
public:
	CExplorerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXPLORER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGo();
	// 搜索文件 C语言
	BOOL FileFindC(CListCtrl* pList, CString& strPath);
	// 搜索文件 Windows API
	BOOL FileFindAPI(CListCtrl* pList, CString& strPath);
	// 搜索文件 MFC
	BOOL FileFindMFC(CListCtrl* pList, CString& strPath);
	// 隐藏文件与.和..
	inline static BOOL IsHidden(const _wfinddata_t& cFile)
	{	
		//if (cFile.attrib & _A_HIDDEN)
		//	return TRUE;
		//if (0==_tcscmp(cFile.name, _T(".")))
		//	return TRUE;
		//if (!_tcscmp(cFile.name, _T("..")))
		//	return TRUE;
		//return FALSE;

		return (cFile.attrib & _A_HIDDEN) || (!_tcscmp(cFile.name, _T("."))) || (!_tcscmp(cFile.name, _T("..")));
	}
	inline static BOOL IsHidden(const WIN32_FIND_DATA& cFile)
	{
		return (cFile.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) || (!_tcscmp(cFile.cFileName, _T("."))) || (!_tcscmp(cFile.cFileName, _T("..")));
	}

};
