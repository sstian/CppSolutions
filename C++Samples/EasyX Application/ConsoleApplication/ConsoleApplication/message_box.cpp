#include <iostream>
#include <graphics.h>
#include <Windows.h>
using namespace std;

void NewGame();
void Quit();
/* ������ */
int main(void)
{
	HWND wnd = GetHWnd();  //�õ���ͼ���ڵľ��
//	MessageBox(wnd, _T("����ϵͳ�汾̫�ͣ�������ϵͳ��"), _T("����"), MB_OK | MB_ICONWARNING);
	if (MessageBox(wnd,_T("��Ϸ������\n����һ����"), _T("ѯ��"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		NewGame();
	else
		Quit();
	return 0;
}
/* ������ */
void NewGame()
{
	wchar_t name[20];
	wcout << "Input your name:\n";
	wcin >> name;
	wcout << name << endl;
}
/* �˳� */
void Quit()
{
	exit(0);
}

