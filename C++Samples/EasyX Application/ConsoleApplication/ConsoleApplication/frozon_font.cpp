////////////////////////////////////////////
// 程序名称：艺术字系列：冰封的 EasyX
// 编译环境：Visual C++ 6.0 / 2010，EasyX 2011惊蛰版
// 程序编写：yangw80 <yw80@qq.com>
// 最后更新：2011-6-20
//
#include <graphics.h>
#include <conio.h>
#include <time.h>


// 定义全局变量
POINT *g_pDst;      // 点集(目标)
POINT *g_pSrc;      // 点集(源)
int g_nWidth;       // 文字的宽度
int g_nHeight;      // 文字的高度
int g_nCount;       // 点集包含的点的数量


					// 获取目标点集
void GetDstPoints()
{
	// 设置临时绘图对象
	IMAGE img;
	SetWorkingImage(&img);

	// 定义目标字符串
	TCHAR s[] = _T("EasyX");

	// 计算目标字符串的宽高，并调整临时绘图对象的尺寸
	setcolor(WHITE);
	setfont(100, 0, _T("Arial"));
	g_nWidth = textwidth(s);
	g_nHeight = textheight(s);
	Resize(&img, g_nWidth, g_nHeight);

	// 输出目标字符串至 img 对象
	outtextxy(0, 0, s);

	// 计算构成目标字符串的点的数量
	int x, y;
	g_nCount = 0;
	for (x = 0; x < g_nWidth; x++)
		for (y = 0; y < g_nHeight; y++)
			if (getpixel(x, y) == WHITE)
				g_nCount++;

	// 计算目标数据
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

	// 恢复对屏幕的绘图操作
	SetWorkingImage(NULL);
}


// 获取源点集
void GetSrcPoints()
{
	// 设置随机种子
	srand((unsigned int)time(NULL));

	// 设置随机的源数据
	g_pSrc = new POINT[g_nCount];
	for (int i = 0; i < g_nCount; i++)
	{
		g_pSrc[i].x = rand() % 640;
		g_pSrc[i].y = rand() % 480;
	}
}


// 全屏模糊处理(忽略屏幕第一行和最后一行)
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


// 主函数
void main()
{
	// 初始化
	initgraph(640, 480);                // 创建绘图窗口看
	DWORD* pBuf = GetImageBuffer();     // 获取显存指针
	GetDstPoints();                     // 获取目标点集
	GetSrcPoints();                     // 获取源点集

										// 运算
	int x, y;
	for (int i = 2; i <= 256; i += 2)
	{
		COLORREF c = RGB(i - 1, i - 1, i - 1);
		Blur(pBuf);                     // 全屏模糊处理

		for (int d = 0; d < g_nCount; d++)
		{
			x = g_pSrc[d].x + (g_pDst[d].x - g_pSrc[d].x) * i / 256;
			y = g_pSrc[d].y + (g_pDst[d].y - g_pSrc[d].y) * i / 256;
			pBuf[y * 640 + x] = c;      // 直接操作显存画点
		}

		FlushBatchDraw();               // 使显存操作生效
		Sleep(20);                      // 延时
	}

	// 清理内存
	delete g_pDst;
	delete g_pSrc;

	// 按任意键退出
	getch();
	closegraph();
}