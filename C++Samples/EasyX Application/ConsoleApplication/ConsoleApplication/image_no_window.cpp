#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void main()
{
	// 创建一个 300 x 300 的 IMAGE 对象
	IMAGE img(300, 300);
	// 设定 img 为绘图操作的目标
	SetWorkingImage(&img);

	// 执行若干绘图语句
	circle(150, 150, 50);
	line(50, 150, 250, 150);
	line(150, 50, 150, 250);

	// 保存 img 在当前路径下的为文件 test.bmp
	saveimage(_T("test.bmp"), &img);

	// 提示保存完毕，按任意键退出
	printf("图片保存完毕\n");
	getch();
}
