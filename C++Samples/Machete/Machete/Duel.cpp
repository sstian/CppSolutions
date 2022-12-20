//Duel.cpp  ���� Դ�ļ�
#include <cmath>
#include <ctime>
#include <vector>
#include <graphics.h>
#include "Constant.h"
#include "Duel.h"
#include "Style.h"

//using namespace std;

//��Ϸ����ȫ�ֱ���������
//////////////////////////////////////////////////////////////////////////////////////////////////////
vector<CardButton> g_cbOtherHand(FIELD);	//�Է�������
vector<CardButton> g_cbOtherField(FIELD);	//�Է�������
vector<CardButton> g_cbSelfField(FIELD);	//����������
vector<CardButton> g_cbSelfHand(FIELD);		//����������
CardButton g_cbDeck(65, 243, 65 + POKER_W, 243 + POKER_H);		//������
OutButton  g_obEnsure = { 710, 466, 710 + OUT_W, 466 + OUT_H };		//���ư�ť
OutButton  g_obAttack = { 710, 526, 710 + OUT_W, 526 + OUT_H };		//ս����ť
Button	   g_btnOtherLife[BLOOD];									//�Է�Ѫ��
Button	   g_btnSelfLife[BLOOD];									//����Ѫ��
RECT g_rectOtherLife = { 20, 24, 200, 84 };						//�Է�������ֵ��
RECT g_rectSelfLife  = { 20, HEIGHT - 84, 200, HEIGHT - 24 };	//����������ֵ��
RECT g_rectOtherName = { 20, 144 , 200, 228 };					//�Է����������
RECT g_rectSelfName  = { 20, HEIGHT - 228, 200, HEIGHT - 144 };	//�������������
//RECT g_rectOtherHint;										//�Է�������ʾ
//RECT g_rectSelfHint;										//����������ʾ
RECT g_rectDeckCount = { 150, 273, 210, 333 };					//������Ŀ��
int g_DeckCard  = CARDS - 10;		//����ʣ�࿨�Ƽ�����
int g_DeckThick;					//�����ȣ���ʾ����Ч��  //= THICK
int g_OtherLife = BLOOD;			//�Է�������ֵ
int g_SelfLife  = BLOOD;			//����������ֵ
TCHAR g_OtherName[20] = _T("King");	//�Է��������
TCHAR g_SelfName[20]  = _T("Jack");	//�����������
enum Draw g_Draw = Before;				//��ҳ���˳��
//Poker g_PokersCopy[CARDS - 1];		//���鸱��
vector<Poker> g_PokersCopy;				//���鸱����54�ſ��ƣ�ʹ�������������飬�����Զ�������С��˳��
vector<CardButton> g_check;		//���ȥ����
vector<CardButton> g_respond;	//�Է���Ӧ����
int g_hurt;						//�˺�������
int g_defend;					//����������
////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��ʼ��Ϸ */
void StartGame()
{
	//MessageBox(NULL, _T("��Ϸ"), _T("�����µ���;��"), MB_OK);
	cleardevice();
	//HWND hWnd = Button::MouseShape(MOUSE_ARROW);

	//while (true)
	{
		SelectMode();
	}
}

