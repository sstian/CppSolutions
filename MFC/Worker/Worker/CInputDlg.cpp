// CInputDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Worker.h"
#include "WorkerDlg.h"		//cpp文件中需要头文件
#include "CInputDlg.h"
#include "afxdialogex.h"


// CInputDlg 对话框

IMPLEMENT_DYNAMIC(CInputDlg, CDialogEx)

CInputDlg::CInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_DIALOG, pParent)
	, m_uNumber(0)
	, m_szName(_T(""))
	, m_bSex(FALSE)
	, m_dSalary(0)
	, m_date(COleDateTime::GetCurrentTime())
	, m_nGraduate(0)
	, m_bEnglish(FALSE)
	, m_bJapanese(FALSE)
	, m_bKorean(FALSE)
	, m_bFrench(FALSE)
	, m_bRussian(FALSE)
{
	m_ids.RemoveAll();
	// 添加控件ID
	m_ids.Add(IDC_EDIT_NUM);
	m_ids.Add(IDC_EDIT_NAME);
	m_ids.Add(IDC_EDIT_SALARY);
	m_ids.Add(IDC_DATETIMEPICKER);

}

CInputDlg::~CInputDlg()
{
	m_ids.RemoveAll();
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM, m_uNumber);
	DDX_Text(pDX, IDC_EDIT_NAME, m_szName);
	DDX_Radio(pDX, IDC_RADIO_SEX, m_bSex);
	DDX_Text(pDX, IDC_EDIT_SALARY, m_dSalary);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER, m_date);
	DDX_Radio(pDX, IDC_RADIO_GRADUATE, m_nGraduate);
	DDX_Check(pDX, IDC_CHECK_ENGLISH, m_bEnglish);
	DDX_Check(pDX, IDC_CHECK_JAPANESE, m_bJapanese);
	DDX_Check(pDX, IDC_CHECK_KOREAN, m_bKorean);
	DDX_Check(pDX, IDC_CHECK_FRENCH, m_bFrench);
	DDX_Check(pDX, IDC_CHECK_RUSSIAN, m_bRussian);
	DDX_Text(pDX, IDC_EDIT_NUM, m_uNumber);
	DDX_Text(pDX, IDC_EDIT_SALARY, m_dSalary);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialogEx)
//	ON_EN_CHANGE(IDC_EDIT_SALARY, &CInputDlg::OnChangeEditSalary)
END_MESSAGE_MAP()


// CInputDlg 消息处理程序

BOOL CInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CInputDlg::OnOK()
{
	//NextDlgCtrl();						//当按下回车键时焦点跳到下一个控件上。如果焦点位于最后一个控件，则移到第一个控件上。
	//int id = GetFocus()->GetDlgCtrlID();
	//if (IDOK == id || IDC_EDIT_NUM == id)
	//{
		this->AddToList();
	//	SetFocus();
	//}

	//CDialogEx::OnOK();
}

void CInputDlg::AddToList()
{	
	CString cstr;
	GetDlgItemText(m_ids.GetAt(0), cstr);
	if (m_pWorkerDlg->IsNumberExit(cstr))
	{
		AfxMessageBox(_T("工号: ") + cstr + _T(" 已存在！请重输"));
		return;
	}
	CListCtrl& list = m_pWorkerDlg->m_list;
	int item = list.GetItemCount();
	//int size = (int)m_ids.GetSize();
	//for (int i = 0; i < size; i++)
	//{
	//	GetDlgItemText(m_ids.GetAt(i), cstr);
	//	(0 == i) ? list.InsertItem(item, cstr) : list.SetItemText(item, i, cstr);

	//}
	
	UpdateData(TRUE);
	this->UpdateLanguages();
	CString str; 
	str.Empty();
	str.Format(_T("%u"), m_uNumber);
	list.InsertItem(item, str);
	list.SetItemText(item, Name, m_szName);
	list.SetItemText(item, Sex, m_bSex ? theApp.m_szSex[CWorkerApp::Male] : theApp.m_szSex[CWorkerApp::Female]);
	str.Empty();
	str.Format(_T("%0.2lf"), m_dSalary);
	list.SetItemText(item, Salary, str);
	list.SetItemText(item, Date, m_date.Format(_T("%Y/%m/%d")));
	list.SetItemText(item, Graduate, theApp.m_szGraduate[m_nGraduate]);
	this->GetLanguages(str);
	list.SetItemText(item, Language, str);

	m_pWorkerDlg->m_modified = TRUE;

}

void CInputDlg::UpdateLanguages()
{
	// 添加复选框变量
	m_langs.RemoveAll();
	m_langs.Add(m_bEnglish);
	m_langs.Add(m_bJapanese);
	m_langs.Add(m_bKorean);
	m_langs.Add(m_bFrench);
	m_langs.Add(m_bRussian);
}

void CInputDlg::GetLanguages(CString & str)
{
	str.Empty();
	int size = (int)m_langs.GetSize();
	for (int i = 0; i < size; i++)
	{
		if (m_langs.GetAt(i))
			str += theApp.m_szLanguage[i];
	}	
}

// 自定义控件消息反射格式控制
//void CInputDlg::OnChangeEditSalary()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	CString str;
//	TCHAR tchar;
//	GetDlgItemText(IDC_EDIT_SALARY, str);
//	int size = str.GetLength();
//	for (int i = 0; i < size; i++)
//	{
//		tchar = str.GetAt(i);
//		if (tchar < _T('0') || tchar > _T('9') && tchar != _T('.'))
//		{
//			str.Delete(i, 1);
//			size--;
//		}
//	}
//	SetDlgItemText(IDC_EDIT_SALARY, str);
//}
