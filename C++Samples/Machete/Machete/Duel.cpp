//Duel.cpp  决斗 源文件
#include <cmath>
#include <ctime>
#include <vector>
#include <graphics.h>
#include "Constant.h"
#include "Duel.h"
#include "Style.h"

//using namespace std;

//游戏决斗全局变量数据区
//////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CardButton> g_cbOtherHand(FIELD);	//对方手牌区
vector<CardButton> g_cbOtherField(FIELD);	//对方场地区
vector<CardButton> g_cbSelfField(FIELD);	//己方场地区
vector<CardButton> g_cbSelfHand(FIELD);		//己方手牌区
CardButton g_cbDeck(65, 243, 65 + POKER_W, 243 + POKER_H);		//卡组区
OutButton  g_obEnsure = { 710, 466, 710 + OUT_W, 466 + OUT_H };		//出牌按钮
OutButton  g_obAttack = { 710, 526, 710 + OUT_W, 526 + OUT_H };		//战斗按钮
Button	   g_btnOtherLife[BLOOD];									//对方血条
Button	   g_btnSelfLife[BLOOD];									//己方血条
RECT g_rectOtherLife = { 20, 24, 200, 84 };						//对方生命数值区
RECT g_rectSelfLife  = { 20, HEIGHT - 84, 200, HEIGHT - 24 };	//己方生命数值区
RECT g_rectOtherName = { 20, 144 , 200, 228 };					//对方玩家名字区
RECT g_rectSelfName  = { 20, HEIGHT - 228, 200, HEIGHT - 144 };	//己方玩家名字区
//RECT g_rectOtherHint;										//对方出牌提示
//RECT g_rectSelfHint;										//己方出牌提示
RECT g_rectDeckCount = { 150, 273, 210, 333 };					//卡牌数目区
int g_DeckCard  = CARDS - 10;		//卡组剩余卡牌计数器
int g_DeckThick;					//卡组厚度，显示立体效果  //= THICK
int g_OtherLife = BLOOD;			//对方生命数值
int g_SelfLife  = BLOOD;			//己方生命数值
TCHAR g_OtherName[20] = _T("King");	//对方玩家名字
TCHAR g_SelfName[20]  = _T("Jack");	//己方玩家名字
enum Draw g_Draw = Before;				//玩家抽牌顺序
//Poker g_PokersCopy[CARDS - 1];		//卡组副本
vector<Poker> g_PokersCopy;				//卡组副本；54张卡牌（使用向量代替数组，可以自动调整大小和顺序）
vector<CardButton> g_check;		//打出去的牌
vector<CardButton> g_respond;	//对方响应的牌
int g_hurt;						//伤害计数器
int g_defend;					//反击计数器
////////////////////////////////////////////////////////////////////////////////////////////////////

/* 开始游戏 */
void StartGame()
{
	//MessageBox(NULL, _T("游戏"), _T("开启新的旅途！"), MB_OK);
	cleardevice();
	//HWND hWnd = Button::MouseShape(MOUSE_ARROW);

	//while (true)
	{
		SelectMode();
	}
}

