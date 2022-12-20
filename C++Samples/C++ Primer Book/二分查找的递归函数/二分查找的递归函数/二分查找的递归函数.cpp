/*1、函数的实现部分可以包含对该函数自身的调用。
2、有效递归函数体的定义：
(1)在函数完成其任务过程中的一种或多种情况，可以通过一个或多个的函数递归调用来完成其任务的缩略版本；
(2)在函数完成其任务过程中，存在不需要使用递归调用的一种或多种情况(递归的基本问题/终止问题)。
3、正确的递归函数满足3个属性：
(1)函数中没有无限递归的情况；
(2)每个终止情况都正确执行；
(3)对于包含递归的每个情况：如果所有的递归调用都正确地执行，那么整个函数就正确地执行。*/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
const int ARRAY_SIZE = 3;

void sort(int a[]);        //排序
void search(const int a[], int first, int last, int key, bool& found, int& location);
//前提条件：从a[first]~a[last]的数组元素是按照升序排列的。
//执行结果：若key不是在a[first]~a[last]之间的一个值，则found==false;
//          否则，a[location]=key且found=true。

int main()
{
	int a[ARRAY_SIZE];
	const int finalIndex = ARRAY_SIZE - 1;
	int key, location;
	bool found;
	sort(a);
	cout << "Enter number to be located: ";
	cin >> key;
	search(a, 0, finalIndex, key, found, location);
	if (found)
		cout << key << " is in index location "
		<< location << endl;
	else
		cout << key << " is not in the array." << endl;
	return 0;
}
void sort(int a[])
{
	int i, j, t;
	cout << "Input " << ARRAY_SIZE << " numbers : \n";
	for (i = 0; i < ARRAY_SIZE; i++)
		cin >> a[i];
	for (i = 0; i < ARRAY_SIZE - 1; i++)
		for (j = i + 1; j < ARRAY_SIZE; j++)
			if (a[j] < a[i])
			{
				t = a[i]; a[i] = a[j]; a[j] = t;
			}
	cout << "The array sorted:\n";
	for (i = 0; i < ARRAY_SIZE; i++)
		cout << a[i] << " ";
	cout << endl;
}
void search(const int a[], int first, int last, int key, bool& found, int& location)
{
	int mid;
	if (first > last)
	{
		found = false;
	}
	else
	{
		mid = (first + last) / 2;
		if (key == a[mid])
		{
			found = true;
			location = mid;
		}
		else if (key < a[mid])
		{
			search(a, first, mid - 1, key, found, location);
		}
		else if (key > a[mid])
		{
			search(a, mid + 1, last, key, found, location);
		}
	}
}

/*==========二分查找函数的迭代实现版本==========
相同计算机系统中，迭代版本程序运行的效率高于递归实现的，
迭代版本的程序实现是从递归版本的程序实现中导出来的。
void search(const int a[], int lowEnd, int highEnd, int key, bool& found, int& location)
{
int first = lowEnd;
int last = highEnd;
int mid;
found = false;
while ((first <= last) && !(found))
{
mid = (first + last) / 2;
if (key == a[mid])
{
found = true;
location = mid;
}
else if (key < a[mid])
{
last = mid - 1;
}
else if (key > a[mid])
{
first = mid + 1;
}
}
}*/