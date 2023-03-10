
// WorkerDlg.h: 头文件
//

#pragma once

class CInputDlg;
class CModifyDlg;

// CWorkerDlg 对话框
class CWorkerDlg : public CDialogEx
{
// 构造
public:
	CWorkerDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CWorkerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
public:
	CListCtrl m_list;
	//// 控件IDs
	//CArray<int> m_ids;
	// 是否修改过
	BOOL m_modified;
	CInputDlg* m_pInputDlg;
protected:
	HICON m_hIcon;

protected:
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	// 检查工号是否存在
	BOOL IsNumberExit(const CString& cstr);
	// 加载文件
	VOID LoadFile();
	// 查找单选组字符串
	int FindGraduate(const CString& cstr);
	// 组合复选框组字
	DWORD CombineLanguages(const CString& cstr);
	// 分离复选框字符串
	void SeparateLanguages(DWORD in_langs, CString& out_cstr);
	// 修改对话框数据初始化
	void InitModifyDlg(int item, CModifyDlg& modifydlg);
	// 修改list数据
	void OverModifyDlg(int item, CModifyDlg& modifydlg);
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnMod();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnSave();

	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
