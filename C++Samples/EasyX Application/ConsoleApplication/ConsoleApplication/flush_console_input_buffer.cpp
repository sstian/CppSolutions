#include <graphics.h>
#include <stdio.h>
#include <conio.h>

int main()
{
	printf("延时 5 秒钟。请在 5 秒钟内随便按键。\n");
	Sleep(5000);

	// 调用控制台 API，清空之前缓冲区内的所有按键。
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	printf("延时结束。刚才您按下的按键是：\n");

	while (_kbhit())
	{
		char c = _getch();
		printf("%c", c);
	};

	return 0;
}