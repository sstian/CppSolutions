/*1��������ʵ�ֲ��ֿ��԰����Ըú�������ĵ��á�
2����Ч�ݹ麯����Ķ��壺
(1)�ں����������������е�һ�ֻ�������������ͨ��һ�������ĺ����ݹ�������������������԰汾��
(2)�ں����������������У����ڲ���Ҫʹ�õݹ���õ�һ�ֻ�������(�ݹ�Ļ�������/��ֹ����)��
3����ȷ�ĵݹ麯������3�����ԣ�
(1)������û�����޵ݹ�������
(2)ÿ����ֹ�������ȷִ�У�
(3)���ڰ����ݹ��ÿ�������������еĵݹ���ö���ȷ��ִ�У���ô������������ȷ��ִ�С�*/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
const int ARRAY_SIZE = 3;

void sort(int a[]);        //����
void search(const int a[], int first, int last, int key, bool& found, int& location);
//ǰ����������a[first]~a[last]������Ԫ���ǰ����������еġ�
//ִ�н������key������a[first]~a[last]֮���һ��ֵ����found==false;
//          ����a[location]=key��found=true��

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

/*==========���ֲ��Һ����ĵ���ʵ�ְ汾==========
��ͬ�����ϵͳ�У������汾�������е�Ч�ʸ��ڵݹ�ʵ�ֵģ�
�����汾�ĳ���ʵ���Ǵӵݹ�汾�ĳ���ʵ���е������ġ�
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