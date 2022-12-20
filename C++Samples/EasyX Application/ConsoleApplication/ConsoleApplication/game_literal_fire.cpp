/*
* 作者：674729261
* QQ：2292683261
* 图像引擎：EasyX（http://www.easyx.cn）
* 编译环境：Visual Studio 2015 Community
* 这只是个小游戏，所以全部内联
* 编译需要先安装 EasyX 2015(beta)
*/
#include <easyx.h>
#include <time.h>
#include <conio.h>

class Bullet;
class Tank;
class E_Bullet;
class Boss;
bool dead = false;
bool wined = false;
struct pos//坐标类
{
	int a;
	int b;
};
class E_Bullet//敌人打出的子弹
{
public:
	clock_t d;
	int x;
	int y;
	bool on = false;
	pos show()//画出新的位置
	{
		setfillcolor(RGB(255, 180, 20));
		fillrectangle(x - 5, y - 5, x + 5, y + 5);
		return pos{ x,y };
	}
	pos del()//覆盖原来的位置
	{
		setfillcolor(0);
		setlinecolor(0);
		fillrectangle(x - 5, y - 5, x + 5, y + 5);
		rectangle(x - 5, y - 5, x + 5, y + 5);
		return pos{ x,y };
	}
	pos move()//左移
	{
		x -= 3;
		return pos{ x,y };
	}
};
class Bullet//玩家打出的子弹，同上
{
public:
	clock_t d;
	int x;
	int y;
	bool on = false;
	pos show()
	{
		setfillcolor(RGB(150, 180, 210));
		fillrectangle(x - 5, y - 5, x + 5, y + 5);
		return pos{ x,y };
	}
	pos del()
	{
		setfillcolor(0);
		setlinecolor(0);
		fillrectangle(x - 5, y - 5, x + 5, y + 5);
		rectangle(x - 5, y - 5, x + 5, y + 5);
		return pos{ x,y };
	}
	pos move()//右移
	{
		x += 3;
		return pos{ x,y };
	}
};
class Boss//敌人
{
public:
	bool hurting = false;
	clock_t d_hurt;
	COLORREF clr = RGB(0, 130, 125);
	int x;
	int y;
	int hp = 100;//生命
	clock_t d;//无阻塞延时，其实不是延时,只是判断举例上一次执行某一函数过了多久
	clock_t att_d;
	bool angle = false;//方向
	pos show()
	{
		setfillcolor(clr);
		fillrectangle(x - 20, y - 40, x + 20, y + 40);
		return pos{ x,y };
	}
	pos del()
	{
		setfillcolor(0);
		setlinecolor(0);
		rectangle(x - 20, y - 40, x + 20, y + 40);
		fillrectangle(x - 20, y - 40, x + 20, y + 40);
		return pos{ x,y };
	}
	void fire(E_Bullet& but)//攻击
	{
		but.on = true;//放置一个子弹
		but.x = x - 20;
		but.y = y;
		but.d = clock();
	}
	void move()//上上下下得移动
	{
		if (angle == true)
			y -= 5;
		if (angle == false)
			y += 5;
		if (y >= 440)
			angle = true;
		if (y <= 40)
			angle = false;
	}
	void hurt()//受伤
	{
		hp -= 4;
		d_hurt = clock();
		setfillcolor(0);
		setlinecolor(WHITE);
		fillrectangle(160, 485, 560, 510);//更新血条
		rectangle(160, 485, 160 + hp * 4, 510);
		setfillcolor(RGB(230, 0, 1));
		setlinecolor(RGB(255, 255, 255));
		fillrectangle(160, 485, 160 + hp * 4, 510);
		rectangle(160, 485, 160 + hp * 4, 510);
		hurting = true;
		if (hp <= 0)//挂屁
		{
			wined = true;
		}
	}
};
class Tank//玩家类，同上
{
public:
	bool hurting = false;
	int hp = 100;
	int x;
	COLORREF clr = RGB(150, 180, 210);
	int y;
	clock_t d_hurt;
	Tank() {}
	Tank(int _x, int _y) { x = _x; y = _y; }
	Tank operator=(pos p) { x = p.a; y = p.a; }
	pos show()
	{
		setfillcolor(clr);
		fillrectangle(x - 25, y - 25, x + 25, y + 25);
		setfillcolor(RGB(100, 200, 180));
		fillrectangle(x, y + 5, x + 40, y - 5);
		return pos{ x,y };
	}
	pos del()
	{
		setfillcolor(0);
		setlinecolor(0);
		fillrectangle(x - 25, y - 25, x + 25, y + 25);
		rectangle(x - 25, y - 25, x + 25, y + 25);
		fillrectangle(x, y + 5, x + 40, y - 5);
		rectangle(x, y + 5, x + 40, y - 5);
		return pos{ x,y };
	}
	void fire(Bullet& but)
	{
		but.on = true;
		but.x = x + 45;
		but.y = y;
		but.d = clock();
		but.show();
	}
	void hurt()
	{
		hp -= 2;
		d_hurt = clock();
		setfillcolor(0);
		setlinecolor(WHITE);
		fillrectangle(160, 515, 560, 540);
		rectangle(160, 515, 560, 540);
		rectangle(160, 515, 160 + hp * 4, 540);
		setfillcolor(RGB(0, 255, 1));
		setlinecolor(RGB(255, 255, 255));
		fillrectangle(160, 515, 160 + hp * 4, 540);
		rectangle(160, 515, 160 + hp * 4, 540);
		hurting = true;
		if (hp <= 0)
			dead = true;
	}
};
#define BT_MAX 8
int main()
{
	initgraph(640, 550, 4);//初始化屏幕
	settextcolor(RGB(0, 254, 0));
	settextstyle(35, 0, L"黑体");
	outtextxy(150, 200, L"W,S移动,K攻击");
	Sleep(3000);
	setlinecolor(0);
	setfillcolor(0);
	rectangle(0, 0, 640, 550);
	fillrectangle(0, 0, 640, 550);
	setlinecolor(RGB(255, 255, 255));
	setfillcolor(RGB(255, 255, 255));
	clock_t delay = clock();//玩家移动的延时
	clock_t d_f = clock();//玩家开火的延时
	line(0, 481, 640, 481);//分割画面与血条
	Bullet bt[BT_MAX];//玩家的子弹
	Tank tk(30, 30);//玩家
	Boss bo;//敌人
	bo.x = 580;
	bo.y = 240;
	E_Bullet ebt[BT_MAX];//敌人的子弹
	bo.d = clock();//初始化延时
	bo.att_d = clock();
	tk.show();
	settextstyle(20, 0, L"黑体");
	outtextxy(10, 485, L"BOSS的生命值:");
	setfillcolor(RGB(230, 0, 1));
	fillrectangle(160, 485, 560, 510);//敌人血条
	outtextxy(10, 520, L"玩家的生命值:");
	setfillcolor(RGB(0, 255, 1));
	fillrectangle(160, 515, 560, 540);//玩家血条
	while (1)//主循环
	{
		if (wined || dead)//玩家死了或者敌人死了
			break;
		if (GetAsyncKeyState('W') & 0x8000)//玩家移动
		{
			if (tk.y > 28 && (clock() - delay) >= 40)
			{
				tk.del(); tk.y -= 3; tk.show(); delay = clock();
			}
		}
		if (GetAsyncKeyState('w') & 0x8000)//玩家移动
		{
			if (tk.y > 28 && (clock() - delay) >= 40)
			{
				tk.del(); tk.y -= 3; tk.show(); delay = clock();
			}
		}
		if (GetAsyncKeyState('k') & 0x8000)//玩家开火
		{
			for (int i = 0; i < BT_MAX; i++)
			{
				if (bt[i].on == false && (clock() - d_f) > 800)
				{
					bt[i].on = true;
					tk.fire(bt[i]);
					d_f = clock();
					break;
				}
			}
		}
		if (GetAsyncKeyState('K') & 0x8000)//玩家开火
		{
			for (int i = 0; i < BT_MAX; i++)
			{
				if (bt[i].on == false && (clock() - d_f) > 800)
				{
					tk.fire(bt[i]);
					d_f = clock();
					break;
				}
			}
		}
		if (GetAsyncKeyState('S') & 0x8000)//玩家移动
		{
			if (tk.y < 452 && (clock() - delay) >= 40)
			{
				tk.del(); tk.y += 3; tk.show(); delay = clock();
			}
		}
		if (GetAsyncKeyState('s') & 0x8000)//玩家移动
			if (tk.y < 452 && (clock() - delay) >= 40)
			{
				tk.del(); tk.y += 3; tk.show(); delay = clock();
			}
		for (int i = 0; i < BT_MAX; i++)//遍历子弹，使子弹刷新
		{
			if (bt[i].on == true && (clock() - bt[i].d) > 20)
			{
				bt[i].del();
				bt[i].move();
				bt[i].show();
				bt[i].d = clock();
				if (bt[i].x >= 635)
					bt[i].on = false, bt[i].del();//到达了屏幕最右端
				if ((bt[i].x + 5 >= bo.x - 20 && bt[i].x - 5 <= bo.x + 20) && (bt[i].y - 5 < bo.y + 40 && bt[i].y + 5 > bo.y - 40))
					//击中敌人
					bt[i].on = false, bo.hurt(), bt[i].del();
			}
		}
		if (clock() - bo.att_d > 700)//敌人自动开火
		{
			for (int i = 0; i < BT_MAX; i++)
			{
				if (ebt[i].on == false)
				{
					bo.fire(ebt[i]); break;
				}
			}
			bo.att_d = clock();
		}
		for (int i = 0; i < BT_MAX; i++)//敌人子弹刷新，同上
		{
			if (ebt[i].on == true && (clock() - ebt[i].d > 20))
			{
				ebt[i].del();
				ebt[i].move();
				ebt[i].show();
				ebt[i].d = clock();
				if (ebt[i].x < 5)
					ebt[i].del(), ebt[i].on = false;
				if (ebt[i].x - 5 < tk.x + 25 && ebt[i].x + 5 > tk.x - 25 && ebt[i].y - 5 < tk.y + 25 && ebt[i].y + 5 > tk.y - 25)
				{
					ebt[i].on = false, tk.hurt(), ebt[i].del();
				}
			}
		}
		if (tk.hurting == true)//玩家受伤闪烁0.1秒
			if (clock() - tk.d_hurt > 100)
			{

				tk.clr = RGB(150, 180, 210), tk.show(), tk.hurting = false;
			}
			else
				tk.clr = RGB(255, 0, 0), tk.show();
		if (bo.hurting == true)//敌人受伤闪烁0.1秒
			if (clock() - bo.d_hurt > 100)
			{

				bo.clr = RGB(0, 130, 125), bo.show(), bo.hurting = false;
			}
			else
				bo.clr = RGB(0, 255, 0), bo.show();
		if (clock() - bo.d > 50)//敌人移动延时;
			bo.del(), bo.move(), bo.show(), bo.d = clock();
	}
	if (wined)//胜负已分
	{
		settextcolor(RGB(0, 254, 0));
		settextstyle(35, 0, L"黑体");
		outtextxy(150, 200, L"你打败了boss!你赢了！！");
	}
	else
	{
		settextcolor(RGB(254, 0, 0));
		settextstyle(35, 0, L"黑体");
		outtextxy(140, 200, L"你被boss打败了！");
	}
	Sleep(5000);
	closegraph();//关闭画布
	return 0;
}