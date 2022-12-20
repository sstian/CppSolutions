/////////////////////////////////////////////////////////
// 程序名称：实现桌面截图
// 编译环境：Visual C++ 6.0 / 2010，EasyX 20130117(beta)
// 作    者：yangw80 <yw80@qq.com>
// 最后修改：2013-1-29
// 项目类型：Win32 Application
//
#include <graphics.h>


// 抓取桌面图像到 *pimg 对象中
void CaptureDesktop(IMAGE *pimg)
{
	// 通过 Windows API 获取桌面的宽高
	int w = GetSystemMetrics(SM_CXSCREEN) / 2;
	int h = GetSystemMetrics(SM_CYSCREEN) / 2;

	// 调整 pimg 的大小
	Resize(pimg, w, h);

	// 获取桌面 DC
	HDC srcDC = GetDC(NULL);
	// 获取 IMAGE 对象的 DC
	HDC dstDC = GetImageHDC(pimg);

	// 在两个 DC 之间执行图像拷贝，将桌面抓图拷贝到 IMAGE 对象里面
	BitBlt(dstDC, 0, 0, w, h, srcDC, 0, 0, SRCCOPY);
}


// 主函数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 定义 IMAGE 对象
	IMAGE img;

	// 调用抓取桌面图像的函数
	CaptureDesktop(&img);

	// 创建绘图窗口
	initgraph(940, 480);

	// 在窗口中显示 IMAGE 中保存的桌面图像
	putimage(0, 0, &img);

	// 按 ESC 键退出
	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
		Sleep(20);

	closegraph();
	return 0;
}
