/*  2017.3.22 15:00
	掷骰子
游戏规则：每个骰子有六面，分别为1,2,3,4,5,6。
	玩家在程序开始时输入一个无符号整数，作为产生随机数的种子。
	每轮投两次骰子，第一轮若和数为7或11则胜利，游戏结束；
							和数为2,3或12则失败，游戏结束；
	和数为其它值，将此值作为自己的点数，继续第二轮、第三轮……直到某轮和数为点数则胜利；
	若出现点数为7则失败。
*/
#include <iostream>
#include <cstdlib>
using namespace std;

enum GameStatus {draw = 0, win = 1, lose = 2};  //定义游戏状态枚举类型：平局0、胜利1、失败2
int throwdice();  //掷骰子
enum GameStatus gamevote(int sumvalue);  //游戏结果判定

int main(void)
{
	unsigned int seed;  //初始值种子
	int sum;  //骰子总和
	enum GameStatus status;  //游戏状态
	cout << "******** Throw Dice ********" << endl;
	cout << "Please input an unsigned integer: ";
	cin >> seed;
	
	srand(seed);  //初始化随机数发生器
	sum = throwdice();
	status = gamevote(sum);
	
	if(win == status)
		cout << "Player wins!" << endl;
	else
		cout << "Player loses." << endl;

	system("pause");
	return 0;
}
//掷骰子，返回骰子总和
int throwdice()
{
	int dice1, dice2;  //两粒骰子
	int sumdice;  //骰子总和
	dice1 = rand() % 6 + 1;
	dice2 = rand() % 6 + 1;
	sumdice = dice1 + dice2;
	cout << "Player rolled " << dice1 << " + " << dice2 << " = " << sumdice << endl;
	return sumdice;
}
//游戏结果判定，返回游戏状态
enum GameStatus gamevote(int sumvalue)
{
	enum GameStatus gamestatus;  //游戏状态
	switch(sumvalue)
	{
	case 7:
	case 11:
		gamestatus = win;  //胜利
		break;
	case 2:
	case 3:
	case 12:
		gamestatus = lose;  //失败
		break;
	default:
		gamestatus = draw;  //其它，进入下一轮
		cout << "Point is " << sumvalue << "..." << endl;
		while(draw == gamestatus)
		{
			int sum = throwdice();
			if(sum == sumvalue)
				gamestatus = win;
			else if(7 == sum)
				gamestatus = lose;
		}
		break;
	}
	return gamestatus;
}