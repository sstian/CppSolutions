/*
	2019.11.01 20:26 - 21:34
	ɾȥk�����ֺ����Сֵ
*/
#include <iostream>
#include <string>

using namespace std;

// ɾ��������k�����֣����ɾ�������Сֵ
// str: ԭ����, k: ɾ������
string RemoveKDigits(string str, int k)
{
	// �����Ϣ
	cout << "original number = " << str << ", k = " << k;
	cout << ", output number = ";

	//����һ��ջ�����ڽ������е�����
	int len = static_cast<int>(str.length());
	char* stack = new char[len];
	int top = 0;
	for (int i = 0; i < len; i++)
	{
		//������ǰ����
		char c = str.at(i);
		//��ջ�����ִ��ڱ������ĵ�ǰ���֣�ջ�����ֳ�ջ���൱��ɾ�����֣�
		while (top > 0 && stack[top - 1] > c && k > 0)
		{
			top--;
			k--;
		}
		//�������ĵ�ǰ������ջ
		stack[top++] = c;
	}
	stack[top] = '\0';
	string newstr(stack);
	delete[] stack;

	// �ҵ�ջ�е�һ���������ֵ�λ�ã��Դ˹����µ������ַ���
	size_t pos = newstr.find_first_not_of('0');
	if (string::npos == pos)
		return "0";
	return newstr.substr(pos);
}

int main()
{
	cout << RemoveKDigits("1593212", 3) << endl;
	cout << RemoveKDigits("30200", 1) << endl;
	cout << RemoveKDigits("10", 2) << endl;
	cout << RemoveKDigits("541270936", 3) << endl;
	return 0;
}

/*** output
original number = 1593212, k = 3, output number = 1212
original number = 30200, k = 1, output number = 200
original number = 10, k = 2, output number = 0
original number = 541270936, k = 3, output number = 120936

E:\unlimited rulebook\C++ Laboratory\Coder-\x64\Debug\Coder.exe (���� 13020)���˳������ش���Ϊ: 0��
��������رմ˴���...
***/