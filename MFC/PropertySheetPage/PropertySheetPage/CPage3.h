#pragma once


// CPage3

class CPage3 : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CPage3)

public:
	CPage3();
	virtual ~CPage3();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE3 };
#endif
	virtual void DoDataExchange(CDataExchange* pDX);


protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	CString m_szPhone;
	CString m_szAddress;
	CString m_szEmail;
};


