///////////////////////////////////////////////////
// �������ƣ����ӽ���һ���򵥵�С��Ϸ��
// ���뻷����Visual C++ 6.0��EasyX 2013˪����
// �������ߣ�ʥʯ <2464847121@qq.com>
// ����޸ģ�2013-12-1
// �淨������������ƺ����ƶ���סС���ܹ��� 20s ����Ϸʱ�䣬����ʱΪ 0 ʱ��Ϸ����
//
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

// ���峣��
#define NUM 10
#define CMD_LEFT        1
#define CMD_RIGHT       2
#define CMD_QUIT        4

int box_x = 10;
int box_y = 420;

// ������Ľṹ��
struct Ball
{
	int x, y, v;
};

// ��ȡ�û�����
int GetCommand()
{
	int c = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)     c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)    c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)   c |= CMD_QUIT;

	return c;
}

// ����ʱ
int Time(int t)
{
	char strsec[10];
	int sec = 20 - (GetTickCount() - t) / 1000;
	itoa(sec, strsec, 10);
	outtextxy(570, 110, L"      ");
	outtextxy(570, 110, (TCHAR*)strcat(strsec, "s"));
	return sec;
}

// ����
void menu()
{
	line(449, 0, 449, 480);
	TCHAR runTime[] = L"��Ϸ����ʱ     : ",
		receiveBallNum[] = L"�ӵ����������:", copyRight[] = L"��Ȩ����:ʥʯ",
		finishWorkDate[] = L"�������:2012��12��1��",
		introductiona[] = L"����������ƺ����ƶ���ס", introductionb[] = L"С��,����ʱΪ0ʱ��Ϸ����";

	settextcolor(GREEN);
	outtextxy(450, 10, introductiona);
	outtextxy(450, 30, introductionb);
	outtextxy(450, 110, runTime);
	outtextxy(450, 210, receiveBallNum);
	outtextxy(450, 310, copyRight);
	outtextxy(450, 410, finishWorkDate);
}

// ���������
void ballRandom(Ball ball[], int i)
{
	ball[i].x = 16 + 45 * i;
	ball[i].y = 8 + rand() % 32;
	ball[i].v = 1 + rand() % 5;
}

// ���򣬲�����÷�
void calculateScore(Ball ball[], int &score)
{
	for (int i = 0; i < NUM; i++)
	{
		fillcircle(ball[i].x, ball[i].y, 8);
		if (ball[i].y >= 472)
		{
			ballRandom(ball, i);
			continue;
		}
		if (box_x + 8 <= ball[i].x && ball[i].x <= box_x + 72 && ball[i].y >= 412)
		{
			score++;
			ballRandom(ball, i);
		}
	}
}

// ������
int main()
{
	// ��ʼ��
	initgraph(640, 480);
	srand(time(NULL));
	BeginBatchDraw();
	setlinecolor(GREEN);
	setfillcolor(WHITE);

	menu();

	Ball ball[NUM];
	int dx, i, c, score = 0;
	bool flag = true;

	for (i = 0; i<NUM; i++)
	{
		ballRandom(ball, i);
	}

	int t = GetTickCount();
	char strScore[10], str[] = "your score:";

	// ��Ϸ��ѭ��
	while (flag)
	{
		dx = 0;

		// ��ʾ�÷�
		char strScore[10];
		itoa(score, strScore, 10);
		outtextxy(570, 210, (TCHAR*)strScore);

		// ���򣬲�����÷�
		calculateScore(ball, score);

		// ������
		fillrectangle(box_x, box_y, box_x + 80, box_y + 60);
		FlushBatchDraw();

		// ��ȡ�û���������
		c = GetCommand();
		if (c & CMD_LEFT)   dx = -10;
		if (c & CMD_RIGHT)  dx = 10;
		if (c & CMD_QUIT)   flag = false;
		if (!Time(t)) flag = false;

		// ��ʱ
		Sleep(25);

		// ������Ϸ��
		clearrectangle(0, 0, 448, 480);

		// �������������
		for (i = 0; i < NUM; i++)
		{
			ball[i].y += ball[i].v;
		}

		// �ƶ�����
		box_x += dx;
		if (box_x < 0)   box_x = 0;
		if (box_x > 368) box_x = 368;
	}

	// ��ռ��̻�����
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	// �����Ϸ���
	itoa(score, strScore, 10);
	outtextxy(222, 240, (TCHAR*)strcat(str, strScore));
	outtextxy(220, 300, L"��������˳�");
	EndBatchDraw();

	// ��������˳�
	getch();
	closegraph();

	return 0;
}