/* ѡ����Ϸģʽ�����������ã���˫�ˣ���ս����� */
void SelectMode()
{	
	///��ȡ���ھ�����ָ�ΪĬ�ϵļ�ͷ���ָ��
	HWND hWnd = Button::MouseShape(MOUSE_ARROW);

	//�������겹����x��߿��ȣ�y��߿�߶ȡ��������߶ȣ����鲹������
	int cxf = GetSystemMetrics(SM_CXFIXEDFRAME) + FACTOR;									//3 + 6
	int cyf = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION) + FACTOR;	//3 + 23 + 6
	////��ֵ�ⶨ
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
		{ (LONG)(HALFW + cxf)						 , (LONG)(HALFH - RADIUS + cyf)                },	//1 ����Ϊ���㣬˳ʱ�뷽��
		{ (LONG)(HALFW + RADIUS * sin(RAD(36)) + cxf), (LONG)(HALFH + RADIUS * cos(RAD(36)) + cyf) }	//3
	};	//����Σ�����ǣ����ڵ�����ꡣ��Ҫ���ϲ���������
	///��������βü������������������Ͻ�Ϊԭ�㣨�����߿�ͱ�������
	HRGN hRgn = CreatePolygonRgn(points, 5, WINDING);	//ALTERNATE������������м��ο�
	///���ô�������
	SetWindowRgn(hWnd, hRgn, true);	 ///int SetWindowRgn(HWND hWnd, HRGN hRgn, BOOL bRedraw); 
	//DeleteObject(hRgn);		//����hRgnռ�õ�ϵͳ��Դ

	////���������
	//pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72 * 1) / 180.0*PI);
	//pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72 * 2) / 180.0*PI);
	//pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72 * 3) / 180.0*PI);
	//pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72 * 4) / 180.0*PI);

	//��������Ǵ��ڱ���ͼ
	loadimage(NULL, _T("res/images/starsky.jpg"));	
	
	StarButton sbutton[STARS + 1];				//��Ϸģʽ�������� 5+1 = 0���ı���ʾ�� 1 2 3 4 5���հ�����
	POINT pts_star[STARS][3] = {				//����������ΰ�ť�������x < ������x
		{ g_stars[0], g_stars[9], g_stars[5] },	//0-��ѡ����Ϸģʽ��
		{ g_stars[4], g_stars[8], g_stars[9] },	//1-����
		{ g_stars[1], g_stars[5], g_stars[6] },	//2-˫��
		{ g_stars[2], g_stars[7], g_stars[6] },	//3-��ս
		{ g_stars[3], g_stars[8], g_stars[7] }	//4-���
	};
	//��Ϸģʽ�ı�
	LOGFONT font;
	gettextstyle(&font);
	font.lfQuality = ANTIALIASED_QUALITY;	//���ÿ��������
	settextstyle(&font);
		//ѡ���ı���ʾ
	settextcolor(RGB(253, 6, 204));			//������ɫ��ƫ�Ϻ�ɫ
	settextstyle(30, 20, _T("���Ĳ���"));
	outtextxy(380, 110, _T("��"));
	outtextxy(352, 160, _T("ѡ ��"));
	settextstyle(30, 20, _T("��������"));
	outtextxy(313, 230, _T("��Ϸģʽ"));
	settextstyle(50, 30, _T("���Ĳ���"));
	outtextxy(385, 285, _T("��"));
		//��Ϸģʽѡ��
	settextstyle(50, 30, _T("������κ"));
	settextcolor(RGB(242,250,36));			//������ɫ��ƫ���ɫ
	outtextxy(180, 215, g_mode[1][0]);		//"��"
	outtextxy(240, 240, g_mode[1][1]);		//"��"
	outtextxy(490, 240, g_mode[2][0]);		//"˫"
	outtextxy(550, 215, g_mode[2][1]);		//"��"
	outtextxy(440, 375, g_mode[3][0]);		//"��"
	outtextxy(470, 430, g_mode[3][1]);		//"ս"
	outtextxy(285, 375, g_mode[4][0]);		//"��"
	outtextxy(250, 430, g_mode[4][1]);		//"��"

	//��ʼ�����Ͱ�ť��������
	for (int i = 0; i < STARS; i++)
	{
		sbutton[i].SetStar(pts_star[i]);	
	}
	//ģʽѡ��Ч��
	while (true)	//����������ѭ�����Զ�����״�ش��ڲ��ܱ��棡
	{
		MOUSEMSG m = StarButton::MouseMsg();		//��ȡ�����Ϣ
		////��ȡ�����Դ��ڵ�����
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
		case WM_MOUSEMOVE:		//����ƶ�ѡ����Ϸģʽ
			BeginBatchDraw();
			if(sbutton[0].IsWithin(SELECT))		
				///������Ϣ
				//���������£���ƭ windows �����˱������ϡ�
				//WM_LBUTTONDOWN���ڡ��ͻ���������������Ϣ��WM_NCLBUTTONDOWN���ڡ��ǿͻ���������������Ϣ��
				//�ǿͻ��������������������������ڱ߿򡱣������������ȡ�
				PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(m.x, m.y));
			else if (sbutton[1].IsWithin(SINGLE))	sbutton[1].MouseMove(SINGLE);
			else if (sbutton[2].IsWithin(COUPLE))	sbutton[2].MouseMove(COUPLE);
			else if (sbutton[3].IsWithin(TRIPLE))	sbutton[3].MouseMove(TRIPLE);
			else if (sbutton[4].IsWithin(TEAM))		sbutton[4].MouseMove(TEAM);  //��ѡ���С���Ϊ���ο�

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
		case WM_LBUTTONDOWN:		//���������½�����Ӧģʽ���棬��ʼ����
				 if (sbutton[1].IsWithin(SINGLE))	SingleMode();
			else if (sbutton[2].IsWithin(COUPLE))	CoupleMode();
			else if (sbutton[3].IsWithin(TRIPLE))	TripleMode();
			else if (sbutton[4].IsWithin(TEAM))		TeamMode();
			break;
		case WM_RBUTTONUP:			//������Ҽ����ص����˵�����
			MainMenu();
			break;
		default:
			break;
		}
	}
}

