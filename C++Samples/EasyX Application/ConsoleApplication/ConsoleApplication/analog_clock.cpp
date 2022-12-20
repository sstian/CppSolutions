////////////////////////////////////////////
// �������ƣ��ӱ�ģ�����(������ʽ)
// ���뻷����Visual C++ 6.0��EasyX 2013��¶��
// �����д��BestAns <BestAns@qq.com>
// �����£�2010-10-30
//
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define PI  3.1415926536

void DrawHand(int hour, int minute, int second)
{
	double a_hour, a_min, a_sec;                    // ʱ���֡�����Ļ���ֵ
	int x_hour, y_hour, x_min, y_min, x_sec, y_sec; // ʱ���֡������ĩ��λ��

													// ����ʱ���֡�����Ļ���ֵ
	a_sec = second * 2 * PI / 60;
	a_min = minute * 2 * PI / 60 + a_sec / 60;
	a_hour = hour * 2 * PI / 12 + a_min / 12;

	// ����ʱ���֡������ĩ��λ��
	x_sec = int(120 * sin(a_sec));  y_sec = int(120 * cos(a_sec));
	x_min = int(100 * sin(a_min));  y_min = int(100 * cos(a_min));
	x_hour = int(70 * sin(a_hour));  y_hour = int(70 * cos(a_hour));

	// ��ʱ��
	setlinestyle(PS_SOLID, 10);
	setcolor(WHITE);
	line(320 + x_hour, 240 - y_hour, 320 - x_hour / 7, 240 + y_hour / 7);

	// ������
	setlinestyle(PS_SOLID, 6);
	setcolor(LIGHTGRAY);
	line(320 + x_min, 240 - y_min, 320 - x_min / 5, 240 + y_min / 5);

	// ������
	setlinestyle(PS_SOLID, 2);
	setcolor(RED);
	line(320 + x_sec, 240 - y_sec, 320 - x_sec / 3, 240 + y_sec / 3);
}

void DrawDial()
{
	// ����һ���򵥵ı���
	circle(320, 240, 2);
	circle(320, 240, 60);
	circle(320, 240, 160);
	outtextxy(296, 310, L"BestAns");

	// ���ƿ̶�
	int x, y;
	for (int i = 0; i<60; i++)
	{
		x = 320 + int(145 * sin(PI * 2 * i / 60));
		y = 240 + int(145 * cos(PI * 2 * i / 60));

		if (i % 15 == 0)
			bar(x - 5, y - 5, x + 5, y + 5);
		else if (i % 5 == 0)
			circle(x, y, 3);
		else
			putpixel(x, y, WHITE);
	}
}

void main()
{
	initgraph(640, 480);        // ��ʼ�� 640 x 480 �Ļ�ͼ����

	DrawDial();                 // ���Ʊ���

	setwritemode(R2_XORPEN);    // ���� XOR ��ͼģʽ

								// ���Ʊ���
	SYSTEMTIME ti;              // ����������浱ǰʱ��
	while (!kbhit())             // ��������˳��ӱ����
	{
		GetLocalTime(&ti);      // ��ȡ��ǰʱ��
		DrawHand(ti.wHour, ti.wMinute, ti.wSecond); // ������
		Sleep(1000);            // ��ʱ 1 ��
		DrawHand(ti.wHour, ti.wMinute, ti.wSecond); // �����루������ͻ�����Ĺ�����һ���ģ�
	}

	closegraph();               // �رջ�ͼ����
}