#include <iostream>
#include <cstdlib>
using namespace std;
class IntPair
{
public:
	IntPair(int firstValue, int secondValue);
	IntPair operator ++();                             //前置版本
	IntPair operator ++(int);                          //后置版本
	void setFirst(int newValue) { first = newValue; }
	void setSecond(int newValue){ second = newValue;}
	int getFirst() const        { return first; }
	int getSecond() const       { return second; }
private:
	int first;
	int second;
};
int main()
{
	IntPair a(1, 2);
	cout << "Postfix a++: Start value of object a: ";
	cout << a.getFirst() << " " << a.getSecond() << endl;
	IntPair b = a++;
	cout << "Valued returned: ";
	cout << b.getFirst() << " " << b.getSecond() << endl;
	cout << "Changed object: ";
	cout << a.getFirst() << " " << a.getSecond() << endl;
	a = IntPair(1, 2);
	cout << "Prefix ++a: Start Value of object a: ";
	cout << a.getFirst() << " " << a.getSecond() << endl;
	IntPair c = ++a;
	cout << "Valued returned: ";
	cout << c.getFirst() << " " << c.getSecond() << endl;
	cout << "Changed object: ";
	cout << a.getFirst() << " " << a.getSecond() << endl;
	return 0;
}
IntPair::IntPair(int firstValue, int secondValue) 
	             :first(firstValue), second(secondValue)
{/*函数体有意为空*/}
IntPair IntPair::operator ++()
{
	first++;
	second++;
	return IntPair(first, second);
}
IntPair IntPair::operator ++(int ignoreMe)
{
	int temp1 = first;
	int temp2 = second;
	first++;
	second++;
	return IntPair(temp1, temp2);
}
