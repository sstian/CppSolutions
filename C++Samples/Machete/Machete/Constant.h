//Constant.h  程序常量头文件
#pragma once

#include <cmath>
#include <vector>
#include "Style.h"

using namespace std;

//单位：像素
/* 窗口参数 */
#define WIDTH		800					//窗口的宽（默认值） 800
#define HEIGHT		600					//窗口的高（默认值） 600
#define SOLUTION	(WIDTH * HEIGHT)	//窗口分辨率 800 * 600

const int HALFW = WIDTH	 / 2;		//窗口的宽二分屏 400
const int HALFH = HEIGHT / 2;		//窗口的高二分屏 300

/* 主菜单界面 */
#define NUMBERS		4		//按钮个数 4
#define DIMENTIONS	2		//坐标维数 2
const int RECT_WIDTH		= 200;	//圆角矩形按钮的宽 200
const int RECT_HEIGHT		= 50;	//圆角矩形按钮的高 50
const int ELLIPSE_WIDTH		= 50;	//圆角矩形的椭圆的宽 50 
const int ELLIPSE_HEIGHT	= 100;	//圆角矩形的椭圆的高 100
const int g_coordinate[NUMBERS][DIMENTIONS] = { 
	{250,200},{250,300},{250,400},{250,500} };			//按钮位置起始坐标：开始、选项、帮助、退出

const TCHAR g_title[10]		= _T("砍  刀");			//游戏标题
const TCHAR g_subtitle[20]	= _T("Machete  v1.0");	//游戏副标题（英文）及版本号

const TCHAR g_menutext[NUMBERS][10] = {
	_T("开 始"),_T("选 项"), _T("帮 助"), _T("退 出") 
};													 //菜单按钮文本

/* 数学常量 */
const double PI = 3.14159265358979323846;	//圆周率

#define RAD(angle) (angle / 180.0 * PI)		//弧度转换宏：将角度转换为弧度 

/* 游戏模式选择界面（五角星窗口）*/
//#define MODE_SINGE	100		//单机模式
//#define MODE_COUPLE 200		//双人模式
//#define MODE_TRIPLE 300		//混战模式
//#define MODE_TEAM	400			//组队模式

const enum Mode { SELECT = 0, SINGLE = 1, COUPLE = 2, TRIPLE = 3, TEAM = 4, BLANK = 10 };	//游戏模式
				//选择提示	  单机模式，  双人模式，  混战模式，  组队模式，//空白区域

#define STARS  5				//五角星的三角形按钮个数 5
#define POINTS 15				//五角星坐标个数 15
const LONG FACTOR = 5;				//五角星坐标补偿因数 5
const LONG RADIUS = 300;			//五角星外接圆的半径（默认值） 300
const LONG REDUCE = 250;			//五角星外接圆的收缩半径 280

