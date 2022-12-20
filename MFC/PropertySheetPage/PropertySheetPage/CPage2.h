#pragma once


// CPage2

class CPage2 : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2();
	virtual ~CPage2();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE2 };
#endif
	virtual void DoDataExchange(CDataExchange* pDX);


protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();

	COleDateTime m_birth;
	CString m_szBlood;
	CString m_szNative;
};


