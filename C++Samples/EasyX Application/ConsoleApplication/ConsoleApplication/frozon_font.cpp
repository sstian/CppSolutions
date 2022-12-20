////////////////////////////////////////////
// �������ƣ�������ϵ�У������ EasyX
// ���뻷����Visual C++ 6.0 / 2010��EasyX 2011���ݰ�
// �����д��yangw80 <yw80@qq.com>
// �����£�2011-6-20
//
#include <graphics.h>
#include <conio.h>
#include <time.h>


// ����ȫ�ֱ���
POINT *g_pDst;      // �㼯(Ŀ��)
POINT *g_pSrc;      // �㼯(Դ)
int g_nWidth;       // ���ֵĿ��
int g_nHeight;      // ���ֵĸ߶�
int g_nCount;       // �㼯�����ĵ������


					// ��ȡĿ��㼯
void GetDstPoints()
{
	// ������ʱ��ͼ����
	IMAGE img;
	SetWorkingImage(&img);

	// ����Ŀ���ַ���
	TCHAR s[] = _T("EasyX");

	// ����Ŀ���ַ����Ŀ�ߣ���������ʱ��ͼ����ĳߴ�
	setcolor(WHITE);
	setfont(100, 0, _T("Arial"));
	g_nWidth = textwidth(s);
	g_nHeight = textheight(s);
	Resize(&img, g_nWidth, g_nHeight);

	// ���Ŀ���ַ����� img ����
	outtextxy(0, 0, s);

	// ���㹹��Ŀ���ַ����ĵ������
	int x, y;
	g_nCount = 0;
	for (x = 0; x < g_nWidth; x++)
		for (y = 0; y < g_nHeight; y++)
			if (getpixel(x, y) == WHITE)
				g_nCount++;

	// ����Ŀ������
	g_pDst = new POINT[g_nCount];
	int i = 0;
	for (x = 0; x < g_nWidth; x++)
		for (y = 0; y < g_nHeight; y++)
			if (getpixel(x, y) == WHITE)
			{
				g_pDst[i].x = x + (640 - g_nWidth) / 2;
				g_pDst[i].y = y + (480 - g_nHeight) / 2;
				i++;
			}

	// �ָ�����Ļ�Ļ�ͼ����
	SetWorkingImage(NULL);
}


// ��ȡԴ�㼯
void GetSrcPoints()
{
	// �����������
	srand((unsigned int)time(NULL));

	// ���������Դ����
	g_pSrc = new POINT[g_nCount];
	for (int i = 0; i < g_nCount; i++)
	{
		g_pSrc[i].x = rand() % 640;
		g_pSrc[i].y = rand() % 480;
	}
}


// ȫ��ģ������(������Ļ��һ�к����һ��)
void Blur(DWORD* pMem)
{
	for (int i = 640; i < 640 * 479; i++)
	{
		pMem[i] = RGB(
			(GetRValue(pMem[i]) + GetRValue(pMem[i - 640]) + GetRValue(pMem[i - 1]) + GetRValue(pMem[i + 1]) + GetRValue(pMem[i + 640])) / 5,
			(GetGValue(pMem[i]) + GetGValue(pMem[i - 640]) + GetGValue(pMem[i - 1]) + GetGValue(pMem[i + 1]) + GetGValue(pMem[i + 640])) / 5,
			(GetBValue(pMem[i]) + GetBValue(pMem[i - 640]) + GetBValue(pMem[i - 1]) + GetBValue(pMem[i + 1]) + GetBValue(pMem[i + 640])) / 5);
	}
}


// ������
void main()
{
	// ��ʼ��
	initgraph(640, 480);                // ������ͼ���ڿ�
	DWORD* pBuf = GetImageBuffer();     // ��ȡ�Դ�ָ��
	GetDstPoints();                     // ��ȡĿ��㼯
	GetSrcPoints();                     // ��ȡԴ�㼯

										// ����
	int x, y;
	for (int i = 2; i <= 256; i += 2)
	{
		COLORREF c = RGB(i - 1, i - 1, i - 1);
		Blur(pBuf);                     // ȫ��ģ������

		for (int d = 0; d < g_nCount; d++)
		{
			x = g_pSrc[d].x + (g_pDst[d].x - g_pSrc[d].x) * i / 256;
			y = g_pSrc[d].y + (g_pDst[d].y - g_pSrc[d].y) * i / 256;
			pBuf[y * 640 + x] = c;      // ֱ�Ӳ����Դ滭��
		}

		FlushBatchDraw();               // ʹ�Դ������Ч
		Sleep(20);                      // ��ʱ
	}

	// �����ڴ�
	delete g_pDst;
	delete g_pSrc;

	// ��������˳�
	getch();
	closegraph();
}