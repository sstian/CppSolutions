// �Զ���ؼ�
#pragma once
#define TIMER_LAMPCTRL	0x0010

class CLampCtrl : public CWnd
{
public:
	CLampCtrl();
	virtual ~CLampCtrl();
	// ����
	BOOL Create(CString& szText, CRect& rect, CWnd* pParent, UINT nID);
	BOOL CreateEx(DWORD dwExStyle, CString& szText, CRect& rect, CWnd* pParent, UINT nID);
	// ����
	void Start()
	{
		SetTimer(TIMER_LAMPCTRL, 15, NULL);
	}
	// ��ͣ
	void Pause()
	{
		KillTimer(TIMER_LAMPCTRL);
	}
	// ���裨������������
	void Reset();

	void SetTextColor(COLORREF coText) { m_coText = coText; }
	void SetBackColor(COLORREF coBack) { m_coBack = coBack; }
	void SetFont(CFont* pFont);

public:
	CString m_szText;	//�ı�����
	int m_nLeft;		//�ı�λ��
	int m_nLeft2;		//�ı�λ��2
	COLORREF m_coText;	//�ı���ɫ
	COLORREF m_coBack;	//������ɫ
	CFont m_font;		//����

	CMemoryDC m_mdc;		//�ڴ滺��DC

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

