//Help.cpp  帮助 源文件
#include <graphics.h>

/* 帮助文档 */
void HelpDoc()
{
	HWND hWnd = GetHWnd();
	int msgboxID = MessageBox(hWnd, _T("鼠标：\n  左键选择。\n   右键 - 主界面、模式选择界面为返回；\n          - 游戏决斗界面为不出牌。\n希望对你有用。"),
		_T("帮助"), MB_OK | MB_ICONQUESTION);				//确定，询问图标

}