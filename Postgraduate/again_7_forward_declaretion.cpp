
/*  2017.3.7 23:19
  前向引用声明：使用在定义前
限制：1、不能定义类的对象；->需要分配内存
2、可定义指向此类型的指针和引用；3、可声明（不是定义）使用此类型的参数或返回值类型的函数。->不分配内存
*/
#include <iostream>
using namespace std;

class B;
class A
{
public:
	A(int ma = 1):a(ma){}
	void show(B b);
	int get(){return a;}
private:
	int a;
};

class B
{
public:
	B(int mb = 2):b(mb){}
	void show(A a)
	{
		cout << "B: a = " << a.get() << endl;
	}

	int get(){return b;}
private:
	int b;
};

void A::show(B b)
{
	cout << "A: b = " << b.get() << endl;
}
/*
void B::show(A a)
{
	cout << "B: a = " << a.get() << endl;
}
*/
int main(void)
{
	A aa;
	B bb;
	cout << "A: " << aa.get() << endl;
	aa.show(bb);
	cout << "B: " << bb.get() << endl;
	bb.show(aa);
	return 0;
}

/*在VC++6.0中的运行结果：
===========================================================================
A: 1
A: b = 2
B: 2
B: a = 1
Press any key to continue
===========================================================================*/