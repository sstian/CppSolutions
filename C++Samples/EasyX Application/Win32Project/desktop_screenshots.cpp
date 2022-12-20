/////////////////////////////////////////////////////////
// �������ƣ�ʵ�������ͼ
// ���뻷����Visual C++ 6.0 / 2010��EasyX 20130117(beta)
// ��    �ߣ�yangw80 <yw80@qq.com>
// ����޸ģ�2013-1-29
// ��Ŀ���ͣ�Win32 Application
//
#include <graphics.h>


// ץȡ����ͼ�� *pimg ������
void CaptureDesktop(IMAGE *pimg)
{
	// ͨ�� Windows API ��ȡ����Ŀ��
	int w = GetSystemMetrics(SM_CXSCREEN) / 2;
	int h = GetSystemMetrics(SM_CYSCREEN) / 2;

	// ���� pimg �Ĵ�С
	Resize(pimg, w, h);

	// ��ȡ���� DC
	HDC srcDC = GetDC(NULL);
	// ��ȡ IMAGE ����� DC
	HDC dstDC = GetImageHDC(pimg);

	// ������ DC ֮��ִ��ͼ�񿽱���������ץͼ������ IMAGE ��������
	BitBlt(dstDC, 0, 0, w, h, srcDC, 0, 0, SRCCOPY);
}


// ������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���� IMAGE ����
	IMAGE img;

	// ����ץȡ����ͼ��ĺ���
	CaptureDesktop(&img);

	// ������ͼ����
	initgraph(940, 480);

	// �ڴ�������ʾ IMAGE �б��������ͼ��
	putimage(0, 0, &img);

	// �� ESC ���˳�
	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
		Sleep(20);

	closegraph();
	return 0;
}