const POINT g_stars[POINTS] = {		//五角星顶点坐标
/*下标*/	//角点坐标：最顶为起始点，顺时针方向
/*0  10*/	{ (LONG)(HALFW) 					   , (LONG)(HALFH - RADIUS)                },
/*1  20*/	{ (LONG)(HALFW + RADIUS * cos(RAD(18))), (LONG)(HALFH - RADIUS * sin(RAD(18))) },
/*2  30*/	{ (LONG)(HALFW + RADIUS * sin(RAD(36))), (LONG)(HALFH + RADIUS * cos(RAD(36))) },
/*3  40*/	{ (LONG)(HALFW - RADIUS * sin(RAD(36))), (LONG)(HALFH + RADIUS * cos(RAD(36))) },
/*4  50*/	{ (LONG)(HALFW - RADIUS * cos(RAD(18))), (LONG)(HALFH - RADIUS * sin(RAD(18))) },
			//腰点坐标：最顶偏右为起始点，顺时针方向
/*5  15*/	{ (LONG)(HALFW + (RADIUS - RADIUS * sin(RAD(18))) * tan(RAD(18))), (LONG)(HALFH - RADIUS * sin(RAD(18)))							   },
/*6  25*/	{ (LONG)(HALFW + RADIUS / 2 * tan(RAD(36)))						 , (LONG)(HALFH + RADIUS * sin(RAD(18)) * sin(RAD(18)) / cos(RAD(36))) },
/*7  35*/	{ (LONG)(HALFW)													 , (LONG)(HALFH + RADIUS * sin(RAD(18)) / cos(RAD(36)))				   },
/*8  45*/	{ (LONG)(HALFW - RADIUS / 2 * tan(RAD(36)))						 , (LONG)(HALFH + RADIUS * sin(RAD(18)) * sin(RAD(18)) / cos(RAD(36))) },
/*9  55*/	{ (LONG)(HALFW - (RADIUS - RADIUS * sin(RAD(18)))* tan(RAD(18))) , (LONG)(HALFH - RADIUS * sin(RAD(18)))							   },
			//收缩五角星的交点坐标：最顶为起始点，顺时针方向
/*10  010*/	{ (LONG)(HALFW) 					   , (LONG)(HALFH - REDUCE)                },
/*11  020*/	{ (LONG)(HALFW + REDUCE * cos(RAD(18))), (LONG)(HALFH - REDUCE * sin(RAD(18))) },
/*12  030*/	{ (LONG)(HALFW + REDUCE * sin(RAD(36))), (LONG)(HALFH + REDUCE * cos(RAD(36))) },
/*13  040*/	{ (LONG)(HALFW - REDUCE * sin(RAD(36))), (LONG)(HALFH + REDUCE * cos(RAD(36))) },
/*14  050*/	{ (LONG)(HALFW - REDUCE * cos(RAD(18))), (LONG)(HALFH - REDUCE * sin(RAD(18))) }
};						
//LONG sx = 300 * sin(RAD(18));							//圆心到五角星角三角形的垂直距离
//LONG sy = (300 - 300 * sin(RAD(18))) * tan(RAD(18));	//五角星角三角形底边长的一半
//LONG sz = 300 * sin(RAD(18)) / cos(RAD(36));			//圆心到腰点的连线距离

//const TCHAR g_modeHint[] = _T("请选择游戏模式？");		//游戏模式文本
const TCHAR g_mode[STARS][5] = { { _T("") }, { _T("单机") }, { _T("双人") }, { _T("混战") }, { _T("组队") } };
								//0				//1-0 1			//2-0 1			//3-0 1			//4-0 1

/* 系统参数 */
#define FIELD 5									//对决场地方格数（默认值） 5
#define BLOOD 12								//玩家生命值（默认值） 12
					//手形，	箭头，		十字
const enum Mouse { MOUSE_HAND, MOUSE_ARROW, MOUSE_CROSS };	//鼠标指针形状

const int OUT_W		= 80;		//出牌按钮圆角矩形的宽度
const int OUT_H		= 40;		//出牌按钮圆角矩形的高度
//const int OUT_EW	= 20;		//出牌按钮圆角矩形的椭圆的宽度
//const int OUT_EH	= 40;		//出牌按钮圆角矩形的椭圆的宽度
const TCHAR g_outtext[2][4] = { _T("出牌") ,_T("战斗") };		//出牌按钮文本
const enum Putout { Ensure, Attack };							//出牌选项：出牌、战斗
const enum Draw { Before, After };	//抽牌先后：先攻 VS 后攻
const enum Player { Self, Other };	//玩家：己方 VS 对方

const TCHAR g_result[3][10] = { _T("DRAW"), _T("YOU WIN"), _T("YOU LOSE") };	//决斗结果：平局、胜利、失败

/* 扑克牌 */
#define CARDS	 54			//扑克牌张数（默认值） 54张牌（不包括1张封面）
#define POKER_W	 80			//扑克牌的宽 80
#define POKER_H	120			//扑克牌的高 120

const int DRIFT = POKER_W / 4;	//卡牌浮动高度
const int THICK = 5;			//卡组厚度立体显示

const enum Color { Spade = 1, Heart = 2, Club = 3, Diamond = 4 };										//扑克牌花色
//4 5 6 7 8 9 10 J Q K A B C SMALL LARGE 
const enum Point { P4 = 4, P5 = 5, P6 = 6, P7 = 7, P8 = 8, P9 = 9, P10 = 10,
J = 11, Q = 12, K = 13, A = 14, B = 15, C = 16, SMALL = 1000, LARGE = 2000 };	//扑克牌点数
//11 12 13 % 10 = 1 2 3，//100 200 300 / 100 = 1 2 3，//...

