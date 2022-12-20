#include <graphics.h>
#include <conio.h>
#include "resource.h"

int main(void)
{
	initgraph(600, 400);

//	loadimage(NULL, _T("sister.jpg"), 600, 400);
	loadimage(NULL, _T("IMAGE"), _T("BACK"), 600, 400);  //可以，没问题 I'm a genius!
//	loadimage(NULL, _T("IMAGE"), MAKEINTRESOURCE(IDR_IMAGE_BACK));
	getch();
	closegraph();
	return 0;
}