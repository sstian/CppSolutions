/************************************************************
*															*
*	�������ƣ�	Valentine's Day	Fireworks					*
*	���뻷����	VS2017 Professional + EasyX_20190529(beta)	*
*	������أ�	Sears Saint Tian - ��̻�					*
*	��ϵ��ʽ��	st.tian@foxmail.com							*
*	����޸ģ�	2020.02.13 Thur.							*
*															*
*************************************************************/
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <mmsystem.h>
#include <iostream>
#include "resource.h"

using namespace std;
#pragma comment (lib, "winmm.lib")
#pragma warning(disable: 4996)

/***** �궨���� ******/

#define NUM		13			// �̻����������궨��
#define PI      3.141592653

const int WIDTH		= 1200;
const int HEIGHT	= 800;

/***** �ṹ������ **********/

// �̻��ṹ
struct FIRE
{
	int r;					// ��ǰ��ը�뾶
	int max_r;				// ��ը���ľ����Ե���뾶
	int x, y;				// ��ը�����ڴ��ڵ�����
	int cen_x, cen_y;		// ��ը�������ͼƬ���Ͻǵ�����
	int width, height;		// ͼƬ�Ŀ��
	int xy[240][240];		// ����ͼƬ���ص�

	bool show;				// �Ƿ�����
	bool draw;				// ��ʼ������ص�
	DWORD t1, t2, dt;		// �����ٶ�
}Fire[NUM];

// �̻����ṹ
struct JET
{
	int x, y;				// ���������
	int hx, hy;				// ��ߵ�����------����ֵ�� FIRE ����� x, y
	int height;				// �̻��߶�
	bool shoot;				// �Ƿ���Է���

	DWORD t1, t2, dt;		// �����ٶ�
	IMAGE img[2];			// ���滨��һ��һ��ͼƬ
	byte n : 1;				// ͼƬ�±�
}Jet[NUM];


/**** ���������� ****/

void welcome();
void Init(int);			// ��ʼ���̻�
void Load();			// �����̻�ͼƬ
void Shoot();			// �����̻�
void Chose(DWORD&);		// ɸѡ�̻�
void Style(DWORD&);		// ������ʽ
void Show(DWORD*);		// �����̻�
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);	//��ȡ��Դ������

// ������
void main()
{
	initgraph(WIDTH, HEIGHT);
	srand((unsigned int)time(NULL));

	// ���ô��ڱ��⡢λ��
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"Kiss: ϲ�����������ɰ�����(#^_^#) -- ���װ���");
	SetWindowPos(hwnd, NULL, 0, 0, WIDTH, HEIGHT, 0);
	
	// ���ű�������
	//mciSendString(L"open ./fire/С����.mp3 alias bk", 0, 0, 0);
	//mciSendString(L"play bk", 0, 0, 0);
	wchar_t tmpmp3[100];
	::GetTempPath(100, tmpmp3);
	_tcscat_s(tmpmp3, L"love_app_bgm.mp3");
	ExtractResource(tmpmp3, L"MP3", MAKEINTRESOURCE(IDR_MP3_LUCKY));
	wchar_t mcicmd[100];
	swprintf_s(mcicmd, L"open \"%s\" alias lucky", tmpmp3);
	mciSendString(mcicmd, 0, 0, 0);
	mciSendString(L"play lucky", 0, 0, 0);


	welcome();

	DWORD t1 = timeGetTime();			// ɸѡ�̻���ʱ
	DWORD st1 = timeGetTime();			// ���Ż�����ʱ
	DWORD stover = timeGetTime();		// ����������ʱ
	DWORD* pMem = GetImageBuffer();		// ��ȡ�����Դ�ָ��

	for (int i = 0; i < NUM; i++)		// ��ʼ���̻�
	{
		Init(i);
	}
	Load();								// ���̻�ͼƬ��Ϣ���ؽ���Ӧ�ṹ��
	BeginBatchDraw();					// ��ʼ������ͼ

	bool over = false;
	
	while (!over)	// !over || !kbhit()	// !kbhit()
	{
		Sleep(10);

		// ���ѡ�� 4000 �����ص����
		for (int clr = 0; clr < 1000; clr++)
		{
			for (int j = 0; j < 2; j++)
			{
				int px1 = rand() % 1200;
				int py1 = rand() % 800;

				if (py1 < 799)				// ��ֹԽ��
					pMem[py1 * 1200 + px1] = pMem[py1 * 1200 + px1 + 1] = BLACK;	// ���Դ渳ֵ�������ص�
			}
		}
		Chose(t1);			// ɸѡ�̻�
		Shoot();			// �����̻�
		Show(pMem);			// �����̻�
		Style(st1);			// ��������
		FlushBatchDraw();	// ��ʾǰ������л�ͼ����

		over = timeGetTime() - stover > 140*1000 ? true : false;
	}

	::DeleteFile(tmpmp3);
	closegraph();
}