/* ��Ϸ��ʼ��*/
void GameInit()
{
	loadimage(NULL, _T("res/images/duel.jpg"));		//���ؾ�������ͼ
	//���ó�ʼ����
	//
	//����˫���������볡������
	for (int i = 0; i < 4; i++)				//4��
		for (int j = 0; j < FIELD; j++)		//5��
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
	////����˫��������ʾ����
	//RECT rectOtherHint	= { g_cbOtherField[1].getLeft(), g_cbOtherField[1].getTop(),
	//	g_cbOtherField[3].getRight(), g_cbOtherField[3].getBottom() };				//�Է�������ʾ
	//RECT rectSelfHint	= { g_cbSelfField[1].getLeft(), g_cbSelfField[1].getTop(),
	//	g_cbSelfField[3].getRight(), g_cbSelfField[3].getBottom() };				//����������ʾ
	//g_rectOtherHint = rectOtherHint;
	//g_rectSelfHint	= rectSelfHint;
	//�������鸱��
	vector<Poker> pokersTemp;	//��ʱ����洢
	for (int copy = 1; copy <= CARDS; copy++)	//1 -- 54
		pokersTemp.push_back(g_pokers[copy]);
		//���ɿ����������˳��ľ�������
	srand((unsigned int)time(NULL));	
	int random;
	for(int card = CARDS; g_PokersCopy.size() < CARDS; card--)
	{
		random = rand() % card;	//0 -- 53
		g_PokersCopy.push_back(pokersTemp.at(random));	//pokersTemp.at(random) <==> pokersTemp[random]�����Ⱥ��߰�ȫ
		pokersTemp.erase(pokersTemp.begin() + random);	//pokersTemp.begin() + random <==> pokersTemp�±�Ϊ[random]
	}
	//˫�����ƶ���
	for (int anime = 0; anime < FIELD; anime++)
	{
		if (Before == g_Draw)	//�����ȹ�
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
	//����˫��Ѫ������
	for (int hp = 0; hp < BLOOD; hp++)
	{
		g_btnOtherLife[hp].SetRect(20 + 15 * hp, 84, 30 + 15 * hp, 144);
		g_btnSelfLife[hp].SetRect(20 + 15 * hp, 456, 30 + 15 * hp, 516);
		setfillcolor(RGB(248, 91, 239));	//Ѫ����ɫ��ƫ�ۺ�ɫ
		fillrectangle(g_btnOtherLife[hp].getLeft(), g_btnOtherLife[hp].getTop(),
			g_btnOtherLife[hp].getRight(), g_btnOtherLife[hp].getBottom());
		fillrectangle(g_btnSelfLife[hp].getLeft(), g_btnSelfLife[hp].getTop(),
			g_btnSelfLife[hp].getRight(), g_btnSelfLife[hp].getBottom());
	}
	//����������ֵ��Ѫ�������忨����ʾ��������Ŀ
	LifeValue(Self, BLOOD);
	LifeValue(Other, BLOOD);
	DeckCount();
	//��ʾ�������
	settextcolor(RGB(242, 250, 36));			//������ɫ��ƫ���ɫ
	drawtext(g_OtherName, &g_rectOtherName, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(g_SelfName, &g_rectSelfName, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//�ַ�˫������
	for (int dr = 0; dr < FIELD; dr++)
	{
		if (Before == g_Draw)	//�����ȹ�
		{
			g_cbSelfHand[dr] = g_PokersCopy.front();
			g_cbSelfHand[dr].setDown(false);	//��ʼ����־λ��Ϊѡ�У�����
			g_cbSelfHand[dr].setExit(true);
			g_PokersCopy.erase(g_PokersCopy.begin());
			g_cbOtherHand[dr] = g_PokersCopy.front();
			g_cbOtherHand[dr].setDown(false);
			g_cbOtherHand[dr].setExit(true);
			g_PokersCopy.erase(g_PokersCopy.begin());
		}
		else					//�����󹥣����Է��ȹ�
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
	//g_cbSelfHand[0].setDown(false);	//��ʼ����־λ��Ϊѡ�У�����
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
	//g_cbOtherHand[0].setDown(false);	//��ʼ����־λ��Ϊѡ�У�����
	//g_cbOtherHand[0].setExit(true);

	//g_cbOtherHand[1] = g_pokers[26];
	//g_cbOtherHand[1].setDown(false);	//��ʼ����־λ��Ϊѡ�У�����
	//g_cbOtherHand[1].setExit(true);

	//g_cbOtherHand[2] = g_pokers[29];
	//g_cbOtherHand[2].setDown(false);	//��ʼ����־λ��Ϊѡ�У�����
	//g_cbOtherHand[2].setExit(true);

	//g_cbOtherHand[3] = g_pokers[30];
	//g_cbOtherHand[3].setDown(false);	//��ʼ����־λ��Ϊѡ�У�����
	//g_cbOtherHand[3].setExit(true);

	//g_cbOtherHand[4] = g_pokers[51];
	//g_cbOtherHand[4].setDown(false);	//��ʼ����־λ��Ϊѡ�У�����
	//g_cbOtherHand[4].setExit(true);

	//������������
	ShuffleHand();
}

/* �����ȳ��� i: �������±� */
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
		loadimage(NULL, _T("res/images/duel.jpg"));		//���ؾ�������ͼ
		if (xs >= g_cbSelfHand[i].getLeft()) xs = g_cbSelfHand[i].getLeft();
		if (ys >= g_cbSelfHand[i].getTop()) ys = g_cbSelfHand[i].getTop();
	}
}

/* �Է��ȳ��� i: �������±� */
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
		loadimage(NULL, _T("res/images/duel.jpg"));		//���ؾ�������ͼ
		if (xo >= g_cbOtherHand[i].getLeft()) xo = g_cbOtherHand[i].getLeft();
		if (yo <= g_cbOtherHand[i].getTop()) yo = g_cbOtherHand[i].getTop();
	}
}

