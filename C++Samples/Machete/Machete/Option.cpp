//Option.cpp  选项 源文件
#include <graphics.h>

/* 选项设置 */
void OptionSetting()
{
	HWND hWnd = GetHWnd();
	int msgboxID = MessageBox(hWnd, _T("\
		体は剣で出来ている\n吾为所持剑之骨\n\n\
		血潮は鉄で　心は硝子\n血潮如铁 心如琉璃\n\n\
		几たびの戦场を越えて不败\n纵横无数战场而不败\n\n\
		ただの一度も败走はなく\n不为死所知\n\n\
		ただの一度も理解されない\n亦不为生所知\n\n\
		彼の者は常に独り　剣の丘で胜利に酔う\n其常立于剑丘之巅，独醉于胜利之中\n\n\
		故に、生涯に意味はなく\n故此，此生已无意义\n\n\
		その体は、きっと剣で出来ていた\n故如我祈求，无限之剑制！"),
		_T("无限剑制"), MB_OK | MB_ICONQUESTION);				//确定，询问图标

}