void welcome()
{
	//setfillstyle(0);
	bool flag = false;
	for (int i = 0; i < 50; i++)
	{
		int x = 600 + int(180 * sin(PI * 2 * i / 60));
		int y = 200 + int(180 * cos(PI * 2 * i / 60));
		cleardevice();
		flag = flag ? (setcolor(YELLOW), false) : (setcolor(LIGHTMAGENTA), true);
		settextstyle(i, 0, L"��������");
		outtextxy(x, y, L"���˽ڿ���!");
		outtextxy(x - 130, y + 100, L"My Lover");
		Sleep(50);
	}
	//getchar();
	Sleep(3000);

	LPCTSTR strs[] = {
		L"����Ϧ�ģ����ǵ�Լ��",
		L"������ã��Һ�ϲ����",
		L"���۾���������Ҫ����ʲô",
		L"��Ҫ���ǣ��㲻��һ����",
		L"����һ���һ�һֱ���������",
		L"���е��������Ǳ����������㵽��ʱ����������",
		L"����ˮ����䣣����������",
		L"---- С���� & С˫˫ [2020.02.14]"
	};

	cleardevice();
	settextstyle(25, 0, L"����");
	for (int xi = 0; xi <= 400; xi += 10)
	{
		cleardevice();
		outtextxy(xi, 200, strs[0]);
		Sleep(10);
	}

	Sleep(1000);
	for (int xi = 0; xi <= 400; xi += 10)
	{
		cleardevice();
		outtextxy(400, 200, strs[0]);
		outtextxy(xi, 250, strs[1]);
		Sleep(10);
	}

	Sleep(1000);
	for (int xi = 0; xi <= 400; xi += 10)
	{
		cleardevice();
		outtextxy(400, 200, strs[0]);
		outtextxy(400, 250, strs[1]);
		outtextxy(xi, 300, strs[2]);
		Sleep(10);
	}

	Sleep(1000);
	for (int xi = 0; xi <= 400; xi += 10)
	{
		cleardevice();
		outtextxy(400, 200, strs[0]);
		outtextxy(400, 250, strs[1]);
		outtextxy(400, 300, strs[2]);
		outtextxy(xi, 350, strs[3]);
		Sleep(10);
	}

	Sleep(1000);
	for (int xi = 0; xi <= 400; xi += 10)
	{
		cleardevice();
		outtextxy(400, 200, strs[0]);
		outtextxy(400, 250, strs[1]);
		outtextxy(400, 300, strs[2]);
		outtextxy(400, 350, strs[3]);
		outtextxy(xi, 400, strs[4]);
		Sleep(10);
	}

	Sleep(1000);
	for (int xi = 0; xi <= 400; xi += 10)
	{
		cleardevice();
		outtextxy(400, 200, strs[0]);
		outtextxy(400, 250, strs[1]);
		outtextxy(400, 300, strs[2]);
		outtextxy(400, 350, strs[3]);
		outtextxy(400, 400, strs[4]);
		outtextxy(xi, 450, strs[5]);
		Sleep(10);
	}

	Sleep(1000);
	for (int xi = 0; xi <= 400; xi += 10)
	{
		cleardevice();
		outtextxy(400, 200, strs[0]);
		outtextxy(400, 250, strs[1]);
		outtextxy(400, 300, strs[2]);
		outtextxy(400, 350, strs[3]);
		outtextxy(400, 400, strs[4]);
		outtextxy(400, 450, strs[5]);
		outtextxy(xi, 500, strs[6]);
		Sleep(10);
	}

	Sleep(1000);
	for (int xi = 0; xi <= 600; xi += 10)
	{
		cleardevice();
		outtextxy(400, 200, strs[0]);
		outtextxy(400, 250, strs[1]);
		outtextxy(400, 300, strs[2]);
		outtextxy(400, 350, strs[3]);
		outtextxy(400, 400, strs[4]);
		outtextxy(400, 450, strs[5]);
		outtextxy(400, 500, strs[6]);
		outtextxy(xi, 550, strs[7]);
		Sleep(10);
	}


	//getchar();
	Sleep(3000);
}

