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
	char select;	//��Ŀѡ���ַ�
	int error;		//�����־
	cout << "***************************************************************" << endl;
	cout << "ѡ����ʾ������\"H\",ѡ�����������\"G\"��ѡ�����¿�ʼ������\"Q\"��" << endl;
	cout << "�����ڵĵ÷�Ϊ��" << m_score << "��������" << m_chance << "�λ��ᡣ" << endl;
	cout << "***************************************************************" << endl;
	/* ���������� */
	//����һ��do{}while;
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
	////��������while(true){}��ѭ��
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
	////���������ȼ�������while(error){}
	//error = 1;	//�ȼ������
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
	/// ��������Ǵ��������⣺bool CheckDigit(string strNum);
	if (CheckDigit(strNum))
		setNumber(stoi(strNum));

	if (getNumber() != getRand())
	{
		cout << "�´��ˣ�" << endl;
		m_chance--;
		if (m_chance <= 0)
			ExitGame(EXITGAME_FAILURE);
		if (strNum.length() > 3)		//���ȹ�����ʾ
			cout << "Dear~, the length of number is 3." << endl;
	}
	else
	{
		cout << "��ĵ÷�Ϊ��" << m_score << endl;
		cout << "����������Ϊ" << getRand() << endl;
		ExitGame(EXITGAME_SUCCESS);
	}
	return getNumber();
}

int Game::HelpMenu()
{
	char help;
	cout << "***************************************************************" << endl;
	cout << "1���ж��������ֱȲ��������ִ���С��" << endl;
	cout << "2���ж�����������ż����" << endl;
	cout << "3���ж��ǲ������������һ����Χ�ڵ����������磺200 500����" << endl;
	cout << "4���ж��ܲ��ܱ�3������" << endl;
	cout << "5���ж��ܲ��ܱ�5������" << endl;
	cout << "6����λ����ʲô��" << endl;
	cout << "7���������������������һ����ʮλ����" << endl;
	cout << "8������λ���ĺͣ�" << endl;
	cout << "***************************************************************" << endl;
	//������� ������ �� ����Խ�� ����
	while (true)
	{
		cin >> help;
		/// ������뻺����
		cin.clear();			/// ����cin��״̬��ʾ��
		//cin.sync();				/// ������뻺����ȫ��������
		cin.ignore(1024, '\n');	/// ������뻺�����еĻس��������س���֮ǰ�������ַ���basic_istream& ignore(streamsize _Count = 1,int_type _Metadelim = _Traits::eof());
		
		if (help < '0' || help > '9')			//������
			cout << "Please input a integer!" << endl;
		else if ('0' == help || '9' == help)	//����Խ��
			cout << "The range is from 1 to 8!" << endl;
		else
			break;
	}
	
	switch (help)
	{
	case '1':
		if (0 == getNumber())
			cout << "�㻹û������²�����֣�" << endl;
		else
		{
			cout << "��ѡ������ʾ��Ϣ" << help << "����۵�ǰ������1/10��" << endl << endl;
			m_score -= (int)(m_score * DEDUCT_SCORE_12345);
			cout << "���ϴ������" << getNumber() << ((getNumber() > getRand()) ? "����" : "С��") << "����������" << endl;
			if (m_score <= 0)
				ExitGame(EXITGAME_FAILURE);
		}
		break;
	case '2':
		cout << "��ѡ������ʾ��Ϣ" << help << "����۵�ǰ������1/10��" << endl << endl;
		m_score -= (int)(m_score * DEDUCT_SCORE_12345);
		cout << "������������" << ((getRand() % 2 == 0) ? "ż��" : "����") << "!" << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '3':
		cout << "��ѡ������ʾ��Ϣ" << help << "����۵�ǰ������1/10��" << endl << endl;
		m_score -= (int)(m_score * DEDUCT_SCORE_12345);
		//setRand(123);	//���������������ֵ���ڲ���
		if(IsPrime(getRand()))
		{
			int first, second;	//���ַ�Χ��[first,second]
			int count = 0;		//��������������
			cout << "����������������!" << endl;
			cout << "������Ҫ��֪�����ķ�Χ�����磺200 500����";
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
			cout << "���������ֲ�������!" << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '4':
		cout << "��ѡ������ʾ��Ϣ" << help << "����۵�ǰ������1/10��" << endl << endl;
		m_score -= (int)(m_score * DEDUCT_SCORE_12345);
		cout << "����������" << ((getRand() % 3 == 0) ? "��" : "����") << "��3������" << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '5':
		cout << "��ѡ������ʾ��Ϣ" << help << "����۵�ǰ������1/10��" << endl << endl;
		m_score -= (int)(m_score * DEDUCT_SCORE_12345);
		cout << "����������" << ((getRand() % 5 == 0) ? "��" : "����") << "��5������" << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '6':
		cout << "��ѡ������ʾ��Ϣ" << help << "����ǰ������" << DEDUCT_SCORE_6 << "!" << endl << endl;
		m_score -= DEDUCT_SCORE_6;
		cout << "��λ��Ϊ" << getRand() % 10 << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '7':
		int value[2];
		cout << "��ѡ������ʾ��Ϣ" << help << "����ǰ������" << DEDUCT_SCORE_7 << "!" << endl << endl;
		m_score -= DEDUCT_SCORE_7;
		RandTwo(value);
		cout << value[0] << " " << value[1] << endl;
		if (m_score <= 0)
			ExitGame(EXITGAME_FAILURE);
		break;
	case '8':
		cout << "��ѡ������ʾ��Ϣ" << help << "����ǰ������" << DEDUCT_SCORE_8 << "!" << endl << endl;
		m_score -= DEDUCT_SCORE_8;
		cout << "����λ��֮��Ϊ" << SumDigit(getRand()) << endl;
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
		cout << "������²�����֣�";
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
	int tens;	//���²��������ʮλ
	int other;	//��һ���������
	int index;		//�����±�
	tens = getRand() % 100 / 10;
	while (true)
	{
		other = rand() % 10;
		if (other != tens)
			break;
	}
	index = rand() % 2;	//�������� 0 1
	value[index] = tens;
	value[number - 1 - index] = other;
}

void Game::RandTwo_bad(int value[], int number)
{
	int tens = getRand() % 100 / 10;	//���²��������ʮλ
	int n, m, i;
	bool same;

	while (true)
	{
		//��֤�����������������ͬ
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
		//��֤�����������������²����ֵ�ָ������
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
	/// ��ʼ�����Ӳ������������λ��
	srand((unsigned int)time(NULL));
	m_rand = rand() % 900 + 100;
}
