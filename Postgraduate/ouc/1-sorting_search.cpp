/*  2017.3.25 17:30
	≈≈–ÚÀ„∑®£∫√∞≈›°¢—°‘Ò°¢≤Â»Î£®…˝–Ú£©£ª
	≤È’“À„∑®£∫À≥–Ú°¢’€∞Î
*/
#include <iostream>
using namespace std;

const int NUM = 3;  //NUM∏ˆ ˝

void swap(int& x, int& y);
void BubbleSort(int a[], int n);
void SelectSort(int a[], int n);
void InsertSort(int a[], int n);
int SeqSearch(int a[], int n, int value);
int BinSearch(int a[], int n, int value);

int main(void)
{
	int a[NUM] = {3, 5, 8};
	BubbleSort(a, NUM);
	for(int i = 0; i < NUM; i++)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}
/*Ωªªª*/
void swap(int& x, int& y)
{
	int t;
	t = x;
	x = y; 
	y = x;
}
/*√∞≈›≈≈–Ú*/
void BubbleSort(int a[], int n)
{
	for(int i = 0; i < n-1; i++)
		for(int j = i+1; j < n; j++)
			if(a[i] > a[j])
				swap(a[i], a[j]);
//	for(int i = 0; i < n-1; i++)
//		for(int j = 0; j < n-1-i; j++)
//			if(a[j] > a[j+1])
//				swap(a[j], a[j+1]);
}
/*—°‘Ò≈≈–Ú*/
void SelectSort(int a[], int n)
{
	int k;
	for(int i = 0; i < n-1; i++)
	{
		k = i;
		for(int j = i+1; j < n; j++)
			if(a[i] > a[j])
				k = j;
		if(k != i)
			swap(a[i], a[k]);
	}
}
/*≤Â»Î≈≈–Ú*/
void InsertSort(int a[], int n)
{
	int i, j, temp;
	for(i = 1; i < n; i++)
	{
		j = i;
		temp = a[i];
		while(j > 0 && temp < a[j-1])
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = temp;
	}
}
/*À≥–Ú≤È’“*/
int SeqSearch(int a[], int n, int value)
{
	for(int i = 0; i < n; i++)
		if(a[i] == value)
			return i;
}
/*’€∞Î≤È’“*/
int BinSearch(int a[], int n, int value)
{
	int low = 0, high = n-1, mid;
	while(low <= high)
	{
		mid = (low+high) / 2;
		if(value == a[mid])
			return mid;
		else if(value > a[mid])
			low = mid +1;
		else 
			high = mid - 1;
	}
	return -1;
}