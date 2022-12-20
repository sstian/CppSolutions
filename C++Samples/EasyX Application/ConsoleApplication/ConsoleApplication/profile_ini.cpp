/******************************************************************
 * 程序名称：实现小球移动与正确处理鼠标消息
 * 编译环境：Visual Studio 2017，EasyX 20170421(beta)
 * 作    者：兔儿草<st.tian@foxmail.com>
 * 最后修改：2017-5-23
 * 项目类型：Win32 Console Application
 ******************************************************************/
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define R 30		// 定义球的半径

void main()
{
	// 创建图形窗口，禁用“关闭”按钮，以防止无法正确保存配置文件
	initgraph(640, 480, NOCLOSE);

	// 读取上一次的位置
	int x, y;
	x = GetPrivateProfileInt(_T("Ball"), _T("x"), 320, _T(".\\test.ini"));
	y = GetPrivateProfileInt(_T("Ball"), _T("y"), 240, _T(".\\test.ini"));

	// 设置球的颜色，并绘制
	setfillcolor(GREEN);
	solidcircle(x, y, R);

	MOUSEMSG msg;			// 鼠标消息
	int mx, my;				// 鼠标上一次的位置
	bool keydown = false;	// 左键是否按下

							// 主循环
	while (!_kbhit())
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();		// 获取鼠标消息
			switch (msg.uMsg)
			{
				// 按下鼠标左键，开始拖动
			case WM_LBUTTONDOWN:
				if (sqrt((double)((msg.x - x) * (msg.x - x) + (msg.y - y) * (msg.y - y))) < R)
				{
					keydown = true;
					mx = msg.x;
					my = msg.y;
				}
				break;

				// 抬起鼠标左键，停止拖动
			case WM_LBUTTONUP:
				keydown = false;
				break;

				// 鼠标移动，处理拖动
			case WM_MOUSEMOVE:
				if (keydown)
				{
					clearcircle(x, y, R);
					x += (msg.x - mx);
					y += (msg.y - my);
					mx = msg.x;
					my = msg.y;
					solidcircle(x, y, R);
				}
				break;
			}
		}

		// 延时，降低 cpu 占用率
		Sleep(10);
	}

	// 保存坐标到配置文件
	TCHAR s[20];
	_stprintf(s, _T("%d"), x);			// vc6 的写法
										//	_stprintf_s(s, _T("%d"), x);	// >= vc6 的写法
	::WritePrivateProfileString(_T("Ball"), _T("x"), s, _T(".\\test.ini"));

	_stprintf(s, _T("%d"), y);			// vc6 的写法
										//	_stprintf_s(s, _T("%d"), y);	// >= vc6 的写法
	::WritePrivateProfileString(_T("Ball"), _T("y"), s, _T(".\\test.ini"));

	// 关闭绘图窗口
	closegraph();
}

/***************************************************************************************************
正确处理鼠标消息（解决鼠标操作不灵敏的问题）：
可以确保每次都能处理每一个鼠标消息，并且不会造成鼠标消息的丢失。
*********************************************************************
// 定义变量，保存鼠标消息
MouseMsg msg;

// 游戏的主循环
while(true)
{
	while (MouseHit())			// 当有鼠标消息的时候执行
	{
		msg = GetMouseMsg();	// 获取鼠标消息

		switch(msg.uMsg)		// 根据不同的鼠标消息，执行不同的代码
		{
			case xxxx: 进行游戏运算(); break;
			case xxxx: 进行游戏运算(); break;
		}
	}

	绘制游戏内容();

	Sleep(xx);					// 延时，降低 CPU 占用率
}
*****************************************************************************************************/