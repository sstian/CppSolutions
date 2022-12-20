/*  2017.3.22 15:57
	游泳池计算问题-面向对象的程序设计思想
	有一圆形游泳池，需在其周围建一扇形过道，并围上栅栏。
游泳池半径由键盘输入，过道宽度为3米；
过道造价为20元/平方米，栅栏价格为35元/平方米。
求：过道和栅栏的价格？
*/
#include <iostream>
using namespace std;

const double PI = 3.141592653;  //圆周率常量
const double CorridorPrice = 20.0;  //过道价格常量，单位：元/平方米
const double CorridorWidth = 3.0;  //过道宽度常量，单位：米
const double FencePrice = 35.0;  //栅栏价格常量，单位：元/平方米

class Circle  //圆类
{
public:
	Circle(double r = 0.0):radius(r) {}  //带一个默认参数构造函数
	Circle(const Circle& rcircle) { this->radius = rcircle.radius; }  //复制构造函数
	double getRadius() const { return radius; }  //获取半径
	void setRadius(double newRadius) { radius = newRadius; }  //设置半径
	double area() const { return PI * radius * radius; }  //圆面积
	double circumference() const { return 2 * PI * radius; }  //圆周长
	virtual ~Circle() {}  //虚析构函数
private:
	double radius;  //半径
};

int main(void)
{
	Circle pool, poolfence;  //建立 游泳池、游泳池+过道 的圆对象
	double radius;
	cout << "******** Swimming Pool ********" << endl;
	cout << "Please input the radius of swimming pool:\nradius = ";
	cin >> radius;
	pool.setRadius(radius);
	poolfence.setRadius(radius + CorridorWidth);
	//输出过道造价
	cout << "Corridor's price is ￥" << CorridorPrice * (poolfence.area() - pool.area())<< endl;  
	//输出栅栏造价
	cout << "Fence's circumference is ￥" << FencePrice * poolfence.circumference()<< endl;
	system("pause");
	return 0;
}