/*	2018.05.17 11:08
	��������B 
������ί��֣��������Ǵ���0����������ί�������ڵ���5��С�ڵ���50����ȥ��������߷ֺ�������ͷ֣�
���㲢���ƽ���÷֣�С���������λ��Ч���֣���
*/
#include <iostream>
#include <iomanip>
#define N 50		//��ί������� 
using namespace std;

void InsertSort(int value[], int lenght);
int main()
{
	int score[N];
	int index = 0, temp;
	int sum = 0;
	float average;
	while(true)
	{
		cin >> temp;
		if(-1 == temp)
			break;
		else
			score[index++] = temp;		 
	}
	
	InsertSort(score, index); 
	for(int i = 2; i < index - 2; i++)
	{
		sum += score[i]; 
	} 
	average = 1.0 * sum / (index - 4);
	cout << fixed << setprecision(2) << average << endl;
	return 0;
}

/* �������� */
void InsertSort(int value[], int lenght)
{
	int temp;
	for(int i = 0; i < lenght - 1; i++)
		for(int j = i + 1; j < lenght; j++)
			if(value[j] < value[i])
			{
				temp = value[j];
				value[j] = value[i];
				value[i] = temp;
			}
}
