/****************************************************************************
 * 程序名称：砍刀（Machete v1.0）纸牌游戏
 * 编译环境：Microsoft Visual Studio Professional 2017, EasyX 20170421(beta)
 * 作    者：兔儿草 <st.tian@foxmail.com>
 * 设计时间：2017-06-01 ~ 06-11
 ***************************************************************************/
#include <graphics.h>
#include <cstdlib>
#include "Constant.h"
#include "Style.h"
using namespace std;

/* 主程序 */
int main(void)
{
	initgraph(WIDTH, HEIGHT);	//初始化窗口

	MainMenu();	//主菜单

	system("pause");			//系统暂停
	closegraph();				//关闭窗口
	return 0;
}
