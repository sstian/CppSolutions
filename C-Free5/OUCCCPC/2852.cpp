/*	2018.05.17 11:08
	大奖赛评分B 
读入评委打分（分数都是大于0的整数，评委人数大于等于5，小于等于50），去掉两个最高分和两个最低分，
计算并输出平均得分（小数点后保留两位有效数字）。
*/
#include <iostream>
#include <iomanip>
#define N 50		//评委最多人数 
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

/* 插入排序 */
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
