/////////////////////////////////////////////////////////////////////////////////////
// 窗口技巧：利用窗体句柄实现圆形窗口
//
#include <graphics.h>
#include <iostream>
using namespace std;

void main()
{
	initgraph(400, 400);			// 初始化图形窗口
	HWND hWnd = GetHWnd();		// 获取窗口句柄

								// 获取窗口边框宽高
	int cx = GetSystemMetrics(SM_CXFIXEDFRAME);										// 3
	int cy = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);	// 3 + 23 = 26

	// 设置圆形区域
	HRGN rgn = CreateEllipticRgn(111 + cx, 111 + cy, 300 + cx, 300 + cy);  //默认窗口最左边（含边框和标题栏）为原点

//	HRGN rgn = CreateEllipticRgn(100, 100, 300, 300);

	SetWindowRgn(hWnd, rgn, true);

	// 画彩虹球
	setlinestyle(PS_SOLID, 2, NULL);
	for (int r = 100; r>0; r--)
	{
		setcolor(HSLtoRGB(360 - r*3.6, 1, 0.5));
		circle(200, 200, r);  //图形绘制以客户区（不含边框和标题栏）左上角为原点
	}

	MOUSEMSG m;						// 定义鼠标消息

	while (true)
	{
		m = GetMouseMsg();			// 获取一条鼠标消息

		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			// 如果左键按下，欺骗 windows 点在了标题栏上
			//WM_LBUTTONDOWN是在“客户区”按下鼠标的消息，WM_NCLBUTTONDOWN是在“非客户区”按下鼠标的消息，
			//非客户区：包括“标题栏”，“窗口边框”，“滚动条”等。
			PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(m.x, m.y));
			break;

		case WM_RBUTTONUP:			// 按鼠标右键退出程序
			closegraph();
			cout << "cx = " << cx << endl;
			cout << "cy = " << cy << endl;
			exit(0);
		}
	}
}