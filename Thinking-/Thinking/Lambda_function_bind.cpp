/*
	2019.02.18 16:03
	C++11 Lambda, function, bind
	[capture list] (params list) mutable exception-> return type { function body }
capture list��	�����ⲿ�����б�
params list��	�β��б�
mutableָʾ����	����˵���Ƿ�����޸Ĳ���ı���
exception��		�쳣�趨
return type��	��������
function body��	������
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>	//class function

using namespace std;

bool cmp(int a, int b)
{
	return  a < b;
}

void print_num(int x)
{
	cout << x << endl;
}

size_t CPrint(const char* pc) { return 0; }

int Func(int x, int y) { return 0; }

int main()
{
	/// Lambda
	vector<int> myvec{ 3, 2, 5, 7, 3, 2 };
	vector<int> lbvec(myvec);

	sort(myvec.begin(), myvec.end(), cmp);											// ��ʽ����
	cout << "predicate function:" << endl;
	for (int it : myvec)
		cout << it << ' ';
	cout << endl;

	sort(lbvec.begin(), lbvec.end(), [](int a, int b) -> bool { return a < b; });   // Lambda���ʽ
	cout << "lambda expression:" << endl;
	for (int it : lbvec)
		cout << it << ' ';

	// �����ⲿ����
	cout << endl << endl << "�����ⲿ����" << endl;
	int a1 = 123;
	auto f = [a1] { cout << "a1 = " << a1 << endl; };
	f();											// �����123
	//��ͨ���������塱����ġ�()���������
	[](int a1) {cout << "a1 = " << a1 << endl; }(123);

	// ֵ����
	cout << endl << endl << "ֵ����" << endl;
	int a2 = 123;
	auto f2 = [a2] { cout << a2 << endl; };	
	//auto f2 = [=] { cout << a2 << endl; };	//��ʽ����
	a2 = 321;
	f2();											// �����123

	// ���ò���
	cout << endl << endl << "���ò���" << endl;
	int a3 = 123;
	auto f3 = [&a3] { cout << a3 << endl; };
	//auto f3 = [&] { cout << a3 << endl; };	//��ʽ����
	a3 = 321;
	f3();											// �����321

	// �޸Ĳ������
	cout << endl << endl << "�޸Ĳ������" << endl;
	int a4 = 123;
	auto f4 = [a4]()mutable { cout << ++a4; }; // ���ᱨ��
	cout << a4 << endl;								// �����123
	f4();											// �����124

	// ���þ���
	cout << endl << endl << "���þ���" << endl;
	int m = [](int x) { return [](int y) { return y * 2; }(x)+6; }(5);
	std::cout << "m:" << m << std::endl;													//�����m:16

	std::cout << "n:" << [](int x, int y) { return x + y; }(5, 4) << std::endl;				//�����n:9

	auto gFunc = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };
	auto lFunc = gFunc(4);
	std::cout << lFunc(5) << std::endl;														//�����9

	auto hFunc = [](const function<int(int)>& f, int z) { return f(z) + 1; };
	auto aa = hFunc(gFunc(7), 8);
	cout << "aa = " << aa << endl;															//�����aa = 16

	int a = 111, b = 222;
	auto func = [=, &b]()mutable { a = 22; b = 333; std::cout << "a:" << a << " b:" << b << std::endl; };
	//[=, &b]() == [](int a, int& b)
	func();																					//�����a:22 b:333
	std::cout << "a:" << a << " b:" << b << std::endl;										//�����a:111 b:333

	a = 333;
	auto func2 = [=, &a] { a = 444; std::cout << "a:" << a << " b:" << b << std::endl; };
	func2();																				//�����a:444 b:333

	auto func3 = [](int x) ->function<int(int)> { return [=](int y) { return x + y; }; };

	std::function<void(int x)> f_display_42 = [](int x) { print_num(x); };
	f_display_42(44);																		//�����44

	/// Lambda
	vector< int> vec;
	// 1. simple lambda  
	auto it = std::find_if(vec.begin(), vec.end(), [](int i) { return i > 50; });
	class A																	///* �º���
	{
	public:
		bool operator()(int i) const { return i > 50; }
	};
	auto it2 = std::find_if(vec.begin(), vec.end(), A());

	// 2. lambda return syntax  
	std::function< int(int)> square = [](int i) -> int { return i * i; };	/// function + Lanbda

	// 3. lambda expr: capture of local variable  
	{
		int min_val = 10;
		int max_val = 1000;

		auto it = std::find_if(vec.begin(), vec.end(), [=](int i) {
			return i > min_val && i < max_val;
		});

		auto it3 = std::find_if(vec.begin(), vec.end(), [&](int i) {
			return i > min_val && i < max_val;
		});

		auto it4 = std::find_if(vec.begin(), vec.end(), [=, &max_val](int i) {
			return i > min_val && i < max_val;
		});
	}

	// 4. lambda expr: capture of class member  
	class AA
	{
	public:
		void DoSomething()
		{
			// 4.1 capture member by this  
			auto it = std::find_if(m_vec.begin(), m_vec.end(), [this](int i) {
				return i > m_min_val && i < m_max_val; });

			//// 4.2 capture member by default pass-by-value  
			//auto it = std::find_if(m_vec.begin(), m_vec.end(), [=](int i) {
			//	return i > m_min_val && i < m_max_val; });

			//// 4.3 capture member by default pass-by-reference  
			//auto it = std::find_if(m_vec.begin(), m_vec.end(), [&](int i) {
			//	return i > m_min_val && i < m_max_val; });
		}
	private:
		std::vector<int>  m_vec;
		int m_min_val;
		int m_max_val;
	};


	/// function
	std::function< size_t(const char*) > print_func;

	// normal function -> std::function object  
	//size_t CPrint(const char* pc) { }
	print_func = CPrint;
	print_func("hello world");

	// functor -> std::function object  
	class CxxPrint
	{
	public:
		size_t operator()(const char*) { return 1; }
	};
	CxxPrint p;
	print_func = p;
	print_func("hello world");


	/// bind
	int Func(int x, int y);
	auto bf1 = std::bind(Func, 10, std::placeholders::_1);
	bf1(20); // same as Func(10, 20)  

	class AAA
	{
	public:
		int Func(int x, int y, int z) { return 1; }
	};

	AAA aaa;
	auto bf2 = std::bind(&AAA::Func, aaa, std::placeholders::_1, std::placeholders::_2, 100);	/// bind
	bf2(10, 20); // same as a.Func(10, 20)  

	std::function< int(int, int)> bf3 = std::bind(&AAA::Func, aaa, std::placeholders::_1, std::placeholders::_2, 100);
	bf3(10, 1); // same as a.Func(10, 100)


	system("pause");
	return 0;
}