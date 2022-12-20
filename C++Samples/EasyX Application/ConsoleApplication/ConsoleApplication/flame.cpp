///////////////////////////////////////////////////
// �������ƣ�����ģ�����
// ���뻷����VC6.0 / VC2010��EasyX 2011���ݰ�
// �������ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2012-1-21
// PS: �����㷨�ο���΢�������ڴ˸�л��
//
#include <graphics.h>
#include <conio.h>
#include <time.h>

// �곣��
#define WIDTH       640
#define HEIGHT      480
#define FIREWIDTH   320
#define FIREHEIGHT  180

// ȫ�ֱ���
COLORREF    g_Colors[193];                      // ����ɫϵ��ʹ�õ�ȫ����ɫ
BYTE        g_Fire[FIREWIDTH];                  // ��������
BYTE        g_Bits[FIREHEIGHT * FIREWIDTH];     // ��������

												// ��������
int m_nDecay = 5;           // ˥���ȣ���Χ [1, 100]��Ĭ�� 5
int m_nFlammability = 385;  // ��ȼ�ԣ���Χ [1, 399]��Ĭ�� 385
int m_nMaxHeat = 192;       // ����ȶȣ���Χ [0, 192]��Ĭ�� 192
int m_nSpreadRate = 20;     // �������ʣ���Χ [1, 100]��Ĭ�� 20
int m_nSize = 160;          // ��Դ��ȣ���Χ [40, FIREWIDTH]��Ĭ�� 160
int m_nSmoothness = 1;      // ƽ���ȣ���Χ [0, 5]��Ĭ�� 1
int m_nDistribution = 1;    // �ֲ�����Χ [0, 10]��Ĭ�� 1
int m_nChaos = 50;          // ���磬��Χ [1, 100]��Ĭ�� 50



							// ��ʼ������
void InitFire()
{
	// ��ʼ����ɫ
	int r, g, b;

	// Ĭ�Ϻ�ɫ���档����ע��ѡ��ͬ�Ļ���Ч��
	b = 256 + 256 + 255;    g = 256 + 255;    r = 255;    // ��ɫ����
														  // r = 256+256+255; g = 256+255;    b = 255;    // ��ɫ����
														  // g = 256+256+255; b = 256+255;    r = 255;    // ��ɫ����

														  // ���ɻ���ɫϵ
	for (int i = 192; i >= 0; i--)
	{
		g_Colors[i] = RGB((r > 255) ? 255 : r, (g > 255) ? 255 : g, (b > 255) ? 255 : b);
		r = (r > 3) ? (r - 4) : 0;
		g = (g > 3) ? (g - 4) : 0;
		b = (b > 3) ? (b - 4) : 0;
	}

	// �ÿջ�������
	memset(g_Fire, 0, FIREWIDTH);
	memset(g_Bits, 0, FIREWIDTH * FIREHEIGHT);
}



// ��ɫϵ
void DrawColorScheme()
{
	POINT s[8] = { { 0, 450 },{ 580, 450 },{ 580, 420 },{ 610, 420 },
	{ 610, 0 },{ 639, 0 },{ 639, 479 },{ 0, 479 } };

	HRGN rgn1 = CreatePolygonRgn(s, 8, WINDING);
	HRGN rgn2 = CreateEllipticRgn(550, 390, 611, 451);
	CombineRgn(rgn1, rgn1, rgn2, RGN_DIFF);

	// ����ü�����
	setcliprgn(rgn1);           // �������� rgn Ϊ�ü���
	DeleteObject(rgn1);
	DeleteObject(rgn2);

	// ��ɫϵ
	int c, x, y;
	for (int i = 0; i < 1120; i++)
	{
		c = int(i / 5.8);
		x = (i <= 479 ? 639 : 639 - i + 479);
		y = (i <= 479 ? i : 479);
		setcolor(BGR(g_Colors[c]));
		line(0, 0, x, y);
	}

	// ȡ���ü�����
	setcliprgn(NULL);
}



