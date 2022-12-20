/* 2017.3.25 20:50
	房间类
*/
#include <iostream>
using namespace std;

const int PI = 3.141592653;

class Room  //房间类
{
public:
	virtual double area() = 0;
};

class SquareRoom : public Room  //方形房间类
{
public:
	SquareRoom(double width, double height):m_width(width),m_height(height) { }
	virtual double area() { return m_width * m_height; }
private:
	double m_width;  //宽
	double m_height;  //高
};

class CircleRoom : public Room  //圆形房间类
{
public:
	CircleRoom(double radius):m_radius(radius) { }
	virtual double area() { return PI * m_radius * m_radius; }
private:
	double m_radius;  //半径
};

class Rent  //房租缴费合同类
{
public:
	Rent(double rence, double commit, double term)
		:rence_(rence),commit_(commit),term_(term) { }
	double sumRent(Room& rRoom) const;
private:
	double rence_;  //单位面积租金
	double commit_;  //单位面积佣金
	double term_;  //租住期限
};
double Rent::sumRent(Room& rRoom) const
{
	return (rence_*term_ + commit_) * rRoom.area();
}
int main(void)
{
	SquareRoom sroom(12,13);
	CircleRoom croom(15);
	Rent srent(7,8,9), crent(4,5,6);
	cout << "square room rent is " << srent.sumRent(sroom) << endl;
	cout << "circle room rent is " << srent.sumRent(croom) << endl;
	return 0;
}