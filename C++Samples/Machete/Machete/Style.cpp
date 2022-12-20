//Style.cpp  样式 实现文件
#include <graphics.h>
#include <ctime>
#include <vector>
#include <string>
#include <mmsystem.h>
#include "Constant.h"
#include "Style.h"
#include "Duel.h"
#include "Option.h"
#include "Help.h"

#pragma comment(lib,"winmm.lib")
//using namespace std;

/* 主菜单界面 */
void MainMenu()
{	
	mciSendString(_T("stop bgm"), 0, 0, 0);
	mciSendString(_T("close bgm"), 0, 0, 0);

	mciSendString(_T("open res/sounds/overlap.mp3 alias theme"), 0, 0, 0);
	mciSendString(_T("play theme repeat"), 0, 0, 0);

	//界面切换初始化准备
	cleardevice();
	HWND hWnd = Button::MouseShape(MOUSE_ARROW);
	SetWindowText(hWnd, _T("Machete -- 兔儿草"));	//窗口标题
	SetWindowRgn(hWnd, NULL, true);	 //恢复默认的矩形窗口，主菜单界面绘制

	MenuButton mbutton[NUMBERS];	//菜单按钮对象数组 4

	//背景图
	loadimage(NULL, _T("res/images/main.jpg"));

	//标题
	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight = 100;
	font.lfWidth = 60;
	wcscpy_s(font.lfFaceName, _T("华文楷体"));
	font.lfQuality = ANTIALIASED_QUALITY;	//设置抗锯齿质量
	settextstyle(&font);					

	//settextstyle(100, 60, _T("华文楷体"));	//文本样式：宽度、高度、字体
	setbkmode(TRANSPARENT);					//文字背景透明
	settextcolor(RGB(8, 246, 221));			//标题背景色：偏青色
	outtextxy(105, 45, g_title);			//输出文本位置及内容
	settextcolor(RGB(4, 132, 251));			//标题前景色：偏蓝色
	outtextxy(100, 40, g_title);	
	//英文副标题及版本号
	settextstyle(40, 20, _T("Times New Roman"));
	settextcolor(RGB(221, 25, 250));		//偏紫色
	outtextxy(340, 150, g_subtitle);
	//菜单按钮
	int y = 0;  //纵坐标
	RECT rect;	//临时矩形存储区
	for (int i = 0; i < NUMBERS; i++)
	{
		rect = { g_coordinate[i][y], g_coordinate[i][y + 1],
			 g_coordinate[i][y] + RECT_WIDTH, g_coordinate[i][y + 1] + RECT_HEIGHT };  //构建矩形
		setlinestyle(PS_SOLID, 3);	//线型：实线、厚度
		roundrect(rect.left, rect.top, rect.right, rect.bottom, ELLIPSE_WIDTH, ELLIPSE_HEIGHT);  //绘制圆角矩形
		setfillcolor(RGB(226, 224, 225));  //填充色：偏银色
		fillroundrect(rect.left, rect.top, rect.right, rect.bottom, ELLIPSE_WIDTH, ELLIPSE_HEIGHT);  //填充圆角矩形

		mbutton[i].SetRect(rect);  //初始化菜单按钮对象数组

		//菜单按钮文本
		font.lfHeight = 45;
		font.lfWidth = 25;
		wcscpy_s(font.lfFaceName, _T("隶书"));
		settextstyle(&font);
		//settextstyle(45, 25, _T("隶书"));
		settextcolor(RGB(249, 80, 80));  //偏红色
		drawtext(g_menutext[i], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //水平垂直居中、单行
	}

	//菜单按钮选中效果
	while (true)
	{
		//获取鼠标消息
		switch (MenuButton::MouseMsg().uMsg)
		{
		case WM_MOUSEMOVE:		//鼠标移动显示特效
			BeginBatchDraw();
				 if (mbutton[0].IsWithin())		mbutton[0].MouseMove(g_menutext[0]);
			else if (mbutton[1].IsWithin())		mbutton[1].MouseMove(g_menutext[1]);
			else if (mbutton[2].IsWithin())		mbutton[2].MouseMove(g_menutext[2]);
			else if (mbutton[3].IsWithin())		mbutton[3].MouseMove(g_menutext[3]);
			else
			{
				mbutton[0].MouseLeave(g_menutext[0]);
				mbutton[1].MouseLeave(g_menutext[1]);
				mbutton[2].MouseLeave(g_menutext[2]);
				mbutton[3].MouseLeave(g_menutext[3]);
			}
			EndBatchDraw();
			break;
		case WM_LBUTTONDOWN:	//按鼠标左键选择功能
				 if (mbutton[0].IsWithin())		StartGame();		//开始
			else if (mbutton[1].IsWithin())		OptionSetting();	//选项
			else if (mbutton[2].IsWithin())		HelpDoc();			//帮助
			else if (mbutton[3].IsWithin())		ExitProgram();		//退出
			break;
		case WM_RBUTTONUP:		//按鼠标右键退出程序
			ExitProgram(1);
			break;	
		}
	}
}

/* 退出程序（默认为0）
//函数声明中设置默认形参值后，其定义中不能再有默认形参值！*/
void ExitProgram(int status)
{
	HWND hWnd = GetHWnd();
	int msgboxID;
	switch (status)
	{
	case 0:
		msgboxID = MessageBox(hWnd, _T("真的要退出吗？"), _T("后会无期"),
			MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1);				//确定 取消，询问图标，默认按钮第一个
		if (IDOK == msgboxID)
			exit(0);
		break;
	case 1:
		msgboxID = MessageBox(hWnd, _T("凡王之血，\n必以剑终！\n要离开这个世界吗？"), _T("次元传送门"),
			MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON1);				//确定 取消，警告图标，默认按钮第一个
		if (IDOK == msgboxID)
			exit(0);
		break;
	default:
		break;
	}
}

/* 五角星闪亮：从中间由小及大扩展开来 */
void StarBloom()
{
	POINT pts_pentagon[5];
	for (LONG REDUCE = 0; REDUCE < 300; REDUCE += 10)
	{
		//填充五角星角的坐标
		pts_pentagon[0] = { (LONG)(HALFW - REDUCE * cos(RAD(18))), (LONG)(HALFH - REDUCE * sin(RAD(18))) };//14
		pts_pentagon[1] = { (LONG)(HALFW + REDUCE * cos(RAD(18))), (LONG)(HALFH - REDUCE * sin(RAD(18))) };//11
		pts_pentagon[2] = { (LONG)(HALFW - REDUCE * sin(RAD(36))), (LONG)(HALFH + REDUCE * cos(RAD(36))) };//13
		pts_pentagon[3] = { (LONG)(HALFW)						 , (LONG)(HALFH - REDUCE)                };//10
		pts_pentagon[4] = { (LONG)(HALFW + REDUCE * sin(RAD(36))), (LONG)(HALFH + REDUCE * cos(RAD(36))) };//12
		//srand((unsigned int )time(NULL));					//以当前时间初始化随机发生器的种子
		setlinecolor(HSLtoRGB((float)(rand()%360), 1, 0.5));	//随机产生颜色值
		polygon(pts_pentagon, 5);								//绘制五角星
		Sleep(20);												//延时50毫秒（0.05秒）
	}
}

/* 计算整数的绝对值 */
int calc_abs(int value)
{
	if (value < 0)
		value *= -1;
	return value;
}
/* copy img2 to img1 */
void copy_image(IMAGE* img1, IMAGE* img2)
{
	IMAGE* now_working = GetWorkingImage();
	Resize(img1, img2->getwidth(), img2->getheight());
	SetWorkingImage(img2);
	getimage(img1, 0, 0, img1->getwidth(), img1->getheight());
	SetWorkingImage(now_working);
}
/* 图像透明处理 
排除颜色为avoid_color，容差为deviation，透明度tp(transparency)从0到100 */
void transp_image(int dstX, int dstY, IMAGE *pimg, int avoid_color, int deviation, int tp)
{
	int x, y, num;
	int R, G, B;	//记录贴图某点色彩
					//记录排除颜色色彩
	int avoid_r = GetRValue(avoid_color);
	int avoid_g = GetGValue(avoid_color);
	int avoid_b = GetBValue(avoid_color);
	IMAGE pSrcImg;	//背景图
	IMAGE tempimg;	//临时贴图
	copy_image(&tempimg, pimg);
	SetWorkingImage(NULL);//对默认绘图窗口的绘图操作
	getimage(&pSrcImg, dstX, dstY, pimg->getwidth(), pimg->getheight());

	//透明度容错
	if (tp < 0)
	{
		tp = 0;
	}
	else if (tp > 100)
	{
		tp = 100;
	}

	// 获取背景指向显存的指针
	DWORD* bk_pMem = GetImageBuffer(&pSrcImg);
	//贴图指向显存的指针
	DWORD* pMem = GetImageBuffer(&tempimg);

	for (y = 0; y < pimg->getheight(); y++)
	{
		for (x = 0; x < pimg->getwidth(); x++)
		{
			num = y * pimg->getwidth() + x;
			R = GetRValue(pMem[num]);
			G = GetGValue(pMem[num]);
			B = GetBValue(pMem[num]);
			if ((calc_abs(R - avoid_r) <= deviation) && (calc_abs(G - avoid_g) <= deviation) && (calc_abs(B - avoid_b) <= deviation))
			{
				pMem[num] = bk_pMem[num];
			}
			else
			{
				pMem[num] = RGB((R*tp + GetRValue(bk_pMem[num])*(100 - tp)) / 100, (G*tp + GetGValue(bk_pMem[num])*(100 - tp)) / 100, (B*tp + GetBValue(bk_pMem[num])*(100 - tp)) / 100);
			}
		}
	}
	putimage(dstX, dstY, &tempimg);
}

/***********************************************************************************************************/

/* * 设置鼠标形状 */
HWND Button::MouseShape(int shape)
{
	HWND hWnd = GetHWnd();							//获取窗口句柄
	HCURSOR hCursor;
	switch (shape)
	{
	case MOUSE_HAND:			//手形鼠标指针
		hCursor = LoadCursor(NULL, IDC_HAND);			//加载光标资源
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);	//设置光标属性
		break;
	case MOUSE_ARROW:			//箭头鼠标指针
		hCursor = LoadCursor(NULL, IDC_ARROW);
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);
		break;
	case MOUSE_CROSS:			//十字鼠标指针
		hCursor = LoadCursor(NULL, IDC_CROSS);
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);
		break;
	default:
		break;
	}
	return hWnd;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

