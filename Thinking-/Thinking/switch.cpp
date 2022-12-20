#include <iostream>
using namespace std;
int main()
{
	int choice;
	cout << "输入一个数：";
	cin >> choice;
	switch (choice)
	{
	case 0: cout << "您输入的是一！\n"; cout << "Hello world...\n"; break;
	case 1: cout << "您输入的是二！\n"; break;
	default: break;
	}
	return 0;
}