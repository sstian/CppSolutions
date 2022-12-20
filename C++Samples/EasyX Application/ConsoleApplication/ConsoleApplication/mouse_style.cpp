////////////////////////////////////////////
// �������ƣ����������ʽ�ķ���
// ���뻷����Visual C++ 6.0��EasyX 2011���ݰ�
//
#include <graphics.h>
#include <conio.h>

void main()
{
	initgraph(640, 480);							// ������ͼ����

	HCURSOR hcur = LoadCursor(NULL, IDC_CROSS);		// ����ϵͳԤ�õ������ʽ
	HWND hwnd = GetHWnd();							// ��ȡ��ͼ���ھ��
	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	// ���ô�����������ʽ

													// ��������˳�
	getch();
	closegraph();
}

/***************************************************************************************************
һ����ȡ�����ʽ�ľ��
ʹ�� API ���� LoadCursor ʵ�ּ��������ʽ��
�ú������Զ�ȡϵͳĬ�ϵ���ʽ��Ҳ���Լ�����Դ��ʽ�� .cur �����ʽͼƬ��
������ͨ�� API ���� LoadImage �����ļ���ʽ�������ʽͼƬ��

(1) ����ϵͳĬ�ϵ�ʮ����ʽ����꣺
HCURSOR hcur = LoadCursor(NULL, IDC_CROSS);

(2) ������Դ�е������ʽͼƬ��
HMODULE hmod = GetModuleHandle(NULL);  // ��ȡ��ǰ���̵ľ��
HCURSOR hcur = LoadCursor(hmod, _T("MyCursor")); // ������Դ�е������ʽͼƬ
// ע�����Ƚ� .cur ��ʽ��ͼƬ��ӵ�ϵͳ��Դ�ļ��У�������Ϊ "MyCursor"��

(3) ���� c:\\test.cur ��Ϊ�����ʽ��
HCURSOR hcur = (HCURSOR)LoadImage(NULL, _T("C:\\test.cur"), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);

�������ô�����������ʽ
ʹ�� SetClassLong ���ô����࣬ʹ�� GetHWnd() ���ش��ھ����

HWND hwnd = GetHWnd();    // ��ȡ��ͼ���ھ��
SetClassLong(hwnd, GCL_HCURSOR, (long)hcur); // ���û�ͼ�����ڵ������ʽ
****************************************************************************************************/