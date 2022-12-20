#pragma once

#include <string>
using namespace std;

/* 游戏初始化参数 */
const int SCORE  = 100;	//分数
const int CHANCE = 7;	//机会

/* 对应帮助选项扣分 */
const double DEDUCT_SCORE_12345 = 0.1;	//帮助选项1-5，扣当前分数的1/10
const int DEDUCT_SCORE_6 = 30;	//帮助选项6，当前分数减30
const int DEDUCT_SCORE_7 = 20;	//帮助选项7，当前分数减20
const int DEDUCT_SCORE_8 = 33;	//帮助选项8，当前分数减33

/* 游戏退出 */
const int EXITGAME_SUCCESS = 1;	//成功
const int EXITGAME_FAILURE = 0;	//失败

class Game	//Game类
{
public:
	//构造与析构
	Game();
	virtual ~Game();
	//get set 方法
	int		getScore()	const;
	void	setScore(int score);
	int		getChance()	const;
	void	setChance(int chance);
	int		getRand()	const;
	void	setRand(int rand);
	int		getNumber()	const;
	void	setNumber(int number);

	//菜单提示。返回输入字符
	char MenuHint();
	//猜数字。返回猜测的数字
	int GuessNumber();
	//帮助菜单。返回帮助菜单编号
	int HelpMenu();
	//退出并重新开始
	void QuitRestart();
	//退出游戏。exitcode: 退出代码
	void ExitGame(int exitcode);

	//检查输入是否为纯数字
	bool CheckDigit(string& strNum);
	//计算各个位数之和
	int SumDigit(int digit);
	//判断是否为素数
	bool IsPrime(int number);
	//随机生成两个一位数，其中一个是十位数字。方法一
	void RandTwo(int value[], int number = 2);
	// 方法二，效率太低！不推荐使用
	void RandTwo_bad(int value[], int number = 2);	
private:
	int m_score;	//玩家得分
	int m_chance;	//玩家机会
	int m_rand;		//产生的随机数：三位数，100~999
	int m_number;	//玩家猜测的数字
	//游戏参数初始化
	void initialize();
};