/* 2017.3.25 18:01
	质数，指定范围2~500
*/
#include <iostream>
#include <iomanip>
using namespace std;

bool IsPrime(int n);

int main(void)
{
	int count = 0;  //计数
	for(int i = 2; i <= 500; i++)
		if(IsPrime(i) == true)
		{
			cout << setw(3) << i << " "; 
			count++;
			if(count % 10 == 0)
				cout << endl;
		}
	cout << endl;
	return 0;
}
/*判断素数*/
bool IsPrime(int n)
{
	for(int i = 2; i < n; i++)
		if(n % i == 0)
			return false;
	return true;
}