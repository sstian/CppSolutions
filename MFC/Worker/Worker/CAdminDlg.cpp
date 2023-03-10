// CAdminDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Worker.h"
#include "CAdminDlg.h"
#include "afxdialogex.h"


// CAdminDlg 对话框


IMPLEMENT_DYNAMIC(CAdminDlg, CDialogEx)

CAdminDlg::CAdminDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMIN_DIALOG, pParent)
{
	m_modified = FALSE;
}

CAdminDlg::~CAdminDlg()
{
}

void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADMIN_LIST, m_ListCtrl);
	DDX_Control(pDX, IDC_COMBO_PRIORITY, m_prority);
}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADMIN_ADD, &CAdminDlg::OnBnClickedBtnAdminAdd)
	ON_BN_CLICKED(IDC_BTN_ADMIN_DELETE, &CAdminDlg::OnBnClickedBtnAdminDelete)
	ON_BN_CLICKED(IDC_BTN_ADMIN_MODIFY, &CAdminDlg::OnBnClickedBtnAdminModify)
	//ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_ADMIN_SAVE, &CAdminDlg::OnBnClickedBtnAdminSave)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ADMIN_LIST, &CAdminDlg::OnItemchangedAdminList)
END_MESSAGE_MAP()


// CAdminDlg 消息处理程序

BOOL CAdminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_userids.Add(IDC_EDIT_NAME);
	m_userids.Add(IDC_EDIT_PASS);
	m_userids.Add(IDC_COMBO_PRIORITY);

	// 关联变量
	//CListCtrl* list = (CListCtrl*)GetDlgItem(IDC_ADMIN_LIST);		//method 0.
	//m_list.Attach(::GetDlgItem(m_hWnd, IDC_ADMIN_LIST));			//method 1-1.(需要在OnDestroy()解除)
	//m_list.SubclassWindow(::GetDlgItem(m_hWnd, IDC_ADMIN_LIST));	//method 2-1. ...
	//m_list.SubclassDlgItem(IDC_ADMIN_LIST, this);					//method 3.
	//method 4.添加控件变量（推荐使用）										
	m_ListCtrl.InsertColumn(0, _T("账号"), LVCFMT_LEFT, 150);
	m_ListCtrl.InsertColumn(1, _T("密码"), LVCFMT_LEFT, 150);
	m_ListCtrl.InsertColumn(2, _T("权限"), LVCFMT_LEFT, 115);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_CHECKBOXES*/);
	this->LoadFile();
	
	// 手动在后面添加列表数据 或者修改控件属性 Data: 普通;高级 ，以英文分号分隔。
	//m_prority.AddString(_T("普通"));
	//m_prority.AddString(_T("高级"));
	m_prority.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CAdminDlg::OnBnClickedBtnAdminAdd()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT_USER, cstr);
	if (!this->Check(cstr))
		return;

	int item = m_ListCtrl.GetItemCount();
	m_ListCtrl.InsertItem(item, cstr);
	//GetDlgItemText(IDC_EDIT_PASS, cstr);
	//m_ListCtrl.SetItemText(item, 1, cstr);
	//GetDlgItemText(IDC_COMBO_PRIORITY, cstr);
	//m_ListCtrl.SetItemText(item, 2, cstr);
	for (int subitem = 1; subitem < m_userids.GetSize(); subitem++)
	{
		GetDlgItemText(m_userids.GetAt(subitem), cstr);
		m_ListCtrl.SetItemText(item, subitem, cstr);
	}

	m_modified = TRUE;
}


void CAdminDlg::OnBnClickedBtnAdminDelete()
{
	if (!m_ListCtrl.GetSelectedCount())
	{
		AfxMessageBox(_T("请至少选中一行"));
		return;
	}
	//只有直接删除
	POSITION pos = nullptr;								//类似于链表CList操作
	while (m_ListCtrl.GetFirstSelectedItemPosition())	//猜测存在重新计算被选中标志
	{
		int item = m_ListCtrl.GetNextSelectedItem(pos);
		m_ListCtrl.DeleteItem(item);
		m_modified = TRUE;
	}
}


void CAdminDlg::OnBnClickedBtnAdminModify()
{
	if (!m_ListCtrl.GetSelectedCount())
	{
		AfxMessageBox(_T("请至少选中一行"));
		return;
	}
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	while (pos)
	{
		int item = m_ListCtrl.GetNextSelectedItem(pos);
		//CString hint = _T("确定修改 ") + m_ListCtrl.GetItemText(item, 0) + _T(" 吗？");
		//if (IDNO == AfxMessageBox(hint, MB_YESNO))
		//	continue;
		// 修改操作，账户名不可修改
		CString cstr;
		for (int i = 1; i < m_userids.GetSize(); i++)
		{
			GetDlgItemText(m_userids.GetAt(i), cstr);
			m_ListCtrl.SetItemText(item, i, cstr);
		}
		m_modified = TRUE;
	}

}

void CAdminDlg::OnBnClickedBtnAdminSave()
{
	this->SaveFile();
	m_modified = FALSE;
}



//void CAdminDlg::OnDestroy()
//{
//	CDialogEx::OnDestroy();
//	// 解除
//	//m_list.Detach();				//method 1-2.
//	//m_list.UnsubclassWindow();	//method 2-2.
//}


