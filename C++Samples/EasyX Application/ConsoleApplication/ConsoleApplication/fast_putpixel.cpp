/////////////////////////////////////////////////
// ���ٻ���
//
// �ܵ�˼�룺ͨ��ֱ���Դ����������ϵͳ������Ҫ�����㡣
// �㷨��ƣ��� EasyX ��ͼ���ڵ��Դ��У�ÿ����ռ�� 4 ���ֽڣ�
//		�� DWORD ָ��ָ���Դ�Ϳ�����һά����һ�������ˡ�
//		Ȼ����ǽ���ά���� (x, y) ӳ�䵽һά�����У��ܼ򵥣�y * 640 + x ���ǡ�
// ע�⣺��ɫ COLORREF ���ڴ��еı�ʾ��ʽΪ��0xbbggrr (bb=����gg=�̣�rr=��)��
//		�����Դ��е���ɫ RGBTRIPLE ���ڴ��еı�����ʽΪ 0xrrggbb�����ߵĺ�ɫ����ɫ���෴�ġ�
//		ֱ�Ӳ����Դ�ʱ������ͨ�� BGR �꽻����ɫ�ĺ�ɫ����ɫ���֡�
//
#include <graphics.h>
#include <conio.h>

#define	WIDTH	640
#define	HEIGHT	480

// �Դ�ָ��
DWORD* g_pBuf;

// ���ٻ��㺯��
void fast_putpixel(int x, int y, COLORREF c)
{
	g_pBuf[y * WIDTH + x] = BGR(c);
}

// ���ٶ��㺯��
COLORREF fast_getpixel(int x, int y)
{
	COLORREF c = g_pBuf[y * WIDTH + x];
	return BGR(c);
}

// ������
void main()
{
	// ��ʼ����ͼ����
	initgraph(WIDTH, HEIGHT);

	// ��ȡ��ͼ���ڵ��Դ�ָ�벢����Ϊȫ�ֱ���
	g_pBuf = GetImageBuffer();

	// ����� 100 ����
	for (int i = 0; i< 100; i++)
		fast_putpixel(rand() % WIDTH, rand() % HEIGHT, RED);

	// ʹ��Ի�ͼ���ڵ��Դ������Ч��ע������ָ�� IMAGE ���Դ�ʱ����Ҫ������䣩
	FlushBatchDraw();

	// ɨ��ÿһ���㣬����Ǻ�ɫ�����Ըõ�ΪԲ�Ļ�һ��Բ��
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
			if (fast_getpixel(x, y) == RED)
				circle(x, y, 10);

	// ��������˳�
	getch();
	closegraph();
}

/*****************************************************************************************
IMAGE img;
loadimage(&img, _T("test.jpg"));	// ��ȷ����ͼƬ�� 640x480 ����

// ��ȡ��ͼ���ں� img ������Դ�ָ��
DWORD* pbWnd = GetImageBuffer();
DWORD* pbImg = GetImageBuffer(&img);
******************************************************************************************/