// 程序名称：彩虹
// 编译环境：Visual C++ 6.0，EasyX 2011惊蛰版
// 最后更新：2010-8-25
//
#include <graphics.h>
#include <conio.h>

void main()
{
	float H, S, L;

	initgraph(640, 480);

	// 画渐变的天空(通过亮度逐渐增加)
	H = 190;    // 色相
	S = 1;      // 饱和度
	L = 0.7f;   // 亮度
	for (int y = 0; y < 480; y++)
	{
		L += 0.0005f;
		setcolor(HSLtoRGB(H, S, L));
		line(0, y, 639, y);
	}

	// 画彩虹(通过色相逐渐增加)
	H = 0;
	S = 1;
	L = 0.5f;
	setlinestyle(PS_SOLID, 2, NULL);   // 设置线宽为 2
	for (int r = 400; r > 344; r--)
	{
		H += 5;
		setcolor(HSLtoRGB(H, S, L));
		circle(500, 480, r);
	}

	getch();
	closegraph();
}