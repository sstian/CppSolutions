/*  2017.3.17 10:56
	����������
*/
#include <iostream>
using namespace std;

class Pair
{
public:
	Pair(int newFirst = 0, int newSecond = 0):first(newFirst),second(newSecond){cout << "Constructor..." << endl;}
	virtual ~Pair(){ cout << "Deconstructor" << endl;}
/*	Pair operator ++();  //ǰ��++
	Pair operator ++(int);  //����++�����õ���Ҫ����
*/
	friend Pair operator ++(Pair& rp);  //��Ԫǰ��++
	friend Pair operator ++(Pair& rp, int ignore);  //��Ԫ����++
	void display() const { cout << "first = " << first << ", second = " << second << endl;}
private:
	int first;
	int second;
};

int main(void)
{
	cout << "1 start->" << endl;
	Pair pa(10,20), pb;
	cout << "pa: ";
	pa.display();
	cout << "pb: ";
	pb.display();
	
	cout << "2 formar ++pa ->" << endl;
	pb = ++pa;
	cout << "pa: ";
	pa.display();
	cout << "pb: ";
	pb.display();

	cout << "3 latter pa++ ->" << endl;
	pb = pa++;
	cout << "pa: ";
	pa.display();
	cout << "pb: ";
	pb.display();
	return 0;
}
/*
Pair Pair::operator ++()
{
	first++;
	second++;
	return Pair(first, second);
}

Pair Pair::operator ++(int ignoreMe)
{
	int tempFirst = first;
	int tempSecond = second;
	first++;
	second++;
	return Pair(tempFirst, tempSecond);
}
*/
Pair operator ++(Pair& rp)
{
	rp.first++;
	rp.second++;
//	return Pair(rp.first, rp.second);
	return rp;
}

Pair operator ++(Pair& rp, int ignore)
{
	int tempFirst = rp.first;
	int tempSecond = rp.second;
	rp.first++;
	rp.second++;
	return Pair(tempFirst, tempSecond);
}