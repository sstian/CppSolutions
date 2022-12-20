/*	
	项目名称：与电脑猜数字
						——一种命令窗口式的人机交互小游戏
	开发环境：Visual Studio 2017 Professional
	作    者：田继辉 (st.tian@foxmail.com)
	设计时间：2018.04.10 15:34 - 04.11 04:25
*/
//#include <iostream>
//#include <cstdlib>
#include "Game.h"
//using namespace std;

int main()
{
	Game game;
	//int value[2];
	//int bad[2];
	/// 控制游戏循环进行：while(true){}
	while (true)
	{
		game.MenuHint();
		//cout << game.getRand() << endl;
		//game.RandTwo(value);
		//cout << value[0] << "+" << value[1] << endl;
		//game.RandTwo_bad(bad);
		//cout << bad[0] << "-" << bad[1] << endl;
		//game.IsPrime(9);
		system("pause");
		system("cls");
	}
	return 0;
}