MOUSEMSG MenuButton::mouse_;

/* 设置矩形区域（RECT对象） */
void Button::SetRect(const RECT& rect)
{
	left_	= rect.left;
	top_	= rect.top;
	right_	= rect.right;
	bottom_ = rect.bottom;
}

/* 设置矩形区域（点的坐标）*/
void Button::SetRect(int left, int top, int right, int bottom)
{
	left_	= left;
	top_	= top;
	right_	= right;
	bottom_ = bottom;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

///* 设置矩形区域（RECT对象） */
//void MenuButton::SetRect(const RECT& rect)
//{
//	Button::SetRect(rect);	//调用父类的方法
//	//setLeft(rect.left);
//	//setTop(rect.top);
//	//setRight(rect.right);
//	//setBottom(rect.bottom);
//}
//
///* 设置矩形区域（点的坐标）*/
//void MenuButton::SetRect(int left, int top, int right, int bottom)
//{
//	Button::SetRect(left, top, right, bottom);  //调用父类的方法
//	//setLeft(left);
//	//setTop(top);
//	//setRight(right);
//	//setBottom(bottom);
//}

/* * 获取外界鼠标消息接口 */
MOUSEMSG& MenuButton::MouseMsg()
{
	mouse_ = GetMouseMsg();
	return mouse_;
}

/* 判断鼠标是否在范围内（不包括边界），需要先调用MouseMsg()以获取鼠标消息 */
bool MenuButton::IsWithin()
{
	int x = mouse_.x;	//鼠标指针x轴坐标
	int y = mouse_.y;	//鼠标指针x轴坐标
	//在范围内：left_ <= x <= right_ 且 top_ <= y <= bottom_
	if ((x > getLeft() && x < getRight()) && (y > getTop() && y < getBottom()))
		return true;
	else
		return false;
}

/* 鼠标悬浮样式：手形鼠标，黄色填充，字体绿色、稍有放大 
	menutext: 菜单文本 */
void MenuButton::MouseMove(const TCHAR* menutext)
{
	Button::MouseShape(MOUSE_HAND);

	RECT rect = { getLeft(), getTop(), getRight(), getBottom() };								//以对象属性建立矩形
	setlinestyle(PS_SOLID, 1);			//线型：实线、厚度1
	roundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);		//圆角矩形
	
	setfillcolor(YELLOW);				//填充色：黄色
	fillroundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);	//填充圆角矩形

	settextstyle(47, 27, _T("隶书"));	//字体放大2像素
	settextcolor(GREEN);				//字体颜色：绿色
	drawtext(menutext, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);						//水平垂直居中、单行
}

