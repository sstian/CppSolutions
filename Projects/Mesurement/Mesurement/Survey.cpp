#include <iostream>
#include <cmath>
#include <cstring>
#define N 100
using namespace std;
class Mesure
{
public:
	float data[N];						 //data[N]��Ų�������
	int n = 16;						 //nΪ�������ݸ���
	void Divation();
	void ErrorLine();
	void ErrorCycle();
	float getAve() const { return ave; }
	float getSumVi2() const { return sumVi2; }
	float getSigma() const { return sigma; }
	int getN() const { return n; }
	int getFlag() const { return flag; }
private:
	float vi[N];                      //data[N]��Ų������ݣ�vi[N]��Ųв
	float ave, sumXi, sumVi2, sigma;  //aveΪ������������ƽ��ֵ��sumXiΪ���������ܺͣ�
	float maxAbsVi;                   //sumVi2Ϊ�в�ƽ���ͣ�sigmaΪ��׼ƫ�
	int flag = 0;					  //maxAbsViΪ�в�vi����ֵ�����ֵ��flag=1��ʾ����ϵͳ��
};							 
/******************************************************************************
��  ����main()������
��  ����
����ֵ��int
��  �ܣ���ϵͳ���̣��������ݣ���ʾ�������
******************************************************************************/
int main()
{
	Mesure survey;
	int i;
	float c;		//����ϵͳ��������
	float datum[N] = { 205.30, 204.94, 205.63, 205.24, 206.65, 204.97, 205.36, 205.16, 205.71, 204.70, 204.86, 205.35, 205.21, 205.19, 205.21, 205.32 };
	memcpy(survey.data, datum, sizeof(datum));
	/*cout << "������Ҫ�������ݵĸ�����";
	cin >> survey.n;
	cout << "������" << survey.getN() << "�����ݣ�\n";
	for (i = 0; i < survey.getN(); i++)
		cin >> survey.data[i];
	cout << "\n�������" << survey.getN() << "������Ϊ��\n";
	for (i = 0; i < survey.getN(); i++)
		cout << survey.data[i] << endl;*/
	cout << "\n******�޳���ֵ�������ֵ������ƽ��ֵ���׼ƫ��******" << endl;
	survey.Divation();
	cout << "\n******�ж���������ϵͳ���**************************" << endl;
	survey.ErrorLine();
	cout << "\n******�ж�����������ϵͳ���************************" << endl;
	survey.ErrorCycle();
	if (survey.getFlag())					//flag=1��ʾ����ϵͳ���
	{
		c = survey.getSumVi2() / survey.getN();			//����ϵͳ���
		for (i = 0; i < survey.getN(); i++)
			survey.data[i] += c;
		cout << "\n====================================================\n";
		cout << "����ϵͳ���������Ϊ��\n";
		for (i = 0; i < survey.getN(); i++)
			cout << survey.data[i] << endl;
		cout << "c=" << c << endl;
		survey.Divation();
	}
	cout << "\n====================================================\n";
	cout << "����ƽ��ֵ�ı�׼ƫ��(����ֵ)Ϊ��" << survey.getSigma() / sqrt(survey.getN()) << endl;
	cout << "����������ʽΪ��x=" << survey.getAve() << "��" << 3 * survey.getSigma() / sqrt(survey.getN()) << endl;
	return 0;
}
/******************************************************************************
��  ����Divation()
��  ����
����ֵ��void
��  �ܣ��޳���ֵ�������ֵ������ƽ��ֵ���׼ƫ��
******************************************************************************/
void Mesure::Divation()
{
	int i, j, k;
	float absVi[N];         //absVi[N]Ϊ��Vi[N]ȡ����ֵ
	sumXi = 0.0;			   
	sumVi2 = 0.0;
	for (i = 0; i < n; i++)
		sumXi += data[i];
	ave = sumXi / (float)n;
	for (i = 0; i < n; i++)
	{
		vi[i] = data[i] - ave;
		sumVi2 += vi[i] * vi[i];
	}
	sigma = sqrt(sumVi2 / (float)(n - 1));
	for (i = 0; i < n; i++)
		absVi[i] = fabs(vi[i]);
	maxAbsVi = absVi[0];
	j = 0;
	for (i = 0; i < n; i++)
		if (absVi[i] > maxAbsVi)
		{
			maxAbsVi = absVi[i];
			j = i;
		}
	if (maxAbsVi > 3 * sigma)				        //��֤|Vi[N]|>=3�Ҳ��޳�
	{
		cout << "��" << ++j << "�������ǻ�ֵ��\n";
		cout << "��ֵ=" << data[j-1] << endl;
		for (k = j; k < n; k++)
			data[k - 1] = data[k];
		n = n - 1;
		Divation();
	}
	else
	{
		cout << "����ƽ��ֵΪ��" << ave << endl;
		cout << "��׼ƫ��Ϊ��" << sigma << endl;
	}
}
/******************************************************************************
��  ����ErrorLine()
��  ����
����ֵ��void
��  �ܣ��ж���������ϵͳ���
		���ֿƷ��оݣ�|ǰһ������-��һ������|<|���в�|����������ϵ��
******************************************************************************/
void Mesure::ErrorLine()
{
	int i;
	float former = 0.0, latter = 0.0, dValue;
	if (n % 2 == 0)
	{
		for (i = 0; i < n / 2; i++)
			former += vi[i];
		for (i = n / 2; i < n; i++)
			latter += vi[i];
	}
	else
	{
		for (i = 0; i < (n-1) / 2; i++)
			former += vi[i];
		for (i = (n-1) / 2; i < n; i++)
			latter += vi[i];
	}
	dValue = former - latter;
	if (fabs(dValue) < maxAbsVi)
	{
		cout << "��������ϵͳ����" << endl;
		flag = 1;
	}
	else
		cout << "����������ϵͳ���" << endl;
}
/******************************************************************************
��  ����ErrorCycle()
��  ����
����ֵ��void
��  �ܣ��ж�����������ϵͳ���
		����-��÷���оݣ�|i=0��n-1�Ĳв�v[i]*v[i+1]|��(�в�ƽ����/������(n-1))����������ϵ��
******************************************************************************/
void Mesure::ErrorCycle()
{
	int i;
	float sum = 0.0;
	for (i = 0; i < n - 1; i++)
		sum += vi[i] * vi[i + 1];
	if (fabs(sum) >= (sumVi2 / sqrt(n - 1)))
	{
		cout << "����������ϵͳ����" << endl;
		flag = 1;
	}
	else
		cout << "������������ϵͳ���" << endl;
}
