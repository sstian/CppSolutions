// CPage1.cpp: 实现文件
//

#include "stdafx.h"
#include "PropertySheetPage.h"
#include "CPage1.h"


// CPage1

IMPLEMENT_DYNAMIC(CPage1, CMFCPropertyPage)

CPage1::CPage1() : CMFCPropertyPage(IDD_PAGE1)
, m_szAccount(_T(""))
, m_szNickname(_T(""))
, m_sex(FALSE)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange * pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_szAccount);
	DDX_Text(pDX, IDC_EDIT_NICKNAME, m_szNickname);
	DDX_Radio(pDX, IDC_RADIO_FEMALE, m_sex);
}


BEGIN_MESSAGE_MAP(CPage1, CMFCPropertyPage)
END_MESSAGE_MAP()



// CPage1 消息处理程序




BOOL CPage1::OnSetActive()
{
	CMFCPropertySheet* pSheet = (CMFCPropertySheet*)GetParent();
	// 摧毁 帮助 按钮
	pSheet->m_psh.dwSize &= ~PSH_HASHELP;
	CWnd* pHelp = pSheet->GetDlgItem(IDHELP);
	if (pHelp)
		pHelp->DestroyWindow();

	pSheet->SetWizardButtons(PSWIZB_NEXT);

	return CMFCPropertyPage::OnSetActive();
}


// 截获 下一步 消息
LRESULT CPage1::OnWizardNext()
{
	CString str;
	GetDlgItemText(IDC_EDIT_SN, str);
	if (str == _T("123456"))
		return 0;
	AfxMessageBox(_T("序列号错误，请重新填写！SN = 123456"));
	return -1;

	//return CMFCPropertyPage::OnWizardNext();
}
