#pragma once


// CFlatTab
// 自定义控件类
class CFlatTab : public CWnd
{
	DECLARE_DYNAMIC(CFlatTab)

// DeleteItem(int item)			// 动态数组
// DetetePosition(POSITION pos) // 双向链表
private:
	int m_index;			//索引
	CArray<CString> m_attr;	//属性
	CArray<CRect> m_rect;	//区域
	CFont m_font;			//字体

	CMemoryDC m_mdc;		//内存缓冲DC;
public:
	CFlatTab();
	virtual ~CFlatTab();

	// 创建
	BOOL Create(CRect rect, CWnd* pParent, UINT id);
	// 插入项
	void InsertItem(int index, LPCTSTR text)
	{
		m_attr.InsertAt(index, text);
	}
	// 项的数目，只读成员函数
	int GetSize() const
	{
		return (int)m_attr.GetSize();
	}
	// 设置字体
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


