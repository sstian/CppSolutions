#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void main()
{
	// ����һ�� 300 x 300 �� IMAGE ����
	IMAGE img(300, 300);
	// �趨 img Ϊ��ͼ������Ŀ��
	SetWorkingImage(&img);

	// ִ�����ɻ�ͼ���
	circle(150, 150, 50);
	line(50, 150, 250, 150);
	line(150, 50, 150, 250);

	// ���� img �ڵ�ǰ·���µ�Ϊ�ļ� test.bmp
	saveimage(_T("test.bmp"), &img);

	// ��ʾ������ϣ���������˳�
	printf("ͼƬ�������\n");
	getch();
}
