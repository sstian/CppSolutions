#include <iostream>
using std::cin;
using std::cout;
using std::endl;
typedef int* IntArrayPtr;
int main()
{
	int d1, d2;
	cout << "Enter the row and colum dimensions of the array:\n";
	cin >> d1 >> d2;
	IntArrayPtr *m = new IntArrayPtr[d1];
	int i, j;
	for (i = 0; i < d1; i++)
		m[i] = new int[d2];                                        //m现在就变成了d1行d2列的二维数组
	cout << "Enter " << d1 << " rows of "
		 << d2 << " integers each:\n";
	for (i = 0; i < d1; i++)
		for (j = 0; j < d2; j++)
			cin >> m[i][j];
	cout << "Echoing the two-dimensional array:\n";
	for (i = 0; i < d1; i++)
	{
		for (j = 0; j < d2; j++)
			cout << m[i][j] << " ";
		cout << endl;
	}
	for (i = 0; i < d1; i++)
		delete[] m[i];
	delete m;
}