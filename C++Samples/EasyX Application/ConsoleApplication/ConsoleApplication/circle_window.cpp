/////////////////////////////////////////////////////////////////////////////////////
// ���ڼ��ɣ����ô�����ʵ��Բ�δ���
//
#include <graphics.h>
#include <iostream>
using namespace std;

void main()
{
	initgraph(400, 400);			// ��ʼ��ͼ�δ���
	HWND hWnd = GetHWnd();		// ��ȡ���ھ��

								// ��ȡ���ڱ߿���
	int cx = GetSystemMetrics(SM_CXFIXEDFRAME);										// 3
	int cy = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);	// 3 + 23 = 26

	// ����Բ������
	HRGN rgn = CreateEllipticRgn(111 + cx, 111 + cy, 300 + cx, 300 + cy);  //Ĭ�ϴ�������ߣ����߿�ͱ�������Ϊԭ��

//	HRGN rgn = CreateEllipticRgn(100, 100, 300, 300);

	SetWindowRgn(hWnd, rgn, true);

	// ���ʺ���
	setlinestyle(PS_SOLID, 2, NULL);
	for (int r = 100; r>0; r--)
	{
		setcolor(HSLtoRGB(360 - r*3.6, 1, 0.5));
		circle(200, 200, r);  //ͼ�λ����Կͻ����������߿�ͱ����������Ͻ�Ϊԭ��
	}

	MOUSEMSG m;						// ���������Ϣ

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
}