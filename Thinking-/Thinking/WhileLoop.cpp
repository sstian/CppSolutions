#include <iostream>
using namespace std;
int main()
{
	char many;
	cout << "你想看人家几次：";
	cin >> many;
	while (many > 0)
	{
		cout << "我亲爱的公主，你在哪里！\n";
		many--;
	}
	cout << "后会有期。。。" << endl;
	return 0;
}