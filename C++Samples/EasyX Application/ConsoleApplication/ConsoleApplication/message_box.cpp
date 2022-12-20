#include <iostream>
#include <graphics.h>
#include <Windows.h>
using namespace std;

void NewGame();
void Quit();
/* 主函数 */
int main(void)
{
	HWND wnd = GetHWnd();  //得到绘图窗口的句柄
//	MessageBox(wnd, _T("您的系统版本太低，请升级系统。"), _T("警告"), MB_OK | MB_ICONWARNING);
	if (MessageBox(wnd,_T("游戏结束。\n重来一局吗？"), _T("询问"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		NewGame();
	else
		Quit();
	return 0;
}
/* 新名字 */
void NewGame()
{
	wchar_t name[20];
	wcout << "Input your name:\n";
	wcin >> name;
	wcout << name << endl;
}
/* 退出 */
void Quit()
{
	exit(0);
}

