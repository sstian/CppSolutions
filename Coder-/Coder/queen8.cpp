/*
	2019.11.01 17:01 - 17:47
	�˻ʺ�����
	��8��8��Ĺ��������ϰڷŰ˸��ʺ�ʹ�䲻�ܻ��๥���������������ʺ󶼲��ܴ���ͬһ�С�ͬһ�л�ͬһб����
����������ݹ���ݣ���������һ��ö�ٷ�
1. �ҳ���һ����ȷ�ڷŷ�ʽ��������ȱ�����(��ʵ��)
2. �ҳ�ȫ������ȷ�ڷŷ�ʽ��������ȱ�����
*/
#include <iostream>

using namespace std;

// �ʺ���
class Queen
{
public:
	Queen(int number = 8) : m_number(number) { }

	// �������Ƿ���Ϲ���
	bool CheckPoint(int x, int y);
	// �ݹ����
	bool SettleQueen(int y);
	// ��ӡ���̵�ǰֵ
	void Printchess();

private:
	static const int RANGE = 8;			//���̸��ӵķ�Χ
	int m_number = 8;					//�ʺ�����
	int m_chess[RANGE][RANGE] = {0};	//��ά������Ϊ����
};

bool Queen::CheckPoint(int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		//�������
		if (1 == this->m_chess[x][i])
			return false;
		//���������
		if (x - 1 - i >= 0 && 1 == this->m_chess[x - 1 - i][y - 1 - i])
			return false;
		//����Ҳ����
		if (x + 1 + i < RANGE && 1 == this->m_chess[x + 1 + i][y - 1 - i])
			return false;
	}
	return true;
}

bool Queen::SettleQueen(int y)
{
	//ɨ��������������������˵���Ѿ��ҵ���
	if (y >= RANGE)
		return true;

	//������ǰ�У���һ������֤
	for (int i = 0; i < RANGE; i++)
	{
		//Ϊ��ǰ�����㣬�����ڻ��ݵĹ����г���������
		for (int x = 0; x < RANGE; x++)
			this->m_chess[x][y] = 0;

		//����Ƿ���Ϲ���������ϣ�����Ԫ��ֵ����һ���ݹ�
		if (this->CheckPoint(i, y))
		{
			this->m_chess[i][y] = 1;
			//�ݹ��������true��˵���²����ҵ��ⷨ���������ѭ��
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
	// ��ʼ�����ݹ�ڷŻʺ�������
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

E:\unlimited rulebook\C++ Laboratory\Coder-\x64\Debug\Coder.exe (���� 15900)���˳������ش���Ϊ: 0��
��������رմ˴���...
***/