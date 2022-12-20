#pragma once

#include <string>
using namespace std;

/* ��Ϸ��ʼ������ */
const int SCORE  = 100;	//����
const int CHANCE = 7;	//����

/* ��Ӧ����ѡ��۷� */
const double DEDUCT_SCORE_12345 = 0.1;	//����ѡ��1-5���۵�ǰ������1/10
const int DEDUCT_SCORE_6 = 30;	//����ѡ��6����ǰ������30
const int DEDUCT_SCORE_7 = 20;	//����ѡ��7����ǰ������20
const int DEDUCT_SCORE_8 = 33;	//����ѡ��8����ǰ������33

/* ��Ϸ�˳� */
const int EXITGAME_SUCCESS = 1;	//�ɹ�
const int EXITGAME_FAILURE = 0;	//ʧ��

class Game	//Game��
{
public:
	//����������
	Game();
	virtual ~Game();
	//get set ����
	int		getScore()	const;
	void	setScore(int score);
	int		getChance()	const;
	void	setChance(int chance);
	int		getRand()	const;
	void	setRand(int rand);
	int		getNumber()	const;
	void	setNumber(int number);

	//�˵���ʾ�����������ַ�
	char MenuHint();
	//�����֡����ز²������
	int GuessNumber();
	//�����˵������ذ����˵����
	int HelpMenu();
	//�˳������¿�ʼ
	void QuitRestart();
	//�˳���Ϸ��exitcode: �˳�����
	void ExitGame(int exitcode);

	//��������Ƿ�Ϊ������
	bool CheckDigit(string& strNum);
	//�������λ��֮��
	int SumDigit(int digit);
	//�ж��Ƿ�Ϊ����
	bool IsPrime(int number);
	//�����������һλ��������һ����ʮλ���֡�����һ
	void RandTwo(int value[], int number = 2);
	// ��������Ч��̫�ͣ����Ƽ�ʹ��
	void RandTwo_bad(int value[], int number = 2);	
private:
	int m_score;	//��ҵ÷�
	int m_chance;	//��һ���
	int m_rand;		//���������������λ����100~999
	int m_number;	//��Ҳ²������
	//��Ϸ������ʼ��
	void initialize();
};