// ��ʼ���̻�����
void Init(int i)
{
	// �ֱ�Ϊ���̻����ĵ�ͼƬ��Ե����Զ���롢�̻����ĵ�ͼƬ���Ͻǵľ��� (x��y) ��������
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	/**** ��ʼ���̻� *****/

	Fire[i].x = 0;						// �̻���������
	Fire[i].y = 0;
	Fire[i].width = 240;				// ͼƬ��
	Fire[i].height = 240;				// ͼƬ��
	Fire[i].max_r = r[i];				// ���뾶
	Fire[i].cen_x = x[i];				// ���ľ����ϽǾ���
	Fire[i].cen_y = y[i];
	Fire[i].show = false;				// �Ƿ�����
	Fire[i].dt = 5;						// ����ʱ����
	Fire[i].t1 = timeGetTime();
	Fire[i].r = 0;						// �� 0 ��ʼ����

	/**** ��ʼ���̻��� *****/

	Jet[i].x = -240;				// �̻������Ͻ�����
	Jet[i].y = -240;
	Jet[i].hx = -240;				// �̻���������ߵ�����
	Jet[i].hy = -240;
	Jet[i].height = 0;				// ����߶�
	Jet[i].t1 = timeGetTime();
	Jet[i].dt = rand() % 10;		// �����ٶ�ʱ����
	Jet[i].n = 0;					// �̻�����˸ͼƬ�±�
	Jet[i].shoot = false;			// �Ƿ���
}


// ����ͼƬ
void Load()
{
	/**** �����̻������ص���ɫ ****/
	IMAGE fm, gm;
	//loadimage(&fm, L"./fire/flower.jpg", 3120, 240);
	loadimage(&fm, L"IMAGE", MAKEINTRESOURCE(IDR_IMAGE_FLOWER), 3120, 240);

	for (int i = 0; i < 13; i++)
	{
		SetWorkingImage(&fm);
		getimage(&gm, i * 240, 0, 240, 240);
		SetWorkingImage(&gm);

		for (int a = 0; a < 240; a++)
			for (int b = 0; b < 240; b++)
				Fire[i].xy[a][b] = getpixel(a, b);
	}

	/**** �����̻��� ************/
	IMAGE sm;
	//loadimage(&sm, L"./fire/shoot.jpg", 200, 50);
	loadimage(&sm, L"JPG", MAKEINTRESOURCE(IDB_BITMAP_SHOOT), 200, 50);

	for (int i = 0; i < 13; i++)
	{
		SetWorkingImage(&sm);
		int n = rand() % 5;

		getimage(&Jet[i].img[0], n * 20, 0, 20, 50);			// ��
		getimage(&Jet[i].img[1], (n + 5) * 20, 0, 20, 50);		// ��
	}

	SetWorkingImage();		// ���ûػ�ͼ����
}


