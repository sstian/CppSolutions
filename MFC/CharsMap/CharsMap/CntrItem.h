
// CntrItem.h: CCharsMapCntrItem 类的接口
//

#pragma once

class CCharsMapDoc;
class CCharsMapView;

class CCharsMapCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CCharsMapCntrItem)

// 构造函数
public:
	CCharsMapCntrItem(REOBJECT* preo = nullptr, CCharsMapDoc* pContainer = nullptr);
		// 注意: 允许 pContainer 为 NULL 以启用 IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE 要求类具有带零
		//  参数的构造函数。  OLE 项通常是用
		//  非 null 文档指针

// 特性
public:
	CCharsMapDoc* GetDocument()
		{ return reinterpret_cast<CCharsMapDoc*>(CRichEditCntrItem::GetDocument()); }
	CCharsMapView* GetActiveView()
		{ return reinterpret_cast<CCharsMapView*>(CRichEditCntrItem::GetActiveView()); }

// 实现
public:
	~CCharsMapCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