/* �ػ�˫��������ֵ��Ѫ�� 
 player: ��ң�value: ʣ������ֵ */
void LifeValue(int player, int value)
{
	TCHAR life[4];
	settextcolor(RGB(88, 242, 88));		//������ɫ��ƫ��ɫ
	settextstyle(50, 30, _T("���Ĳ���"));
	setfillcolor(RGB(6, 4, 51));		//�����ɫ��ƫ����ɫ
	switch (player)
	{
	case Self:		//��������
		solidellipse(g_rectSelfLife.left, g_rectSelfLife.top, g_rectSelfLife.right, g_rectSelfLife.bottom);
		swprintf_s(life, _T("%d"), value);
		drawtext(life, &g_rectSelfLife, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		setfillcolor(RGB(100, 122, 169));		//Ѫ���ۼ���ɫ��ƫ����ɫ
		for (int hp = value; hp < BLOOD; hp++)
		{
			fillrectangle(g_btnSelfLife[hp].getLeft(), g_btnSelfLife[hp].getTop(),
				g_btnSelfLife[hp].getRight(), g_btnSelfLife[hp].getBottom());
		}
		break;
	case Other:		//�Է�����
		solidellipse(g_rectOtherLife.left, g_rectOtherLife.top, g_rectOtherLife.right, g_rectOtherLife.bottom);
		swprintf_s(life, _T("%d"), value);
		drawtext(life, &g_rectOtherLife, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		setfillcolor(RGB(100, 122, 169));		//Ѫ���ۼ���ɫ��ƫ����ɫ
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

/* �ػ濨��������������嶯̬��ʾ */
void DeckCount()
{
	//������Ŀ
	setfillcolor(RGB(186, 188, 237));	//ƫ���ɫ
	solidcircle((g_rectDeckCount.left + g_rectDeckCount.right) / 2, (g_rectDeckCount.top + g_rectDeckCount.bottom) / 2, 30);
	TCHAR card[4];
	swprintf_s(card, _T("%d"), g_DeckCard);
	settextstyle(40, 20, _T("������κ"));
	settextcolor(RGB(129, 247, 58));			//������ɫ��ƫ����ɫ
	drawtext(card, &g_rectDeckCount, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//���忨�鶯̬��ʾ
	g_DeckThick = g_DeckCard / 10;
	if (0 == g_DeckThick)
		g_DeckThick = 1;
	for (int d = 0; d < g_DeckThick; d++)
		g_pokers[0].PlaceCard(g_cbDeck.getLeft() - d, g_cbDeck.getTop() - d);
}

/* �������� */
void RightDown()
{
	FlushMouseMsgBuffer();
	g_Draw = After;		//�Է�Ϊ����
	g_check.clear();	//��ճ��Ʊ�
	g_respond.clear();
	for (int r = 0; r < FIELD; r++)		//������������
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

/* �Է��ȹ� */
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

/* ���ƽ��� */
void SwapCard(CardButton& src, CardButton& dst)
{
	Poker temp;
	temp = src.getPoker();
	src.setPoker(dst.getPoker());
	dst.setPoker(temp);
}

/* ϴ�ƣ�˫�����ư�������С������������У������ң�*/
void ShuffleHand()
{	
	//?ѡ���������������Ч��,���ǲ�������ȫ��ȷ����
	//����ð�������㷨��
	for (int i = 0; i < FIELD - 1; i++)
	{
		for (int j = i + 1; j < FIELD; j++)
		{
			if (g_cbSelfHand[i].GetPoint() > g_cbSelfHand[j].GetPoint())	//����
			{
				SwapCard(g_cbSelfHand[i], g_cbSelfHand[j]);
			}
			if (g_cbOtherHand[i].GetPoint() > g_cbOtherHand[j].GetPoint())	//����
			{
				SwapCard(g_cbOtherHand[i], g_cbOtherHand[j]);
			}
		}
	}
	for (int put = 0; put < FIELD; put++)
	{
		g_cbOtherHand[put].getPoker().PlaceCard(g_cbOtherHand[put]);
		g_pokers[0].PlaceCard(g_cbOtherHand[put]);	//�Է����Ʋ���ʾ��#ֻ�ǽ����渲��ԭ�п��ƣ����ı�ԭ�п��Ʋ���
	}
	Sleep(500);	//�������·��ã��ӳ�0.5��
	for (int put = 0; put < FIELD; put++)
	{
		g_cbSelfHand[put].getPoker().PlaceCard(g_cbSelfHand[put]);
	}
}


/* ���·ַ����ƹ�5�� */
void DealCards(int draw)
{
	if (0 == g_PokersCopy.size())
	{
			setlinestyle(PS_SOLID, 0);
			LifeValue(Self, 0);
			RECT givein = { 100, 100, 700, 500 };
			settextstyle(70, 35, _T("������κ"));
			drawtext(g_result[0], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//DRAW
			Sleep(2000);	//����ͣ��2��
			MainMenu();
	}
	g_Draw = (enum Draw)draw;
	if (Before == g_Draw)	//��������
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
	else					//�������֣����Է�����
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
/* �������ͼ��� */
bool CheckOut(vector<CardButton>& check)
{
	bool flag = false;
	g_check.clear();	//��ճ��Ʊ�
	for (int hand = 0; hand < FIELD; hand++)
	{
		if (true == g_cbSelfHand[hand].getDown())
		{
			check.push_back(g_cbSelfHand[hand]);
		}
	}
	int size = check.size();	//��������
	if (size != 0)
	{
		enum Point next = (enum Point)(check[0].GetPoint());	//˳���ж�
		int start = check[0].GetPoint();						//��ͬ�ж�
		switch (size)
		{
		case 1:		//������
			flag = true;
			break;
		case 2:		//һ�Զ�
			if (check[0].GetPoint() == check[1].GetPoint())
				flag = true;
			else
				flag = false;
			break;
		case 3:		//��ͬ �� ��˳��
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
		case 4:		//��öԶ� �� ��ͬ �� ��˳�� 
					//22 33�ԡ�33 44��
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
		case 5:		//ը������˳�ӣ�MIN=4 5 6 7 8 -> MAX=Q K A 2 3
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

/* ս�����ͼ��� */
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

/* �Է�ѹ�� 
   play: ��ҳ��Ʊ�respond: ��Ӧѹ�Ʊ� */
bool OtherProduce(vector<CardButton>& play, vector<CardButton>& respond)
{
	bool flag = false;	//�Ƿ�ѹ�Ʊ�־λ
	bool find = false;	//�Ƿ���ڶ�Ӧ���ͱ�־λ
	int first, second, third, fourth;	//��һ��������������Ҫ���������
	//int seq;							//ͬ��˳�����Ƶĵ���
	int size = play.size();				//��������
	respond.clear();	//��նԷ����Ʊ�
	switch (size)
	{
	case 1:		//���� 7
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
	case 2:		//һ�Զ� 77  //MAX=J J / A A
		for (first = 0; first < FIELD; first++)
		{
			respond.clear();		//���������ȫ��Ԫ��
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
						break;		//break��������ѭ����forѭ����ѭ�������޸���������ִ�У�
					}
				}
				if (second >= FIELD)
					g_cbOtherHand[first].setExit(true);
			}
			if (find)
				break;
		}
		break;
	case 3:		//����ͬ �� /*��˳��*/ 777  //MAX=J J J / A A A
		if (play.at(0).GetPoint() == play.at(1).GetPoint())		//����ͬ 
		{
			for (first = 0; first < FIELD; first++)
			{
				respond.clear();		//���������ȫ��Ԫ��
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
									goto END;	//goto�����Ȼ�ƻ�����ṹ�������Կ�����������ѭ��
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
		//else	//��˳��
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
	case 4:		///*����ͬ*/ �� ��öԶ� �� /*��˳��*/ 7788  //MAX=10 10 J J 
		//if (play.at(0).GetPoint() == play.at(1).GetPoint())		//����ͬ 
		//{
		//	for (first = 0; first < FIELD; first++)
		//	{
		//		respond.clear();		//���������ȫ��Ԫ��
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
		//								goto END;	//goto�����Ȼ�ƻ�����ṹ�������Կ�����������ѭ��
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
		if (play[2].GetPoint() == play[0].GetPoint() + 1)	//��öԶ�	
		{
			for (first = 0; first < FIELD; first++)
			{
				respond.clear();		//���������ȫ��Ԫ��
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

/* ����ѹ���жϴ�С
play: �Է����Ʊ�respond: ������Ӧѹ�Ʊ� */
bool CheckProduce(vector<CardButton>& play, vector<CardButton>& respond)
{
	bool flag = false;	//�Ƿ�ѹ�Ʊ�־λ
	int start = respond.front().GetPoint();			//����ѹ�Ʊ���ʼ��
	int size = play.size();				//��������
	if (play.size() != respond.size())
		return false;
	switch (size)
	{
	case 0:
		flag = true;
		break;
	case 1:		//���� 7
		if (start > play.front().GetPoint())
			flag = true;
		else
			flag = false;
		break;
	case 2:		//һ�Զ� 77  
		if (start > play.front().GetPoint() && start == respond[1].GetPoint())
			flag = true;
		else
			flag = false;
		break;
	case 3:		//����ͬ �� /*��˳��*/ 777  
		if (start > play.front().GetPoint() && start == respond[1].GetPoint() && start == respond[2].GetPoint())
			flag = true;
		else if (start > play.front().GetPoint() && start + 1 == respond[1].GetPoint() && start + 2 == respond[2].GetPoint())
		flag = true;
		else
			flag = false;
		break;
	case 4:		///*����ͬ*/ �� ��öԶ� �� /*��˳��*/ 7788  
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

/* �������� */
bool CheckAgainst(vector<CardButton>& play)
{
	bool flag = true;
	int defend = 0;	//����������
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

/* �Է�ӭ�� */
bool OtherAgainst(vector<CardButton>& play, vector<CardButton>& respond)
{
	bool flag = false;
	int hurt = 0;	//�˺�������
	int defend = 0;	//����������
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


/* ����ģʽ */
void SingleMode()
{
	mciSendString(_T("stop theme"), 0, 0, 0);
	mciSendString(_T("close theme"), 0, 0, 0);

	StarBloom();	//��������������Ŷ�������һ������ѺϽ���ɶ[����Ц]

	cleardevice();
	HWND hWnd = Button::MouseShape(MOUSE_ARROW);
	SetWindowText(hWnd, _T("Machete"));	//���ڱ���
	SetWindowRgn(hWnd, NULL, true);	 //�ָ�Ĭ�ϵľ��δ��ڣ���ʼ�������ػ���

	mciSendString(_T("open res/sounds/haeschenlied.mp3 alias bgm"), 0, 0, 0);
	mciSendString(_T("play bgm"), 0, 0, 0);

	GameInit();		//��Ϸ��ʼ��

	while (true)
	{
		switch (MenuButton::MouseMsg().uMsg)
		{
		case WM_MOUSEMOVE:		//����ƶ���ʾ״̬
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
		case WM_LBUTTONDOWN:	//���������±�ʾѡ��
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
		case WM_RBUTTONUP:		//����Ҽ������ʾ���ƹ�����������  ?�����Ȳ�������Ҫ���������һ����нϿ����Ӧ
			RightDown();
			break;
		default:
			break;
		}
	}
	
}

/* ˫��ģʽ */
void CoupleMode()
{
	StarBloom();
	HWND hWnd = GetHWnd();
	TCHAR text[30] = _T("  ��·��꣬����ʤ��\n�˹��ܴ���������");
	MessageBox(hWnd, text, _T("˫��ģʽ"), MB_OK | MB_ICONINFORMATION );	//ȷ�� ������ͼ��
}
/* ��սģʽ */
void TripleMode()
{
	StarBloom();
	HWND hWnd = GetHWnd();
	TCHAR text[30] = _T("  �����ɾ�Ӣ�ۣ�\n���ڵ�С���ӵ�������ʧ��~");
	MessageBox(hWnd, text, _T("��սģʽ"), MB_OK | MB_ICONINFORMATION);		//ȷ�� ������ͼ��
}
/* ���ģʽ */
void TeamMode()
{
	StarBloom();
	HWND hWnd = GetHWnd();
	TCHAR text[30] = _T("  ���»�һ���Ķ��֣�������һ���Ķ��ѣ�\n��˵����");
	MessageBox(hWnd, text, _T("���ģʽ"), MB_OK | MB_ICONINFORMATION);		//ȷ�� ������ͼ��
}
