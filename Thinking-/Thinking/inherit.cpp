#include <iostream>
using namespace std;
class A
{
public:
	A()
	{
		cout << "A Constructed 1\n";
	}
	A(int a, int b)
	{
		this->a = a;
		this->b = b;
		cout << "A Constructed 2\n";
	}
private:
	int a;
	int b;

};
class B :public A
{
public:
	B() :A()
	{
		cout << "B Constructed 1\n";
	}
	B(int c, int d) :A(c, d)	//:A(100, 200)
	{/*
		this->c = c;
		this->d = d;
	*/
		cout << "B Constructed 2\n";
	}
private:
//	int c;
//	int d;
};

int main()
{
	B b(1, 1);
	return 1;
}