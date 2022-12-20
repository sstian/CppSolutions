/*
	2018.05.12 16:02
	����������A  
*/
#include <iostream>
#include <iomanip>
#define N 9
using namespace std;

struct Student
{
	int number;		//ѧ�� 
	char name[11];	//���� 
	int score[4];	//�ܳɼ�����ѧ��Ӣ����� 		
};

void swap(struct Student& one, struct Student& two);
int main()
{
	struct Student stu[N]; 
	int num;
	//���� 
	cout << "Input the numbers of student:" << endl;
	while(true)
	{
		cin >> num;
		if(num > N)
			cout << "Please input 1-9" << endl;
		else
			break;
	}
	cout << "Input " << num << " students' number, name, Math, English, Chinese:" << endl;
	for(int i = 0; i < num; i++)
	{
		//cout << "No" << i + 1 << ": ";
		cin >> stu[i].number >> stu[i].name;
		cin >> stu[i].score[1] >> stu[i].score[2] >> stu[i].score[3];
		stu[i].score[0] = stu[i].score[1] + stu[i].score[2] + stu[i].score[3];
	}
	// ���� 
	for(int j = 0; j < num - 1; j++)
	{
		for(int k = j + 1; k < num; k++)
		{
			if(stu[k].score[0] > stu[j].score[0])
				swap(stu[k],stu[j]);
		 	if(stu[k].score[0] == stu[j].score[0])
		 		if(stu[k].number < stu[j].number)
		 			swap(stu[k],stu[j]);
		}
	}
	// ���  
	int rank = 1;
	cout << endl << setw(4) << rank << " ";
	for(int m = 0; m < num; m++)
	{
		if(m >= 1)
		{
			if(stu[m].score[0] == stu[m-1].score[0])
				cout << setw(4) << rank << " ";
			else
			{
				rank = m + 1;
				cout << setw(4) << rank << " ";
			}
		}	
		cout << setw(10) << stu[m].number << " " << setw(10) << stu[m].name << " ";
		for(int n = 1; n < 4; n++)
			cout << setw(5) << stu[m].score[n] << " ";
		cout << endl;
	}
	return 0;
}
/* �ṹ��Ԫ�ؽ��� */ 
void swap(struct Student& one, struct Student& two)
{
	struct Student temp;
	
	temp.number = one.number;
	strcpy(temp.name, one.name);
	for(int i = 0; i < 4; i++)
		temp.score[i] = one.score[i];
		
	one.number = two.number;
	strcpy(one.name, two.name);
	for(int j = 0; j < 4; j++)
		one.score[j] = two.score[j];

	two.number = temp.number;
	strcpy(two.name, temp.name);
	for(int k = 0; k < 4; k++)
		two.score[k] = temp.score[k];	
}
