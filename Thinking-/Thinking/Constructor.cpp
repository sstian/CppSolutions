#include <iostream>
using namespace std;
class Human
{
public:
	Human(int h, int w){ hight = h; weight = w; }
	void minus(){ cout << "���-����= " << hight - weight << endl; }
private:
	int hight;
	int weight;
};
int main()
{
	Human Jack(175, 130);
	Jack.minus();
	return 0;
}