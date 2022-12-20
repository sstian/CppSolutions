#pragma once
#include "CLayer.h"

// 画线
class CLine :
	public CLayer
{
public:
	CPoint m_startPos;	//起始点
	CPoint m_endPos;	//终止点

public:
	CLine() : m_startPos(MAXLONG, MAXLONG), m_endPos(MAXLONG, MAXLONG) { }
	CLine(const CPoint& startPos, const CPoint& endPos) 
		: m_startPos(startPos), m_endPos(endPos)
	{ }

	virtual ~CLine() { }

	void OnLButtonDown(UINT nFlags, CPoint point)
	{
		m_startPos = point;
	}
	void OnLButtonUp(UINT nFlags, CPoint point)
	{
		m_endPos = point;
	}
	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC)
	{
		if (nFlags & MK_LBUTTON)
		{
			pDC->SetROP2(R2_NOT);
			if (m_endPos.x != MAXLONG)
			{
				pDC->MoveTo(m_startPos);
				pDC->LineTo(m_endPos);
			}

			m_endPos = point;
			pDC->MoveTo(m_startPos);
			pDC->LineTo(m_endPos);
		}
	}

	void OnDraw(CDC* pDC)
	{
		CPen pen(PS_SOLID, 1, m_clFront);
		CPen* pOldPen = pDC->SelectObject(&pen);

		pDC->MoveTo(m_startPos);
		pDC->LineTo(m_endPos);

		pDC->SelectObject(pOldPen);

		if (TYPE_SELECTED == m_type)
		{
			pDC->FillSolidRect(m_startPos.x - 3, m_startPos.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
			pDC->FillSolidRect(m_endPos.x - 3, m_endPos.y - 3, 6, 6, GetSysColor(COLOR_HIGHLIGHT));
		}
	}
	void SelectLayer(UINT nFlags, CPoint point)
	{
		CRect rect(m_startPos, m_endPos);
		rect.NormalizeRect();
		m_type = rect.PtInRect(point) ? TYPE_SELECTED : TYPE_NORMAL;
	}

	// 计算点到直线的距离
	int GetDistance(CPoint point)
	{
		
		int x1 = m_startPos.x;
		int y1 = m_startPos.y;
		int x2 = m_endPos.x;
		int y2 = m_endPos.y;
		int x0 = point.x;
		int y0 = point.y;

		//// 方法1
		//int m = abs((y2 - y2) * x0 + (x1 - x2) * y0 + (x2 * y1 - x1 * y2));
		//int n = (int)sqrt((y2 - y1) * (y2 - y1) + (x1 - x2) * (x1 - x2));
		//return (m / n);

		// 方法2. 海伦公式
		double a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		double b = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
		double c = sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));
		double p = (a + b + c) / 2;
		double s = sqrt(p * (p - a) * (p - b) * (p - c));
		return (int)(2 * s / a);
	}
};

/***
// Binary raster ops
#define R2_BLACK            1   //  0      
#define R2_NOTMERGEPEN      2	// DPon     
#define R2_MASKNOTPEN       3   // DPna     
#define R2_NOTCOPYPEN       4   // PN
#define R2_MASKPENNOT       5   // PDna
#define R2_NOT              6   // Dn 
#define R2_XORPEN           7   // DPx
#define R2_NOTMASKPEN       8   // DPan  
#define R2_MASKPEN          9   // DPa
#define R2_NOTXORPEN        10  // DPxn 
#define R2_NOP              11  // D   
#define R2_MERGENOTPEN      12  // DPno 
#define R2_COPYPEN          13  // P  
#define R2_MERGEPENNOT      14  // PDno  
#define R2_MERGEPEN         15  // DPo   
#define R2_WHITE            16  // 1
#define R2_LAST             16

#define MINCHAR     0x80
#define MAXCHAR     0x7f
#define MINSHORT    0x8000
#define MAXSHORT    0x7fff
#define MINLONG     0x80000000
#define MAXLONG     0x7fffffff
#define MAXBYTE     0xff
#define MAXWORD     0xffff
#define MAXDWORD    0xffffffff

***/
