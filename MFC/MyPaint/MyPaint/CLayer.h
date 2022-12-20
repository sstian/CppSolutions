// ͼ�����
// �������
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
	EType m_type;			//ͼ�����״̬

	COLORREF m_clFront;		//ǰ��ɫ
	COLORREF m_clBack;		//����ɫ
public:
	CLayer() : m_type(TYPE_DRAWING) { }
	virtual ~CLayer() { }

	// ���麯������������
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
	virtual	void OnMouseMove(UINT nFlags, CPoint point, CDC* pDC) = 0;

	// ���麯��������
	virtual void OnDraw(CDC* pDC) = 0;
	// ���麯����ѡ��ͼ��
	virtual void SelectLayer(UINT nFlags, CPoint point) = 0;
};