/* 鼠标离开样式：恢复原来效果（箭头鼠标，银色填充，字体红色） 
	menutext: 菜单文本 */
void MenuButton::MouseLeave(const TCHAR* menutext)
{
	Button::MouseShape(MOUSE_ARROW);

	RECT rect = { getLeft(), getTop(), getRight(), getBottom() };								//以对象属性建立矩形
	setlinestyle(PS_SOLID, 3);			//线型：实线、厚度3
	roundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);		//圆角矩形

	setfillcolor(RGB(226, 224, 225));	//填充色：偏银色
	fillroundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);	//填充圆角矩形

	settextstyle(45, 25, _T("隶书"));	//字体大小恢复
	settextcolor(RGB(249, 80, 80));		//字体颜色：偏红色
	drawtext(menutext, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);						//水平垂直居中、单行
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 星按钮构造函数：坐标点，个数（一般取3个）*/
//StarButton::StarButton(const POINT* pPoints, int num)
//{
//	for (int i = 0; i < num; i++)
//	{
//		switch (i)
//		{
//		case 0:
//			first_  = pPoints->x;
//			second_ = pPoints->y;
//			break;
//		case 1:
//			setLeft(pPoints->x);
//			setTop(pPoints->y);
//			break;
//		case 2:
//			setRight(pPoints->x);
//			setBottom(pPoints->y);
//			break;
//		default:
//			break;
//		}
//	}
//}

/* 设置五角星三角形按钮：坐标点，个数（默认为3个） */
void StarButton::SetStar(const POINT* pPoints, int num)
{
	for (int i = 0; i < num; i++)
	{
		switch (i)
		{
		case 0:
			firstpt_.x  = pPoints[0].x;
			firstpt_.y  = pPoints[0].y;
			break;
		case 1:
			secondpt_.x = pPoints[1].x;
			secondpt_.y = pPoints[1].y;
			break;
		case 2:
			thirdpt_.x  = pPoints[2].x;
			thirdpt_.y  = pPoints[2].y;
			break;
		default:
			break;
		}
	}
}