/* 选择游戏模式：单机（可用），双人，混战，组队 */
void SelectMode()
{	
	///获取窗口句柄，恢复为默认的箭头鼠标指针
	HWND hWnd = Button::MouseShape(MOUSE_ARROW);

	//联合坐标补偿：x轴边框宽度，y轴边框高度、标题栏高度，试验补偿因数
	int cxf = GetSystemMetrics(SM_CXFIXEDFRAME) + FACTOR;									//3 + 6
	int cyf = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION) + FACTOR;	//3 + 23 + 6
	////数值测定
	//TCHAR sysinfo[10];
	//swprintf(sysinfo, _T("%d"), GetSystemMetrics(SM_CXFIXEDFRAME));
	//outtextxy(100, 100, sysinfo);
	//swprintf(sysinfo, _T("%d"), GetSystemMetrics(SM_CYFIXEDFRAME));
	//outtextxy(100, 200, sysinfo);
	//swprintf(sysinfo, _T("%d"), GetSystemMetrics(SM_CYCAPTION));
	//outtextxy(100, 300, sysinfo);

	POINT points[5] = {	
		{ (LONG)(HALFW - RADIUS * cos(RAD(18)) + cxf), (LONG)(HALFH - RADIUS * sin(RAD(18)) + cyf) },	//5
		{ (LONG)(HALFW + RADIUS * cos(RAD(18)) + cxf), (LONG)(HALFH - RADIUS * sin(RAD(18)) + cyf) },	//2
		{ (LONG)(HALFW - RADIUS * sin(RAD(36)) + cxf), (LONG)(HALFH + RADIUS * cos(RAD(36)) + cyf) },	//4
		{ (LONG)(HALFW + cxf)						 , (LONG)(HALFH - RADIUS + cyf)                },	//1 最上为顶点，顺时针方向
		{ (LONG)(HALFW + RADIUS * sin(RAD(36)) + cxf), (LONG)(HALFH + RADIUS * cos(RAD(36)) + cyf) }	//3
	};	//多边形（五角星）窗口点的坐标。需要联合补偿因数！
	///创建多边形裁剪区：以整个窗口左上角为原点（包括边框和标题栏）
	HRGN hRgn = CreatePolygonRgn(points, 5, WINDING);	//ALTERNATE可设置五角星中间镂空
	///设置窗口区域
	SetWindowRgn(hWnd, hRgn, true);	 ///int SetWindowRgn(HWND hWnd, HRGN hRgn, BOOL bRedraw); 
	//DeleteObject(hRgn);		//清理hRgn占用的系统资源

	////五角星内线
	//pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72 * 1) / 180.0*PI);
	//pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72 * 2) / 180.0*PI);
	//pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72 * 3) / 180.0*PI);
	//pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72 * 4) / 180.0*PI);

	//加载五角星窗口背景图
	loadimage(NULL, _T("res/images/starsky.jpg"));	
	
	StarButton sbutton[STARS + 1];				//游戏模式对象数组 5+1 = 0（文本提示） 1 2 3 4 5（空白区）
	POINT pts_star[STARS][3] = {				//五角星三角形按钮：点二的x < 点三的x
		{ g_stars[0], g_stars[9], g_stars[5] },	//0-“选择游戏模式”
		{ g_stars[4], g_stars[8], g_stars[9] },	//1-单机
		{ g_stars[1], g_stars[5], g_stars[6] },	//2-双人
		{ g_stars[2], g_stars[7], g_stars[6] },	//3-混战
		{ g_stars[3], g_stars[8], g_stars[7] }	//4-组队
	};
	//游戏模式文本
	LOGFONT font;
	gettextstyle(&font);
	font.lfQuality = ANTIALIASED_QUALITY;	//设置抗锯齿质量
	settextstyle(&font);
		//选择文本提示
	settextcolor(RGB(253, 6, 204));			//字体颜色：偏紫红色
	settextstyle(30, 20, _T("华文彩云"));
	outtextxy(380, 110, _T("请"));
	outtextxy(352, 160, _T("选 择"));
	settextstyle(30, 20, _T("华文琥珀"));
	outtextxy(313, 230, _T("游戏模式"));
	settextstyle(50, 30, _T("华文彩云"));
	outtextxy(385, 285, _T("？"));
		//游戏模式选项
	settextstyle(50, 30, _T("华文新魏"));
	settextcolor(RGB(242,250,36));			//字体颜色：偏金黄色
	outtextxy(180, 215, g_mode[1][0]);		//"单"
	outtextxy(240, 240, g_mode[1][1]);		//"机"
	outtextxy(490, 240, g_mode[2][0]);		//"双"
	outtextxy(550, 215, g_mode[2][1]);		//"人"
	outtextxy(440, 375, g_mode[3][0]);		//"混"
	outtextxy(470, 430, g_mode[3][1]);		//"战"
	outtextxy(285, 375, g_mode[4][0]);		//"组"
	outtextxy(250, 430, g_mode[4][1]);		//"队"

	//初始化星型按钮对象数组
	for (int i = 0; i < STARS; i++)
	{
		sbutton[i].SetStar(pts_star[i]);	
	}
	//模式选中效果
	while (true)	//必须在无限循环中自定义形状地窗口才能保存！
	{
		MOUSEMSG m = StarButton::MouseMsg();		//获取鼠标消息
		////获取鼠标相对窗口的坐标
		//clearrectangle(400, 200, 520, 350);
		//TCHAR pos[10];
		//swprintf(pos, _T("%d"), m.x);
		//outtextxy(350, 200, _T("X: "));
		//outtextxy(400, 200, pos);
		//swprintf(pos, _T("%d"), m.y);
		//outtextxy(350, 300, _T("Y: "));
		//outtextxy(400, 300, pos);

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:		//鼠标移动选择游戏模式
			BeginBatchDraw();
			if(sbutton[0].IsWithin(SELECT))		
				///发送消息
				//如果左键按下，欺骗 windows 点在了标题栏上。
				//WM_LBUTTONDOWN是在“客户区”按下鼠标的消息，WM_NCLBUTTONDOWN是在“非客户区”按下鼠标的消息，
				//非客户区：包括“标题栏”，“窗口边框”，“滚动条”等。
				PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(m.x, m.y));
			else if (sbutton[1].IsWithin(SINGLE))	sbutton[1].MouseMove(SINGLE);
			else if (sbutton[2].IsWithin(COUPLE))	sbutton[2].MouseMove(COUPLE);
			else if (sbutton[3].IsWithin(TRIPLE))	sbutton[3].MouseMove(TRIPLE);
			else if (sbutton[4].IsWithin(TEAM))		sbutton[4].MouseMove(TEAM);  //？选不中。改为矩形框！

			//else if (sbutton[5].IsWithin(BLANK))	sbutton[5].MouseMove(BLANK);
			else
			{
				sbutton[1].MouseLeave(SINGLE);
				sbutton[2].MouseLeave(COUPLE);
				sbutton[3].MouseLeave(TRIPLE);
				sbutton[4].MouseLeave(TEAM);

				//sbutton[5].MouseLeave(BLANK);
			}
			EndBatchDraw();
			break;
		case WM_LBUTTONDOWN:		//鼠标左键按下进入相应模式界面，开始决斗
				 if (sbutton[1].IsWithin(SINGLE))	SingleMode();
			else if (sbutton[2].IsWithin(COUPLE))	CoupleMode();
			else if (sbutton[3].IsWithin(TRIPLE))	TripleMode();
			else if (sbutton[4].IsWithin(TEAM))		TeamMode();
			break;
		case WM_RBUTTONUP:			//按鼠标右键返回到主菜单界面
			MainMenu();
			break;
		default:
			break;
		}
	}
}

