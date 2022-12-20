/*
	2019.04.04 11:25
	二维数组存储每行不定长字符串
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	int number = 0;						//行数
	vector<vector<string>> vvstr;		//string[number][x]
	vector<string> vstr;
	string str;

	// 数据存储，！直接以换行结束一行且不能打空格
	cin >> number;
	for (int index = 0; index < number; index++)
	{
		vstr.clear();
		while (true)
		{
			cin >> str;
			vstr.push_back(str);
			if (cin.get() == '\n')
				break;
		}
		vvstr.push_back(vstr);
	}

	// 数据输出：for-atuo
	cout << "== for-atuo ===========================" << endl;
	for (auto& vsi : vvstr)
	{
		for (auto& si : vsi)
			cout << si << " ";
		cout << endl;
	}
	// 数据输出：迭代器遍历
	cout << "== 迭代器遍历 =========================" << endl;
	vector<vector<string>>::iterator vvit;
	vector<string>::iterator vit;
	vector<string> tvstr;
	for (vvit = vvstr.begin(); vvit != vvstr.end(); vvit++)
	{
		tvstr = *vvit;
		for (vit = tvstr.begin(); vit != tvstr.end(); vit++)
			cout << *vit << " ";
		cout << endl;
	}
	// 数据输出：取出第二行
	cout << "== 取出第二行 =========================" << endl;
	vector<string> vs2(vvstr[1].begin(), vvstr[1].end());
	for (int k = 0; k < vs2.size(); k++)
		cout << vs2.at(k) << " ";
	cout << endl;
	// 数据输出：下标遍历
	cout << "== 下标遍历 ===========================" << endl;
	for (int i = 0; i < vvstr.size(); i++)
	{
		for (int j = 0; j < vvstr[i].size(); j++)
			cout << vvstr[i][j] << " ";
		cout << endl;
	}


	system("pause");
	return 0;
}

/*== 输出结果：
3
AA SS
DD SS FF
GG
== for-atuo ===========================
AA SS
DD SS FF
GG
== 迭代器遍历 =========================
AA SS
DD SS FF
GG
== 取出第二行 =========================
DD SS FF
== 下标遍历 ===========================
AA SS
DD SS FF
GG
请按任意键继续. . .

*/