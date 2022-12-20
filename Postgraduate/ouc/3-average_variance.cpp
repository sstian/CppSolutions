/* 2017.3.25 18:12
	均值，方差
*/
#include <iostream>
#include <cmath>
using namespace std;

const int NUM = 3;

double average(int a[], int n);
double variance(int a[], int n);

int main(void)
{
	int a[NUM] = {3, 4, 5};
	cout << "average: " << average(a, NUM) << endl;
	cout << "variance: " << variance(a, NUM) << endl;
	return 0;
}
/*均值*/
double average(int a[], int n)
{
	double sum = 0;
	for(int i = 0; i < n; i++)
		sum += a[i];
	return sum / n;
}
/*方差*/
double variance(int a[], int n)
{
	double ave = average(a, n);
	double sum = 0, temp;
	for(int j = 0; j < n; j++)
	{
		temp = a[j] - ave;
		sum += temp * temp;
	}
	return sqrt(sum / n);
}