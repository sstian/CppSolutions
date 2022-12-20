#pragma once


// CPage1

class CPage1 : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1();
	virtual ~CPage1();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE1 };
#endif
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	
	CString m_szAccount;
	CString m_szNickname;
	BOOL m_sex;
	virtual LRESULT OnWizardNext();
};


