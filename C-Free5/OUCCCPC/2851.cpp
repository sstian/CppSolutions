/*
	2018.05.17 14:37
	数组与排序B 
*/
#include <iostream>
#include <iomanip>
#include <cstring>
#define N 9			//最大学生人数 
using namespace std;

struct Student
{
	int number;		//学号 
	char name[11];	//姓名 
	int score[4];	//总成绩，数学、英语、语文 		
};

void swap(struct Student& one, struct Student& two);
int main()
{
	struct Student stu[N]; 
	int num;
	int rank[N];	//排名 
	//输入 
	while(true)
	{
		cin >> num;
		if(num > N)
			cout << "Please input 1-9." << endl;
		else
			break;
	}
	for(int i = 0; i < num; i++)
	{
		cin >> stu[i].number >> stu[i].name;
		cin >> stu[i].score[1] >> stu[i].score[2] >> stu[i].score[3];
		stu[i].score[0] = stu[i].score[1] + stu[i].score[2] + stu[i].score[3];
	}
	// 排序 
//	int index;
	for(int j = 0; j < num - 1; j++)
	{
//		index = j;
		for(int k = j + 1; k < num; k++)
		{
			if(stu[k].score[0] < stu[j].score[0])
//				index = k;
				swap(stu[k],stu[j]);
		 	else if(stu[k].score[0] == stu[j].score[0] && stu[k].number < stu[j].number)
//		 		index = k;
	 			swap(stu[k],stu[j]);
		}
//		if(index != j)
//			swap(stu[index],stu[j]);
		
	}
	int noi = 2;
	rank[num-1] = 1;
	for(int n = num - 2; n >= 0; n--, noi++)
	{
		if(stu[n].score[0] == stu[n+1].score[0])
			rank[n] = rank[n+1];
		else
			rank[n] = noi;
	} 
	// 输出  
	for(int m = 0; m < num; m++)
	{
		cout << setw(4) << rank[m];
		cout << setw(10) << stu[m].number << setw(10) << stu[m].name;
		for(int n = 1; n < 4; n++)
			cout << setw(5) << stu[m].score[n];
		cout << endl;
	}
	return 0;
}
/* 结构体元素交换 */ 
void swap(struct Student& one, struct Student& two)
{
	struct Student temp;
	temp = one;
	one = two;
	two = temp;
/*	
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
*/
}
