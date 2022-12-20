#include "Game.h"
#include <iostream>
//#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
//using namespace std;

Game::Game()
{
	initialize();
}

Game::~Game()
{
}

int Game::getScore() const
{
	return m_score;
}

void Game::setScore(int score)
{
	m_score = score;
}

int Game::getChance() const
{
	return m_chance;
}

void Game::setChance(int chance)
{
	m_chance = chance;
}

int Game::getRand() const
{
	return m_rand;
}

void Game::setRand(int rand)
{
	m_rand = rand;
}

int Game::getNumber() const
{
	return m_number;
}

void Game::setNumber(int number)
{
	m_number = number;
}

char Game::MenuHint()
{
	char select;	//项目选择字符
	int error;		//出错标志
	cout << "***************************************************************" << endl;
	cout << "选择提示请输入\"H\",选择猜数请输入\"G\"，选择重新开始请输入\"Q\"：" << endl;
	cout << "您现在的得分为：" << m_score << "，您还有" << m_chance << "次机会。" << endl;
	cout << "***************************************************************" << endl;
	/* 输入错误纠正 */
	//方法一：do{}while;
	do
	{
		error = 0;
		cin >> select;
		switch (select)
		{
		case 'h':
		case 'H':
			HelpMenu();
			break;
		case 'g':
		case 'G':
			GuessNumber();
			break;
		case 'q':
		case 'Q':
			QuitRestart();
			break;
		default:
			error = 1;
			cout << "Input error! Please retry." << endl;
			break;
		}
	} while (error);
	////方法二：while(true){}死循环
	//while (true)
	//{
	//	error = 0;
	//	cin >> select;
	//	switch (select)
	//	{
	//	case 'h':
	//	case 'H':
	//		break;
	//	case 'g':
	//	case 'G':
	//		break;
	//	case 'q':
	//	case 'Q':
	//		break;
	//	default:
	//		error = 1;
	//		break;
	//	}
	//	if (error)
	//		cout << "Input error! Please retry.." << endl;
	//	else
	//		break;
	//}
	////方法三：先假设错误的while(error){}
	//error = 1;	//先假设错误
	//while (error)
	//{
	//	error = 0;
	//	cin >> select;
	//	switch (select)
	//	{
	//	case 'h':
	//	case 'H':
	//		break;
	//	case 'g':
	//	case 'G':
	//		break;
	//	case 'q':
	//	case 'Q':
	//		break;
	//	default:
	//		error = 1;
	//		cout << "Input error! Please retry..." << endl;
	//		break;
	//	}
	//}

	return select;
}

int Game::GuessNumber()
{
	string strNum;
	/// 处理输入非纯数字问题：bool CheckDigit(string strNum);
	if (CheckDigit(strNum))
		setNumber(stoi(strNum));

	if (getNumber() != getRand())
	{
		cout << "猜错了！" << endl;
		m_chance--;
		if (m_chance <= 0)
			ExitGame(EXITGAME_FAILURE);
		if (strNum.length() > 3)		//长度过长提示
			cout << "Dear~, the length of number is 3." << endl;
	}
	else
	{
		cout << "你的得分为：" << m_score << endl;
		cout << "产生的数字为" << getRand() << endl;
		ExitGame(EXITGAME_SUCCESS);
	}
	return getNumber();
}

