// CPage3.cpp: 实现文件
//

#include "stdafx.h"
#include "PropertySheetPage.h"
#include "CPage3.h"


// CPage3

IMPLEMENT_DYNAMIC(CPage3, CMFCPropertyPage)

CPage3::CPage3() : CMFCPropertyPage(IDD_PAGE3)
, m_szPhone(_T(""))
, m_szAddress(_T(""))
, m_szEmail(_T(""))
{

}

CPage3::~CPage3()
{
}
void CPage3::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类

	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_szPhone);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_szAddress);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_szEmail);
}


BEGIN_MESSAGE_MAP(CPage3, CMFCPropertyPage)
END_MESSAGE_MAP()



// CPage3 消息处理程序




BOOL CPage3::OnSetActive()
{
	CMFCPropertySheet* pSheet = (CMFCPropertySheet*)GetParent();
	//// 摧毁 帮助 按钮
	//pSheet->m_psh.dwSize &= ~PSH_HASHELP;
	//CWnd* pHelp = pSheet->GetDlgItem(IDHELP);
	//if (pHelp)
	//	pHelp->DestroyWindow();

	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);


	return CMFCPropertyPage::OnSetActive();
}


