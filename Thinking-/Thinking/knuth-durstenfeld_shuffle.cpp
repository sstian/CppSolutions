/*
	2019.10.21
	Knuth-Durstenfeld Shuffle ϴ���㷨
	ÿ�δ�δ��������������ȡ��һ�����֣�Ȼ��Ѹ����ַ��������β����������β����ŵ����Ѿ�����������֡�
�㷨����Ϊ��
1. ����һ�������СΪ n ������ arr���ֱ��� 1 �� n ����ֵ��
2. ����һ���� 0 �� n - 1 ������� x��
3. ��� arr �±�Ϊ x ����ֵ����Ϊ��һ���������
4. �� arr ��βԪ�غ��±�Ϊ x ��Ԫ�ػ�����
5. ͬ2������һ���� 0 �� n - 2 ������� x��
6. ��� arr �±�Ϊ x ����ֵ��Ϊ�ڶ����������
7. �� arr �ĵ����ڶ���Ԫ�غ��±�Ϊ x ��Ԫ�ػ�����
����
���ϣ�ֱ�����m ����Ϊֹ
ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)��ȱ�����֪�����鳤��n��
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#define N 54

using namespace std;

// ���
template <class T>
void show(std::vector<T>& vec)
{
	for (auto& at : vec)
		cout << at << " ";
	cout << endl;
}

// ϴ���㷨
void shuffle(std::vector<int>& vec)
{
	int n = static_cast<int>(vec.size());
	int num = 0;
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < n; i++)
	{
		num = rand() % (n - i);
		std::swap(vec[num], vec[n - i - 1]);
	}
}

int main()
{
	//vector<int> vec;
	//for (int i = 0; i < N; i++)
	//	vec.push_back(i + 1);

	vector<int> vec(N);
	for (int i = 0; i < N; i++)
		vec[i] = i + 1;

	show(vec);
	shuffle(vec);
	show(vec);

	return 0;
}