#pragma once
#include "CLayer.h"

// »­Ô²
class CEllipse :
	public CLayer
{
public:
	CRect m_rect;

public:
	CEllipse() : m_rect(MAXLONG, MAXLONG, MAXLONG, MAXLONG) { }
	CEllipse(const CRect& rect) : m_rect(rect) { }

	virtual ~CEllipse() { }

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
			pDC->SelectStockObject(NULL_BRUSH);

			pDC->SetROP2(R2_NOT);
			if (m_rect.right != MAXLONG)
				pDC->Ellipse(m_rect);
			m_rect.BottomRight() = point;
			pDC->Ellipse(m_rect);
		}
	}

	void OnDraw(CDC* pDC)
	{
		CPen pen(PS_SOLID, 1, m_clFront);
		CPen* pOldPen = pDC->SelectObject(&pen);

		pDC->Ellipse(m_rect);

		pDC->SelectObject(pOldPen);
	}
	void SelectLayer(UINT nFlags, CPoint point)
	{

	}

};


