/*
	2018.11.09 21:14 - 2019.10.31 18:28
	数据检索 类模板：
	查找：顺序查找，折半查找
	排序：冒泡排序，选择排序，插入排序，快速排序，希尔排序，堆排序，归并排序，计数排序，桶排序，基数排序
2018.11.19 10:05 - 11:45 增加表外排序，通过二级指针指向元素或一级指针记录下标，存储序列而元素原始位置保持不变。
2019.05.29 增加快速排序并测试
2019.08.27 增加结合辗转相除法和更相减损术求最大公约数，并测试
2019.09.07 完成十大排序算法的代码，并测试通过
2019.10.31 添加归并排序-C语言版 MergeSort2，优化计数排序根据最大值最小值缩小区间规模，添加旋转数组的二分查找
*/
#pragma once
#include <vector>
#include <algorithm>

template<class T>
class DataIndex
{
public:
	// 表外排序回调函数指针
	using OrderCallback = bool(*)(T, T);

public:
	DataIndex();
	~DataIndex();

	// 顺序查找，返回查到的值的索引，没有则返回-1
	static int SequenceSearch(const T arr[], int n, const T& key);

	// 折半查找
	static int BinarySearch(const T arr[], int n, const T& key);
	// 旋转数组的二分查找， { 9, 10, 11, 12, 13, 1, 3, 4, 5, 8 }, 10, 12 -> 3
	static int RotateBinarySearch(const T arr[], int n, const T& key);

	// 冒泡排序
	static void BubleSort(T arr[], int n);

	// 选择排序
	static void SelectSort(T arr[], int n);

	// 插入排序
	static void InsertSort(T arr[], int n);

	//// 交换排序
	//static void ExchangeSort(T arr[], int n);

	// 快速排序
	static int FindPos(T arr[], int low, int high);
	static void QuickSort(T arr[], int low, int high);
	static void QuickSort(T arr[], int n);

	// 堆排序
	static void MaxHeapify(T arr[], int start, int end);
	static void HeapSort(T arr[], int n);

	// 希尔排序
	static void ShellSort(T arr[], int n);

	// 归并排序, begin = 0, end = 最后元素索引下标
	static void Merge(std::vector<T>& vecArr, int begin, int middle, int end);
	static void MergeSort(std::vector<T>& vecArr, int begin, int end);
	static void MergeSort(T arr[], int n);
	// 归并排序，C语言版
	static void Merge2(T arr[], int begin, int middle, int end);
	static void MergeSort2(T arr[], int begin, int end);
	static void MergeSort2(T arr[], int n);

	// 计数排序
	// 适用于正整数，且取值范围相差不大
	static void CountSort(int arr[], int n);

	// 桶排序
	// 桶表示：二维动态数组；桶数量：(最大值-最小值)/(长度-1)；桶内排序：系统std::sort或自定义的
	static void BucketSort(T arr[], int n);

	// 基数排序
	static void RadixSort(T arr[], int n);

	// 交换。亦可用于交换指针指向
	static void Swap(T& x, T& y);

	// 显示，打印数组元素
	static void Print(T arr[], int n);
	static void Print(std::vector<T> vec);


	// 数组表外排序，二级指针
	static T** ExternalOrderArray(T arr[], int n, OrderCallback function);
	// 表外排序打印，二级指针
	static void ExternalPrintArray(T** pOrder, int n);

	// 数组表外排序，一级指针，记录下标
	static T* ExternalOrderIndex(T arr[], int n, OrderCallback function);
	// 表外排序打印，一级指针，记录下标
	static void ExternalPrintIndex(T* pOrder, T arr[], int n);

	// 求最大公约数：辗转相除法+更相减损术
	static int gcd(int a, int b);

};

template<class T>
DataIndex<T>::DataIndex()
{
}

template<class T>
DataIndex<T>::~DataIndex()
{
}

template<class T>
inline int DataIndex<T>::SequenceSearch(const T arr[], int n, const T& key)
{
	for (int i = 0; i < n; i++)
		if (arr[i] == key)
			return i;

	return -1;
}

template<class T>
inline int DataIndex<T>::BinarySearch(const T arr[], int n, const T& key)
{
	int mid, low = 0, high = n - 1;	//中间，低与高索引下标
	T midval;
	while (low <= high)
	{
		mid = (low + high) / 2;
		midval = arr[mid];
		
		if (key == midval)
			return mid;
		else if (key < midval)
			high = mid - 1;
		else
			low = mid + 1;
	}

	return -1;
}

