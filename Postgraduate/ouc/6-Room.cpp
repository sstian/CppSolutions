/* 2017.3.25 20:50
	������
*/
#include <iostream>
using namespace std;

const int PI = 3.141592653;

class Room  //������
{
public:
	virtual double area() = 0;
};

class SquareRoom : public Room  //���η�����
{
public:
	SquareRoom(double width, double height):m_width(width),m_height(height) { }
	virtual double area() { return m_width * m_height; }
private:
	double m_width;  //��
	double m_height;  //��
};

class CircleRoom : public Room  //Բ�η�����
{
public:
	CircleRoom(double radius):m_radius(radius) { }
	virtual double area() { return PI * m_radius * m_radius; }
private:
	double m_radius;  //�뾶
};

class Rent  //����ɷѺ�ͬ��
{
public:
	Rent(double rence, double commit, double term)
		:rence_(rence),commit_(commit),term_(term) { }
	double sumRent(Room& rRoom) const;
private:
	double rence_;  //��λ������
	double commit_;  //��λ���Ӷ��
	double term_;  //��ס����
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