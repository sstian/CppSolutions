// 程序名称：同时检测多个按键及平滑按键输入的范例
// 编译环境：Visual C++ 6.0 / 2010，EasyX 惊蛰版
//
#include <graphics.h>

/////////////////////////////////////////////
// 定义常量、枚举量、结构体、全局变量
/////////////////////////////////////////////

#define	CMD_UP			1	//0000 0001
#define	CMD_DOWN		2	//0000 0010
#define	CMD_LEFT		4	//0000 0100
#define	CMD_RIGHT		8	//0000 1000
#define	CMD_ZOOMIN		16	//0001 0000
#define	CMD_ZOOMOUT		32	//0010 0000
#define	CMD_QUIT		64  //0100 0000

// 声明圆的坐标和半径
int g_x, g_y, g_r;



/////////////////////////////////////////////
// 函数声明
/////////////////////////////////////////////

void Init();						// 初始化
void Quit();						// 退出
int  GetCommand();					// 获取控制命令
void DispatchCommand(int _cmd);		// 分发控制命令
void OnUp();						// 上移
void OnDown();						// 下移
void OnLeft();						// 左移
void OnRight();						// 右移
void OnZoomIn();					// 放大
void OnZoomOut();					// 缩小



									/////////////////////////////////////////////
									// 函数定义
									/////////////////////////////////////////////

									// 主函数
void main()
{
	Init();

	int c;
	do
	{
		c = GetCommand();
		DispatchCommand(c);
		Sleep(10);
	} while (!(c & CMD_QUIT));

	Quit();
}

// 初始化
void Init()
{
	// 设置绘图屏幕和绘图模式
	initgraph(640, 480);
	setwritemode(R2_XORPEN);

	// 设置圆的初始位置和大小
	g_x = 320;
	g_y = 240;
	g_r = 20;

	// 显示操作说明
	setfont(14, 0, _T("宋体"));
	outtextxy(20, 270, _T("操作说明"));
	outtextxy(20, 290, _T("上：上移"));
	outtextxy(20, 310, _T("下：下移"));
	outtextxy(20, 330, _T("左：左移"));
	outtextxy(20, 350, _T("右：右移"));
	outtextxy(20, 370, _T("左 Shift：放大"));
	outtextxy(20, 390, _T("左 Ctrl：缩小"));
	outtextxy(20, 410, _T("ESC：退出"));
	outtextxy(20, 450, _T("注：可以同时按多个键，但能同时按下的键的数量，受键盘硬件限制"));

	// 画圆
	circle(g_x, g_y, g_r);
}

// 退出
void Quit()
{
	closegraph();
}

// 获取控制命令
int GetCommand()
{
	int c = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)		c |= CMD_DOWN;
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)	c |= CMD_ZOOMIN;
	if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)	c |= CMD_ZOOMOUT;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)	c |= CMD_QUIT;

	return c;
}

// 分发控制命令
void DispatchCommand(int _cmd)
{
	if (_cmd & CMD_UP)			OnUp();
	if (_cmd & CMD_DOWN)		OnDown();
	if (_cmd & CMD_LEFT)		OnLeft();
	if (_cmd & CMD_RIGHT)		OnRight();
	if (_cmd & CMD_ZOOMIN)		OnZoomIn();
	if (_cmd & CMD_ZOOMOUT)		OnZoomOut();
}

// 上移
void OnUp()
{
	circle(g_x, g_y, g_r);
	if (g_y <= 0) g_y = 480; else g_y -= 2;
	circle(g_x, g_y, g_r);
}

// 下移
void OnDown()
{
	circle(g_x, g_y, g_r);
	if (g_y >= 480) g_y = 0; else g_y += 2;
	circle(g_x, g_y, g_r);
}

// 左移
void OnLeft()
{
	circle(g_x, g_y, g_r);
	if (g_x <= 0) g_x = 640; else g_x -= 2;
	circle(g_x, g_y, g_r);
}

// 右移
void OnRight()
{
	circle(g_x, g_y, g_r);
	if (g_x >= 640) g_x = 0; else g_x += 2;
	circle(g_x, g_y, g_r);
}

// 放大
void OnZoomIn()
{
	circle(g_x, g_y, g_r);
	if (g_r < 100) g_r++;
	circle(g_x, g_y, g_r);
}

// 缩小
void OnZoomOut()
{
	circle(g_x, g_y, g_r);
	if (g_r > 10) g_r--;
	circle(g_x, g_y, g_r);
}

/*************************************************************************************************
GetAsyncKeyState() 判断函数调用时指定虚拟键的状态。函数原型：
SHORT GetAsyncKeyState(
	int vKey		// virtual-key code 要检测的按键的虚拟键码
);
返回的 SHORT 值，如果最高位为 1，表示该键被按下；否则表示该键弹起。
该函数的最低位还可以用来检测开关键（比如大小写锁定键）的状态。
作为按键处理，还可以使用 GetKeyState、GetKeyboardState 等函数
//对于 26 个字母的键码，可以直接写 'A'、'B'……，而不要写 VK_A、VK_B。数字键也是，请直接写 '0'、'1'……。
常用键的VK值：
VK_SHIFT		Shift键
VK_LSHIFT		左Shift键
VK_RSHIFT		右Shift键
VK_CONTROL		Ctrl键
VK_LCONTROL		左Ctrl键
VK_RCONTROL		右Ctril键
VK_MENU			Alt键
VK_LMENU		左Alt键
VK_RMENU		右Alt键
VK_LBUTTON		鼠标左键
VK_RBUTTON		鼠标右键
VK_ESCAPE		ESC键
VK_RETURN		回车键
VK_TAB			TAB键
VK_SPACE		空格键
VK_NUMLOCK		NUM LOCK key
VK_CAPITAL		CAPS LOCK key
VK_SCROLL		SCROLL LOCK key
VK_F1			F1 key ……
VK_PRIOR		PAGE UP key
VK_NEXT			PAGE DOWN key
VK_END			END key
VK_HOME			HOME key
VK_SNAPSHOT		PRINT SCREEN key
VK_INSERT		INS key
VK_DELETE		DEL key
VK_LWIN			Left Windows key (Natural keyboard)
VK_RWIN			Right Windows key (Natural keyboard)
VK_NUMPAD0		Numeric keypad 0 key ……
VK_ADD			Add key
VK_SUBTRACT		Subtract key
VK_MULTIPLY		Multiply key
VK_DIVIDE		Divide key
0x30			0 key ……
0x41			A key ……
**************************************************************************************************/