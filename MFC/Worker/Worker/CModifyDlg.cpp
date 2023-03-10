// CModifyDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Worker.h"
#include "WorkerDlg.h"
#include "CModifyDlg.h"
#include "afxdialogex.h"


// CModifyDlg 对话框

IMPLEMENT_DYNAMIC(CModifyDlg, CDialogEx)

CModifyDlg::CModifyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODIFY_DIALOG, pParent)
	, m_nNumber(0)
	, m_szName(_T(""))
	, m_szSex(FALSE)
	, m_dSalary(0)
	, m_datetime(COleDateTime::GetCurrentTime())
	, m_nGraduate(0)
	, m_bEnglish(FALSE)
	, m_bJapanese(FALSE)
	, m_bKorean(FALSE)
	, m_bFrench(FALSE)
	, m_bRussian(FALSE)
{
	m_ids.RemoveAll();
	// 添加控件ID
	m_ids.Add(IDC_EDIT_MODIFY_NUM);
	m_ids.Add(IDC_EDIT_MODIFY_NAME);
	m_ids.Add(IDC_EDIT_MODIFY_SALARY);
	m_ids.Add(IDC_MODIFY_DATETIMEPICKER);

}

CModifyDlg::~CModifyDlg()
{
	m_ids.RemoveAll();
}

void CModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODIFY_DATETIMEPICKER, m_date);
	DDX_Text(pDX, IDC_EDIT_MODIFY_NUM, m_nNumber);
	DDX_Text(pDX, IDC_EDIT_MODIFY_NAME, m_szName);
	DDX_Radio(pDX, IDC_RADIO_MODIFY_SEX, m_szSex);
	DDX_Text(pDX, IDC_EDIT_MODIFY_SALARY, m_dSalary);
	DDX_DateTimeCtrl(pDX, IDC_MODIFY_DATETIMEPICKER, m_datetime);
	DDX_Radio(pDX, IDC_RADIO_MODIFY_GRADUATE, m_nGraduate);
	DDX_Check(pDX, IDC_CHECK_MODIFY_ENGLISH, m_bEnglish);
	DDX_Check(pDX, IDC_CHECK_MODIFY_JAPANESE, m_bJapanese);
	DDX_Check(pDX, IDC_CHECK_MODIFY_KOREAN, m_bKorean);
	DDX_Check(pDX, IDC_CHECK_MODIFY_FRENCH, m_bFrench);
	DDX_Check(pDX, IDC_CHECK_MODIFY_RUSSIAN, m_bRussian);
}


BEGIN_MESSAGE_MAP(CModifyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CModifyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CModifyDlg 消息处理程序


BOOL CModifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//// 填充对话框数据
	//CListCtrl& list = m_pWorkerDlg->m_list;
	//POSITION pos = list.GetFirstSelectedItemPosition();
	//int item = list.GetNextSelectedItem(pos);
	//SetDlgItemText(IDC_EDIT_MODIFY_NUM, list.GetItemText(item, 0));
	//SetDlgItemText(IDC_EDIT_MODIFY_NAME, list.GetItemText(item, 1));
	//SetDlgItemText(IDC_EDIT_MODIFY_SALARY, list.GetItemText(item, 2));
	//COleDateTime time;
	//time.ParseDateTime(list.GetItemText(item, 3), VAR_DATEVALUEONLY);
	//m_date.SetTime(time);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CModifyDlg::OnBnClickedOk()
{
	//NextDlgCtrl();
	//int id = GetFocus()->GetDlgCtrlID();
	//if (IDOK == id || IDC_EDIT_MODIFY_NUM == id)
	//{
		//this->ModifyData();
		//SetFocus();
		//GetDlgItem(IDC_EDIT_MODIFY_NAME)->SetFocus();
	//}
	CDialogEx::OnOK();
}

void CModifyDlg::ModifyData()
{
	CListCtrl& list = m_pWorkerDlg->m_list;
	if (!list.GetSelectedCount())
	{
		AfxMessageBox(_T("请至少选中一行"));
		return;
	}
	POSITION pos = list.GetFirstSelectedItemPosition();
	//while (pos)
	{
		int item = list.GetNextSelectedItem(pos);
		CString hint = _T("确定修改 ") + list.GetItemText(item, 0) + _T(" 吗？");
		if (IDNO == AfxMessageBox(hint, MB_YESNO))
			//continue;
			return;
		// 修改操作
		CString cstr;
		for (int i = 1; i < m_ids.GetSize(); i++)
		{
			GetDlgItemText(m_ids.GetAt(i), cstr);
			list.SetItemText(item, i, cstr);
		}
		m_pWorkerDlg->m_modified = TRUE;
	}
}

