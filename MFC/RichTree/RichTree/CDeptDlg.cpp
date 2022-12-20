// CDeptDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "RichTree.h"
#include "CDeptDlg.h"
#include "afxdialogex.h"


// CDeptDlg 对话框

IMPLEMENT_DYNAMIC(CDeptDlg, CDialogEx)

CDeptDlg::CDeptDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEPT_DIALOG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CDeptDlg::~CDeptDlg()
{
}

void CDeptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMP, m_comboComp);
	DDX_Control(pDX, IDC_COMBO_DEPT, m_comboDept);
}


BEGIN_MESSAGE_MAP(CDeptDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_COMP, &CDeptDlg::OnSelchangeComboComp)
END_MESSAGE_MAP()


// CDeptDlg 消息处理程序


void CDeptDlg::FillCombo(CString strPath, CComboBox& combo)
{
	// 要逆序删除
	for (int i = combo.GetCount(); i >= 0; i--)
		combo.DeleteString(i);

	CFileFind file;
	BOOL find = file.FindFile(strPath + _T("\\*.*"));
	while (find)
	{
		find = file.FindNextFile();
		if (file.IsDirectory() && !file.IsDots())
			combo.AddString(file.GetFileName());
	}
}

void CDeptDlg::SetCombo(CString strText, CComboBox & combo)
{
	int count = combo.GetCount();
	CString str;
	for (int i = 0; i < count; i++)
	{
		combo.GetLBText(i, str);
		if (str == strText)
		{
			combo.SetCurSel(i);
			//this->OnSelchangeComboComp();
			break;
		}
	}
}


BOOL CDeptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->FillCombo(_T("总公司"), m_comboComp);
	this->SetCombo(_T("www.snowflake.com"), m_comboComp);

	this->FillCombo(_T("总公司\\www.snowflake.com"), m_comboDept);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDeptDlg::OnSelchangeComboComp()
{
	CString str;
	int sel = m_comboComp.GetCurSel();
	m_comboComp.GetLBText(sel, str);
	this->FillCombo(_T("总公司\\") + str, m_comboDept);
	m_comboDept.SetCurSel(0);
}
