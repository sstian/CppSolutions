/*
	2019.04.04 11:25
	��ά����洢ÿ�в������ַ���
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	int number = 0;						//����
	vector<vector<string>> vvstr;		//string[number][x]
	vector<string> vstr;
	string str;

	// ���ݴ洢����ֱ���Ի��н���һ���Ҳ��ܴ�ո�
	cin >> number;
	for (int index = 0; index < number; index++)
	{
		vstr.clear();
		while (true)
		{
			cin >> str;
			vstr.push_back(str);
			if (cin.get() == '\n')
				break;
		}
		vvstr.push_back(vstr);
	}

	// ���������for-atuo
	cout << "== for-atuo ===========================" << endl;
	for (auto& vsi : vvstr)
	{
		for (auto& si : vsi)
			cout << si << " ";
		cout << endl;
	}
	// �������������������
	cout << "== ���������� =========================" << endl;
	vector<vector<string>>::iterator vvit;
	vector<string>::iterator vit;
	vector<string> tvstr;
	for (vvit = vvstr.begin(); vvit != vvstr.end(); vvit++)
	{
		tvstr = *vvit;
		for (vit = tvstr.begin(); vit != tvstr.end(); vit++)
			cout << *vit << " ";
		cout << endl;
	}
	// ���������ȡ���ڶ���
	cout << "== ȡ���ڶ��� =========================" << endl;
	vector<string> vs2(vvstr[1].begin(), vvstr[1].end());
	for (int k = 0; k < vs2.size(); k++)
		cout << vs2.at(k) << " ";
	cout << endl;
	// ����������±����
	cout << "== �±���� ===========================" << endl;
	for (int i = 0; i < vvstr.size(); i++)
	{
		for (int j = 0; j < vvstr[i].size(); j++)
			cout << vvstr[i][j] << " ";
		cout << endl;
	}


	system("pause");
	return 0;
}

/*== ��������
3
AA SS
DD SS FF
GG
== for-atuo ===========================
AA SS
DD SS FF
GG
== ���������� =========================
AA SS
DD SS FF
GG
== ȡ���ڶ��� =========================
DD SS FF
== �±���� ===========================
AA SS
DD SS FF
GG
�밴���������. . .

*/