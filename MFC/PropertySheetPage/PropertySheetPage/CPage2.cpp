// CPage2.cpp: 实现文件
//

#include "stdafx.h"
#include "PropertySheetPage.h"
#include "CPage2.h"


// CPage2

IMPLEMENT_DYNAMIC(CPage2, CMFCPropertyPage)

CPage2::CPage2() : CMFCPropertyPage(IDD_PAGE2)
, m_birth(COleDateTime::GetCurrentTime())
, m_szBlood(_T(""))
, m_szNative(_T(""))
{

}

CPage2::~CPage2()
{
}
void CPage2::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 在此添加专用代码和/或调用基类

	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_BIRTH, m_birth);
	DDX_CBString(pDX, IDC_COMBO_BLOOD, m_szBlood);
	DDX_Text(pDX, IDC_EDIT_NATIVE, m_szNative);
}


BEGIN_MESSAGE_MAP(CPage2, CMFCPropertyPage)
END_MESSAGE_MAP()



// CPage2 消息处理程序




BOOL CPage2::OnSetActive()
{
	CMFCPropertySheet* pSheet = (CMFCPropertySheet*)GetParent();
	//// 摧毁 帮助 按钮
	//pSheet->m_psh.dwSize &= ~PSH_HASHELP;
	//CWnd* pHelp = pSheet->GetDlgItem(IDHELP);
	//if (pHelp)
	//	pHelp->DestroyWindow();

	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);


	return CMFCPropertyPage::OnSetActive();
}


