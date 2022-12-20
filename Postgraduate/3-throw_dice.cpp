/*  2017.3.22 15:00
	������
��Ϸ����ÿ�����������棬�ֱ�Ϊ1,2,3,4,5,6��
	����ڳ���ʼʱ����һ���޷�����������Ϊ��������������ӡ�
	ÿ��Ͷ�������ӣ���һ��������Ϊ7��11��ʤ������Ϸ������
							����Ϊ2,3��12��ʧ�ܣ���Ϸ������
	����Ϊ����ֵ������ֵ��Ϊ�Լ��ĵ����������ڶ��֡������֡���ֱ��ĳ�ֺ���Ϊ������ʤ����
	�����ֵ���Ϊ7��ʧ�ܡ�
*/
#include <iostream>
#include <cstdlib>
using namespace std;

enum GameStatus {draw = 0, win = 1, lose = 2};  //������Ϸ״̬ö�����ͣ�ƽ��0��ʤ��1��ʧ��2
int throwdice();  //������
enum GameStatus gamevote(int sumvalue);  //��Ϸ����ж�

int main(void)
{
	unsigned int seed;  //��ʼֵ����
	int sum;  //�����ܺ�
	enum GameStatus status;  //��Ϸ״̬
	cout << "******** Throw Dice ********" << endl;
	cout << "Please input an unsigned integer: ";
	cin >> seed;
	
	srand(seed);  //��ʼ�������������
	sum = throwdice();
	status = gamevote(sum);
	
	if(win == status)
		cout << "Player wins!" << endl;
	else
		cout << "Player loses." << endl;

	system("pause");
	return 0;
}
//�����ӣ����������ܺ�
int throwdice()
{
	int dice1, dice2;  //��������
	int sumdice;  //�����ܺ�
	dice1 = rand() % 6 + 1;
	dice2 = rand() % 6 + 1;
	sumdice = dice1 + dice2;
	cout << "Player rolled " << dice1 << " + " << dice2 << " = " << sumdice << endl;
	return sumdice;
}
//��Ϸ����ж���������Ϸ״̬
enum GameStatus gamevote(int sumvalue)
{
	enum GameStatus gamestatus;  //��Ϸ״̬
	switch(sumvalue)
	{
	case 7:
	case 11:
		gamestatus = win;  //ʤ��
		break;
	case 2:
	case 3:
	case 12:
		gamestatus = lose;  //ʧ��
		break;
	default:
		gamestatus = draw;  //������������һ��
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