// ��һ����Χ��ɸѡ�ɷ�����̻�������ʼ���������������̻�������Ļ����������
void Chose(DWORD& t1)
{
	DWORD t2 = timeGetTime();

	if (t2 - t1 > 100)
	{
		int n = rand() % 20;

		if (n < 13 && Jet[n].shoot == false && Fire[n].show == false)
		{
			/**** �����̻�����Ԥ������ *****/
			Jet[n].x = rand() % 1200;
			Jet[n].y = rand() % 100 + 600;
			Jet[n].hx = Jet[n].x;
			Jet[n].hy = rand() % 400;
			Jet[n].height = Jet[n].y - Jet[n].hy;
			Jet[n].shoot = true;
			putimage(Jet[n].x, Jet[n].y, &Jet[n].img[Jet[n].n], SRCINVERT);

			/**** ����ÿ���̻��������� *****/
			//char c1[50], c2[30], c3[30];
			//wchar_t c1[50], c2[30], c3[30];
			wchar_t c1[100], c2[30], c3[30];

			wchar_t tmpmp3[100];
			::GetTempPath(100, tmpmp3);
			_tcscat_s(tmpmp3, L"love_app_shoot.mp3");
			ExtractResource(tmpmp3, L"MP3", MAKEINTRESOURCE(IDR_MP3_SHOOT));
			//wchar_t mcicmd[MAX_PATH];
			swprintf_s(c1, L"open \"%s\" alias s%d", tmpmp3, n);

			//swprintf(c1, L"open ./fire/shoot.mp3 alias s%d", n);
			swprintf(c2, L"play s%d", n);
			swprintf(c3, L"close n%d", n);

			mciSendString(c3, 0, 0, 0);
			mciSendString(c1, 0, 0, 0);
			mciSendString(c2, 0, 0, 0);

			//::DeleteFile(tmpmp3);

		}
		t1 = t2;
	}
}


// ɨ���̻���������
void Shoot()
{
	for (int i = 0; i < 13; i++)
	{
		Jet[i].t2 = timeGetTime();

		if (Jet[i].t2 - Jet[i].t1 > Jet[i].dt && Jet[i].shoot == true)
		{
			/**** �̻��������� *****/
			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);

			if (Jet[i].y > Jet[i].hy)
			{
				Jet[i].n++;
				Jet[i].y -= 5;
			}

			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);

			/**** �������߶ȵ� 3 / 4������ *****/
			if ((Jet[i].y - Jet[i].hy) * 4 < Jet[i].height)
				Jet[i].dt = rand() % 4 + 10;

			/**** ���������߶� *****/
			if (Jet[i].y <= Jet[i].hy)
			{
				// ���ű�ը��
				//char c1[50], c2[30], c3[30];
				wchar_t c1[100], c2[30], c3[30];

				wchar_t tmpmp3[100];
				::GetTempPath(100, tmpmp3);
				_tcscat_s(tmpmp3, L"love_app_bomb.wav");
				ExtractResource(tmpmp3, L"WAVE", MAKEINTRESOURCE(IDR_WAVE_BOMB));
				//wchar_t mcicmd[MAX_PATH];
				swprintf_s(c1, L"open \"%s\" alias n%d", tmpmp3, i);
				//swprintf(c1, L"open ./fire/bomb.wav alias n%d", i);
				swprintf(c2, L"play n%d", i);
				swprintf(c3, L"close s%d", i);

				mciSendString(c3, 0, 0, 0);
				mciSendString(c1, 0, 0, 0);
				mciSendString(c2, 0, 0, 0);

				::DeleteFile(tmpmp3);

				putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);		// �����̻���
				Fire[i].x = Jet[i].hx + 10;											// ���̻����м䱬ը
				Fire[i].y = Jet[i].hy;												// ����ߵ�����
				Fire[i].show = true;					// ��ʼ����
				Jet[i].shoot = false;					// ֹͣ����

			}
			Jet[i].t1 = Jet[i].t2;
		}
	}

}



