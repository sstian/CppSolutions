// 程序名称：通过 API 获取鼠标状态
// 编译环境：Visual C++ 6.0 / 2008 / 2010，EasyX 2011惊蛰版
//
#include <graphics.h>
#include <stdio.h>

void main()
{
	initgraph(640, 480);		// 初始化绘图窗口
	HWND hwnd = GetHWnd();		// 获取绘图窗口句柄

	POINT point;
	TCHAR s[10];

	while (true)
	{
		GetCursorPos(&point);			// 获取鼠标指针位置（屏幕坐标）
		ScreenToClient(hwnd, &point);	// 将鼠标指针位置转换为窗口坐标

										// 获取鼠标按键状态可以用 GetAsyncKeyState 函数，这里不再详述。

										// 输出鼠标坐标
		swprintf(s, _T("%d    "), point.x);
		outtextxy(0, 0, s);

		swprintf(s, _T("%d    "), point.y);
		outtextxy(0, 20, s);

		// 适当延时
		Sleep(10);
	}
}