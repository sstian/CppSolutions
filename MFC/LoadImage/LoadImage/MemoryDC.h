// 2019.03.10
// 自定义图像内存加载类的封装：支持从内部资源/外部加载，支持bmp/jpg/gif/png图像文件，文件显示/收缩透明位图
// 使用时，将此头文件在"stdafx.h"中添加 #include "MemoryDC.h"
#include "stdafx.h"
#include <functional>

#pragma once

class CMemoryDC : public CDC
{
public:
	// 构造 与 析构
	CMemoryDC():m_size(0, 0)
	{

	}
	CMemoryDC(UINT nBitmapID, CDC* pDC = nullptr) :m_size(0, 0)
	{
		this->LoadBitmap(nBitmapID, pDC);
	}
	CMemoryDC(LPCTSTR szBitmap, CDC* pDC = nullptr) :m_size(0, 0)
	{
		this->LoadBitmap(szBitmap, pDC);
	}
	CMemoryDC(int cx, int cy, CDC* pDC = nullptr) :m_size(0, 0)
	{
		this->Create(cx, cy, pDC);
	}
	virtual ~CMemoryDC()
	{
		this->DeleteObject();
	}

	//创建一张空白内存画布
	BOOL Create(int cx, int cy, CDC* pDC = nullptr)
	{
		BOOL result;
		CBitmap bitmap;
		if (pDC)
			result = bitmap.CreateCompatibleBitmap(pDC, cx, cy);
		else
			result = bitmap.CreateCompatibleBitmap(&CClientDC(NULL), cx, cy);

		//std::function<BOOL(CDC*, int, int)> fcompatile = bitmap.CreateCompatibleBitmap;
		m_size.SetSize(cx, cy);
		this->CreateCompatibleDC(pDC);
		this->SelectObject(bitmap);
		return result;
	}
	// 释放
	BOOL DeleteObject()
	{
		if (!GetSafeHdc())
			return FALSE;
		CBitmap* pBitmap = GetCurrentBitmap();
		if (pBitmap)
			pBitmap->DeleteObject();
		return CDC::DeleteDC();
	}

