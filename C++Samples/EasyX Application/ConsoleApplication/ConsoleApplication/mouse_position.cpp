// �������ƣ�ͨ�� API ��ȡ���״̬
// ���뻷����Visual C++ 6.0 / 2008 / 2010��EasyX 2011���ݰ�
//
#include <graphics.h>
#include <stdio.h>

void main()
{
	initgraph(640, 480);		// ��ʼ����ͼ����
	HWND hwnd = GetHWnd();		// ��ȡ��ͼ���ھ��

	POINT point;
	TCHAR s[10];

	while (true)
	{
		GetCursorPos(&point);			// ��ȡ���ָ��λ�ã���Ļ���꣩
		ScreenToClient(hwnd, &point);	// �����ָ��λ��ת��Ϊ��������

										// ��ȡ��갴��״̬������ GetAsyncKeyState ���������ﲻ��������

										// ����������
		swprintf(s, _T("%d    "), point.x);
		outtextxy(0, 0, s);

		swprintf(s, _T("%d    "), point.y);
		outtextxy(0, 20, s);

		// �ʵ���ʱ
		Sleep(10);
	}
}