// �������ƣ��ʺ�
// ���뻷����Visual C++ 6.0��EasyX 2011���ݰ�
// �����£�2010-8-25
//
#include <graphics.h>
#include <conio.h>

void main()
{
	float H, S, L;

	initgraph(640, 480);

	// ����������(ͨ������������)
	H = 190;    // ɫ��
	S = 1;      // ���Ͷ�
	L = 0.7f;   // ����
	for (int y = 0; y < 480; y++)
	{
		L += 0.0005f;
		setcolor(HSLtoRGB(H, S, L));
		line(0, y, 639, y);
	}

	// ���ʺ�(ͨ��ɫ��������)
	H = 0;
	S = 1;
	L = 0.5f;
	setlinestyle(PS_SOLID, 2, NULL);   // �����߿�Ϊ 2
	for (int r = 400; r > 344; r--)
	{
		H += 5;
		setcolor(HSLtoRGB(H, S, L));
		circle(500, 480, r);
	}

	getch();
	closegraph();
}