// ��ʾ����
void Style(DWORD& st1)
{
	DWORD st2 = timeGetTime();

	if (st2 - st1 >20000)		// һ�׸��ʱ��
	{
		// ��������
		int x[13] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
		int y[13] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };

		wchar_t tmpmp3[100];

		for (int i = 0; i < NUM; i++)
		{
			//cleardevice();
			/**** ���ɷֲ��̻��� ***/
			Jet[i].x = x[i] * 10;
			Jet[i].y = (y[i] + 75) * 10;
			Jet[i].hx = Jet[i].x;
			Jet[i].hy = y[i] * 10;
			Jet[i].height = Jet[i].y - Jet[i].hy;
			Jet[i].shoot = true;
			Jet[i].dt = 7;
			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);	// ��ʾ�̻���

			/**** �����̻����� ***/
			Fire[i].x = Jet[i].x + 10;
			Fire[i].y = Jet[i].hy;
			Fire[i].show = false;
			Fire[i].r = 0;

			/**** ���ŷ������� ***/
			//char c1[50], c2[30], c3[30];
			wchar_t c1[100], c2[30], c3[30];

			::GetTempPath(100, tmpmp3);
			_tcscat_s(tmpmp3, L"love_app_shoot_style.mp3");
			ExtractResource(tmpmp3, L"MP3", MAKEINTRESOURCE(IDR_MP3_SHOOT));
			//wchar_t mcicmd[MAX_PATH];
			swprintf_s(c1, L"open \"%s\" alias s%d", tmpmp3, i);
			//swprintf(c1, L"open ./fire/shoot.mp3 alias s%d", i);
			swprintf(c2, L"play s%d", i);
			swprintf(c3, L"close n%d", i);

			mciSendString(c3, 0, 0, 0);
			mciSendString(c1, 0, 0, 0);
			mciSendString(c2, 0, 0, 0);
		
		}
		st1 = st2;

		::DeleteFile(tmpmp3);

	}
}


// �����̻�
void Show(DWORD* pMem)
{
	// �̻����׶�����ʱ������������������Ч��
	int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 55 };

	for (int i = 0; i < NUM; i++)
	{
		Fire[i].t2 = timeGetTime();

		// ���ӱ�ը�뾶�������̻�������ʱ����������Ч��
		if (Fire[i].t2 - Fire[i].t1 > Fire[i].dt && Fire[i].show == true)
		{
			if (Fire[i].r < Fire[i].max_r)
			{
				Fire[i].r++;
				Fire[i].dt = drt[Fire[i].r / 10];
				Fire[i].draw = true;
			}

			if (Fire[i].r >= Fire[i].max_r - 1)
			{
				Fire[i].draw = false;
				Init(i);
			}
			Fire[i].t1 = Fire[i].t2;
		}

		// ����ú��ڻ��ɱ�ը�����ݵ�ǰ��ը�뾶���̻�����ɫֵ�ӽ���ɫ�Ĳ������
		if (Fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a += 0.01)
			{
				int x1 = (int)(Fire[i].cen_x + Fire[i].r * cos(a));					// �����ͼƬ���Ͻǵ�����
				int y1 = (int)(Fire[i].cen_y - Fire[i].r * sin(a));

				if (x1 > 0 && x1 < Fire[i].width && y1 > 0 && y1 < Fire[i].height)	// ֻ���ͼƬ�ڵ����ص�
				{
					int b = Fire[i].xy[x1][y1] & 0xff;
					int g = (Fire[i].xy[x1][y1] >> 8) & 0xff;
					int r = (Fire[i].xy[x1][y1] >> 16);

					// �̻����ص��ڴ����ϵ�����
					int xx = (int)(Fire[i].x + Fire[i].r * cos(a));
					int yy = (int)(Fire[i].y - Fire[i].r * sin(a));

					// �ϰ������ص㲻�������ֹԽ��
					if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800)
						pMem[yy * 1200 + xx] = BGR(Fire[i].xy[x1][y1]);	// �Դ���������̻�
				}
			}
			Fire[i].draw = false;
		}
	}
}

// ��ȡָ��ģ���е���Դ�ļ�
// ������
//     strDstFile:     Ŀ���ļ�������ȡ����Դ�����������
//     strResType:     ��Դ���ͣ�
//     strResName:     ��Դ���ƣ�
// ����ֵ��
//     true: ִ�гɹ���
//     false: ִ��ʧ�ܡ�
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// �����ļ�
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
       return false;

    // ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
    HRSRC	hRes = ::FindResource(NULL, strResName, strResType);
    HGLOBAL hMem = ::LoadResource(NULL, hRes);
    DWORD dwSize = ::SizeofResource(NULL, hRes);

    // д���ļ�
   DWORD dwWrite = 0; // ����д���ֽ�
    ::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
    ::CloseHandle(hFile);

   return true;
}