// ��������ÿ����
inline void BurnPoint(BYTE* pRow, BYTE* pNextRow)
{
	BYTE* pTarget;

	int off = rand() % (m_nDistribution + 1);

	int val = m_nDecay + 1;
	val = rand() % val;
	val = *pNextRow - val;

	pTarget = (rand() & 1) ? pRow + off : pRow - off;
	*pTarget = (val > 0) ? (BYTE)val : 0;
}



// �������
void RenderFlame()
{
	int xStart, xEnd, x, y;
	BYTE* pRow;
	BYTE* pNextRow;

	xStart = (FIREWIDTH - m_nSize) / 2;
	xEnd = xStart + m_nSize + 1;

	pRow = g_Bits;
	for (x = 0; x < FIREWIDTH; x++)
	{
		if (x < (xStart + m_nDistribution) || x >= (xEnd - m_nDistribution))
			g_Fire[x] = 0;
		*pRow++ = g_Fire[x];
	}

	for (y = FIREHEIGHT - 1; y > 0; y--) // y = 0 �������y++ �����С
	{
		pRow = (g_Bits + FIREWIDTH * y);
		pNextRow = (g_Bits + FIREWIDTH * (y - 1));

		if (rand() & 1)
		{
			for (x = 0; x < FIREWIDTH; x++)
			{
				BurnPoint(pRow, pNextRow);
				pRow++;
				pNextRow++;
			}
		}
		else
		{
			pRow += FIREWIDTH - 1;
			pNextRow += FIREWIDTH - 1;
			for (x = 0; x < FIREWIDTH; x++)
			{
				BurnPoint(pRow, pNextRow);
				pRow--;
				pNextRow--;
			}
		}
	}

	if (rand() % (400 - m_nFlammability) == 0)
	{
		int off = m_nSize - 5;
		off = rand() % off;
		off += xStart;

		for (x = off; x < off + 5; x++)
			g_Fire[x] = 239;
	}

	for (x = xStart; x < xEnd; x++)
	{
		if (g_Fire[x] < m_nMaxHeat)
		{
			int val = rand() % m_nChaos + 1;
			val -= m_nChaos / 2;
			val += m_nSpreadRate;
			val += g_Fire[x];

			if (val > m_nMaxHeat)
				g_Fire[x] = m_nMaxHeat;
			else if (val < 0)
				g_Fire[x] = 0;
			else
				g_Fire[x] = val;
		}
		else
			g_Fire[x] = m_nMaxHeat;
	}

	if (m_nSmoothness > 0)
	{
		xStart += m_nSmoothness;
		xEnd -= m_nSmoothness;
		for (x = xStart; x < xEnd; x++)
		{
			int val = 0;
			for (y = x - m_nSmoothness; y < x + 1 + m_nSmoothness; y++)
				val += g_Fire[y];

			g_Fire[x] = val / (2 * m_nSmoothness + 1);
		}
	}
}



// ��ʾ����
void PaintFlame(int offset_x, int offset_y)
{
	DWORD* pDst = GetImageBuffer(); // ��ȡ�Դ�ָ��

	for (int y = 0; y < FIREHEIGHT; y++)
		for (int x = 0; x < FIREWIDTH; x++)
		{
			COLORREF c = g_Colors[g_Bits[y * FIREWIDTH + x]];
			pDst[(offset_y - y) * WIDTH + offset_x + x] = c;
		}

	FlushBatchDraw();               // ʹ�Դ������Ч
}



// ������
void main()
{
	initgraph(WIDTH, HEIGHT);       // ������ͼ����
	srand((unsigned)time(NULL));    // �����������

	InitFire();                     // ��ʼ������
	DrawColorScheme();              // ����ɫϵͼ

	while (!kbhit())                 // ��������˳�
	{
		RenderFlame();              // ��Ⱦ����
		PaintFlame(145, 320);       // ��ʾ����
		Sleep(33);                  // ��ʱ
	}

	closegraph();
}