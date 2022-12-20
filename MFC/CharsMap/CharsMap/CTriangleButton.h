// 绘制三角形按钮

#pragma once


// CTriangleButton

class CTriangleButton : public CMFCButton
{
	DECLARE_DYNAMIC(CTriangleButton)

public:
	CTriangleButton();
	virtual ~CTriangleButton();

public:

	enum POINTDIRECTION { POINT_UP, POINT_DOWN, POINT_LEFT, POINT_RIGHT };

	void SetDirection(POINTDIRECTION Direction); //sets the direction of triangle
	POINTDIRECTION GetDirection(); //gets the direction of triangle

	BOOL SetWindowPos(const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);

protected:
	POINTDIRECTION PointDirection;
	CRgn CurrentRegion;

protected:
	DECLARE_MESSAGE_MAP()

	virtual void PreSubclassWindow();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


