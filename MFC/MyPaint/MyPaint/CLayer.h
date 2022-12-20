// 图层管理
// 抽象基类
#pragma once

#include "stdafx.h"

class CLayer
{
public:
	enum EType
	{
		TYPE_NORMAL,
		TYPE_DRAWING,
		TYPE_SELECTED
	};
	EType m_type;			//图层操作状态

	COLORREF m_clFront;		//前景色
	COLORREF m_clBack;		//背景色
public:
	CLayer() : m_type(TYPE_DRAWING) { }
	virtual ~CLayer() { }

	// 纯虚函数，传递数据
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
	virtual	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC) = 0;

	// 纯虚函数，绘制
	virtual void OnDraw(CDC* pDC) = 0;
	// 纯虚函数，选择图层
	virtual void SelectLayer(UINT nFlags, CPoint point) = 0;
};



