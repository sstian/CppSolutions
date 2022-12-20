#include <iostream>
#include <cstring>
#define N 100
using namespace std;
int main()
{
	char x[] = { "I Love You! Girls" };
	char a[N];
	int n;
	int i, j, k;
	n = sizeof(x) / sizeof(char);
	cout << "n=" << n << endl;
	for (i = 0, j = 0, k = 0; i < 128; i++)
	{
		if (x[j++] == i)
			a[k++] = i;
		if (x[j] == '\0')
			break;
	}
	for (i = 0; a[i] != '\0'; i++)
		cout << a[i];
	cout << endl;
	return 0;
}