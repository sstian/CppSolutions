/*
	2019.11.01 20:26 - 21:34
	删去k个数字后的最小值
*/
#include <iostream>
#include <string>

using namespace std;

// 删除整数的k个数字，获得删除后的最小值
// str: 原整数, k: 删除数量
string RemoveKDigits(string str, int k)
{
	// 输出信息
	cout << "original number = " << str << ", k = " << k;
	cout << ", output number = ";

	//创建一个栈，用于接收所有的数字
	int len = static_cast<int>(str.length());
	char* stack = new char[len];
	int top = 0;
	for (int i = 0; i < len; i++)
	{
		//遍历当前数字
		char c = str.at(i);
		//当栈顶数字大于遍历到的当前数字，栈顶数字出栈（相当于删除数字）
		while (top > 0 && stack[top - 1] > c && k > 0)
		{
			top--;
			k--;
		}
		//遍历到的当前数字入栈
		stack[top++] = c;
	}
	stack[top] = '\0';
	string newstr(stack);
	delete[] stack;

	// 找到栈中第一个非零数字的位置，以此构建新的整数字符串
	size_t pos = newstr.find_first_not_of('0');
	if (string::npos == pos)
		return "0";
	return newstr.substr(pos);
}

int main()
{
	cout << RemoveKDigits("1593212", 3) << endl;
	cout << RemoveKDigits("30200", 1) << endl;
	cout << RemoveKDigits("10", 2) << endl;
	cout << RemoveKDigits("541270936", 3) << endl;
	return 0;
}

/*** output
original number = 1593212, k = 3, output number = 1212
original number = 30200, k = 1, output number = 200
original number = 10, k = 2, output number = 0
original number = 541270936, k = 3, output number = 120936

E:\unlimited rulebook\C++ Laboratory\Coder-\x64\Debug\Coder.exe (进程 13020)已退出，返回代码为: 0。
按任意键关闭此窗口...
***/