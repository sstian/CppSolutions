/*
	2018.06.27 15:43
	������֬��

	��֬����ָ������֬����������������������ռ�ı������ֳ���֬�ٷ���������ӳ������֬�������Ķ��١�
���㹫ʽ��
	����Ů�ԣ�
	����a=��Χ��cm����0.74
	����b=���أ�kg����0.082+34.89
	��֬��������kg��=a��b
	��֬��=������֬�������������أ���100%

	�������ԣ�
	����a=��Χ��cm����0.74
	����b=���أ�kg����0.082+44.74
	��֬��������kg��=a��b
	��֬��=������֬�������������أ���100%

����ֵ�ο���Χ��
	�����˵���֬��������Χ�ֱ���Ů��20%��25%������15%��18%������֬�ʹ��ߣ����س�������ֵ��20%���ϾͿ���Ϊ���֡�
	�˶�Ա����֬�ʿ����˶���Ŀ������һ�����˶�ԱΪ7%��15%��Ů�˶�ԱΪ12%��25%��

ע�����
	ͬʱ��ȡ��ʳ�Ʒ����˶��Ʒ������ʣ�����������ȡ��ͨ���˶������������ģ��ﵽ���ʵ�Ч����

*/
#include <iostream>
#include <cstdlib>
using namespace std;

enum Sex { Female = 0, Male = 1 };	// �Ա�Ů�ԣ�����
/* ������֬��
sex: Female-Ů�ԣ�Male-���ԣ�
waist: ��Χ��cm��:
weight: ���أ�kg��
����ֵ����֬�� */
double BodyFatRate(enum Sex sex, double waist, double weight)
{
	double para_a, para_b;		//����a������b
	double total_fat_weight;	//����֬��������
	double body_fat_rate;		//��֬��
	para_a = waist * 0.74;
	switch (sex)
	{
	case Female:
		para_b = weight * 0.082 + 34.89;
		break;
	case Male:
		para_b = weight * 0.082 + 44.74;
		break;
	default:
		break;
	}
	total_fat_weight = para_a - para_b;
	body_fat_rate = (total_fat_weight / weight);
	return body_fat_rate;
}

int main()
{
	int value;
	enum Sex sex;			//�Ա�
	double waist, weitght;	//��Χ������
	double rate;			//��֬��

	cout << "****** ������֬�� ******" << endl;
	cout << "�Ա�Ů��-0������-1�� sex = ";
	cin >> value;
	switch (value)
	{
	case 0:	sex = Female; break;
	case 1: sex = Male; break;
	default: break;
	}
	cout << "��Χ(cm) waist = ";
	cin >> waist;
	cout << "����(kg) weight = ";
	cin >> weitght;

	rate = BodyFatRate(sex, waist, weitght);

	cout << endl;
	cout << "��֬�� body fat rate = " << rate << endl << endl;
	switch (sex)
	{
	case Female:
		if (rate < 0.12)
			cout << "��ƫ�ݣ�Ҫע��Ӫ��Ŷ~" << endl;
		else if (rate >= 0.12 && rate < 0.20)
			cout << "������Ů�˶�Ա��Ǳ�ʣ�ʵ��Ů�к��ܣ�" << endl;
		else if (rate >= 0.20 && rate <= 0.25)
			cout << "�������������������֡�" << endl;
		else
			cout << "���е�����ü���������" << endl;
		break;
	case Male:
		if (rate < 0.07)
			cout << "��ƫ�ݣ�Ҫע��Ӫ��������߲ˡ�" << endl;
		else if (rate >= 0.07 && rate < 0.15)
			cout << "���������˶�Ա��Ǳ�ʣ�Ϊ����𣬳�Խ�����ء�" << endl;
		else if (rate >= 0.15 && rate <= 0.18)
			cout << "�������������������֣���˯����" << endl;
		else
			cout << "���Ľ����ǣ������ʵ���������ʳ��Ͷ��˶���" << endl;
		break;
	default:
		break;
	}
	cout << endl;
	system("pause");
	return 0;
}