/* 游戏初始化*/
void GameInit()
{
	loadimage(NULL, _T("res/images/duel.jpg"));		//加载决斗背景图
	//设置初始参数
	//
	//设置双方的手牌与场地区域
	for (int i = 0; i < 4; i++)				//4行
		for (int j = 0; j < FIELD; j++)		//5列
		{
			switch (i)
			{
			case 0:
				g_cbOtherHand[j].SetRect(220 + 100 * j, 24 + 144 * i, 300 + 100 * j, 144 + 144 * i); break;
			case 1:
				g_cbOtherField[j].SetRect(220 + 100 * j, 24 + 144 * i, 300 + 100 * j, 144 + 144 * i); break;
			case 2:
				g_cbSelfField[j].SetRect(220 + 100 * j, 24 + 144 * i, 300 + 100 * j, 144 + 144 * i); break;
			case 3:
				g_cbSelfHand[j].SetRect(220 + 100 * j, 24 + 144 * i, 300 + 100 * j, 144 + 144 * i); break;
			default:
				break;
			}
		}
	////设置双方出牌提示区域
	//RECT rectOtherHint	= { g_cbOtherField[1].getLeft(), g_cbOtherField[1].getTop(),
	//	g_cbOtherField[3].getRight(), g_cbOtherField[3].getBottom() };				//对方出牌提示
	//RECT rectSelfHint	= { g_cbSelfField[1].getLeft(), g_cbSelfField[1].getTop(),
	//	g_cbSelfField[3].getRight(), g_cbSelfField[3].getBottom() };				//己方出牌提示
	//g_rectOtherHint = rectOtherHint;
	//g_rectSelfHint	= rectSelfHint;
	//建立卡组副本
	vector<Poker> pokersTemp;	//临时卡组存储
	for (int copy = 1; copy <= CARDS; copy++)	//1 -- 54
		pokersTemp.push_back(g_pokers[copy]);
		//生成卡牌随机放置顺序的决斗卡组
	srand((unsigned int)time(NULL));	
	int random;
	for(int card = CARDS; g_PokersCopy.size() < CARDS; card--)
	{
		random = rand() % card;	//0 -- 53
		g_PokersCopy.push_back(pokersTemp.at(random));	//pokersTemp.at(random) <==> pokersTemp[random]，但比后者安全
		pokersTemp.erase(pokersTemp.begin() + random);	//pokersTemp.begin() + random <==> pokersTemp下标为[random]
	}
	//双方发牌动画
	for (int anime = 0; anime < FIELD; anime++)
	{
		if (Before == g_Draw)	//己方先攻
		{
			DrawSelf(anime);
			DrawOther(anime);
		}
		else
		{
			DrawOther(anime);
			DrawSelf(anime);
		}
	}
	//设置双方血条区域
	for (int hp = 0; hp < BLOOD; hp++)
	{
		g_btnOtherLife[hp].SetRect(20 + 15 * hp, 84, 30 + 15 * hp, 144);
		g_btnSelfLife[hp].SetRect(20 + 15 * hp, 456, 30 + 15 * hp, 516);
		setfillcolor(RGB(248, 91, 239));	//血条颜色：偏粉红色
		fillrectangle(g_btnOtherLife[hp].getLeft(), g_btnOtherLife[hp].getTop(),
			g_btnOtherLife[hp].getRight(), g_btnOtherLife[hp].getBottom());
		fillrectangle(g_btnSelfLife[hp].getLeft(), g_btnSelfLife[hp].getTop(),
			g_btnSelfLife[hp].getRight(), g_btnSelfLife[hp].getBottom());
	}
	//绘制生命数值、血条，立体卡组显示、卡组数目
	LifeValue(Self, BLOOD);
	LifeValue(Other, BLOOD);
	DeckCount();
	//显示玩家名字
	settextcolor(RGB(242, 250, 36));			//字体颜色：偏金黄色
	drawtext(g_OtherName, &g_rectOtherName, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(g_SelfName, &g_rectSelfName, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//分发双方手牌
	for (int dr = 0; dr < FIELD; dr++)
	{
		if (Before == g_Draw)	//己方先攻
		{
			g_cbSelfHand[dr] = g_PokersCopy.front();
			g_cbSelfHand[dr].setDown(false);	//初始化标志位：为选中，存在
			g_cbSelfHand[dr].setExit(true);
			g_PokersCopy.erase(g_PokersCopy.begin());
			g_cbOtherHand[dr] = g_PokersCopy.front();
			g_cbOtherHand[dr].setDown(false);
			g_cbOtherHand[dr].setExit(true);
			g_PokersCopy.erase(g_PokersCopy.begin());
		}
		else					//己方后攻，即对方先攻
		{
			g_cbOtherHand[dr] = g_PokersCopy.front();
			g_cbOtherHand[dr].setDown(false);
			g_cbOtherHand[dr].setExit(true);
			g_PokersCopy.erase(g_PokersCopy.begin());
			g_cbSelfHand[dr] = g_PokersCopy.front();
			g_cbSelfHand[dr].setDown(false);	
			g_cbSelfHand[dr].setExit(true);
			g_PokersCopy.erase(g_PokersCopy.begin());
		}
	}

	//g_cbSelfHand[0] = g_pokers[1];
	//g_cbSelfHand[0].setDown(false);	//初始化标志位：为选中，存在
	//g_cbSelfHand[0].setExit(true);

	//g_cbSelfHand[1] = g_pokers[2];
	//g_cbSelfHand[1].setDown(false);	
	//g_cbSelfHand[1].setExit(true);

	//g_cbSelfHand[2] = g_pokers[5];
	//g_cbSelfHand[2].setDown(false);	
	//g_cbSelfHand[2].setExit(true);

	//g_cbSelfHand[3] = g_pokers[6];
	//g_cbSelfHand[3].setDown(false);	
	//g_cbSelfHand[3].setExit(true);

	//g_cbSelfHand[4] = g_pokers[49];
	//g_cbSelfHand[4].setDown(false);	
	//g_cbSelfHand[4].setExit(true);

	//g_cbOtherHand[0] = g_pokers[25];
	//g_cbOtherHand[0].setDown(false);	//初始化标志位：为选中，存在
	//g_cbOtherHand[0].setExit(true);

	//g_cbOtherHand[1] = g_pokers[26];
	//g_cbOtherHand[1].setDown(false);	//初始化标志位：为选中，存在
	//g_cbOtherHand[1].setExit(true);

	//g_cbOtherHand[2] = g_pokers[29];
	//g_cbOtherHand[2].setDown(false);	//初始化标志位：为选中，存在
	//g_cbOtherHand[2].setExit(true);

	//g_cbOtherHand[3] = g_pokers[30];
	//g_cbOtherHand[3].setDown(false);	//初始化标志位：为选中，存在
	//g_cbOtherHand[3].setExit(true);

	//g_cbOtherHand[4] = g_pokers[51];
	//g_cbOtherHand[4].setDown(false);	//初始化标志位：为选中，存在
	//g_cbOtherHand[4].setExit(true);

	//升序排列手牌
	ShuffleHand();
}

/* 己方先抽牌 i: 手牌区下标 */
void DrawSelf(int i)
{
	int xs = g_cbDeck.getLeft();
	int ys = g_cbDeck.getTop();
	for (int r = 0; xs != g_cbSelfHand[i].getLeft() || ys != g_cbSelfHand[i].getTop(); r++)
	{
		int dxs = labs(g_cbDeck.getLeft() - g_cbSelfHand[i].getLeft());
		int dys = labs(g_cbDeck.getTop() - g_cbSelfHand[i].getTop());
		xs = g_cbDeck.getLeft() + dxs / 100 * r++;
		ys = g_cbDeck.getTop() + dys / 100 * r++;
		g_pokers[0].PlaceCard(xs, ys);
		loadimage(NULL, _T("res/images/duel.jpg"));		//加载决斗背景图
		if (xs >= g_cbSelfHand[i].getLeft()) xs = g_cbSelfHand[i].getLeft();
		if (ys >= g_cbSelfHand[i].getTop()) ys = g_cbSelfHand[i].getTop();
	}
}

/* 对方先抽牌 i: 手牌区下标 */
void DrawOther(int i)
{
	int xo = g_cbDeck.getLeft();
	int yo = g_cbDeck.getTop();
	for (int t = 0; xo != g_cbOtherHand[i].getLeft() || yo != g_cbOtherHand[i].getTop(); t++)
	{
		int dxo = labs(g_cbDeck.getLeft() - g_cbOtherHand[i].getLeft());
		int dyo = labs(g_cbDeck.getTop() - g_cbOtherHand[i].getTop());
		xo = g_cbDeck.getLeft() + dxo / 100 * t++;
		yo = g_cbDeck.getTop() - dyo / 100 * t++;
		g_pokers[0].PlaceCard(xo, yo);
		loadimage(NULL, _T("res/images/duel.jpg"));		//加载决斗背景图
		if (xo >= g_cbOtherHand[i].getLeft()) xo = g_cbOtherHand[i].getLeft();
		if (yo <= g_cbOtherHand[i].getTop()) yo = g_cbOtherHand[i].getTop();
	}
}

/* 重绘双方生命数值、血条 
 player: 玩家；value: 剩余生命值 */
void LifeValue(int player, int value)
{
	TCHAR life[4];
	settextcolor(RGB(88, 242, 88));		//字体颜色：偏绿色
	settextstyle(50, 30, _T("华文彩云"));
	setfillcolor(RGB(6, 4, 51));		//填充颜色：偏黑蓝色
	switch (player)
	{
	case Self:		//己方生命
		solidellipse(g_rectSelfLife.left, g_rectSelfLife.top, g_rectSelfLife.right, g_rectSelfLife.bottom);
		swprintf_s(life, _T("%d"), value);
		drawtext(life, &g_rectSelfLife, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		setfillcolor(RGB(100, 122, 169));		//血条扣减颜色：偏灰蓝色
		for (int hp = value; hp < BLOOD; hp++)
		{
			fillrectangle(g_btnSelfLife[hp].getLeft(), g_btnSelfLife[hp].getTop(),
				g_btnSelfLife[hp].getRight(), g_btnSelfLife[hp].getBottom());
		}
		break;
	case Other:		//对方生命
		solidellipse(g_rectOtherLife.left, g_rectOtherLife.top, g_rectOtherLife.right, g_rectOtherLife.bottom);
		swprintf_s(life, _T("%d"), value);
		drawtext(life, &g_rectOtherLife, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		setfillcolor(RGB(100, 122, 169));		//血条扣减颜色：偏灰蓝色
		for (int hp = value; hp < BLOOD; hp++)
		{
			fillrectangle(g_btnOtherLife[hp].getLeft(), g_btnOtherLife[hp].getTop(),
				g_btnOtherLife[hp].getRight(), g_btnOtherLife[hp].getBottom());
		}
		break;
	default:
		break;
	}
}

/* 重绘卡组计数、卡组立体动态显示 */
void DeckCount()
{
	//卡牌数目
	setfillcolor(RGB(186, 188, 237));	//偏青灰色
	solidcircle((g_rectDeckCount.left + g_rectDeckCount.right) / 2, (g_rectDeckCount.top + g_rectDeckCount.bottom) / 2, 30);
	TCHAR card[4];
	swprintf_s(card, _T("%d"), g_DeckCard);
	settextstyle(40, 20, _T("华文新魏"));
	settextcolor(RGB(129, 247, 58));			//字体颜色：偏草绿色
	drawtext(card, &g_rectDeckCount, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//立体卡组动态显示
	g_DeckThick = g_DeckCard / 10;
	if (0 == g_DeckThick)
		g_DeckThick = 1;
	for (int d = 0; d < g_DeckThick; d++)
		g_pokers[0].PlaceCard(g_cbDeck.getLeft() - d, g_cbDeck.getTop() - d);
}

/* 手牌重置 */
void RightDown()
{
	FlushMouseMsgBuffer();
	g_Draw = After;		//对方为先手
	g_check.clear();	//清空出牌表
	g_respond.clear();
	for (int r = 0; r < FIELD; r++)		//己方手牌重置
	{
		if (true == g_cbSelfHand[r].getDown())
		{
			g_cbSelfHand[r].setDown(false);
			g_cbSelfHand[r].getPoker().PlaceCard(g_cbSelfHand[r]);
		}
	}
	if (g_hurt != 0)
	{
		g_SelfLife -= g_hurt;
		g_hurt = 0;
		LifeValue(Self, g_SelfLife);
	}
	DealCards(g_Draw);
	ShuffleHand();
	OtherStart();
}

/* 对方先攻 */
void OtherStart()
{
	if (After == g_Draw)
	{
		g_cbOtherField[0] = g_cbOtherHand[0].getPoker();
		g_respond.push_back(g_cbOtherHand[0]);
		g_cbOtherHand[0].setExit(false);
		g_cbOtherHand[0].ClearCard();
		Sleep(300);
		g_pokers[0].PlaceCard(g_cbOtherField[0]);
	}
}

/* 卡牌交换 */
void SwapCard(CardButton& src, CardButton& dst)
{
	Poker temp;
	temp = src.getPoker();
	src.setPoker(dst.getPoker());
	dst.setPoker(temp);
}

/* 洗牌：双方手牌按点数从小到大的升序排列（从左到右）*/
void ShuffleHand()
{	
	//?选择法排序，以提高运行效率,但是并不能完全正确运算
	//改用冒泡排序算法！
	for (int i = 0; i < FIELD - 1; i++)
	{
		for (int j = i + 1; j < FIELD; j++)
		{
			if (g_cbSelfHand[i].GetPoint() > g_cbSelfHand[j].GetPoint())	//己方
			{
				SwapCard(g_cbSelfHand[i], g_cbSelfHand[j]);
			}
			if (g_cbOtherHand[i].GetPoint() > g_cbOtherHand[j].GetPoint())	//己方
			{
				SwapCard(g_cbOtherHand[i], g_cbOtherHand[j]);
			}
		}
	}
	for (int put = 0; put < FIELD; put++)
	{
		g_cbOtherHand[put].getPoker().PlaceCard(g_cbOtherHand[put]);
		g_pokers[0].PlaceCard(g_cbOtherHand[put]);	//对方手牌不显示，#只是将封面覆盖原有卡牌，不改变原有卡牌参数
	}
	Sleep(500);	//手牌重新放置，延迟0.5秒
	for (int put = 0; put < FIELD; put++)
	{
		g_cbSelfHand[put].getPoker().PlaceCard(g_cbSelfHand[put]);
	}
}


/* 重新分发手牌够5张 */
void DealCards(int draw)
{
	if (0 == g_PokersCopy.size())
	{
			setlinestyle(PS_SOLID, 0);
			LifeValue(Self, 0);
			RECT givein = { 100, 100, 700, 500 };
			settextstyle(70, 35, _T("华文新魏"));
			drawtext(g_result[0], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//DRAW
			Sleep(2000);	//界面停留2秒
			MainMenu();
	}
	g_Draw = (enum Draw)draw;
	if (Before == g_Draw)	//己方先手
	{
		for (int hand = 0; hand < FIELD; hand++)
		{
			if (false == g_cbSelfHand[hand].getExit())
			{
				g_cbSelfHand[hand] = g_PokersCopy.front();
				g_cbSelfHand[hand].setDown(false);
				g_cbSelfHand[hand].setExit(true);
				g_PokersCopy.erase(g_PokersCopy.begin());
			}
		}
		for (int show = 0; show < FIELD; show++)
		{
			if (false == g_cbOtherHand[show].getExit())
			{
				g_cbOtherHand[show] = g_PokersCopy.front();
				g_cbOtherHand[show].setDown(false);
				g_cbOtherHand[show].setExit(true);
				g_PokersCopy.erase(g_PokersCopy.begin());
			}
		}
	}
	else					//己方后手，即对方先手
	{
		for (int show = 0; show < FIELD; show++)
		{
			if (false == g_cbOtherHand[show].getExit())
			{
				g_cbOtherHand[show] = g_PokersCopy.front();
				g_cbOtherHand[show].setDown(false);
				g_cbOtherHand[show].setExit(true);
				g_PokersCopy.erase(g_PokersCopy.begin());
			}
		}
		for (int hand = 0; hand < FIELD; hand++)
		{
			if (false == g_cbSelfHand[hand].getExit())
			{
				g_cbSelfHand[hand] = g_PokersCopy.front();
				g_cbSelfHand[hand].setDown(false);
				g_cbSelfHand[hand].setExit(true);
				g_PokersCopy.erase(g_PokersCopy.begin());
			}
		}
	}
	ShuffleHand();
	g_DeckCard = g_PokersCopy.size();
	DeckCount();
}
/* 出牌牌型检验 */
bool CheckOut(vector<CardButton>& check)
{
	bool flag = false;
	g_check.clear();	//清空出牌表
	for (int hand = 0; hand < FIELD; hand++)
	{
		if (true == g_cbSelfHand[hand].getDown())
		{
			check.push_back(g_cbSelfHand[hand]);
		}
	}
	int size = check.size();	//出牌张数
	if (size != 0)
	{
		enum Point next = (enum Point)(check[0].GetPoint());	//顺子判断
		int start = check[0].GetPoint();						//组同判断
		switch (size)
		{
		case 1:		//单张牌
			flag = true;
			break;
		case 2:		//一对儿
			if (check[0].GetPoint() == check[1].GetPoint())
				flag = true;
			else
				flag = false;
			break;
		case 3:		//三同 或 三顺子
			if (start == check[1].GetPoint() && start == check[2].GetPoint())
				flag = true;
			//else if (P4 == check[0].GetPoint() && B == check[1].GetPoint() && C == check[2].GetPoint())
			//{	//4 2 3
			//	flag = true;
			//	check.push_back(check.front());  //->2 3 4
			//	check.erase(check.begin());
			//}
			//else if (P4 == check[0].GetPoint() && P5 == check[1].GetPoint() && C == check[2].GetPoint())
			//{	 //4 5 3
			//	flag = true;
			//	check.insert(check.begin(), check.at(check.size() - 1));  //->3 4 5
			//	check.pop_back();
			//}
			else
			{
				int s;
				for (s = 0; s < size - 1; s++)
				{
					next = (enum Point)(next + 1);
					if (next != check[s + 1].GetPoint())
					{
						flag = false;
						break;
					}
				}
				if (s >= size - 1)
					flag = true;
			}
			break;
		case 4:		//姊妹对儿 或 四同 或 四顺子 
					//22 33对。33 44错！
			if (check[0].GetPoint() == check[1].GetPoint() && check[2].GetPoint() && check[3].GetPoint() && check[2].GetPoint() == check[1].GetPoint() + 1)
				flag = true;
			else if (start == check[1].GetPoint() && start == check[2].GetPoint() && start == check[3].GetPoint())
				flag = true;
			//else if (P4 == check[0].GetPoint() && A == check[1].GetPoint() && B == check[2].GetPoint() && C == check[3].GetPoint())
			//{	// 4 A 2 3
			//	flag = true;
			//	check.push_back(check.front());  //->A 2 3 4
			//	check.erase(check.begin());
			//}
			//else if (P4 == check[0].GetPoint() && P5 == check[1].GetPoint() && B == check[2].GetPoint() && C == check[3].GetPoint())
			//{	// 4 5 2 3
			//	flag = true;
			//	check.insert(check.begin(), check.at(check.size() - 1));  //->2 3 4 5 
			//	check.pop_back();
			//	check.insert(check.begin(), check.at(check.size() - 1));
			//	check.pop_back();
			//}
			//else if (P4 == check[0].GetPoint() && P5 == check[1].GetPoint() && P6 == check[2].GetPoint() && C == check[3].GetPoint())
			//{	// 4 5 6 3
			//	flag = true;
			//	check.insert(check.begin(), check.at(check.size() - 1));  //->3 4 5 6
			//	check.pop_back();
			//}
			else
			{
				int s;
				for (s = 0; s < size - 1; s++)
				{
					next = (enum Point)(next + 1);
					if (next != check[s + 1].GetPoint())
					{
						flag = false;
						break;
					}
				}
				if (s >= size - 1)
					flag = true;
			}
			break;
		case 5:		//炸弹（五顺子）MIN=4 5 6 7 8 -> MAX=Q K A 2 3
			//if (P4 == check[0].GetPoint() && P5 == check[1].GetPoint() && A == check[2].GetPoint() && B == check[3].GetPoint() && C == check[4].GetPoint())
			//{	//4 5 A 2 3
			//	flag = true;
			//	check.push_back(check.front());  //->A 2 3 4 5
			//	check.erase(check.begin());
			//	check.push_back(check.front());
			//	check.erase(check.begin());
			//}
			//else if (P4 == check[0].GetPoint() && P5 == check[1].GetPoint() && P6 == check[2].GetPoint() && B == check[3].GetPoint() && C == check[4].GetPoint())
			//{	// 4 5 6 2 3
			//	flag = true;
			//	check.insert(check.begin(), check.at(check.size() - 1));  //->2 3 4 5 6
			//	check.pop_back();
			//	check.insert(check.begin(), check.at(check.size() - 1));
			//	check.pop_back();
			//}
			//else if (P4 == check[0].GetPoint() && P5 == check[1].GetPoint() && P6 == check[2].GetPoint() && P7 == check[3].GetPoint() && C == check[4].GetPoint())
			//{	//4 5 6 7 3
			//	flag = true;
			//	check.insert(check.begin(), check.at(check.size() - 1));  //->3 4 5 6 7
			//	check.pop_back();
			//}
			int s;
			for (s = 0; s < size - 1; s++)
			{
				next = (enum Point)(next + 1);
				if (next != check[s + 1].GetPoint())
				{
					flag = false;
					break;
				}
			}
			if (s >= size - 1)
				flag = true;

			break;
		default:
			break;
		}
	}
	else
	{
		flag = false;
	}
	return flag;
}

/* 战斗牌型检验 */
bool CheckAttack(vector<CardButton>& check)
{
	bool flag = true;
	for (int hand = 0; hand < FIELD; hand++)
	{
		if (true == g_cbSelfHand[hand].getDown())
		{
			check.push_back(g_cbSelfHand[hand]);
		}
	}
	if (check.size() != 0)
	{
		vector<CardButton>::iterator it;
		for (it = check.begin(); it != check.end(); it++)
		{
			int pt = (*it).GetPoint();
			if (pt != J && pt != Q && pt != K && pt != SMALL && pt != LARGE)
			{
				flag = false;
				break;
			}
		}
		//int at;
		//for (at = 0; at < check.size(); at++)
		//{
		//	int pt = check.at(at).GetPoint();
		//	if(pt != J && pt != Q && pt != K && pt != SMALL && pt != LARGE)
		//	{
		//		flag = false;
		//		break;
		//	}
		//}
		//if (at >= check.size())
		//	flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}

/* 对方压牌 
   play: 玩家出牌表；respond: 响应压牌表 */
bool OtherProduce(vector<CardButton>& play, vector<CardButton>& respond)
{
	bool flag = false;	//是否压牌标志位
	bool find = false;	//是否存在对应牌型标志位
	int first, second, third, fourth;	//第一、二、三、四张要打出的手牌
	//int seq;							//同花顺首张牌的点数
	int size = play.size();				//出牌张数
	respond.clear();	//清空对方出牌表
	switch (size)
	{
	case 1:		//单张 7
		for (first = 0; first < FIELD;first++)
		{
			if (g_cbOtherHand[first].GetPoint() > play.front().GetPoint())
			{
				respond.push_back(g_cbOtherHand[first]);
				g_cbOtherHand[first].setExit(false);
				for (second = first + 1; second < FIELD; second++)
				{
					if (g_cbOtherHand[second].GetPoint() == respond.front().GetPoint())
					{
						respond.clear();
						g_cbOtherHand[first].setExit(true);
						first = second + 1;
						break;
					}
				}
				if (second >= FIELD)
				{
					find = true;
					flag = true;
					break;
				}
			}
			//if (g_cbOtherHand[first].GetPoint() < play.front().GetPoint())
			//	first++;
		}
		break;
	case 2:		//一对儿 77  //MAX=J J / A A
		for (first = 0; first < FIELD; first++)
		{
			respond.clear();		//清空向量中全部元素
			if ((g_cbOtherHand[first].getPoker().getPoint() > play[0].getPoker().getPoint() && g_cbOtherHand[first].getPoker().getPoint() <= J)
				|| g_cbOtherHand[first].GetPoint() == A)
			{
				respond.push_back(g_cbOtherHand[first]);
				g_cbOtherHand[first].setExit(false);
				for (second = first + 1; second < FIELD; second++)
				{
					if (g_cbOtherHand[second].getPoker().getPoint() == respond.front().GetPoint())
					{
						respond.push_back(g_cbOtherHand[second]);
						g_cbOtherHand[second].setExit(false);
						find = true;
						flag = true;
						break;		//break立即跳出循环，for循环的循环变量修改条件不再执行！
					}
				}
				if (second >= FIELD)
					g_cbOtherHand[first].setExit(true);
			}
			if (find)
				break;
		}
		break;
	case 3:		//三组同 或 /*三顺子*/ 777  //MAX=J J J / A A A
		if (play.at(0).GetPoint() == play.at(1).GetPoint())		//三组同 
		{
			for (first = 0; first < FIELD; first++)
			{
				respond.clear();		//清空向量中全部元素
				if ((g_cbOtherHand[first].getPoker().getPoint() > play[0].getPoker().getPoint() && g_cbOtherHand[first].getPoker().getPoint() <= J) 
					|| g_cbOtherHand[first].GetPoint() == A)
				{
					respond.push_back(g_cbOtherHand[first]);
					g_cbOtherHand[first].setExit(false);
					for (second = first + 1; second < FIELD; second++)
					{
						if (g_cbOtherHand[second].getPoker().getPoint() == respond.front().GetPoint())
						{
							for (third = second + 1; third < FIELD; third++)
							{
								if (g_cbOtherHand[third].getPoker().getPoint() == respond.front().GetPoint())
								{
									respond.push_back(g_cbOtherHand[second]);
									respond.push_back(g_cbOtherHand[third]);
									g_cbOtherHand[second].setExit(false);
									g_cbOtherHand[third].setExit(false);
									find = true;
									flag = true;
									goto END;	//goto语句虽然破坏程序结构，但可以快速跳出多重循环
								}
							}
						}
					}
					if (second >= FIELD)
						g_cbOtherHand[first].setExit(true);
				}
			}
		}
		break;
		//else	//三顺子
		//{
		//	seq = play.front().GetPoint();
		//	if (A == seq || B == seq || C == seq)
		//		seq /= 100;
		//	for (first = 0; first < FIELD; first++)
		//	{
		//		if (g_cbOtherHand[first].GetPoint() > seq)
		//		{
		//			enum Point start = (enum Point)(g_cbOtherHand[first].GetPoint());
		//			for (second = first + 1; second < FIELD; second++)
		//			{
		//				if ((start + 1) == g_cbOtherHand[second].GetPoint())
		//				{
		//					for (third = second + 1; third < FIELD; third++)
		//					{
		//						if ((start + 2) == g_cbOtherHand[third].GetPoint())
		//						{

		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
	case 4:		///*四组同*/ 或 姊妹对儿 或 /*四顺子*/ 7788  //MAX=10 10 J J 
		//if (play.at(0).GetPoint() == play.at(1).GetPoint())		//四组同 
		//{
		//	for (first = 0; first < FIELD; first++)
		//	{
		//		respond.clear();		//清空向量中全部元素
		//		if (g_cbOtherHand[first].getPoker().getPoint() > play[0].getPoker().getPoint())
		//		{
		//			respond.push_back(g_cbOtherHand[first]);
		//			g_cbOtherHand[first].setExit(false);
		//			for (second = first + 1; second < FIELD; second++)
		//			{
		//				if (g_cbOtherHand[second].getPoker().getPoint() == respond.front().GetPoint())
		//				{
		//					for (third = second + 1; third < FIELD; third++)
		//					{
		//						if (g_cbOtherHand[third].getPoker().getPoint() == respond.front().GetPoint())
		//						{
		//							for (fourth = third + 1; fourth < FIELD; fourth++)
		//							{
		//								respond.push_back(g_cbOtherHand[second]);
		//								respond.push_back(g_cbOtherHand[third]);
		//								respond.push_back(g_cbOtherHand[fourth]);
		//								g_cbOtherHand[second].setExit(false);
		//								g_cbOtherHand[third].setExit(false);
		//								g_cbOtherHand[fourth].setExit(false);
		//								find = true;
		//								flag = true;
		//								goto END;	//goto语句虽然破坏程序结构，但可以快速跳出多重循环
		//							}
		//						}
		//					}
		//				}
		//			}
		//			if (second >= FIELD)
		//				g_cbOtherHand[first].setExit(true);
		//		}
		//	}
		//}
		if (play[2].GetPoint() == play[0].GetPoint() + 1)	//姊妹对儿	
		{
			for (first = 0; first < FIELD; first++)
			{
				respond.clear();		//清空向量中全部元素
				if (g_cbOtherHand[first].GetPoint() > play[0].GetPoint() && g_cbOtherHand[first].GetPoint() <= J)
				{
					respond.push_back(g_cbOtherHand[first]);
					g_cbOtherHand[first].setExit(false);
					for (second = first + 1; second < FIELD; second++)
					{
						if (g_cbOtherHand[second].GetPoint() == respond.front().GetPoint())
						{
							for (third = second + 1; third < FIELD; third++)
							{
								if(g_cbOtherHand[third].GetPoint() == respond.front().GetPoint() + 1)
									for (fourth = third + 1; fourth < FIELD; fourth++)
									{
										if (g_cbOtherHand[fourth].GetPoint() == respond.front().GetPoint() + 1)
										{
											respond.push_back(g_cbOtherHand[second]);
											respond.push_back(g_cbOtherHand[third]);
											respond.push_back(g_cbOtherHand[fourth]);
											g_cbOtherHand[second].setExit(false);
											g_cbOtherHand[third].setExit(false);
											g_cbOtherHand[fourth].setExit(false);
											find = true;
											flag = true;
											goto END;
										}
									}
							}
						}
					}
					if (second >= FIELD)
						g_cbOtherHand[first].setExit(true);
				}
			}
		}
		break;
	default:
		break;
	}
END:
	return flag;
}

/* 己方压牌判断大小
play: 对方出牌表；respond: 己方响应压牌表 */
bool CheckProduce(vector<CardButton>& play, vector<CardButton>& respond)
{
	bool flag = false;	//是否压牌标志位
	int start = respond.front().GetPoint();			//己方压牌表起始点
	int size = play.size();				//出牌张数
	if (play.size() != respond.size())
		return false;
	switch (size)
	{
	case 0:
		flag = true;
		break;
	case 1:		//单张 7
		if (start > play.front().GetPoint())
			flag = true;
		else
			flag = false;
		break;
	case 2:		//一对儿 77  
		if (start > play.front().GetPoint() && start == respond[1].GetPoint())
			flag = true;
		else
			flag = false;
		break;
	case 3:		//三组同 或 /*三顺子*/ 777  
		if (start > play.front().GetPoint() && start == respond[1].GetPoint() && start == respond[2].GetPoint())
			flag = true;
		else if (start > play.front().GetPoint() && start + 1 == respond[1].GetPoint() && start + 2 == respond[2].GetPoint())
		flag = true;
		else
			flag = false;
		break;
	case 4:		///*四组同*/ 或 姊妹对儿 或 /*四顺子*/ 7788  
		if (start > play.front().GetPoint() && start == respond[1].GetPoint() && start == respond[2].GetPoint() && start == respond[3].GetPoint())
			flag = true;
		else if (start > play.front().GetPoint() && start == respond[1].GetPoint() && start + 1 == respond[2].GetPoint() && start + 1 == respond[3].GetPoint())
			flag = true;
		else if (start > play.front().GetPoint() && start + 1 == respond[1].GetPoint() && start + 2 == respond[2].GetPoint() && start + 3 == respond[3].GetPoint())
			flag = true;
		else
			flag = false;
		break;
	default:
		break;
	}
	return flag;
}

/* 己方反击 */
bool CheckAgainst(vector<CardButton>& play)
{
	bool flag = true;
	int defend = 0;	//反击计数器
	play.clear();
	for (int hand = 0; hand < FIELD; hand++)
	{
		if (true == g_cbSelfHand[hand].getDown())
		{
			play.push_back(g_cbSelfHand[hand]);
		}
	}
	if (play.size() != 0)
	{
		vector<CardButton>::iterator it;
		for (it = play.begin(); it != play.end(); it++)
		{
			int pt = (*it).GetPoint();
			if (pt != A && pt != B && pt != C && pt != SMALL && pt != LARGE)
			{
				flag = false;
				break;
			}
		}
	}
	else
	{
		flag = false;
	}

	for (int d = 0; d < play.size(); d++)
	{
		if (SMALL == play[d].GetPoint() || LARGE == play[d].GetPoint())
		{
			defend += 3;
		}
		else if (A == play[d].GetPoint() || B == play[d].GetPoint() || C == play[d].GetPoint())
		{
			defend += play[d].GetPoint() - K;
		}
	}
	if (defend >= g_defend)
	{
		flag = true;
		g_defend = defend;
	}
	else
	{
		flag = false;
	}
	return flag;
}

/* 对方迎击 */
bool OtherAgainst(vector<CardButton>& play, vector<CardButton>& respond)
{
	bool flag = false;
	int hurt = 0;	//伤害计数器
	int defend = 0;	//反击计数器
	for (int h = 0; h < play.size(); h++)
	{
		if (SMALL == play[h].GetPoint() || LARGE == play[h].GetPoint())
			hurt += 3;
		else
			hurt += play[h].GetPoint() % 10;
	}
	g_hurt = hurt;
	for (int d = 0; d < FIELD; d++)
	{
		if (SMALL == g_cbOtherHand[d].GetPoint() || LARGE == g_cbOtherHand[d].GetPoint())
		{
			defend += 3;
			respond.push_back(g_cbOtherHand[d]);
		}
		else if (A == g_cbOtherHand[d].GetPoint() || B == g_cbOtherHand[d].GetPoint() || C == g_cbOtherHand[d].GetPoint())
		{
			defend += g_cbOtherHand[d].GetPoint() - K;
			respond.push_back(g_cbOtherHand[d]);
		}
		if (defend >= hurt)
		{
			flag = true;
			break;
		}
	}
	g_defend = defend;
	return flag;
}


/* 单机模式 */
void SingleMode()
{
	mciSendString(_T("stop theme"), 0, 0, 0);
	mciSendString(_T("close theme"), 0, 0, 0);

	StarBloom();	//先来个五角星绽放动画闪亮一下你的钛合金那啥[捂嘴笑]

	cleardevice();
	HWND hWnd = Button::MouseShape(MOUSE_ARROW);
	SetWindowText(hWnd, _T("Machete"));	//窗口标题
	SetWindowRgn(hWnd, NULL, true);	 //恢复默认的矩形窗口，开始决斗场地绘制

	mciSendString(_T("open res/sounds/haeschenlied.mp3 alias bgm"), 0, 0, 0);
	mciSendString(_T("play bgm"), 0, 0, 0);

	GameInit();		//游戏初始化

	while (true)
	{
		switch (MenuButton::MouseMsg().uMsg)
		{
		case WM_MOUSEMOVE:		//鼠标移动表示状态
			FlushMouseMsgBuffer();
			BeginBatchDraw();
				 if (g_cbSelfHand[0].IsWithin()) g_cbSelfHand[0].MouseMove();
			else if (g_cbSelfHand[1].IsWithin()) g_cbSelfHand[1].MouseMove();
			else if (g_cbSelfHand[2].IsWithin()) g_cbSelfHand[2].MouseMove();
			else if (g_cbSelfHand[3].IsWithin()) g_cbSelfHand[3].MouseMove();
			else if (g_cbSelfHand[4].IsWithin()) g_cbSelfHand[4].MouseMove();
			else if (g_cbOtherHand[0].IsWithin()) g_cbOtherHand[0].MouseMove();
			else if (g_cbOtherHand[1].IsWithin()) g_cbOtherHand[1].MouseMove();
			else if (g_cbOtherHand[2].IsWithin()) g_cbOtherHand[2].MouseMove();
			else if (g_cbOtherHand[3].IsWithin()) g_cbOtherHand[3].MouseMove();
			else if (g_cbOtherHand[4].IsWithin()) g_cbOtherHand[4].MouseMove();

			else if (g_cbDeck.IsWithin()) g_cbDeck.MouseMove();

			else if (g_obEnsure.IsWithin()) g_obEnsure.MouseMove(g_outtext[0]);
			else if (g_obAttack.IsWithin()) g_obAttack.MouseMove(g_outtext[1]);
			else
			{
				g_cbSelfHand[0].MouseLeave();
				g_cbSelfHand[1].MouseLeave();
				g_cbSelfHand[2].MouseLeave();
				g_cbSelfHand[3].MouseLeave();
				g_cbSelfHand[4].MouseLeave();
				g_cbOtherHand[0].MouseLeave();
				g_cbOtherHand[1].MouseLeave();
				g_cbOtherHand[2].MouseLeave();
				g_cbOtherHand[3].MouseLeave();
				g_cbOtherHand[4].MouseLeave();

				g_cbDeck.MouseLeave();

				g_obEnsure.MouseLeave(g_outtext[0]);
				g_obAttack.MouseLeave(g_outtext[1]);
			}
			EndBatchDraw();
			break;
		case WM_LBUTTONDOWN:	//鼠标左键按下表示选中
			     if (g_cbSelfHand[0].IsWithin()) g_cbSelfHand[0].LeftDown();
			else if (g_cbSelfHand[1].IsWithin()) g_cbSelfHand[1].LeftDown();
			else if (g_cbSelfHand[2].IsWithin()) g_cbSelfHand[2].LeftDown();
			else if (g_cbSelfHand[3].IsWithin()) g_cbSelfHand[3].LeftDown();
			else if (g_cbSelfHand[4].IsWithin()) g_cbSelfHand[4].LeftDown();

			else if (g_cbDeck.IsWithin()) g_cbDeck.LeftDown();

			else if (g_obEnsure.IsWithin()) g_obEnsure.LeftDown(Ensure);
			else if (g_obAttack.IsWithin()) g_obAttack.LeftDown(Attack);
			else
			{

			}
			break;
		case WM_RBUTTONUP:		//鼠标右键弹起表示出牌过、手牌重置  ?灵敏度不够，需要在手牌上右击才有较快的响应
			RightDown();
			break;
		default:
			break;
		}
	}
	
}

/* 双人模式 */
void CoupleMode()
{
	StarBloom();
	HWND hWnd = GetHWnd();
	TCHAR text[30] = _T("  狭路相逢，勇者胜！\n此功能待建。。。");
	MessageBox(hWnd, text, _T("双人模式"), MB_OK | MB_ICONINFORMATION );	//确定 ，帮助图标
}
/* 混战模式 */
void TripleMode()
{
	StarBloom();
	HWND hWnd = GetHWnd();
	TCHAR text[30] = _T("  乱世成就英雄！\n开黑的小伙伴从地球上消失啦~");
	MessageBox(hWnd, text, _T("混战模式"), MB_OK | MB_ICONINFORMATION);		//确定 ，帮助图标
}
/* 组队模式 */
void TeamMode()
{
	StarBloom();
	HWND hWnd = GetHWnd();
	TCHAR text[30] = _T("  不怕虎一样的对手，就怕猪一样的队友！\n你说对吗？");
	MessageBox(hWnd, text, _T("组队模式"), MB_OK | MB_ICONINFORMATION);		//确定 ，帮助图标
}
