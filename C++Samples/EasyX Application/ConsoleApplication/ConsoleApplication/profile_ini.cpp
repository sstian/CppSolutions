/******************************************************************
 * �������ƣ�ʵ��С���ƶ�����ȷ���������Ϣ
 * ���뻷����Visual Studio 2017��EasyX 20170421(beta)
 * ��    �ߣ��ö���<st.tian@foxmail.com>
 * ����޸ģ�2017-5-23
 * ��Ŀ���ͣ�Win32 Console Application
 ******************************************************************/
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define R 30		// ������İ뾶

void main()
{
	// ����ͼ�δ��ڣ����á��رա���ť���Է�ֹ�޷���ȷ���������ļ�
	initgraph(640, 480, NOCLOSE);

	// ��ȡ��һ�ε�λ��
	int x, y;
	x = GetPrivateProfileInt(_T("Ball"), _T("x"), 320, _T(".\\test.ini"));
	y = GetPrivateProfileInt(_T("Ball"), _T("y"), 240, _T(".\\test.ini"));

	// ���������ɫ��������
	setfillcolor(GREEN);
	solidcircle(x, y, R);

	MOUSEMSG msg;			// �����Ϣ
	int mx, my;				// �����һ�ε�λ��
	bool keydown = false;	// ����Ƿ���

							// ��ѭ��
	while (!_kbhit())
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();		// ��ȡ�����Ϣ
			switch (msg.uMsg)
			{
				// ��������������ʼ�϶�
			case WM_LBUTTONDOWN:
				if (sqrt((double)((msg.x - x) * (msg.x - x) + (msg.y - y) * (msg.y - y))) < R)
				{
					keydown = true;
					mx = msg.x;
					my = msg.y;
				}
				break;

				// ̧����������ֹͣ�϶�
			case WM_LBUTTONUP:
				keydown = false;
				break;

				// ����ƶ��������϶�
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

		// ��ʱ������ cpu ռ����
		Sleep(10);
	}

	// �������굽�����ļ�
	TCHAR s[20];
	_stprintf(s, _T("%d"), x);			// vc6 ��д��
										//	_stprintf_s(s, _T("%d"), x);	// >= vc6 ��д��
	::WritePrivateProfileString(_T("Ball"), _T("x"), s, _T(".\\test.ini"));

	_stprintf(s, _T("%d"), y);			// vc6 ��д��
										//	_stprintf_s(s, _T("%d"), y);	// >= vc6 ��д��
	::WritePrivateProfileString(_T("Ball"), _T("y"), s, _T(".\\test.ini"));

	// �رջ�ͼ����
	closegraph();
}

/***************************************************************************************************
��ȷ���������Ϣ����������������������⣩��
����ȷ��ÿ�ζ��ܴ���ÿһ�������Ϣ�����Ҳ�����������Ϣ�Ķ�ʧ��
*********************************************************************
// ������������������Ϣ
MouseMsg msg;

// ��Ϸ����ѭ��
while(true)
{
	while (MouseHit())			// ���������Ϣ��ʱ��ִ��
	{
		msg = GetMouseMsg();	// ��ȡ�����Ϣ

		switch(msg.uMsg)		// ���ݲ�ͬ�������Ϣ��ִ�в�ͬ�Ĵ���
		{
			case xxxx: ������Ϸ����(); break;
			case xxxx: ������Ϸ����(); break;
		}
	}

	������Ϸ����();

	Sleep(xx);					// ��ʱ������ CPU ռ����
}
*****************************************************************************************************/