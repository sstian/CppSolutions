/* 2017.3.25 18:01
	������ָ����Χ2~500
*/
#include <iostream>
#include <iomanip>
using namespace std;

bool IsPrime(int n);

int main(void)
{
	int count = 0;  //����
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
/*�ж�����*/
bool IsPrime(int n)
{
	for(int i = 2; i < n; i++)
		if(n % i == 0)
			return false;
	return true;
}