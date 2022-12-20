
// CntrItem.cpp: CCharsMapCntrItem 类的实现
//

#include "stdafx.h"
#include "CharsMap.h"

#include "CharsMapDoc.h"
#include "CharsMapView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCharsMapCntrItem 实现

IMPLEMENT_SERIAL(CCharsMapCntrItem, CRichEditCntrItem, 0)

CCharsMapCntrItem::CCharsMapCntrItem(REOBJECT* preo, CCharsMapDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: 在此添加一次性构造代码
}

CCharsMapCntrItem::~CCharsMapCntrItem()
{
	// TODO: 在此处添加清理代码
}


// CCharsMapCntrItem 诊断

#ifdef _DEBUG
void CCharsMapCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CCharsMapCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

