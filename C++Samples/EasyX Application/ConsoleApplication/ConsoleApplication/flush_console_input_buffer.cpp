#include <graphics.h>
#include <stdio.h>
#include <conio.h>

int main()
{
	printf("��ʱ 5 ���ӡ����� 5 ��������㰴����\n");
	Sleep(5000);

	// ���ÿ���̨ API�����֮ǰ�������ڵ����а�����
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	printf("��ʱ�������ղ������µİ����ǣ�\n");

	while (_kbhit())
	{
		char c = _getch();
		printf("%c", c);
	};

	return 0;
}