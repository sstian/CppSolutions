///////////////////////////////////////////////////
// 程序名称：漂亮的四叶草
// 编译环境：Visual C++ 6.0，EasyX 2011惊蛰版
// 作　　者：yangw80 <yw80@qq.com>
// 最后修改：2011-10-14
// 注：源程序是网友发在 QQ 群“C 语言革命”里面的 Turbo C 代码，我修改的
//
#include <graphics.h>
#include <math.h>
#include <conio.h>

#define PI 3.1415926535

void main(void)
{
	// 初始化绘图窗口
	initgraph(640, 480);        // 创建绘图窗口
	setcolor(GREEN);            // 设置绘图颜色
	setorigin(320, 240);        // 设置原点坐标

								// 画花朵
	double e;
	int x1, y1, x2, y2;
	for (double a = 0; a < 2 * PI; a += 2 * PI / 720)
	{
		e = 100 * (1 + sin(4 * a));
		x1 = (int)(e * cos(a));
		y1 = (int)(e * sin(a));
		x2 = (int)(e * cos(a + PI / 5));
		y2 = (int)(e * sin(a + PI / 5));

		line(x1, y1, x2, y2);

		Sleep(20);      // 延迟函数，实现慢速绘制的动画效果
	}

	// 按任意键退出
	_getch();
	closegraph();
}