/* 判断鼠标是否在范围内（不包括边界）
	mode: 游戏模式
两点坐标：(x1,y1),(x2,y2) 
-> y = (y2 - y1) / (x2 - x1) * (x - x1) + y1 或 y = (y2 - y1) / (x2 - x1) * (x - x2) + y2 
*/
bool StarButton::IsWithin(int mode)
{
	MOUSEMSG m = MouseMsg();
	bool flag = false;		//判断标志
//							//根据直线方程计算出对应横坐标x的纵坐标值
//	LONG y = (thirdpt_.y - secondpt_.y) / (thirdpt_.x - secondpt_.x) * (m.x - secondpt_.x) + secondpt_.y;
	//LONG y1 = (thirdpt_.y - secondpt_.y) / (thirdpt_.x - secondpt_.x) * (m.x - secondpt_.x) + secondpt_.y;
	//LONG y2 = (thirdpt_.y - firstpt_.y) / (thirdpt_.x - firstpt_.x) * (m.x - firstpt_.x) + firstpt_.y;
	//LONG y3 = (secondpt_.y - firstpt_.y) / (secondpt_.x - firstpt_.x) * (m.x - firstpt_.x) + firstpt_.y;
	switch (mode)
	{						//限定横坐标x为最大的范围
	case SELECT:
		if (m.y < thirdpt_.y)	flag = true;
		else					flag = false;
		break;
	case SINGLE:	
		//if ((m.x > secondpt_.x && m.x < thirdpt_.x && m.y < y1)
		//	&& (m.x > firstpt_.x && m.x < thirdpt_.x && m.y > y2)
		//	&& (m.x > firstpt_.x && m.x < secondpt_.x && m.y < y3))
		//通过局部矩形区域判断
		if ((m.x > firstpt_.x && m.x < secondpt_.x) && (m.y > firstpt_.y && m.y < secondpt_.y))
			flag = true;
		else
			flag = false;
		break;
	case COUPLE:
		if ((m.x > thirdpt_.x && m.x < firstpt_.x) && (m.y > firstpt_.y && m.y < thirdpt_.y))
			flag = true;
		else
			flag = false;
		break;
	case TRIPLE:
		if ((m.x > secondpt_.x && m.x < firstpt_.x) && (m.y > secondpt_.y && m.y < firstpt_.y))
			flag = true;
		else
			flag = false;
		break;
	case TEAM:
		if ((m.x > firstpt_.x && m.x < thirdpt_.x) && (m.y > thirdpt_.y && m.y < firstpt_.y))
			flag = true;
		else
			flag = false;
		break;
	case BLANK:
		if ((m.x > g_stars[8].x && m.x < g_stars[6].x) && (m.y > g_stars[9].y && m.y < g_stars[7].y))
			flag = true;
		else
			flag = false;
		break;
	default:
		break;
	}
	return flag;
}

/* 鼠标悬浮样式：手形鼠标，字体蓝绿色
		mode: 游戏模式 
*/
void StarButton::MouseMove(int mode)
{
	HWND hWnd = GetHWnd();							//获取窗口句柄
	HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);	//加载光标资源
	SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);	//设置光标属性

	settextcolor(RGB(36, 250, 232));		//字体：偏蓝绿色
	switch (mode)
	{						
	case SINGLE:
		outtextxy(180, 215, g_mode[mode][0]);		//"单"
		outtextxy(240, 240, g_mode[mode][1]);		//"机"
		break;
	case COUPLE:
		outtextxy(490, 240, g_mode[mode][0]);		//"双"
		outtextxy(550, 215, g_mode[mode][1]);		//"人"
		break;
	case TRIPLE:
		outtextxy(440, 375, g_mode[mode][0]);		//"混"
		outtextxy(470, 430, g_mode[mode][1]);		//"战"
		break;
	case TEAM:
		outtextxy(285, 375, g_mode[mode][0]);		//"组"
		outtextxy(250, 430, g_mode[mode][1]);		//"队"
		break;
	//case BLANK:
	//	Button::MouseShape(MOUSE_CROSS);
	//	break;
	default:
		break;
	}

}

