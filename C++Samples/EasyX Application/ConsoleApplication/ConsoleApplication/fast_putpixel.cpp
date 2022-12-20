/////////////////////////////////////////////////
// 快速画点
//
// 总的思想：通过直接显存操作来避免系统做不需要的运算。
// 算法设计：在 EasyX 绘图窗口的显存中，每个点占用 4 个字节，
//		用 DWORD 指针指向显存就可以像一维数组一样访问了。
//		然后就是将二维坐标 (x, y) 映射到一维数组中，很简单，y * 640 + x 就是。
// 注意：颜色 COLORREF 在内存中的表示形式为：0xbbggrr (bb=蓝，gg=绿，rr=红)，
//		但是显存中的颜色 RGBTRIPLE 在内存中的表现形式为 0xrrggbb。两者的红色和蓝色是相反的。
//		直接操作显存时，可以通过 BGR 宏交换颜色的红色和蓝色部分。
//
#include <graphics.h>
#include <conio.h>

#define	WIDTH	640
#define	HEIGHT	480

// 显存指针
DWORD* g_pBuf;

// 快速画点函数
void fast_putpixel(int x, int y, COLORREF c)
{
	g_pBuf[y * WIDTH + x] = BGR(c);
}

// 快速读点函数
COLORREF fast_getpixel(int x, int y)
{
	COLORREF c = g_pBuf[y * WIDTH + x];
	return BGR(c);
}

// 主函数
void main()
{
	// 初始化绘图窗口
	initgraph(WIDTH, HEIGHT);

	// 获取绘图窗口的显存指针并保存为全局变量
	g_pBuf = GetImageBuffer();

	// 随机画 100 个点
	for (int i = 0; i< 100; i++)
		fast_putpixel(rand() % WIDTH, rand() % HEIGHT, RED);

	// 使针对绘图窗口的显存操作生效（注：操作指向 IMAGE 的显存时不需要这条语句）
	FlushBatchDraw();

	// 扫描每一个点，如果是红色，就以该点为圆心画一个圆：
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
			if (fast_getpixel(x, y) == RED)
				circle(x, y, 10);

	// 按任意键退出
	getch();
	closegraph();
}

/*****************************************************************************************
IMAGE img;
loadimage(&img, _T("test.jpg"));	// 请确保该图片是 640x480 像素

// 获取绘图窗口和 img 对象的显存指针
DWORD* pbWnd = GetImageBuffer();
DWORD* pbImg = GetImageBuffer(&img);
******************************************************************************************/