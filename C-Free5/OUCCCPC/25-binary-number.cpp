/*	2018.05.17 16:25
	
*/
#include <iostream>
#include <bitset>
using namespace std;

int rtod(unsigned int radix, unsigned int base);
int main()
{
	bitset<16> bint;
	int decimal;
	int count = 0;
	cin >> bint;
	decimal = bint.to_ulong();
	while(decimal != 1)
	{
		if(decimal % 2 == 0)
		{
			decimal /= 2;
			count++;
		}
		else
		{
			decimal++;
			count++;
		}
	}
	cout << count << endl;
	return 0;
}


