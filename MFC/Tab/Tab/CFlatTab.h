#pragma once


// CFlatTab
// �Զ���ؼ���
class CFlatTab : public CWnd
{
	DECLARE_DYNAMIC(CFlatTab)

// DeleteItem(int item)			// ��̬����
// DetetePosition(POSITION pos) // ˫������
private:
	int m_index;			//����
	CArray<CString> m_attr;	//����
	CArray<CRect> m_rect;	//����
	CFont m_font;			//����

	CMemoryDC m_mdc;		//�ڴ滺��DC;
public:
	CFlatTab();
	virtual ~CFlatTab();

	// ����
	BOOL Create(CRect rect, CWnd* pParent, UINT id);
	// ������
	void InsertItem(int index, LPCTSTR text)
	{
		m_attr.InsertAt(index, text);
	}
	// �����Ŀ��ֻ����Ա����
	int GetSize() const
	{
		return (int)m_attr.GetSize();
	}
	// ��������
	void SetFont(CFont* pFont);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
};


