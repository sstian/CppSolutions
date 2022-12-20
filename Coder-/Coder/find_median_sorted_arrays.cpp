/*
	2019.11.01 16:16
	找到两个数组的中位数
	验证i和j:
	1. B[j−1]≤A[i] && A[i−1]≤B[j]
	说明i和j左侧的元素都小于等于右侧，这一组i和j是我们想要的。
	2. A[i]<B[j−1]
	说明i对应的元素偏小了，i应该向右侧移动。
	3. A[i−1]>B[j]
	说明i-1对应的元素偏大了，i应该向左侧移动。
时间复杂度：O(log min(na, nb))
*/
#include <iostream>
#include <algorithm>
using namespace std;

// 找到两个数组的中位数
double FindMedianSortedArrays(int arra[], int na, int arrb[], int nb)
{
	//如果数组A的长度大于等于数组B，则保证数组A的长度较短
	if (na > nb)
		return FindMedianSortedArrays(arrb, nb, arra, na);

	int start = 0; 
	int end = na;
	int mid = (na + nb + 1) / 2;
	while (start <= end)
	{
		int i = (start + end) / 2;
		int j = mid - i;
		if (i < end && arrb[j - 1] > arra[i])
			start = i + 1;								//i偏小了，需要右移
		else if (i > start && arra[i - 1] > arrb[j])
			end = i - 1;								//i偏大了，需要左移
		else											//i刚好合适，或i已达到数组边界
		{
			int maxleft;
			if (0 == i)
				maxleft = arrb[j - 1];
			else if (0 == j)
				maxleft = arra[i - 1];
			else
				maxleft = std::max(arra[i - 1], arrb[j - 1]);
			
			//如果大数组的长度是奇数，中位数就是左半部分的最大值
			if ((na + nb) % 2 == 1)
				return maxleft;

			int minright;
			if (i == na)
				minright = arrb[j];
			else if (j == nb)
				minright = arra[i];
			else
				minright = std::min(arrb[j], arra[i]);

			//如果大数组的长度是偶数，取左侧最大值和右侧最小值的平均
			return (maxleft + minright) / 2.0;
		}
	}
	return 0.0;
}

int main()
{
	int arra[] = { 3,5,6,7,8,12,20 };
	int arrb[] = { 1,10,17,18 };
	int na = _countof(arra);
	int nb = _countof(arrb);

	cout << "=== Find Median Sorted Arrays ==" << endl;
	cout << "na = " << na << " arra = ";
	for (int a : arra)
		cout << a << " ";
	cout << "\nnb = " << nb << " arrb = ";
	for (int b : arrb)
		cout << b << " ";
	cout << "\n\nmedian = " << FindMedianSortedArrays(arra, na, arrb, nb) << endl;

	return 0;
}

/*** out:
=== Find Median Sorted Arrays ==
na = 7 arra = 3 5 6 7 8 12 20
nb = 4 arrb = 1 10 17 18

median = 8

E:\unlimited rulebook\C++ Laboratory\Coder-\x64\Debug\Coder.exe (进程 9956)已退出，返回代码为: 0。
按任意键关闭此窗口...
***/