// 检查账户名是否存在
// FALSE - 已存在
BOOL CAdminDlg::Check(CString& username)
{
	for (int item = 0; item < m_ListCtrl.GetItemCount(); item++)
	{
		if (m_ListCtrl.GetItemText(item, 0) == username)
		{
			AfxMessageBox(_T("账户 ") + username + _T(" 已存在！请重新输入."));
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CAdminDlg::LoadFile()
{
	CFile file;
	if (!file.Open(ADMIN_DATA, CFile::modeRead))
		return FALSE;
	SAdmin user;
	for (int item = 0; sizeof(user) == file.Read(&user, sizeof(user)); item++)
	{
		m_ListCtrl.InsertItem(item, user.sname);
		m_ListCtrl.SetItemText(item, 1, user.spass);
		m_ListCtrl.SetItemText(item, 2, (!user.nprior ? theApp.m_szPrority[CWorkerApp::Normal] : theApp.m_szPrority[CWorkerApp::Advance]));
		//theApp.m_szPrority[theApp.Normal]; or CWorkerApp::m_szPrority[CWorkerApp::EProroty::Normal]; or theApp.m_szPrority[CWorkerApp::Normal];
	}
	file.Close();
	return TRUE;
}

BOOL CAdminDlg::SaveFile()
{
	CFile file;
	if (!file.Open(ADMIN_DATA, CFile::modeCreate | CFile::modeWrite))	//创建并西写入，如果文件存在则覆盖，好狠！
	{
		AfxMessageBox(_T("保存文件时出错！"));
		return FALSE;
	}
	SAdmin user;
	int count = m_ListCtrl.GetItemCount();
	for (int item = 0; item < count; item++)
	{
		m_ListCtrl.GetItemText(item, 0, user.sname, sizeof(user.sname));
		m_ListCtrl.GetItemText(item, 1, user.spass, sizeof(user.spass));
		user.nprior = m_ListCtrl.GetItemText(item, 2) == theApp.m_szPrority[CWorkerApp::Advance];
		file.Write(&user, sizeof(user));
	}
	file.Close();
	return TRUE;
}


void CAdminDlg::OnCancel()
{
	if (m_modified)
	{
		int id = AfxMessageBox(_T("是否将改动保存到文件？"), MB_YESNOCANCEL);
		switch (id)
		{
		case IDYES:
			this->SaveFile();
			break;
			//case IDNO:
			//	break;
		case IDCANCEL:
			return;
			//default:
			//	break;
		}
	}

	EndDialog(IDCANCEL);
	//CDialogEx::OnCancel();
}




void CAdminDlg::OnItemchangedAdminList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//// 方法1
	//if (pNMLV->uChanged == LVIF_STATE)
	//{
	//	if (pNMLV->uNewState & LVIS_SELECTED)
	//	{
	//		int item = pNMLV->iItem;
	//		SetDlgItemText(IDC_EDIT_USER, m_ListCtrl.GetItemText(item, 0));
	//		SetDlgItemText(IDC_EDIT_PASS, m_ListCtrl.GetItemText(item, 1));
	//		m_prority.SetCurSel(m_ListCtrl.GetItemText(item, 2) == theApp.m_szPrority[CWorkerApp::Advance]);	//_T("高级")
	//	}
	//}
	*pResult = 0;
	 //方法2
	if (pNMLV->uOldState == 0)
	{
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		if (!pos)
			return;
		int item = m_ListCtrl.GetNextSelectedItem(pos);
		SetDlgItemText(IDC_EDIT_USER, m_ListCtrl.GetItemText(item, 0));
		SetDlgItemText(IDC_EDIT_PASS, m_ListCtrl.GetItemText(item, 1));
		m_prority.SetCurSel(m_ListCtrl.GetItemText(item, 2) == theApp.m_szPrority[CWorkerApp::Advance]);	//_T("高级")
	}
}
//HDN：Header Notify
//LVN：ListView control Notify
//NM：Notify Message
//TVN：TreeView control Notify
//#define LVIF_TEXT               0x00000001
//#define LVIF_IMAGE              0x00000002
//#define LVIF_PARAM              0x00000004
//#define LVIF_STATE              0x00000008
//#define LVIF_INDENT             0x00000010
//#define LVIF_NORECOMPUTE        0x00000800
//#define LVIF_GROUPID            0x00000100
//#define LVIF_COLUMNS            0x00000200
//#define LVIF_COLFMT             0x00010000 // The piColFmt member is valid in addition to puColumns
//#define LVIS_FOCUSED            0x0001
//#define LVIS_SELECTED           0x0002
//#define LVIS_CUT                0x0004
//#define LVIS_DROPHILITED        0x0008
//#define LVIS_GLOW               0x0010
//#define LVIS_ACTIVATING         0x0020
//#define LVIS_OVERLAYMASK        0x0F00
//#define LVIS_STATEIMAGEMASK     0xF000
//typedef struct tagNMHDR
//{
//	HWND      hwndFrom;
//	UINT_PTR  idFrom;
//	UINT      code;         // NM_ code
//}   NMHDR;
//#define LPNM_LISTVIEW   LPNMLISTVIEW
//#define NM_LISTVIEW     NMLISTVIEW
//typedef struct tagNMLISTVIEW
//{
//	NMHDR   hdr;
//	int     iItem;
//	int     iSubItem;
//	UINT    uNewState;
//	UINT    uOldState;
//	UINT    uChanged;
//	POINT   ptAction;
//	LPARAM  lParam;
//} NMLISTVIEW, *LPNMLISTVIEW;
//	typedef struct tagLVITEMW
//	{
//		UINT mask;
//		int iItem;
//		int iSubItem;
//		UINT state;
//		UINT stateMask;
//		LPWSTR pszText;
//		int cchTextMax;
//		int iImage;
//		LPARAM lParam;
//		int iIndent;
//#if (NTDDI_VERSION >= NTDDI_WINXP)
//		int iGroupId;
//		UINT cColumns; // tile view columns
//		PUINT puColumns;
//#endif
//#if (NTDDI_VERSION >= NTDDI_VISTA)
//		int* piColFmt;
//		int iGroup; // readonly. only valid for owner data.
//#endif
//	} LVITEMW, *LPLVITEMW;
