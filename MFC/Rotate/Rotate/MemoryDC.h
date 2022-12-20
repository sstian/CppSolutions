// 2019.03.10
// �Զ���ͼ���ڴ������ķ�װ��֧�ִ��ڲ���Դ/�ⲿ���أ�֧��bmp/jpg/gif/pngͼ���ļ����ļ���ʾ/����͸��λͼ
// ʹ��ʱ������ͷ�ļ���"stdafx.h"����� #include "MemoryDC.h"
#include "stdafx.h"
#include <functional>

#pragma once

class CMemoryDC : public CDC
{
public:
	// ���� �� ����
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

	//����һ�ſհ��ڴ滭��
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
	// �ͷ�
	BOOL DeleteObject()
	{
		if (!GetSafeHdc())
			return FALSE;
		CBitmap* pBitmap = GetCurrentBitmap();
		if (pBitmap)
			pBitmap->DeleteObject();
		return CDC::DeleteDC();
	}

	// ���ڲ���Դ����λͼ bmp
	BOOL LoadBitmap(UINT nBitmapID, CDC* pDC = nullptr)
	{
		CBitmap bitmap;
		if (!bitmap.LoadBitmap(nBitmapID))			//����ͼ��ֻ��ͨ����ԴID
			return FALSE;

		BITMAP bmp;
		bitmap.GetBitmap(&bmp);						//��ȡͼ�����
		m_size.SetSize(bmp.bmWidth, bmp.bmHeight);	//����ͼ��ߴ�
		this->CreateCompatibleDC(pDC);				//���������豸
		this->SelectObject(bitmap);					//ѡ��ͼ��
		
		bitmap.DeleteObject();
		return TRUE;
	}
	// ���ⲿ�ļ����� bmp / jpg / gif
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
	// ���ⲿ�ļ����� jpg / gif / png -> bmp
	// Ҫ��OnInitDialog()�н�����Դ���أ�
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

	// ͼ��͸����. pDC: Ŀ��DC����ͼ���˴�.
	// CPaintDC dc(this); dc.CDC::BitBlt(int x, int y, int nWidth, int nHeight, CDC* pSrcDC,int xSrc, int ySrc, DWORD dwRop);
	// ��pSrcDC��ͼ��dc��.
	void BitTrans(
		int nXDest,		// Ŀ�����X
		int nYDest,		// Ŀ�����Y
		int nWidthDest,	// Ŀ����
		int nHeightDest,// Ŀ��߶�
		CDC* pDC,		// Ŀ��DC
		int nXSrc,		// ��Դ���X
		int nYSrc,		// ��Դ���Y
		COLORREF crTrans// ͸��ɫ
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);				//��ʱDC
		CBitmap bmpMask;
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);		// ������ɫ����λͼ
		CDC dcMask;														//����DC 
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);
		//������λͼ���ڴ�DC�е�λͼ����������ʱDC��
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);

		// ������ʱDC��͸��ɫ
		dcImage.SetBkColor(crTrans);
		//����DC��͸������Ϊ��ɫ��������Ϊ��ɫ
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//��ʱDC͸������Ϊ��ɫ���������򱣳ֲ���
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		// Ŀ��DC͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
	}
	// ͼ������͸����. pDC: Ŀ��DC����ͼ���˴�.
	// CPaintDC dc(this); dc.CDC::StretchBlt(int x, int y, int nWidth, int nHeight, CDC* pSrcDC,int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop);
	// ��pSrcDC��ͼ��dc��.
	void StretchTrans(
		int nXDest,			// Ŀ�����X
		int nYDest,			// Ŀ�����Y
		int nWidthDest,     // Ŀ����
		int nHeightDest,    // Ŀ��߶�
		CDC* pDC,			// Ŀ��DC
		int nXSrc,			// ��Դ���X
		int nYSrc,			// ��Դ���Y
		int nWidthSrc,		// ��Դ���
		int nHeightSrc,		// ��Դ�߶�
		COLORREF crTrans	// ͸��ɫ
	)
	{
		CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//��ʱDC
		CBitmap bmpMask;
		// ������ɫ����λͼ
		bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);
		CDC dcMask;
		dcMask.CreateCompatibleDC(pDC);
		dcMask.SelectObject(bmpMask);

		// ������λͼ���ڴ�DC�е�λͼ����������ʱDC��
		if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
			dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);
		else
			dcImage.StretchBlt(0, 0, nWidthDest, nHeightDest,
				this, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

		// ������ʱDC��͸��ɫ
		dcImage.SetBkColor(crTrans);
		//����DC��͸������Ϊ��ɫ��������Ϊ��ɫ
		dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

		//��ʱDC͸������Ϊ��ɫ���������򱣳ֲ���
		dcImage.SetBkColor(RGB(0, 0, 0));
		dcImage.SetTextColor(RGB(255, 255, 255));
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

		// Ŀ��DC͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
		pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
	}

	int GetWidth() const { return m_size.cx; }
	int GetHeight() const { return m_size.cy; }

private:
	CSize m_size;	//ͼ���С
};

/***
//pDC: ���þ��ΪNULL���ú�������һ����Ӧ�ó���ĵ�ǰ��ʾ�����ݵ��ڴ��豸�����Ļ���
BOOL CDC::CreateCompatibleDC(CDC* pDC);

//���� icon / cursor / bitmap�����ڲ���Դ���ⲿ�ļ�����
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