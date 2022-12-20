
/*  2017.3.7 23:19
  ǰ������������ʹ���ڶ���ǰ
���ƣ�1�����ܶ�����Ķ���->��Ҫ�����ڴ�
2���ɶ���ָ������͵�ָ������ã�3�������������Ƕ��壩ʹ�ô����͵Ĳ����򷵻�ֵ���͵ĺ�����->�������ڴ�
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

/*��VC++6.0�е����н����
===========================================================================
A: 1
A: b = 2
B: 2
B: a = 1
Press any key to continue
===========================================================================*/