////////////////////////////////////////////
// 程序名称：设置鼠标样式的范例
// 编译环境：Visual C++ 6.0，EasyX 2011惊蛰版
//
#include <graphics.h>
#include <conio.h>

void main()
{
	initgraph(640, 480);							// 创建绘图窗口

	HCURSOR hcur = LoadCursor(NULL, IDC_CROSS);		// 加载系统预置的鼠标样式
	HWND hwnd = GetHWnd();							// 获取绘图窗口句柄
	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	// 设置窗口类的鼠标样式

													// 按任意键退出
	getch();
	closegraph();
}

/***************************************************************************************************
一、获取鼠标样式的句柄
使用 API 函数 LoadCursor 实现加载鼠标样式。
该函数可以读取系统默认的样式，也可以加载资源形式的 .cur 鼠标样式图片，
还可以通过 API 函数 LoadImage 加载文件形式的鼠标样式图片。

(1) 加载系统默认的十字样式的鼠标：
HCURSOR hcur = LoadCursor(NULL, IDC_CROSS);

(2) 加载资源中的鼠标样式图片：
HMODULE hmod = GetModuleHandle(NULL);  // 获取当前进程的句柄
HCURSOR hcur = LoadCursor(hmod, _T("MyCursor")); // 加载资源中的鼠标样式图片
// 注：请先将 .cur 格式的图片添加到系统资源文件中，并命名为 "MyCursor"。

(3) 加载 c:\\test.cur 作为鼠标样式：
HCURSOR hcur = (HCURSOR)LoadImage(NULL, _T("C:\\test.cur"), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);

二、设置窗口类的鼠标样式
使用 SetClassLong 设置窗口类，使用 GetHWnd() 返回窗口句柄。

HWND hwnd = GetHWnd();    // 获取绘图窗口句柄
SetClassLong(hwnd, GCL_HCURSOR, (long)hcur); // 设置绘图窗口内的鼠标样式
****************************************************************************************************/