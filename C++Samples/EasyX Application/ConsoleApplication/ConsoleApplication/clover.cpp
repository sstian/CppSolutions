///////////////////////////////////////////////////
// �������ƣ�Ư������Ҷ��
// ���뻷����Visual C++ 6.0��EasyX 2011���ݰ�
// �������ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2011-10-14
// ע��Դ���������ѷ��� QQ Ⱥ��C ���Ը���������� Turbo C ���룬���޸ĵ�
//
#include <graphics.h>
#include <math.h>
#include <conio.h>

#define PI 3.1415926535

void main(void)
{
	// ��ʼ����ͼ����
	initgraph(640, 480);        // ������ͼ����
	setcolor(GREEN);            // ���û�ͼ��ɫ
	setorigin(320, 240);        // ����ԭ������

								// ������
	double e;
	int x1, y1, x2, y2;
	for (double a = 0; a < 2 * PI; a += 2 * PI / 720)
	{
		e = 100 * (1 + sin(4 * a));
		x1 = (int)(e * cos(a));
		y1 = (int)(e * sin(a));
		x2 = (int)(e * cos(a + PI / 5));
		y2 = (int)(e * sin(a + PI / 5));

		line(x1, y1, x2, y2);

		Sleep(20);      // �ӳٺ�����ʵ�����ٻ��ƵĶ���Ч��
	}

	// ��������˳�
	_getch();
	closegraph();
}