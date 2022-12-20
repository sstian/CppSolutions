/* 2017.3.25 18:31
	行程编码
*/
#include <iostream>
using namespace std;

const int LEN = 100;

void routine(char* str, char* cha, int* num);

int main(void)
{
	char str[LEN];
	static char cha[LEN];
	int num[LEN] = {0};
	cin.getline(str, LEN, '\n');
	routine(str, cha, num);

	cout << str << endl;
	for(int i = 0; cha[i] != '\0'; i++)
		cout << cha[i] << " " << num[i] << ", ";
	cout << endl;
	return 0;
}
/*行程编码*/
void routine(char* str, char* cha, int* num)
{
	static int s = 1;
	for(int i = 0; str[i] != '\0'; i++)
	{
		int flag = 0;
		if(cha[0] == '\0')
		{
			cha[0] = str[0];
			num[0]++;
		}
		else
		{
			for(int j = 0; cha[j] != '\0'; j++)
			{
				if(cha[j] == str[i])
				{
					num[j]++;
					flag = 1;
				}
			}
			if(flag == 0)
			{
				cha[s] = str[i];
				num[s]++;
				s++;
			}
		}
	}
}