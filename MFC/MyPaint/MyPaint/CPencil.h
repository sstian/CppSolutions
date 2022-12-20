#pragma once
#include "CLayer.h"
class CPencil :
	public CLayer
{
public:
	CArray<CPoint> m_points;

public:
	CPencil() { }
	virtual ~CPencil() { }

	void OnLButtonDown(UINT nFlags, CPoint point) 
	{
		m_points.Add(point);
	}
	void OnLButtonUp(UINT nFlags, CPoint point)
	{
		m_points.Add(point);
	}
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
	{
		if (nFlags & MK_LBUTTON)
		{
			int size = (int)m_points.GetSize();
			if (size <= 0)
				return;
			// 算法改进，舍弃距离太近的点，减小资源开销
			CPoint pt = m_points.GetAt(size - 1);
			int cx = point.x - pt.x;
			int cy = point.y - pt.y;
			if (sqrt(cx * cx + cy * cy) < 5)
			{
				TRACE("point.x = %d, point.y = ", point.x, point.y);
				return;
			}

			m_points.Add(point);

			pDC->MoveTo(pt);
			pDC->LineTo(point);
		}
	}

	void OnDraw(CDC* pDC)
	{
		int size = (int)m_points.GetSize();
		if (size <= 0)
			return;

		CPen pen(PS_SOLID, 1, m_clFront);
		CPen* pOldPen = pDC->SelectObject(&pen);

		pDC->MoveTo(m_points.GetAt(0));
		for (int i = 0; i < size; i++)
			pDC->LineTo(m_points.GetAt(i));

		pDC->SelectObject(pOldPen);

		if (TYPE_SELECTED == m_type)
		{
			CPoint& ps = m_points[0];
			CPoint& pe = m_points[size - 1];
			pDC->FillSolidRect(ps.x - 3, ps.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
			pDC->FillSolidRect(pe.x - 3, pe.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
		}
	}
	void SelectLayer(UINT nFlags, CPoint point)
	{
		int size = (int)m_points.GetSize();
		if (size <= 0)
			return;
		
		for (int i = 0; i < size; i++)
		{
			CPoint& pt = m_points.GetAt(i);
			int cx = point.x - pt.x;
			int cy = point.y - pt.y;
			if (sqrt(cx * cx + cy * cy) < 8)
			{
				m_type = TYPE_SELECTED;
				return;
			}
		}
		m_type = TYPE_NORMAL;

	}

};


