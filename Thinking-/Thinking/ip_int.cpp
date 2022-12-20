/*
	2019.11.02 16:55 - 18:21
	IP字符串与整数之间的互相转换，给定数字转为子网掩码（数字形式）
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// ip to unsigned int
unsigned int iptoint(string ip)
{
	unsigned int num = 0;
	int offset = 24;
	const char* delimiter = ".";
	char* token = strtok(const_cast<char*>(ip.c_str()), delimiter);
	while (token)
	{
		num += stoi(token) << offset;
		offset -= 8;
		token = strtok(nullptr, delimiter);
	}
	return num;
}

// unsigned int to ip
string inttoip(unsigned int num)
{
	string ip;
	for (int i = 0; i < 4; i++)
	{
		unsigned int value = num << i * 8 >> 24;
		ip += to_string(value);
		if (i < 3)
			ip += '.';
	}
	return ip;
}

// 给定数字转为子网掩码（数字形式）
unsigned int submask(int number)
{
	unsigned int sub = 0;
	for (int i = 1; i <= number; i++)
		sub += 1 << (32 - i);
	return sub;
}

int main()
{
	cout << "*** ip - int ***" << endl;
	string ip = "10.3.3.193";	
	string ip1 = "255.255.255.224";
	cout << "ip = " << ip << endl;
	cout << "num = " << iptoint(ip) << endl;
	cout << "ip1 = " << ip1 << endl;
	cout << "num1 = " << iptoint(ip1) << endl << endl;

	unsigned int num2 = 167969729;
	cout << "num2 = " << num2 << endl;
	cout << "ip2 = " << inttoip(num2) << endl << endl;
	
	int number = 27;
	unsigned int sub = 0;
	cout << "number = " << number << endl;
	cout << "mask = " << (sub = submask(number)) << endl;
	cout << "sub ip = " << inttoip(sub) << endl;

	return 0;
}

/*** out:
*** ip - int ***
ip = 10.3.3.193
num = 167969729
ip1 = 255.255.255.224
num1 = 4294967264

num2 = 167969729
ip2 = 10.3.3.193

number = 27
mask = 4294967264
sub ip = 255.255.255.224

E:\unlimited rulebook\C++ Laboratory\Thinking-\x64\Debug\Thinking.exe (进程 6840)已退出，返回代码为: 0。
按任意键关闭此窗口...
***/