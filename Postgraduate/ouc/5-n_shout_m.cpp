/* 2017.3.25 20:15
	n个人围成圈，数到m的人出局
*/
#include <iostream>
#include <stdlib.h>
using namespace std;

//const int NUM = 8;  //人数

typedef struct Person
{
	int number;  //数据域
	struct Person* pNext;  //指针域
}NODE, *PNODE;

int main(void)
{
	int num, m;
	cout << "The numbers of person are ";
	cin >> num;
	cout << "The number shouted is ";
	cin >> m;

	PNODE pHead = (PNODE)malloc(sizeof(NODE));  //创建头结点
	if(NULL == pHead)
	{
		cout << "Cannot allocate memory for Head Node. Exit." << endl;
		exit(1);
	}
	PNODE  pTail = pHead;  //创建尾结点
	pTail->pNext = NULL;
	for(int i = 0; i < num; i++)
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));  //创建各个结点
		if(NULL == pNew)
		{
			cout << "Cannot allocate memory." << endl;
			exit(1);
		}
		pNew->number = i+1;
		pTail->pNext = pNew;
		pTail = pNew;
	}
	pTail->pNext = pHead->pNext;  //头尾相连

	PNODE pFront = pHead->pNext;
	PNODE pBack = pTail;
	PNODE pOut = NULL;
	cout << "The sequence out of person is:" << endl;
	for(int count = 0; count < num; count++)
	{
		i = 1;
		while(i != m)
		{
			pBack = pFront;
			pFront = pFront->pNext;
			i++;
		}
		pOut = pFront;
		cout << pOut->number << " ";
		pFront = pFront->pNext;
		pBack->pNext = pFront;
		free(pOut);
	}
	cout << endl;
	return 0;
}