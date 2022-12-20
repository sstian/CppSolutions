#pragma once
#include "CLayer.h"

// »­¾ØÐÎ
class CRectangle :
	public CLayer
{
public:
	CRect m_rect;

public:
	CRectangle() : m_rect(MAXLONG, MAXLONG, MAXLONG, MAXLONG) { }
	CRectangle(const CRect& rect) : m_rect(rect) { }

	virtual ~CRectangle() { }

	void OnLButtonDown(UINT nFlags, CPoint point)
	{
		m_rect.TopLeft() = point;
	}
	void OnLButtonUp(UINT nFlags, CPoint point)
	{
		m_rect.BottomRight() = point;
		m_rect.NormalizeRect();
	}
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
	{
		if (nFlags & MK_LBUTTON)
		{
			//HBRUSH hBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
			//pDC->SelectObject(hBrush);
			pDC->SelectStockObject(NULL_BRUSH);

			pDC->SetROP2(R2_NOT);
			if (m_rect.right != MAXLONG)
				pDC->Rectangle(m_rect);
			m_rect.BottomRight() = point;
			pDC->Rectangle(m_rect);
		}
	}

	void OnDraw(CDC* pDC)
	{
		CPen pen(PS_SOLID, 1, m_clFront);
		CPen* pOldPen = pDC->SelectObject(&pen);
		CBrush brush(m_clBack);
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		pDC->Rectangle(m_rect);

		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);

		if (TYPE_SELECTED == m_type)
		{
			CPoint& ptTopLeft = m_rect.TopLeft();
			CPoint ptTopRight(m_rect.right, m_rect.top);
			CPoint& ptBottomRight = m_rect.BottomRight();
			CPoint ptBottomLeft(m_rect.left, m_rect.bottom);
			pDC->FillSolidRect(ptTopLeft.x - 3, ptTopLeft.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
			pDC->FillSolidRect(ptTopRight.x - 3, ptTopRight.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
			pDC->FillSolidRect(ptBottomRight.x - 3, ptBottomRight.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
			pDC->FillSolidRect(ptBottomLeft.x - 3, ptBottomLeft.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
		}
	}
	void SelectLayer(UINT nFlags, CPoint point)
	{
		m_type = m_rect.PtInRect(point) ? TYPE_SELECTED : TYPE_NORMAL;
	}

};

/***
// Stock Logical Objects
#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define NULL_BRUSH          5
#define HOLLOW_BRUSH        NULL_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define OEM_FIXED_FONT      10
#define ANSI_FIXED_FONT     11
#define ANSI_VAR_FONT       12
#define SYSTEM_FONT         13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE     15
#define SYSTEM_FIXED_FONT   16

***/