/* 鼠标离开样式：恢复原来效果（箭头鼠标，字体金黄色）
	mode: 游戏模式
*/
void StarButton::MouseLeave(int mode)
{
	HWND hWnd = GetHWnd();
	HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);
	SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);

	settextcolor(RGB(242, 250, 36));		//字体颜色：偏金黄色
	switch (mode)
	{						
	case SINGLE:
		outtextxy(180, 215, g_mode[mode][0]);		//"单"
		outtextxy(240, 240, g_mode[mode][1]);		//"机"
		break;
	case COUPLE:
		outtextxy(490, 240, g_mode[mode][0]);		//"双"
		outtextxy(550, 215, g_mode[mode][1]);		//"人"
		break;
	case TRIPLE:
		outtextxy(440, 375, g_mode[mode][0]);		//"混"
		outtextxy(470, 430, g_mode[mode][1]);		//"战"
		break;
	case TEAM:
		outtextxy(285, 375, g_mode[mode][0]);		//"组"
		outtextxy(250, 430, g_mode[mode][1]);		//"队"
		break;
	//case BLANK:
	//	Button::MouseShape(MOUSE_ARROW);
	//	break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 鼠标悬浮
己方：手形鼠标，加框  //卡牌上浮
对方：箭头鼠标（不变），加框  //卡牌下浮
卡组：手形鼠标  //，椭圆 */
void CardButton::MouseMove()
{
	if (getLeft() > 200 && getBottom() > HEIGHT / 2)		//在己方区域
	{
		if (true == exit_)	//卡牌在手
		{
			Button::MouseShape(MOUSE_HAND);
			//poker_.PlaceCard(getLeft(), getTop() - DRIFT);
			//transp_image(getLeft(), getTop() - DRIFT, &GetImage(), WHITE, 200, 100);
			setlinestyle(PS_SOLID, 5);
			rectangle(getLeft() + 2, getTop() + 2, getRight() - 3, getBottom() - 3);
		}
	}
	else if (getLeft() > 200 && getBottom() < HEIGHT / 2)	//在对方区域
	{
		Button::MouseShape(MOUSE_ARROW);
		//poker_.PlaceCard(getLeft(), getTop() + DRIFT);
		setlinestyle(PS_SOLID, 5);
		rectangle(getLeft() + 2, getTop() + 2, getRight() - 3, getBottom() - 3);
	}
	else													//卡组区域
	{
		Button::MouseShape(MOUSE_HAND);
		//setlinestyle(PS_SOLID, 5);
		//ellipse(getLeft() + 15, getTop() + 15, getRight() - 15, getBottom() - 15);
	}
}

/* 鼠标离开
对方、己方、卡组（均恢复）：箭头鼠标，卡牌归位 */
void CardButton::MouseLeave()
{
	Button::MouseShape(MOUSE_ARROW);
	MOUSEMSG m = MenuButton::MouseMsg();
	if (m.x > 200)
	{
		if (m.y > HEIGHT / 2)
		{
			poker_.PlaceCard(getLeft(), getTop());
			if (down_ && exit_)
			{
				circle((getLeft() + getRight()) / 2, (getTop() + getBottom()) / 2, 30);
			}
		}		
	}
	for (int m = 0; m < FIELD; m++)
	{
		g_pokers[0].PlaceCard(g_cbOtherHand[m]);
	}
}

/* 鼠标左键按下，表示此卡牌被选中
己方：在卡牌中心画个圆；再次按下则重新贴图。
对方：无效
卡组：发起投降，弹出警告对话框 */
void CardButton::LeftDown()
{
	if (getLeft() > 200 && getBottom() > HEIGHT / 2)		//在己方区域
	{
		if (exit_)	//卡牌在手
		{
			Button::MouseShape(MOUSE_HAND);
			if (!down_)		//卡牌未被选中的状态下被选中了
			{
				down_ = true;
				setlinestyle(PS_SOLID, 5);
				circle((getLeft() + getRight()) / 2, (getTop() + getBottom()) / 2, 30);
			}
			else			//在选中的状态下再次选中表示未选中
			{
				down_ = false;
				poker_.PlaceCard(getLeft(), getTop());
			}
		}
	}
	else if (getLeft() < 200)
	{
		HWND hWnd = GetHWnd();
		int msgboxID = MessageBox(hWnd, _T("  忍一时风平浪静，\n  退一步海阔天空。\n\n确定要发起投降吗？"), 
			_T("三十六计走为上"),
			MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON2);				//确定 取消，警告图标，默认按钮第二个
		if (IDOK == msgboxID)
		{
			setlinestyle(PS_SOLID, 0);
			LifeValue(Self, 0);
			RECT givein = { 100, 100, 700, 500 };
			settextstyle(70, 35, _T("华文新魏"));
			drawtext(g_result[2], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU LOSE
			Sleep(2000);	//界面停留2秒
			MainMenu();
		}
	}
}

/* 重载赋值=操作符，实现卡牌的快速放置 
//直接通过 g_cbSelfHand[2] = g_pokers[53] 即可使用*/
void CardButton::operator =(const Poker& rPoker) 
{ 
	poker_ = rPoker;
	poker_.PlaceCard(*(this)); 
}

/* 清除卡牌所在区域：颜色矩形填充 */
void CardButton::ClearCard()
{
	setPoker(g_pokers[55]);				//蓝黑填充矩形图像
	setfillcolor(RGB(6, 4, 51));		//填充颜色：偏黑蓝色
	solidrectangle(getLeft(), getTop(), getRight(), getBottom());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 鼠标悬浮：变色，字体放大 */
void OutButton::MouseMove(const TCHAR* outtext)
{
	Button::MouseShape(MOUSE_HAND);

	RECT rect = { getLeft(), getTop(), getRight(), getBottom() };								//以对象属性建立矩形
	setlinestyle(PS_SOLID, 1);			//线型：实线、厚度1
	roundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);		//圆角矩形

	setfillcolor(YELLOW);				//填充色：黄色
	fillroundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);	//填充圆角矩形

	settextstyle(32, 22, _T("隶书"));	//字体放大2像素
	settextcolor(GREEN);				//字体颜色：绿色
	drawtext(outtext, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);						//水平垂直居中、单行
}

/* 鼠标离开 */
void OutButton::MouseLeave(const TCHAR* outtext)
{
	Button::MouseShape(MOUSE_ARROW);

	RECT rect = { getLeft(), getTop(), getRight(), getBottom() };								//以对象属性建立矩形
	setlinestyle(PS_SOLID, 3);			//线型：实线、厚度3
	roundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);		//圆角矩形

	setfillcolor(RGB(226, 224, 225));	//填充色：偏银色
	fillroundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);	//填充圆角矩形

	settextstyle(30, 20, _T("隶书"));	//字体大小恢复
	settextcolor(RGB(249, 80, 80));		//字体颜色：偏红色
	drawtext(outtext, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);						//水平垂直居中、单行
}

