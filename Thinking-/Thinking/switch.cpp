#include <iostream>
using namespace std;
int main()
{
	int choice;
	cout << "����һ������";
	cin >> choice;
	switch (choice)
	{
	case 0: cout << "���������һ��\n"; cout << "Hello world...\n"; break;
	case 1: cout << "��������Ƕ���\n"; break;
	default: break;
	}
	return 0;
}