template<class T>
inline int DataIndex<T>::RotateBinarySearch(const T arr[], int n, const T & key)
{
	int mid, low = 0, high = n - 1;
	T midval;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		midval = arr[mid];
		if (key == midval)
			return mid;
		//情况A：旋转点在中位数右侧
		if (midval >= arr[low])
		{
			//最左侧元素 <= 查找目标 < 中位数
			if (arr[low] <= key && key < midval)
				high = mid - 1;
			else
				low = mid + 1;
		}
		//情况B：旋转点在中位数左侧，或与中位数重合
		else
		{
			//中位数 < 查找目标 <= 最右侧元素
			if (midval < key && key <= arr[high])
				low = mid + 1;
			else
				high = mid - 1;
		}
	}
	return -1;
}

template<class T>
inline void DataIndex<T>::BubleSort(T arr[], int n)
{
	//for (int i = 0; i < n - 1; i++)
	//	for (int j = i + 1; j < n; j++)
	//		if (arr[i] > arr[j])
	//			DataIndex::Swap(arr[i], arr[j]);

	// 算法2
	for (int ii = 0; ii < n - 1; ii++)
		for (int jj = 0; jj < n - ii - 1; jj++)
			if (arr[jj + 1] < arr[jj])
				DataIndex::Swap(arr[jj + 1], arr[jj]);
}

template<class T>
inline void DataIndex<T>::SelectSort(T arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int small = i;
		for (int j = i + 1; j < n; j++)
			if (arr[j] < arr[small])
				small = j;
		if (small != i)
			DataIndex::Swap(arr[small], arr[i]);
	}
}

template<class T>
inline void DataIndex<T>::InsertSort(T arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int j = i;							//记录索引下标
		T value = arr[i];					//记录索引数值
		while (j > 0 && value < arr[j - 1])
			arr[j--] = arr[j - 1];
		arr[j] = value;
	}
}

//template<class T>
//inline void DataIndex<T>::ExchangeSort(T arr[], int n)
//{
//	int last;
//	int i = n - 1;
//	while (i > 0)
//	{
//		last = 0;
//		for(int j = 0; j < i; j++)
//			if (arr[j + 1] < arr[j])
//			{
//				DataIndex::Swap(arr[j + 1], arr[j]);
//				last = j;
//			}
//		i = last;
//	}
//}

template<class T>
int DataIndex<T>::FindPos(T arr[], int low, int high)
{
	T value = arr[low];
	// 循环结束时，low == high
	while (low < high)
	{
		while (low < high && arr[high] >= value)
			--high;
		arr[low] = arr[high];

		while (low < high && arr[low] <= value)
			++low;
		arr[high] = arr[low];
	}
	arr[low] = value;

	return low;
}

template<class T>
void DataIndex<T>::QuickSort(T arr[], int low, int high)
{
	if (low < high)
	{
		int pos = DataIndex<T>::FindPos(arr, low, high);
		DataIndex<T>::QuickSort(arr, low, pos - 1);
		DataIndex<T>::QuickSort(arr, pos + 1, high);
	}
}

template<class T>
inline void DataIndex<T>::QuickSort(T arr[], int n)
{
	DataIndex<T>::QuickSort(arr, 0, n - 1);
}

