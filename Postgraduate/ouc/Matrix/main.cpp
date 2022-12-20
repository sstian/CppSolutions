/*  2017.3.29 19:50
	矩阵类模板
*/
//#include <iostream>
#include <iostream.h>
#include "matrix.h"
//using namespace std;

int main(void)
{
	Matrix<int> a(3,4), b(3,4), c(3,4);
	cout << "  Matrix a: " << endl << a;
//	cin >> b;
	cout << "  Matrix b: " << endl << b;
	cout << "  Matrix c: " << endl << c;
	c = a + b;
	cout << "  c = a + b-> Matrix c: " << endl << c;
	c = a - b;
	cout << "  c = a - b-> Matrix c: " << endl << c;
	cout << "  c transpose:" << endl << c.transpose() << endl;
	Matrix<int> m(4,3), n;
	cout << "  Matrix m: " << endl << m;
	cout << "  Matrix n: " << endl << n;
	n = c * m;
	cout << "  n = c * m-> Matrix n: " << endl << n;
	return 0;
}
/*在VC++6.0中的运行结果：
==================================================================
  Matrix a:
1 7 14 0
9 4 18 18
2 4 5 5
  Matrix b:
1 7 1 11
15 2 7 16
11 4 2 13
  Matrix c:
12 2 1 16
18 15 7 6
11 18 9 12
  c = a + b-> Matrix c:
2 14 15 11
24 6 25 34
13 8 7 18
  c = a - b-> Matrix c:
0 0 13 -11
-6 2 11 2
-9 0 3 -8
  c transpose:
0 -6 -9
0 2 0
13 11 3
-11 2 -8

  Matrix m:
10 9 10
10 6 1
13 8 9
3 4 14
  Matrix n:
16 0 6
16 11 8
4 19 6
  n = c * m-> Matrix n:
136 60 -37
109 54 69
-75 -89 -175
Press any key to continue
==================================================================*/