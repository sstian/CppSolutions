/////////////////////////////////////////////////////////////////////////////////////
// ���ڼ��ɣ����ô�����ʵ������δ���
//
#include <graphics.h>

#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159265358979323846

void main()
{
	initgraph(800, 600);			// ��ʼ��ͼ�δ���
	HWND hWnd = GetHWnd();		/*��ȡ���ھ��*/

								// ��ȡ���ڱ߿���
	int cx = GetSystemMetrics(SM_CXFIXEDFRAME);										// 3
	int cy = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);	// 3 + 23 = 26
/*
	cout << "GetSystemMetrics(SM_CXFIXEDFRAME) = " << GetSystemMetrics(SM_CXFIXEDFRAME) << endl;
	cout << "GetSystemMetrics(SM_CYFIXEDFRAME) = " << GetSystemMetrics(SM_CYFIXEDFRAME) << endl;
	cout << "GetSystemMetrics(SM_CYCAPTION) = " << GetSystemMetrics(SM_CYCAPTION) << endl;
*/	
	int a = 6;	//��������															// ����Բ������
//	HRGN rgn = CreateEllipticRgn( 100+ cx+a, 0 + cy+a, 700 + cx+a, 600 + cy+a);  //Ĭ�ϴ�������ߣ����߿�ͱ�������Ϊԭ��
																		 //	HRGN rgn = CreateEllipticRgn(100, 100, 300, 300);

	//HRGN rgn = CreateEllipticRgn(100 + cx , 0 + cy, 700 , 600 );  //Ĭ�ϴ�������ߣ����߿�ͱ�������Ϊԭ��

	//POINT point[3] = { {100,100},{300,100},{300,300} };
	//HRGN rgn = CreatePolygonRgn(point, 3, ALTERNATE);
	
	POINT points[5] = {
		{ 400 - 300 * cos(18 / 180.0*PI),300 - 300 * sin(18 / 180.0*PI) },	//5
		{ 400 + 300 * cos(18 / 180.0*PI),300 - 300 * sin(18 / 180.0*PI) },	//2
		{ 400 - 300 * sin(36 / 180.0*PI),300 + 300 * cos(36 / 180.0*PI) },	//4
		{ 400,0 },															//1
		{ 400 + 300 * sin(36 / 180.0*PI),300 + 300 * cos(36 / 180.0*PI) }	//3
	};
	polygon(points, 5);	/*���������*/

	//HRGN rgn = CreatePolygonRgn(points, 5, ALTERNATE);
	HRGN rgn = CreatePolygonRgn(points, 5, WINDING);	/*�������������*/


	SetWindowRgn(hWnd, rgn, true);	/*���ô�������*/
	//setcolor(BLUE);
	setbkcolor(BLUE);
	cleardevice();
/*
	POINT points[3] = { {400,300},{400,0},{ 400 - 150 * sqrt(3),150} };
	polygon(points, 3);
	POINT pts[3] = { {400,300},{400,600},{400 + 150 * sqrt(3),450} };
	polygon(pts, 3);
*/
	pie(100, 0, 700, 600, 90 / 180.0*PI, (90+72*1) /180.0*PI);
	pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72*2) / 180.0*PI);
	pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72*3) / 180.0*PI);
	pie(100, 0, 700, 600, 90 / 180.0*PI, (90 + 72*4) / 180.0*PI);
/*
	POINT points[5] = {
	{ 400,0 },
	{ 400 + 300 * cos(18 / 180.0*PI),300 - 300 * sin(18 / 180.0*PI) },
	{ 400 + 300 * sin(36 / 180.0*PI),300 + 300 * cos(36 / 180.0*PI) },
	{ 400 - 300 * sin(36 / 180.0*PI),300 + 300 * cos(36 / 180.0*PI) },
	{ 400 - 300 * cos(18 / 180.0*PI),300 - 300 * sin(18 / 180.0*PI) } };
*/
	//90 / 180 * PI
/*	// ���ʺ���
	setlinestyle(PS_SOLID, 2, NULL);
	for (int r = 100; r>0; r--)
	{
		setcolor(HSLtoRGB(360 - r*3.6, 1, 0.5));
		circle(200, 200, r);  //ͼ�λ����Կͻ����������߿�ͱ����������Ͻ�Ϊԭ��
	}
*/
	
	while (true)	/*//����������ѭ�����Զ�����״�ش��ڲ��ܱ���*/
	{
		MOUSEMSG m;						// ���������Ϣ
		m = GetMouseMsg();
		PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(m.x, m.y));	/*������Ϣ*/

	}
	
	closegraph();
/*
	while (true)
	{
		m = GetMouseMsg();			// ��ȡһ�������Ϣ

		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			// ���������£���ƭ windows �����˱�������
			//WM_LBUTTONDOWN���ڡ��ͻ���������������Ϣ��WM_NCLBUTTONDOWN���ڡ��ǿͻ���������������Ϣ��
			//�ǿͻ��������������������������ڱ߿򡱣������������ȡ�
			PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(m.x, m.y));
			break;

		case WM_RBUTTONUP:			// ������Ҽ��˳�����
			closegraph();
			cout << "cx = " << cx << endl;
			cout << "cy = " << cy << endl;
			exit(0);
		}
	}
*/	
}