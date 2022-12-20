/*
	2019.11.01 17:01 - 17:47
	八皇后问题
	在8×8格的国际象棋上摆放八个皇后，使其不能互相攻击，即任意两个皇后都不能处于同一行、同一列或同一斜线上
解决方案：递归回溯，本质上是一种枚举法
1. 找出第一种正确摆放方式，深度优先遍历。(已实现)
2. 找出全部的正确摆放方式，广度优先遍历。
*/
#include <iostream>

using namespace std;

// 皇后类
class Queen
{
public:
	Queen(int number = 8) : m_number(number) { }

	// 检查落点是否符合规则
	bool CheckPoint(int x, int y);
	// 递归回溯
	bool SettleQueen(int y);
	// 打印棋盘当前值
	void Printchess();

private:
	static const int RANGE = 8;			//棋盘格子的范围
	int m_number = 8;					//皇后数量
	int m_chess[RANGE][RANGE] = {0};	//二维数组作为棋盘
};

bool Queen::CheckPoint(int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		//检查纵向
		if (1 == this->m_chess[x][i])
			return false;
		//检查左侧横向
		if (x - 1 - i >= 0 && 1 == this->m_chess[x - 1 - i][y - 1 - i])
			return false;
		//检查右侧横向
		if (x + 1 + i < RANGE && 1 == this->m_chess[x + 1 + i][y - 1 - i])
			return false;
	}
	return true;
}

bool Queen::SettleQueen(int y)
{
	//扫描行数超过棋盘行数，说明已经找到答案
	if (y >= RANGE)
		return true;

	//遍历当前行，逐一格子验证
	for (int i = 0; i < RANGE; i++)
	{
		//为当前行清零，以免在回溯的过程中出现脏数据
		for (int x = 0; x < RANGE; x++)
			this->m_chess[x][y] = 0;

		//检查是否符合规则，如果符合，更改元素值并进一步递归
		if (this->CheckPoint(i, y))
		{
			this->m_chess[i][y] = 1;
			//递归如果返回true，说明下层已找到解法，无需继续循环
			if (this->SettleQueen(y + 1))
				return true;
		}
	}
	return false;
}

void Queen::Printchess()
{
	for (int i = 0; i < RANGE; i++)
	{
		for (int j = 0; j < RANGE; j++)
			std::cout << this->m_chess[i][j];
		std::cout << std::endl;
	}	
}

int main()
{
	// 初始化，递归摆放皇后，输出结果
	cout << "*** Queen 8 ***" << endl;
	Queen queen8;
	queen8.SettleQueen(0);
	queen8.Printchess();

	//Queen* q = new Queen;	
	//q->SettleQueen(0);
	//q->Printchess();
	//delete q;

	//int* pn = new int(3);
	//cout << *pn << endl;

	return 0;
}


/*** out:
*** Queen 8 ***
10000000
00000010
00001000
00000001
01000000
00010000
00000100
00100000

E:\unlimited rulebook\C++ Laboratory\Coder-\x64\Debug\Coder.exe (进程 15900)已退出，返回代码为: 0。
按任意键关闭此窗口...
***/