int Game::HelpMenu()
{
	char help;
	cout << "***************************************************************" << endl;
	cout << "1、判断输入数字比产生的数字大还是小；" << endl;
	cout << "2、判断是奇数还是偶数；" << endl;
	cout << "3、判断是不是素数，输出一定范围内的素数（例如：200 500）；" << endl;
	cout << "4、判断能不能被3整除；" << endl;
	cout << "5、判断能不能被5整除；" << endl;
	cout << "6、个位数是什么；" << endl;
	cout << "7、随机生成两个数，其中一个是十位数；" << endl;
	cout << "8、三个位数的和；" << endl;
	cout << "***************************************************************" << endl;
	//解决输入 非数字 和 数字越界 问题
	while (true)
	{
		cin >> help;
		/// 清空输入缓冲区
		cin.clear();			/// 更改cin的状态标示符
		//cin.sync();				/// 清除输入缓冲区全部的内容
		cin.ignore(1024, '\n');	/// 清除输入缓冲区中的回车（包括回车）之前的所有字符，basic_istream& ignore(streamsize _Count = 1,int_type _Metadelim = _Traits::eof());
		
		if (help < '0' || help > '9')			//非数字
			cout << "Please input a integer!" << endl;
		else if ('0' == help || '9' == help)	//数字越界
			cout << "The range is from 1 to 8!" << endl;
		else
			break;
	}
	
	switch (help)
	{
	case '1':
		if (0 == getNumber())
			cout << "你还没有输入猜测的数字！" << endl;
		else
		{
			cout << "你选择了提示信息" << help << "，会扣当前分数的1/10！" << endl << endl;
			m_score -= (int)(m_score * DEDUCT_SCORE_12345);
			cout << "你上次输入的" << getNumber() << ((getNumber() > getRand()) ? "大于" : "小于") << "产生的数字" << endl;
			if (m_score <= 0)
				ExitGame(EXITGAME_FAILURE);
		}
		break;
	case '2':
		cout << "你选择了提示信息" << help << "，会扣当前分数的1/10！" << endl << endl;
		m_score -= (int)(m_score * DEDUCT_SCORE_12345);
		cout << "产生的数字是" << ((getRand() % 2 == 0) ? "偶数" : "奇数") << "!" << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '3':
		cout << "你选择了提示信息" << help << "，会扣当前分数的1/10！" << endl << endl;
		m_score -= (int)(m_score * DEDUCT_SCORE_12345);
		//setRand(123);	//自行设置随机数的值用于测试
		if(IsPrime(getRand()))
		{
			int first, second;	//数字范围：[first,second]
			int count = 0;		//素数个数计数器
			cout << "产生的数字是素数!" << endl;
			cout << "请输入要获知素数的范围（例如：200 500）：";
			cin >> first >> second;
			for (int num = first; num <= second; num++)
			{
				if (IsPrime(num))
				{
					cout << setw(5) << num;
					count++;
					if (count % 10 == 0)
						cout << endl;
				}
			}	
		}
		else
			cout << "产生的数字不是素数!" << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '4':
		cout << "你选择了提示信息" << help << "，会扣当前分数的1/10！" << endl << endl;
		m_score -= (int)(m_score * DEDUCT_SCORE_12345);
		cout << "产生的数字" << ((getRand() % 3 == 0) ? "能" : "不能") << "被3整除！" << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '5':
		cout << "你选择了提示信息" << help << "，会扣当前分数的1/10！" << endl << endl;
		m_score -= (int)(m_score * DEDUCT_SCORE_12345);
		cout << "产生的数字" << ((getRand() % 5 == 0) ? "能" : "不能") << "被5整除！" << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '6':
		cout << "你选择了提示信息" << help << "，当前分数减" << DEDUCT_SCORE_6 << "!" << endl << endl;
		m_score -= DEDUCT_SCORE_6;
		cout << "个位数为" << getRand() % 10 << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '7':
		int value[2];
		cout << "你选择了提示信息" << help << "，当前分数减" << DEDUCT_SCORE_7 << "!" << endl << endl;
		m_score -= DEDUCT_SCORE_7;
		RandTwo(value);
		cout << value[0] << " " << value[1] << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '8':
		cout << "你选择了提示信息" << help << "，当前分数减" << DEDUCT_SCORE_8 << "!" << endl << endl;
		m_score -= DEDUCT_SCORE_8;
		cout << "三个位数之和为" << SumDigit(getRand()) << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	default:
		break;
	}
	return (help - '0');
}

void Game::QuitRestart()
{
	initialize();
}

void Game::ExitGame(int exitcode)
{
	switch (exitcode)
	{
	case EXITGAME_SUCCESS:
		break;
	case EXITGAME_FAILURE:
		if (m_chance <= 0)
			cout << "You don't have a chance!" << endl;
		if (m_score <= 0)
			cout << "You use all the scores!" << endl;
		break;
	default:
		break;
	}
	system("pause");
	exit(0);
}

bool Game::CheckDigit(string& strNum)
{
	int i;
	while (true)
	{
		cout << "请输入猜测的数字：";
		cin >> strNum;
		for (i = 0; strNum[i] != '\0'; i++)
		{
			if (strNum[i] < '0' || strNum[i] > '9')
			{
				cout << "non-number! Please be careful." << endl;
				break;
			}
		}
		if ('\0' == strNum[i])
			return true;
	}
}

int Game::SumDigit(int digit)
{
	int value = digit;
	int sum = 0;
	while (value)
	{
		sum += value % 10;
		value /= 10;
	}
	return sum;
}

bool Game::IsPrime(int number)
{
	int root = (int)sqrt(number);
	int n;
	for (n = 2; n <= root; n++)
		if (number % n == 0)
			break;
	if (n > root)
		return true;
	return false;
}

void Game::RandTwo(int value[], int number)
{
	int tens;	//欲猜测随机数的十位
	int other;	//另一个随机数字
	int index;		//数组下标
	tens = getRand() % 100 / 10;
	while (true)
	{
		other = rand() % 10;
		if (other != tens)
			break;
	}
	index = rand() % 2;	//产生数字 0 1
	value[index] = tens;
	value[number - 1 - index] = other;
}

void Game::RandTwo_bad(int value[], int number)
{
	int tens = getRand() % 100 / 10;	//欲猜测随机数的十位
	int n, m, i;
	bool same;

	while (true)
	{
		//保证产生的随机数互不相同
		for (n = 0; n < number; n++)
		{
			same = true;
			while (same)
			{
				srand((unsigned int)time(NULL));
				value[n] = rand() % 10;
				for (m = 0; m < n; m++)
					if (value[n] == value[m])
						break;
				if (m >= n)
				{
					same = false;
				}
			}
		}
		//保证产生的随机数中有与猜测数字的指定数字
		for (i = 0; i < number; i++)
		{
			if (value[i] == tens)
				break;
		}
		if (i < number)
			break;
	}	
}

void Game::initialize()
{
	m_score  = SCORE;
	m_chance = CHANCE;
	m_number = 0;
	/// 初始化种子并产生随机的三位数
	srand((unsigned int)time(NULL));
	m_rand = rand() % 900 + 100;
}