static Poker g_pokers[CARDS + 2] = { Poker(_T("res/images/cover.jpg")),
/*点数/花色*/					//黑桃								//红桃								//梅花									//方块
/*4-  1*/	Poker(_T("res/images/4_spade.jpg")), Poker(_T("res/images/4_heart.jpg")), Poker(_T("res/images/4_club.jpg")), Poker(_T("res/images/4_diamond.jpg")), 
/*5-  5*/	Poker(_T("res/images/5_spade.jpg")), Poker(_T("res/images/5_heart.jpg")), Poker(_T("res/images/5_club.jpg")), Poker(_T("res/images/5_diamond.jpg")),
/*6-  9*/	Poker(_T("res/images/6_spade.jpg")), Poker(_T("res/images/6_heart.jpg")), Poker(_T("res/images/6_club.jpg")), Poker(_T("res/images/6_diamond.jpg")),
/*7- 13*/	Poker(_T("res/images/7_spade.jpg")), Poker(_T("res/images/7_heart.jpg")), Poker(_T("res/images/7_club.jpg")), Poker(_T("res/images/7_diamond.jpg")),
/*8- 17*/	Poker(_T("res/images/8_spade.jpg")), Poker(_T("res/images/8_heart.jpg")), Poker(_T("res/images/8_club.jpg")), Poker(_T("res/images/8_diamond.jpg")),
/*9- 21*/	Poker(_T("res/images/9_spade.jpg")), Poker(_T("res/images/9_heart.jpg")), Poker(_T("res/images/9_club.jpg")), Poker(_T("res/images/9_diamond.jpg")),
/*10-25*/	Poker(_T("res/images/0_spade.jpg")), Poker(_T("res/images/0_heart.jpg")), Poker(_T("res/images/0_club.jpg")), Poker(_T("res/images/0_diamond.jpg")),
/*J- 29*/	Poker(_T("res/images/j_spade.jpg")), Poker(_T("res/images/j_heart.jpg")), Poker(_T("res/images/j_club.jpg")), Poker(_T("res/images/j_diamond.jpg")),
/*Q- 33*/	Poker(_T("res/images/q_spade.jpg")), Poker(_T("res/images/q_heart.jpg")), Poker(_T("res/images/q_club.jpg")), Poker(_T("res/images/q_diamond.jpg")),
/*K- 37*/	Poker(_T("res/images/k_spade.jpg")), Poker(_T("res/images/k_heart.jpg")), Poker(_T("res/images/k_club.jpg")), Poker(_T("res/images/k_diamond.jpg")),
/*A- 41*/	Poker(_T("res/images/1_spade.jpg")), Poker(_T("res/images/1_heart.jpg")), Poker(_T("res/images/1_club.jpg")), Poker(_T("res/images/1_diamond.jpg")),
/*2- 45*/	Poker(_T("res/images/2_spade.jpg")), Poker(_T("res/images/2_heart.jpg")), Poker(_T("res/images/2_club.jpg")), Poker(_T("res/images/2_diamond.jpg")),
/*3- 49*/	Poker(_T("res/images/3_spade.jpg")), Poker(_T("res/images/3_heart.jpg")), Poker(_T("res/images/3_club.jpg")), Poker(_T("res/images/3_diamond.jpg")),
/*SL-53*/	Poker(_T("res/images/joker_small.jpg")), Poker(_T("res/images/joker_large.jpg")),
/*zone-55*/	Poker(_T("res/images/zone.jpg"))
};												//一副扑克牌

/* 全局变量声明 */
extern int g_DeckThick;				//卡组厚度，显示立体效果
extern CardButton g_cbDeck;			//卡组区
extern vector<CardButton> g_cbOtherHand;	//对方手牌区
extern vector<CardButton> g_cbOtherField;	//对方场地区
extern vector<CardButton> g_cbSelfField;	//己方场地区
extern vector<CardButton> g_cbSelfHand;		//己方手牌区
//extern RECT g_rectOtherHint;				//对方出牌提示
//extern RECT g_rectSelfHint;				//己方出牌提示
extern int g_OtherLife;			//对方生命数值
extern int g_SelfLife;			//己方生命数值
extern vector<CardButton> g_check;		//打出去的牌
extern vector<CardButton> g_respond;	//对方响应的牌
extern int g_hurt;						//伤害计数器
extern int g_defend;					//反击计数器
