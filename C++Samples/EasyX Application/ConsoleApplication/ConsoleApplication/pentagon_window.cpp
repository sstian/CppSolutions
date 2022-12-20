/////////////////////////////////////////////////////////////////////////////////////
// 窗口技巧：利用窗体句柄实现五角形窗口
//
#include <graphics.h>

#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159265358979323846

void main()
{
	initgraph(800, 600);			// 初始化图形窗口
	HWND hWnd = GetHWnd();		/*获取窗口句柄*/

								// 获取窗口边框宽高
	int cx = GetSystemMetrics(SM_CXFIXEDFRAME);										// 3
	int cy = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);	// 3 + 23 = 26
/*
	cout << "GetSystemMetrics(SM_CXFIXEDFRAME) = " << GetSystemMetrics(SM_CXFIXEDFRAME) << endl;
	cout << "GetSystemMetrics(SM_CYFIXEDFRAME) = " << GetSystemMetrics(SM_CYFIXEDFRAME) << endl;
	cout << "GetSystemMetrics(SM_CYCAPTION) = " << GetSystemMetrics(SM_CYCAPTION) << endl;
*/	
	int a = 6;	//补偿因数															// 设置圆形区域
//	HRGN rgn = CreateEllipticRgn( 100+ cx+a, 0 + cy+a, 700 + cx+a, 600 + cy+a);  //默认窗口最左边（含边框和标题栏）为原点
																		 //	HRGN rgn = CreateEllipticRgn(100, 100, 300, 300);

	//HRGN rgn = CreateEllipticRgn(100 + cx , 0 + cy, 700 , 600 );  //默认窗口最左边（含边框和标题栏）为原点

	//POINT point[3] = { {100,100},{300,100},{300,300} };
	//HRGN rgn = CreatePolygonRgn(point, 3, ALTERNATE);
	
	POINT points[5] = {
		{ 400 - 300 * cos(18 / 180.0*PI),300 - 300 * sin(18 / 180.0*PI) },	//5
		{ 400 + 300 * cos(18 / 180.0*PI),300 - 300 * sin(18 / 180.0*PI) },	//2
		{ 400 - 300 * sin(36 / 180.0*PI),300 + 300 * cos(36 / 180.0*PI) },	//4
		{ 400,0 },															//1
		{ 400 + 300 * sin(36 / 180.0*PI),300 + 300 * cos(36 / 180.0*PI) }	//3
	};
	polygon(points, 5);	/*多边形坐标*/

	//HRGN rgn = CreatePolygonRgn(points, 5, ALTERNATE);
	HRGN rgn = CreatePolygonRgn(points, 5, WINDING);	/*创建多边形区域*/


	SetWindowRgn(hWnd, rgn, true);	/*设置窗口区域*/
	//setcolor(BLUE);
	setbkcolor(BLUE);
	cleardevice();
/*
	POINT points[3] = { {400,300},{400,0},{ 400 - 150 * sqrt(3),150} };
	polygon(points, 3);
	POINT pts[3] = { {400,300},{400,600},{400 + 150 * sqrt(3),450} };
	polygon(pts, 3);
*/
	pie(100, 0, 700, 600, 90 / 180.0*PI, (90+72*1) /180.0*PI);
	pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72*2) / 180.0*PI);
	pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72*3) / 180.0*PI);
	pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72*4) / 180.0*PI);
/*
	POINT points[5] = {
	{ 400,0 },
	{ 400 + 300 * cos(18 / 180.0*PI),300 - 300 * sin(18 / 180.0*PI) },
	{ 400 + 300 * sin(36 / 180.0*PI),300 + 300 * cos(36 / 180.0*PI) },
	{ 400 - 300 * sin(36 / 180.0*PI),300 + 300 * cos(36 / 180.0*PI) },
	{ 400 - 300 * cos(18 / 180.0*PI),300 - 300 * sin(18 / 180.0*PI) } };
*/
	//90 / 180 * PI
/*	// 画彩虹球
	setlinestyle(PS_SOLID, 2, NULL);
	for (int r = 100; r>0; r--)
	{
		setcolor(HSLtoRGB(360 - r*3.6, 1, 0.5));
		circle(200, 200, r);  //图形绘制以客户区（不含边框和标题栏）左上角为原点
	}
*/
	
	while (true)	/*//必须在无限循环中自定义形状地窗口才能保存*/
	{
		MOUSEMSG m;						// 定义鼠标消息
		m = GetMouseMsg();
		PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(m.x, m.y));	/*发送消息*/

	}
	
	closegraph();
/*
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
*/	
}