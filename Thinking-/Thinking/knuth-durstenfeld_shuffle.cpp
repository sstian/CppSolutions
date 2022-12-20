/*
	2019.10.21
	Knuth-Durstenfeld Shuffle 洗牌算法
	每次从未处理的数据中随机取出一个数字，然后把该数字放在数组的尾部，即数组尾部存放的是已经处理过的数字。
算法步骤为：
1. 建立一个数组大小为 n 的数组 arr，分别存放 1 到 n 的数值；
2. 生成一个从 0 到 n - 1 的随机数 x；
3. 输出 arr 下标为 x 的数值，即为第一个随机数；
4. 将 arr 的尾元素和下标为 x 的元素互换；
5. 同2，生成一个从 0 到 n - 2 的随机数 x；
6. 输出 arr 下标为 x 的数值，为第二个随机数；
7. 将 arr 的倒数第二个元素和下标为 x 的元素互换；
……
如上，直到输出m 个数为止
时间复杂度为O(n)，空间复杂度为O(1)，缺点必须知道数组长度n。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#define N 54

using namespace std;

// 输出
template <class T>
void show(std::vector<T>& vec)
{
	for (auto& at : vec)
		cout << at << " ";
	cout << endl;
}

// 洗牌算法
void shuffle(std::vector<int>& vec)
{
	int n = static_cast<int>(vec.size());
	int num = 0;
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < n; i++)
	{
		num = rand() % (n - i);
		std::swap(vec[num], vec[n - i - 1]);
	}
}

int main()
{
	//vector<int> vec;
	//for (int i = 0; i < N; i++)
	//	vec.push_back(i + 1);

	vector<int> vec(N);
	for (int i = 0; i < N; i++)
		vec[i] = i + 1;

	show(vec);
	shuffle(vec);
	show(vec);

	return 0;
}