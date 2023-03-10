/*
	2018.11.08 15:01 - 2018.11.24 01:51, 2019.05.29
	自定义实现群体数据结构：
	动态数组，链表，栈，队列，映射
*/

#include <iostream>
#include <string>
#include "Array.h"
#include "Stack.h"
#include "List.h"
#include "Queue.h"
#include "Map.h"
#include "String.h"
#include "DataIndex.h"

using namespace std;

template<class T>
void print(T arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

template<class T>
void print(DouBlyList<T>& dlist)
{
	POSITION pos = dlist.GetHeadPosition();
	while (pos)
	{
		cout << dlist.GetNext(pos) << " ";
	}
	cout << endl;
}

bool OrderByData(int first, int second)
{
	return first < second;
}

int main2(int argc, char* argv[])
{
	cout << "*** Template Class ***" << endl;
	cout << "== Array ===============================" << endl;
	Array<int> a(10);
	cout << a.GetSize() << endl;

	for (int i = 0; i < 5; i++)	//a.GetSize()
	{
		a[i] = i + 1;
		cout << a[i] << "-" << a.GetAt(i) << " ";
	}
	cout << endl;

	Array<int> b;
	b = a;
	//b.SetSize(15);
	cout << *b << endl;
	cout << "b.GetCount() = " << b.GetCount() << " b.GetSize() = " << b.GetSize() << endl;
	b.SetAt(4, 500);
	b.InsertAt(3, 220, 9);
	b.RemoveAt(3, 6);
	for (int j = 0; j < b.GetCount(); j++)
		cout << b[j] << " ";
	cout << endl;
	cout << "b.GetCount() = " << b.GetCount() << " b.GetSize() = " << b.GetSize() << endl;


	cout << "== Stack ===============================" << endl;
	Stack<int> stack(10);
	for (int ii = 0; ii < 5; ii++)
		stack.Push(ii + 100);
	cout << "Peek() = " << stack.Peek() << endl;
	cout << "GetCount = " << stack.GetCount() << endl;
	cout << stack.Pop() << endl;
	cout << stack.Pop() << endl;

	stack.Clear();
	//cout << stack.Pop() << endl;
	cout << "empty? " << stack.IsEmpty() << endl;
	cout << "full? " << stack.IsFull() << endl;
	 
	cout << "== List ===============================" << endl;
	List<int> list;
	list.SetName("list:");
	cout << list.GetName().c_str() << endl;
	list.AddTail(12);
	list.AddTail(13);
	list.AddHead(10);

	list.PrintList();
	cout << endl;
	cout << "size = " << list.GetSize() << endl;

	cout << list.InsertAfter(1, 14) << endl;
	list.PrintList();
	cout << endl;
	cout << "size = " << list.GetSize() << endl;

	//cout << list.InsertAt(10, 100) << endl;
	//list.PrintList();
	//cout << endl;

	cout << "insert index = 2" << endl;
	cout << list.InsertAfter(2, 15) << endl;
	list.PrintList();
	cout << endl;
	cout << "size = " << list.GetSize() << endl;

	list.SortAscent();
	cout << "sort: " << endl;
	list.PrintList();
	cout << endl;

	list.ModifyAt(2, 20);
	list.PrintList();
	cout << endl;

	int del = 0;
	list.DeleteHead(&del);
	list.PrintList();
	cout << endl;

	list.DeleteTail(&del);
	list.PrintList();
	cout << endl;

	int de = 0;
	list.DeleteAt(1, &de);
	cout << "delete index = 1 = " << de << endl;
	list.PrintList();
	cout << endl;

	cout << "pos = " << list.FindPosition(14) << endl;

	cout << list.IsEmpty() << endl;

	cout << "== CircularQueue ==========================================" << endl;
	CircularQueue<int> cq(10);
	cq.QueuePush(13);
	cq.QueuePush(24);
	cq.QueuePush(36);

	cout << cq.QueuePop() << endl;
	cout << cq.QueueFront() << endl;
	cout << "QueueLength = " << cq.QueueLength() << endl;
	cout << cq.IsEmpty() << endl;
	cout << cq.IsFull() << endl;

	cout << "== DataIndex ==========================================" << endl;
	int aa[] = { 14, 13, 11, 15, 12 };
	cout << DataIndex<int>::SequenceSearch(aa, 5, 11) << endl;
	cout << DataIndex<int>::BinarySearch(aa, 5, 11) << endl;

	//DataIndex<int>::BubleSort(aa, 5);
	//DataIndex<int>::SelectSort(aa, 5);
	//DataIndex<int>::InsertSort(aa, 5);
	//DataIndex<int>::ExchangeSort(aa, 5);

	//cout << "ExternalSort: " << endl;
	//int** pOrder = DataIndex<int>::ExternalOrderArray(aa, 5, OrderByData);
	//DataIndex<int>::ExternalPrintArray(pOrder, 5);

	cout << "ExternalSort2: " << endl;
	int* pOrder2 = DataIndex<int>::ExternalOrderIndex(aa, 5, OrderByData);
	DataIndex<int>::ExternalPrintIndex(pOrder2, aa, 5);
	for (int i = 0; i < _countof(aa); i++)
		cout << aa[i] << " ";
	cout << endl;

	cout << "==DouBlyList ==========================================" << endl;
	DouBlyList<double> dlist;
	dlist.AddHead(11.1);
	dlist.AddHead(22.2);
	dlist.AddTail(44.4);
	dlist.AddTail(5.6);

	cout << "正向输出：" << endl;
	POSITION pos = dlist.GetHeadPosition();
	while (pos)
	{
		//cout << dlist.GetAt(pos) << " ";
		//dlist.GetNext(pos);
		cout << dlist.GetNext(pos) << " ";
	}
	cout << endl;
	cout << "IsEmpty = " << dlist.IsEmpty() << endl;
	
	cout << "反向输出：" << endl;
	POSITION posr = dlist.GetTailPosition();
	while (posr)
	{
		cout << dlist.GetPrev(posr) << " ";
	}
	cout << endl;
	cout << "GetCount = " << dlist.GetCount() << endl;

	POSITION posr2 = dlist.GetTailPosition();
	dlist.InsertAfter(posr2, 101.1);
	dlist.InsertBefore(posr2, 99.9);
	print(dlist);

	POSITION posf = dlist.Find(NULL, 99);
	if (nullptr == posf)
		cout << "not found!" << endl;
	else
		cout << dlist.GetAt(posf) << endl;

	POSITION posi = dlist.FindIndex(2);
	if (nullptr == posi)
		cout << "correct index!" << endl;
	else
		cout << dlist.GetAt(posi) << endl;

	dlist.SetAt(posi, 444);
	cout << dlist.GetAt(posi) << endl;
	cout << (dlist.GetAt(posi) = 400) << endl;
	
	dlist.RemoveAt(posi);
	print(dlist);
	dlist.RemoveAll();
	cout << dlist.IsEmpty() << endl;

	cout << "== LinkedList ========================" << endl;
	LinkedList<int> llist;
	llist.push_back(12);
	llist.push_back(22);
	llist.push_back(44);
	llist.push_front(70);
	llist.push_front(100);

	LinkedList<int>::Iterator it;
	for (it = llist.begin(); it != llist.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	cout << "ExternalSort: " << endl;
	//LinkedList<int>::Iterator* order = llist.ExternalOrder(OrderByData);
	//llist.ExternalPrint(order);
	llist.ExternalPrint(llist.ExternalOrder(OrderByData));

	cout << "== String ======================================" << endl;
	String strtt("nihaomacat");
	String strdd = "hahaha";
	String straa(strdd);
	String strbb('a', 3);
	String strcc("123456789", 15);
	cout << strtt << " " << strdd << " " << straa << " " << strbb << " "  << strcc << endl;
	cout << strcc[5] << endl;
	String strtt2 = strtt;
	//if (strtt == "nihao")
	if(strtt == strtt2)
		cout << "true" << endl;
	else
		cout << "false" << endl;

	cout << "GetLength() = " << strtt.GetLength() << ", GetSize() = " << strtt.GetSize() << endl;
	cout << "MakeUpper() = " << strtt.MakeUpper() << endl;
	cout << "MakeLower() = " << strtt.MakeLower() << endl;
	cout << "MakeReverse() = " << strtt.MakeReverse() << endl;

	cout << "Find index = " << strcc.Find('7') << endl;
	cout << "Find string = " << strcc.Find("780") << endl;
	cout << "Middle = " << strcc.Middle(4) << " " << strcc.Middle(4, 13) << endl;
	cout << "Left = " << strcc.Left(5) << " " << strcc.Right(5) << endl;

	cout << "== HashMap ==================================================================" << endl;
	HashMap<int, string> maps;
	maps.SetAt(12, "gode");
	maps.SetAt(78, "girl");
	maps[40] = "boy";
	
	string value;
	if (maps.Lookup(78, value))
		cout << value.c_str() << endl;
	else
		cout << "not found!" << endl;

	if (maps.RemoveKey(40))
		cout << "remove ok" << endl;
	else
		cout << "remove not" << endl;
	maps.RemoveAll();

	cout << "== BinaryTreeMap ==========================================" << endl;
	BinaryTreeMap<int, string> btmap;
	btmap.SetAt(123, "one");
	btmap.SetAt(456, "two");
	btmap[789] = "threeqw";
	btmap[20] = "night";

	string valuem;
	if (btmap.Lookup(456, valuem))
		cout << "Lookup: " << valuem.c_str() << endl;
	else
		cout << "lookup not" << endl;
	
	cout << "DLR = ";
	btmap.Preorder(btmap.GetData());
	cout << endl;

	cout << "LDR = ";
	btmap.Inorder(btmap.GetData());
	cout << endl;

	cout << "LRD = ";
	btmap.Postorder(btmap.GetData());
	cout << endl;

	btmap.RemoveAll();

	cout << "== QuickSort: ==========================================" << endl;
	const int SIZE = 5;
	int qs[SIZE] = { 3, 5, 4, 1, 2 };
	cout << "Source Data: ";
	for (int i = 0; i < SIZE; i++)
		cout << qs[i] << " ";
	
	DataIndex<int>::QuickSort(qs, 0, SIZE - 1);
	cout << "\nQuick Sort: ";
	for (int j = 0; j < SIZE; j++)
		cout << qs[j] << " ";
	cout << endl;

	system("pause");
	return 0;
}

int main3(int argc, char* argv[])
{
	cout << "== gcd: ==" << endl;
	int aa = 20;
	int bb = 16;
	cout << aa << " " << bb << " gcd = " << DataIndex<int>::gcd(aa, bb) << endl;

	int ary[] = { 5, 4, 3, 3, 2 };
	int n = 5;
	print(ary, n);
	cout << "== InsertSort ==" << endl;
	DataIndex<int>::InsertSort(ary, n);
	print(ary, n);

	std::swap(aa, bb);
	cout << aa << " " << bb << endl;

	system("pause");
	return 0;
}

void max_heapify(int arr[], int start, int end) {
	// 建立父節點指標和子節點指標
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { // 若子節點指標在範圍內才做比較
		if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
			son++;
		if (arr[dad] > arr[son]) // 如果父節點大於子節點代表調整完畢，直接跳出函數
			return;
		else { // 否則交換父子內容再繼續子節點和孫節點比較
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(int arr[], int len) {
	// 初始化，i從最後一個父節點開始調整
	for (int i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	// 先將第一個元素和已经排好的元素前一位做交換，再從新調整(刚调整的元素之前的元素)，直到排序完畢
	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		max_heapify(arr, 0, i - 1);
	}
}

int main4() 
{
	cout << "== Heap Sort == " << endl;
	int arr[] = { 5,2,3,1,4,8,7 };
	int len = (int) sizeof(arr) / sizeof(*arr);
	cout << "arr = ";
	print(arr, len);
	heap_sort(arr, len);
	print(arr, len);

	system("pause");
	return 0;
}

int main5() 
{
	cout << "== Shell Sort == " << endl;
	int ary[] = { 5,2,3,1,4,8,7 };
	int len = (int) sizeof(ary) / sizeof(*ary);
	cout << "ary = ";
	print(ary, len);
	DataIndex<int>::ShellSort(ary, len);
	print(ary, len);

	system("pause");
	return 0;
}

int main11()
{
	std::cout << "== Heap Sort == " << std::endl;
	int arr[] = { 5,2,3,1,4,8,7 };
	int len = sizeof(arr) / sizeof(*arr);
	std::cout << "arr = ";
	DataIndex<int>::Print(arr, len);
	DataIndex<int>::HeapSort(arr, len);
	DataIndex<int>::Print(arr, len);

	cout << "gcd = " << DataIndex<int>::gcd(3120, 2764) << endl;

	system("pause");
	return 0;
}

int main7()
{
	std::cout << "== Merge Sort == " << std::endl;
	int arr[] = { 5,2,3,1,4,8,7 };
	int len = sizeof(arr) / sizeof(*arr);
	std::cout << "arr = ";
	DataIndex<int>::Print(arr, len);
	DataIndex<int>::MergeSort(arr, len);
	DataIndex<int>::Print(arr, len);

	system("pause");
	return 0;
}

int main8()
{
	std::cout << "== Count Sort == " << std::endl;
	int arr[] = { 5,2,3,1,4,8,7 };
	int len = (int) sizeof(arr) / sizeof(*arr);
	std::cout << "arr = ";
	DataIndex<int>::Print(arr, len);
	DataIndex<int>::CountSort(arr, len);
	DataIndex<int>::Print(arr, len);

	system("pause");
	return 0;
}

int main9()
{
	std::cout << "== Bucket Sort == " << std::endl;
	int arr[] = { 5,2,3,1,4,8,7 };
	int len = (int) sizeof(arr) / sizeof(*arr);
	std::cout << "arr = ";
	DataIndex<int>::Print(arr, len);
	DataIndex<int>::BucketSort(arr, len);
	DataIndex<int>::Print(arr, len);

	system("pause");
	return 0;
}

int main10()
{
	std::cout << "== Radix Sort == " << std::endl;
	int arr[] = { 5,2,3,1,4,8,7 };
	int len = (int) sizeof(arr) / sizeof(*arr);
	std::cout << "arr = ";
	DataIndex<int>::Print(arr, len);
	DataIndex<int>::RadixSort(arr, len);
	DataIndex<int>::Print(arr, len);

	system("pause");
	return 0;
}

int main12()
{
	std::cout << "== Merge Sort 2 == " << std::endl;
	int arr[] = { 5,2,3,1,4,8,7 };
	int len = (int) sizeof(arr) / sizeof(*arr);
	std::cout << "arr = ";
	DataIndex<int>::Print(arr, len);
	DataIndex<int>::MergeSort2(arr, len);
	DataIndex<int>::Print(arr, len);

	system("pause");
	return 0;
}

int main()
{
	cout << "== Rotate Binary Search == " << endl;
	int arr[] = { 9, 10, 11, 12, 13, 1, 3, 4, 5, 8 };
	int len = (int) sizeof(arr) / sizeof(*arr);
	print(arr, len);
	cout << DataIndex<int>::RotateBinarySearch(arr, len, 12) << endl;

	system("pause");
	return 0;
}
