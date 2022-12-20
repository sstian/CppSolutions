/*
	2019.11.01 21:36
	分发红包算法：
	二倍均值法，线段切割法（较好，已实现）
*/
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

// 发红包算法：线段切割法
// amount: 总金额，以分为单位；people: 总人数；red: 红包集合
void DivideRedPackage(int amount, int people, std::vector<double>& red)
{
	std::vector<int> pos;
	srand((unsigned int)(time(NULL)));
	while (pos.size() < people - 1)
	{
		int value = rand() % amount + 1;	//最低1分钱
		//非重复切割添加到集合
		bool exist = false;
		for (auto& at : pos)
			if (at == value)
			{
				exist = true;
				break;
			}
		if (!exist)
			pos.push_back(value);
	}
	std::sort(pos.begin(), pos.end());
	
	red.clear();
	red.push_back(pos.at(0) / 100.0);
	int sum = pos.at(0);
	for (int i = 1; i < people - 1; i++)
	{
		int val = pos.at(i) - pos.at(i - 1);
		sum += val;
		red.push_back(val / 100.0);
	}
	//最后一个红包
	red.push_back((amount - sum) / 100.0);
}

int main()
{
	cout << "*** Divide Red Package ***" << endl;
	std::vector<double> red;
	int amount = 5000;
	int people = 30;
	
	cout << "amount = " << amount << endl;
	cout << "people = " << people << endl;
	DivideRedPackage(amount, people, red);
	int i = 1;
	for (auto& at : red)
		cout << i++ << " = \t" << at << endl;
	return 0;
}

/*** out:
*** Divide Red Package ***
amount = 5000
people = 30
1 =     3.6
2 =     0.44
3 =     0.26
4 =     0.64
5 =     1.09
6 =     0.61
7 =     0.72
8 =     1.85
9 =     0.26
10 =    0.16
11 =    0.57
12 =    1.42
13 =    2.61
14 =    0.33
15 =    0.12
16 =    0.67
17 =    1.27
18 =    3.14
19 =    4.64
20 =    1.78
21 =    0.26
22 =    3.44
23 =    2.56
24 =    1.47
25 =    4.23
26 =    2.23
27 =    2.26
28 =    0.61
29 =    3.33
30 =    3.43

E:\unlimited rulebook\C++ Laboratory\Coder-\x64\Debug\Coder.exe (进程 10588)已退出，返回代码为: 0。
按任意键关闭此窗口...
***/