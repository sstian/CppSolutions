/*  2017.1.10 18:31
	���㷨��ӡͼ��
	            *
              ***
            *****
          *******
          *****
          ***
          *
*/
#include <iostream>
using namespace std;

int main(void)
{
	int i, j, t, s;  //�ֱ�����У��У���˿ո�ÿ�пո�
	int n, space;    //ͼ������е����ͼ����˿ո���

	cout << "****** Print Pattern ******\n";
	cout << "Please input widthest row n = ";
	cin >> n;
	cout << "Plese input left white space = ";
	cin >> space;
	
	for(i = 1; i <= n/2+1; i++)  //�����ӡǰn/2+1��
	{
		for(t = 1; t <= space; t++)
			cout << ' ';         //���space���ո�
		for(s = 1; s <= n-2*i+1; s++)
			cout << ' ';         //��ӡÿ�еĿո�
		for(j = 1; j <= 2*i-1; j++)
			cout << '*';		 //��ӡÿ�е�����
		cout << endl;			 //���н���������
	}
	for(i = n/2; i >=1; i--)	 //�����ӡ��n/2��
	{
		for(t = 1; t <= space; t++)
			cout << ' ';		 //���space���ո�
		for(j = 1; j <= 2*i-1; j++)
			cout << '*';	     //��ӡÿ�е�����
		cout << endl;			 //���н���������
	}

	system("pause");
	return 0;
}