	// 从内部资源加载位图 bmp
	BOOL LoadBitmap(UINT nBitmapID, CDC* pDC = nullptr)
	{
		CBitmap bitmap;
		if (!bitmap.LoadBitmap(nBitmapID))			//加载图像，只能通过资源ID
			return FALSE;

		BITMAP bmp;
		bitmap.GetBitmap(&bmp);						//获取图像参数
		m_size.SetSize(bmp.bmWidth, bmp.bmHeight);	//保存图像尺寸
		this->CreateCompatibleDC(pDC);				//创建兼容设备
		this->SelectObject(bitmap);					//选择图像
		
		bitmap.DeleteObject();
		return TRUE;
	}
	// 从外部文件加载 bmp / jpg / gif
	BOOL LoadBitmap(LPCTSTR szBitmap, CDC* pDC = nullptr)
	{
		HBITMAP hBitmap = (HBITMAP)::LoadImage(nullptr, szBitmap, IMAGE_BITMAP, 0, 0, 
			LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (!hBitmap)
			return FALSE;

		BITMAP bmp;
		::GetObject(hBitmap, sizeof(bmp), &bmp);
		m_size.SetSize(bmp.bmWidth, bmp.bmHeight);
		this->CreateCompatibleDC(pDC);
		this->SelectObject(hBitmap);

		::DeleteObject(hBitmap);
		return TRUE;
	}
	// 从外部文件加载 jpg / gif / png -> bmp
	// 要在OnInitDialog()中进行资源加载！
	HRESULT Load(LPCTSTR pszFileName, CDC* pDC = nullptr)
	{
		CImage image;
		HRESULT result = image.Load(pszFileName);
		CBitmap* pBitmap = CBitmap::FromHandle(image.Detach());

		BITMAP bmp;
		pBitmap->GetBitmap(&bmp);
		m_size.SetSize(bmp.bmWidth, bmp.bmHeight);
		this->CreateCompatibleDC(pDC);
		this->SelectObject(pBitmap);

		image.Destroy();
		pBitmap->DeleteObject();

		return result;
	}

	// 图像透明化. pDC: 目标DC，贴图至此处.
	// CPaintDC dc(this); dc.CDC::BitBlt(int x, int y, int nWidth, int nHeight, CDC* pSrcDC,int xSrc, int ySrc, DWORD dwRop);
	// 则将pSrcDC贴图至dc上.
	void BitTrans(
		int nXDest,		// 目标起点X
		int nYDest,		// 目标起点Y
		int nWidthDest,	// 目标宽度
		int nHeightDest,// 目标高度
		CDC* pDC,		// 目标DC
		int nXSrc,		// 来源起点X
		int nYSrc,		// 来源起点Y
		COLORREF crTrans// 透明色
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);				//临时DC
		CBitmap bmpMask;
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);		// 创建单色掩码位图
		CDC dcMask;														//掩码DC 
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);
		//将载入位图的内存DC中的位图，拷贝到临时DC中
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);

		// 设置临时DC的透明色
		dcImage.SetBkColor(crTrans);
		//掩码DC的透明区域为白色其它区域为黑色
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//临时DC透明区域为黑色，其它区域保持不变
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		// 目标DC透明部分保持屏幕不变，其它部分变成黑色
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
	}
	// 图像收缩透明化. pDC: 目标DC，贴图至此处.
	// CPaintDC dc(this); dc.CDC::StretchBlt(int x, int y, int nWidth, int nHeight, CDC* pSrcDC,int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop);
	// 则将pSrcDC贴图至dc上.
	void StretchTrans(
		int nXDest,			// 目标起点X
		int nYDest,			// 目标起点Y
		int nWidthDest,     // 目标宽度
		int nHeightDest,    // 目标高度
		CDC* pDC,			// 目标DC
		int nXSrc,			// 来源起点X
		int nYSrc,			// 来源起点Y
		int nWidthSrc,		// 来源宽度
		int nHeightSrc,		// 来源高度
		COLORREF crTrans	// 透明色
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//临时DC
		CBitmap bmpMask;
		// 创建单色掩码位图
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);
		CDC dcMask;
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);

		// 将载入位图的内存DC中的位图，拷贝到临时DC中
		if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
			dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);
		else
			dcImage.StretchBlt(0, 0, nWidthDest, nHeightDest,
				this, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

		// 设置临时DC的透明色
		dcImage.SetBkColor(crTrans);
		//掩码DC的透明区域为白色其它区域为黑色
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//临时DC透明区域为黑色，其它区域保持不变
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		// 目标DC透明部分保持屏幕不变，其它部分变成黑色
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
	}

	int GetWidth() const { return m_size.cx; }
	int GetHeight() const { return m_size.cy; }

private:
	CSize m_size;	//图像大小
};

/***
//pDC: 若该句柄为NULL，该函数创建一个与应用程序的当前显示器兼容的内存设备上下文环境
BOOL CDC::CreateCompatibleDC(CDC* pDC);

//加载 icon / cursor / bitmap，从内部资源或外部文件均可
//e.g. (LPCTSTR)IDB_BITMAP / MAKEINTRESOURCE(IDB_BITMAP) or _T("./res/image_bmp.bmp")
HANDLE WINAPI LoadImageW(
	_In_opt_ HINSTANCE hInst,
	_In_ LPCWSTR name,
	_In_ UINT type,
	_In_ int cx,
	_In_ int cy,
	_In_ UINT fuLoad);

#define IMAGE_BITMAP        0
#define IMAGE_ICON          1
#define IMAGE_CURSOR        2

#define LR_DEFAULTCOLOR     0x00000000
#define LR_MONOCHROME       0x00000001
#define LR_COLOR            0x00000002
#define LR_COPYRETURNORG    0x00000004
#define LR_COPYDELETEORG    0x00000008
#define LR_LOADFROMFILE     0x00000010
#define LR_LOADTRANSPARENT  0x00000020
#define LR_DEFAULTSIZE      0x00000040
#define LR_VGACOLOR         0x00000080
#define LR_LOADMAP3DCOLORS  0x00001000
#define LR_CREATEDIBSECTION 0x00002000
#define LR_COPYFROMRESOURCE 0x00004000
#define LR_SHARED           0x00008000

***/