template<class T>
inline void DataIndex<T>::MaxHeapify(T arr[], int start, int end)
{
	// 父节点和子结点索引
	int dad = start;
	int son = dad * 2 + 1;
	// 子结点索引在范围内
	while (son <= end)
	{
		if (son + 1 <= end && arr[son] < arr[son + 1])	//比较子结点大小，选择最大的 //son + 1 <= end <=> son < end
			son++;
		else if (arr[dad] > arr[son])					//若父节点>子结点，跳出函数
			return;
		else											//交换父子结点内容，再比较下一个结点
		{
			Swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

template<class T>
inline void DataIndex<T>::HeapSort(T arr[], int n)
{
	// 初始化，i从最后一个父节点开始调整
	for (int i = n / 2 - 1; i >= 0; i--)
		MaxHeapify(arr, i, n - 1);

	// 交换首元素（已是最大值）和末尾元素，重新调整
	for (int j = n - 1; j > 0; j--)
	{
		Swap(arr[0], arr[j]);
		MaxHeapify(arr, 0, j - 1);
	}
}

template<class T>
inline void DataIndex<T>::ShellSort(T arr[], int n)
{
	int h = 1;
	while (h < n / 3)
		h = h * 3 + 1;
	while (h >= 1)
	{
		for (int i = h; i < n; i++)
			for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h)
				std::swap(arr[j], arr[j - h]);
		h = h / 3;
	}
}

template<class T>
inline void DataIndex<T>::Merge(std::vector<T>& vecArr, int begin, int middle, int end)
{
	// preconditions:
	// Array[front...mid] is sorted
	// Array[mid+1 ... end] is sorted
	// Copy Array[front ... mid] to LeftSubArray
	// Copy Array[mid+1 ... end] to RightSubArray
	std::vector<T> leftArr(vecArr.begin() + begin, vecArr.begin() + middle + 1);
	std::vector<T> rightArr(vecArr.begin() + middle + 1, vecArr.begin() + end + 1);
	leftArr.insert(leftArr.end(), std::numeric_limits<T>::max());
	rightArr.insert(rightArr.end(), std::numeric_limits<T>::max());

	// Pick min of leftArr[nleft] and rightArr[nright], and put into vecArr[i]
	int nleft = 0, nright = 0;
	for (int index = begin; index <= end; index++)
		vecArr[index] = (leftArr.at(nleft) < rightArr.at(nright) ? 
			leftArr.at(nleft++) : rightArr.at(nright++));
}

template<class T>
inline void DataIndex<T>::MergeSort(std::vector<T>& vecArr, int begin, int end)
{
	if (begin >= end)
		return;
	int middle = (begin + end) / 2;	//or int middle = begin + (end - begin) / 2;
	// 分解
	MergeSort(vecArr, begin, middle);
	MergeSort(vecArr, middle + 1, end);
	// 归并
	Merge(vecArr, begin, middle, end);
}

template<class T>
inline void DataIndex<T>::MergeSort(T arr[], int n)
{
	std::vector<T> vecArr;
	for (int i = 0; i < n; i++)
		vecArr.push_back(arr[i]);

	MergeSort(vecArr, 0, n-1);

	for (int j = 0; j < n; j++)
		arr[j] = vecArr.at(j);
}

template<class T>
inline void DataIndex<T>::Merge2(T arr[], int begin, int middle, int end)
{
	//开辟额外大集合，设置指针
	int len = end - begin + 1;
	int* tarr = new int[len];
	int i = 0, ib = begin, ie = middle + 1;
	//比较两个小集合的元素，依次放入大集合
	while (ib <= middle && ie <= end)
		tarr[i++] = arr[ib] <= arr[ie] ? arr[ib++] : arr[ie++];

	//左侧小集合还有剩余，依次放入大集合尾部
	while (ib <= middle)
		tarr[i++] = arr[ib++];
	//右侧小集合还有剩余，依次放入大集合尾部
	while (ie <= end)
		tarr[i++] = arr[ie++];

	//把大集合的元素复制回原数组
	for (int k = 0; k < len; k++)
		arr[begin + k] = tarr[k];

	delete[] tarr;
}

template<class T>
inline void DataIndex<T>::MergeSort2(T arr[], int begin, int end)
{
	if (begin >= end)
		return;
	//折半成两个小集合，分别进行递归
	int middle = (begin + end) / 2;	//or int middle = begin + (end - begin) / 2;
	MergeSort2(arr, begin, middle);
	MergeSort2(arr, middle + 1, end);
	//把两个有序小集合，归并成一个大集合
	Merge2(arr, begin, middle, end);

}

template<class T>
inline void DataIndex<T>::MergeSort2(T arr[], int n)
{
	MergeSort2(arr, 0, n - 1);
}

template<class T>
inline void DataIndex<T>::CountSort(int arr[], int n)
{
	//找到数组中最大值最小值，以缩小区间规模
	int max = arr[0];
	int min = arr[0];
	for (int i = 1; i < n; i++)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}

	//初始化计数数组为0
	int d = max - min;
	int* countArr = new int[d + 1];
	memset(countArr, 0, sizeof(int) * (d + 1));	//起始地址，初始值，字节数！
	//计数
	for (int j = 0; j < n; j++)
		countArr[arr[j] - min]++;
	//顺序累加
	for (int k = 1; k < max + 1; k++)
		countArr[k] += countArr[k - 1];

	//初始化排序后的数组
	int* sortedArr = new T[n];
	//排序，原数组中的元素arr[s]在计数数组中排第x名，则保存在排序数据的x-1位置，需要--
	for (int s = n - 1; s >= 0; s--)
		sortedArr[--countArr[arr[s] - min]] = arr[s];
	//将排序后的数据拷贝到原数组
	for (int t = 0; t < n; t++)
		arr[t] = sortedArr[t];

	delete[] countArr;
	delete[] sortedArr;
}

template<class T>
inline void DataIndex<T>::BucketSort(T arr[], int n)
{
	// 桶列表
	std::vector<std::vector<T>> vecBucket;
	std::vector<T> vt;
	for (int i = 0; i < n; i++)
		vecBucket.push_back(vt);	
	// 最大最小值，每个桶的存储区间
	T max = arr[0];
	T min = arr[0];
	for (int j = 1; j < n; j++)
		if (arr[j] > max)
			max = arr[j];
		else if (arr[j] < min)
			min = arr[j];
	double section = 1.0 * (max - min) / (n - 1);

	// 数据入桶，存放桶的位置下标 = 当前数值 / 存储区间 - 1 
	for (int k = 0; k < n; k++)
	{
		int num = (int)(arr[k] / section) - 1;
		if (num < 0)
			num = 0;
		vecBucket.at(num).push_back(arr[k]);
	}

	// 桶内排序
	for (auto& at : vecBucket)
		std::sort(at.begin(), at.end());	//调用系统排序
	// 写入原数组
	int index = 0;
	for (auto& vvi : vecBucket)
		for (auto& vi : vvi)
			arr[index++] = vi;
}

template<class T>
inline void DataIndex<T>::RadixSort(T arr[], int n)
{
	// 桶列表，长度为10，装入余数为0-9的数据
	std::vector<std::vector<T>> vecBucket;
	std::vector<T> vt;
	for (int radix = 0; radix < 10; radix++)
		vecBucket.push_back(vt);
	// 排序位置，最大值
	int location = 1;
	int max = arr[0];
	for (int j = 1; j < n; j++)
		if (arr[j] > max)
			max = arr[j];

	while (true)
	{
		//判断是否排完
		int dd = (int)pow(10, location - 1);
		if (max < dd)
			break;

		// 数据入桶，计算余数，放入相应的桶
		for (int k = 0; k < n; k++)
		{
			int num = (arr[k] / dd) % 10;
			vecBucket.at(num).push_back(arr[k]);
		}

		// 写回数组
		int index = 0;
		for (auto& vvi : vecBucket)
		{
			for (auto& vi : vvi)
				arr[index++] = vi;
			vvi.clear();
		}		
		location++;
	}
}

template<class T>
inline void DataIndex<T>::Swap(T & x, T & y)
{
	T t = x;
	x = y;
	y = t;
}

template<class T>
inline void DataIndex<T>::Print(T arr[], int n)
{
	for (int i = 0; i < n; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

template<class T>
inline void DataIndex<T>::Print(std::vector<T> vec)
{
	for (auto& at : vec)
		std::cout << at << " ";
	std::cout << std::endl;
}

template<class T>
inline T ** DataIndex<T>::ExternalOrderArray(T arr[], int n, OrderCallback function)
{
	T** pOrder = new T*[n];
	for (int index = 0; index < n; index++)
		pOrder[index] = &arr[index];

	int i, j, m;
	for (i = 0; i < n - 1; i++)
	{
		m = i;
		for (j = i + 1; j < n; j++)
			if (function(*pOrder[j], *pOrder[m]))		//通过函数指针调用
				m = j;
		if (m != i)
			DataIndex<T*>::Swap(pOrder[m], pOrder[i]);	//交换指针指向
	}
	return pOrder;
}

template<class T>
inline void DataIndex<T>::ExternalPrintArray(T ** pOrder, int n)
{
	for (int i = 0; i < n; i++)
		std::wcout << *pOrder[i] << " ";
	std::wcout << std::endl;
}

template<class T>
inline T * DataIndex<T>::ExternalOrderIndex(T arr[], int n, OrderCallback function)
{
	T* pOrder = new T[n];
	for (int index = 0; index < n; index++)
		pOrder[index] = index;

	int i, j, m;
	for (i = 0; i < n - 1; i++)
	{
		m = i;
		for (j = i + 1; j < n; j++)
			if (function(arr[pOrder[j]], arr[pOrder[m]]))		//通过函数指针调用
				m = j;
		if (m != i)
			DataIndex<T>::Swap(pOrder[m], pOrder[i]);			//交换数值引用
	}
	return pOrder;
}

template<class T>
inline void DataIndex<T>::ExternalPrintIndex(T* pOrder, T arr[], int n)
{
	for (int i = 0; i < n; i++)
		std::wcout << arr[pOrder[i]] << " ";
	std::wcout << std::endl;
}

template<class T>
inline int DataIndex<T>::gcd(int a, int b)
{
	if (a == b)
		return a;
	if (a < b)
		return gcd(b, a);
	else
	{
		//和1作位与运算，判断奇偶
		bool isa = a & 1;
		bool isb = b & 1;
		if (!isa && !isb)
			return gcd(a >> 1, b >> 1) << 1;
		else if (!isa && isb)
			return gcd(a >> 1, b);
		else if (isa && !isb)
			return gcd(a, b >> 1);
		else
			return gcd(b, a - b);
	}
}