/* 鼠标左键按下：出牌、战斗 */
void OutButton::LeftDown(int putout)
{
	bool out, attack;
	int field = 0;		//己方移出卡牌
	int zone = 0;		//对方移出卡牌
	switch (putout)
	{
	case Ensure:	//出牌
		if (0 == g_respond.size())	//表示自己先出
		{
			out = CheckOut(g_check);
			if (g_check.size() != 0)
			{
				if (out)
				{
					//手牌向场地移动	
					for (size_t out = 0; out < g_check.size(); out++)
					{
						g_cbSelfField[field++] = g_check.at(out).getPoker();
					}
					for (int hand = 0; hand < FIELD; hand++)		//移出去的手牌卡区设置标志位
					{
						if (true == g_cbSelfHand[hand].getDown())
						{
							g_cbSelfHand[hand].setDown(false);
							g_cbSelfHand[hand].setExit(false);
							g_cbSelfHand[hand].ClearCard();
						}
					}
					//炸弹 YOU WIN
					if (5 == g_check.size())
					{
						RECT bomb[3];
						for (int blast = 0; blast < 3; blast++)
						{
							bomb[blast].left = g_cbSelfField[blast + 1].getLeft();
							bomb[blast].top = g_cbSelfField[blast + 1].getTop();
							bomb[blast].right = g_cbSelfField[blast + 1].getRight();
							bomb[blast].bottom = g_cbSelfField[blast + 1].getBottom();
						}
						Sleep(500);
						drawtext(_T("炸"), &bomb[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						drawtext(_T("弹"), &bomb[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						drawtext(_T("！"), &bomb[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						setlinestyle(PS_SOLID, 0);
						LifeValue(Other, 0);
						RECT givein = { 100, 100, 700, 500 };
						settextstyle(70, 35, _T("华文新魏"));
						drawtext(g_result[1], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU WIN
						Sleep(2000);	//界面停留2秒
						MainMenu();
					}

					//对方压牌
					if (OtherProduce(g_check, g_respond))
					{
						Sleep(200);
						for (size_t play = 0; play < g_respond.size(); play++)		//对方手牌向场地移动
						{
							g_cbOtherField[zone++] = g_respond.at(play).getPoker();
						}
						for (int h = 0; h < FIELD; h++)		//对方移出去的手牌卡区设置标志位
						{
							if (false == g_cbOtherHand[h].getExit())
							{
								g_cbOtherHand[h].ClearCard();
							}
						}

					}
					else
					{
						RECT pass = { g_cbOtherField[0].getLeft(), g_cbOtherField[0].getTop(), g_cbOtherField[0].getRight(), g_cbOtherField[0].getBottom() };
						settextcolor(RGB(247, 121, 157));	//字体颜色：偏红色
						drawtext(_T("过"), &pass, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						g_check.clear();
						g_respond.clear();
						Sleep(1000);
						DealCards(Before);	//先手
					}

					//将场地已出卡牌换成封面
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//将场地已出卡牌换成封面
					for (int m = 0; m < zone; m++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbOtherField[m]);
					}

				}
				else
				{
					HWND hWnd = GetHWnd();
					int msgboxID = MessageBox(hWnd, _T("  牌型有误！\n请重试。。。"), _T("加油！"),
						MB_OK | MB_ICONERROR);				//确定，错误图标
					//settextcolor(RGB(248, 16, 21));		//字体颜色：偏鲜红色
					//settextstyle(30, 12, _T("华文新魏"));
					//drawtext(_T("牌型有误，请重试！"), &g_rectSelfHint, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
		else	//己方要做出回应
		{
			out = CheckOut(g_check);
			//炸弹 YOU WIN
			if (5 == g_check.size())
			{
				RECT bomb[3];
				for (int blast = 0; blast < 3; blast++)
				{
					bomb[blast].left = g_cbSelfField[blast + 1].getLeft();
					bomb[blast].top = g_cbSelfField[blast + 1].getTop();
					bomb[blast].right = g_cbSelfField[blast + 1].getRight();
					bomb[blast].bottom = g_cbSelfField[blast + 1].getBottom();
				}
				Sleep(500);
				drawtext(_T("炸"), &bomb[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext(_T("弹"), &bomb[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext(_T("！"), &bomb[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				setlinestyle(PS_SOLID, 0);
				LifeValue(Other, 0);
				RECT givein = { 100, 100, 700, 500 };
				settextstyle(70, 35, _T("华文新魏"));
				drawtext(g_result[1], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU WIN
				Sleep(2000);	//界面停留2秒
				MainMenu();
			}
			if (g_check.size() != 0)
			{
				if (out && CheckProduce(g_respond, g_check))
				{
					//手牌向场地移动	
					for (size_t out = 0; out < g_check.size(); out++)
					{
						g_cbSelfField[field++] = g_check.at(out).getPoker();
					}
					for (int hand = 0; hand < FIELD; hand++)		//移出去的手牌卡区设置标志位
					{
						if (true == g_cbSelfHand[hand].getDown())
						{
							g_cbSelfHand[hand].setDown(false);
							g_cbSelfHand[hand].setExit(false);
							g_cbSelfHand[hand].ClearCard();
						}
					}
					//对方压牌
					if (OtherProduce(g_check, g_respond))
					{
						Sleep(200);
						for (size_t play = 0; play < g_respond.size(); play++)		//对方手牌向场地移动
						{
							g_cbOtherField[zone++] = g_respond.at(play).getPoker();
						}
						for (int h = 0; h < FIELD; h++)		//对方移出去的手牌卡区设置标志位
						{
							if (false == g_cbOtherHand[h].getExit())
							{
								g_cbOtherHand[h].ClearCard();
							}
						}

					}
					else
					{
						RECT pass = { g_cbOtherField[0].getLeft(), g_cbOtherField[0].getTop(), g_cbOtherField[0].getRight(), g_cbOtherField[0].getBottom() };
						settextcolor(RGB(247, 121, 157));	//字体颜色：偏红色
						drawtext(_T("过"), &pass, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						Sleep(1000);
						DealCards(Before);	//先手
					}

					//将场地已出卡牌换成封面
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//将场地已出卡牌换成封面
					for (int m = 0; m < zone; m++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbOtherField[m]);
					}

				}
				else
				{
					HWND hWnd = GetHWnd();
					int msgboxID = MessageBox(hWnd, _T("  出牌不对哦！\n请专注一点。。。"), _T("相信你！"),
						MB_OK | MB_ICONERROR);				//确定，错误图标
															//settextcolor(RGB(248, 16, 21));		//字体颜色：偏鲜红色
															//settextstyle(30, 12, _T("华文新魏"));
															//drawtext(_T("牌型有误，请重试！"), &g_rectSelfHint, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
		break;
	case Attack:	//战斗
		g_check.clear();
		if (0 == g_respond.size())
		{
			attack = CheckAttack(g_check);
			if (g_check.size() != 0)
			{
				if (attack)
				{
					for (int hand = 0; hand < FIELD; hand++)		//移出去的手牌卡区设置标志位
					{
						if (true == g_cbSelfHand[hand].getDown())
						{
							g_cbSelfHand[hand].setDown(false);
							g_cbSelfHand[hand].setExit(false);
							g_cbSelfField[field++] = g_cbSelfHand[hand].getPoker();
							g_cbSelfHand[hand].ClearCard();
						}
					}
					//将场地已出卡牌换成封面
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//对方反击
					if (OtherAgainst(g_check, g_respond))
					{
						Sleep(200);
						for (size_t play = 0; play < g_respond.size(); play++)		//对方手牌向场地移动
						{
							g_cbOtherField[zone++] = g_respond.at(play).getPoker();
						}
						for (int h = 0; h < FIELD; h++)		//对方移出去的手牌卡区设置标志位
						{
							if (false == g_cbOtherHand[h].getExit())
							{
								g_cbOtherHand[h].ClearCard();
							}
						}
					}
					else
					{
						g_OtherLife -= g_hurt;
						if (g_OtherLife <= 0)
						{
							g_OtherLife = 0;
							LifeValue(Other, g_OtherLife);
							RECT givein = { 100, 100, 700, 500 };
							settextstyle(70, 35, _T("华文新魏"));
							drawtext(g_result[1], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU WIN
							Sleep(2000);	//界面停留2秒
							MainMenu();

						}
						LifeValue(Other, g_OtherLife);
						Sleep(1000);
						DealCards(Before);	//先手
					}

				}
				else
				{
					HWND hWnd = GetHWnd();
					int msgboxID = MessageBox(hWnd, _T("  存在非攻击型卡牌！\n请检查你的武器。。。"), _T("开火！"),
						MB_OK | MB_ICONERROR);				//确定，错误图标
				}
			}
		}
		else
		{
			attack = CheckAgainst(g_check);
			if (g_check.size() != 0)
			{
				if (attack)
				{
					for (int hand = 0; hand < FIELD; hand++)		//移出去的手牌卡区设置标志位
					{
						if (true == g_cbSelfHand[hand].getDown())
						{
							g_cbSelfHand[hand].setDown(false);
							g_cbSelfHand[hand].setExit(false);
							g_cbSelfField[field++] = g_cbSelfHand[hand].getPoker();
							g_cbSelfHand[hand].ClearCard();
						}
					}
					//将场地已出卡牌换成封面
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//对方反击
					if (OtherAgainst(g_check, g_respond))
					{
						Sleep(200);
						for (size_t play = 0; play < g_respond.size(); play++)		//对方手牌向场地移动
						{
							g_cbOtherField[zone++] = g_respond.at(play).getPoker();
						}
						for (int h = 0; h < FIELD; h++)		//对方移出去的手牌卡区设置标志位
						{
							if (false == g_cbOtherHand[h].getExit())
							{
								g_cbOtherHand[h].ClearCard();
							}
						}
					}
					else
					{
						g_OtherLife -= g_hurt;
						g_check.clear();
						g_respond.clear();
						if (g_OtherLife <= 0)
						{
							g_OtherLife = 0;
							LifeValue(Other, g_OtherLife);
							RECT givein = { 100, 100, 700, 500 };
							settextstyle(70, 35, _T("华文新魏"));
							drawtext(g_result[1], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU WIN
							Sleep(2000);	//界面停留2秒
							MainMenu();

						}
						LifeValue(Other, g_OtherLife);
						Sleep(1000);
						DealCards(Before);	//先手
					}
					//将场地已出卡牌换成封面
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//将场地已出卡牌换成封面
					for (int m = 0; m < zone; m++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbOtherField[m]);
					}

				}
				else
				{
					HWND hWnd = GetHWnd();
					int msgboxID = MessageBox(hWnd, _T("  反击无效！\n赶紧抢救。。。"), _T("我受伤了！"),
						MB_OK | MB_ICONERROR);				//确定，错误图标
				}
			}
		}
		break;

	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 构造时获取图像：默认宽度、高度均为0（不收缩） 
	带默认形参的函数，声明时说明，定义时不能再有 */
Poker::Poker(LPCTSTR pImgFile, int nWidth, int nHeight)
{	
	//加载卡牌
	//pImageFile_ = pImgFile;
	loadimage(&image_, pImgFile, nWidth, nHeight);

	wstring wcs = pImgFile;
	//获取卡牌点数
	TCHAR wcsPoints[15][10] = {														//点数字符串
		_T("4_"), _T("5_"), _T("6_"), _T("7_"), _T("8_"), _T("9_"), _T("0_"),
		_T("j_"), _T("q_"), _T("k_"),
		_T("1_"), _T("2_"), _T("3_"),
		_T("joker_s"), _T("joker_l") };
	int nPoints[15] = { P4, P5, P6, P7, P8, P9, P10, J, Q, K, A, B, C, SMALL, LARGE };	//与点数对应关系
	int i;
	for (i = 0; i < 15; i++)
	{
		if (wcs.find(wcsPoints[i]) != wstring::npos)
		{
			point_ = nPoints[i];
			break;
		}
	}
	if (i >= 15)
		point_ = 0;
	//获取卡牌花色
	//if (wcs.find(_T("spade")) != wstring::npos) color_ = Spade;
	//else if (wcs.find(_T("heart")) != wstring::npos) color_ = Heart;
	//else if (wcs.find(_T("club")) != wstring::npos) color_ = Club;
	//else if (wcs.find(_T("diamond")) != wstring::npos) color_ = Diamond;
	TCHAR wcsColors[4][10] = { _T("spade"), _T("heart"), _T("club"), _T("diamond") };	//花色字符串
	int nColors[4] = { Spade, Heart, Club, Diamond };									//与花色对应关系
	for (int i = 0; i < 4; i++)
	{
		if (wcs.find(wcsColors[i]) != wstring::npos)
		{
			color_ = nColors[i];
			break;
		}
	}
}

/* 获取卡牌：默认宽度、高度均为0（不收缩）*/
void Poker::ObtainCard(LPCTSTR pImgFile, int nWidth, int nHeight)
{
	loadimage(&image_, pImgFile, nWidth, nHeight);
}

/* 放置卡牌：指定默认宽度80、高度120（放置位置的矩形框大小） */
void Poker::PlaceCard(int dstX, int dstY, int dstWidth, int dstHeight)
{
	//putimage(dstX, dstY, &image_);
	putimage(dstX, dstY, dstWidth, dstHeight, &image_, 0, 0);
}

/* 放置卡牌：指定默认宽度80、高度120（放置位置的矩形框大小）（CardButotn对象）*/
void Poker::PlaceCard(const CardButton& rCbutton, int dstWidth, int dstHeight)
{
	putimage(rCbutton.getLeft(),rCbutton.getTop(), dstWidth, dstHeight, &image_, 0, 0);
}

///* 等于==操作符重载，实现图像匹配*/
//bool Poker::operator ==(const Poker& rPoker)
//{
//	if (0 == wcscmp(pImageFile_, rPoker.getImageFile()))
//		return true;
//	else
//		return false;
//}

