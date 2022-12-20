/*�����Line��Point�����ͷ�ļ�*/
#ifndef LINE_H
#define LINE_H

#include <cmath>
//��Point��
class Point
{
public:
	//������Ĭ�ϲ����Ĺ��캯����Ĭ�ϵ㣨0.0,0.0��
	Point(double xValue = 0.0, double yValue = 0.0):x(xValue),y(yValue){}
	//���ƹ��캯��
	Point(Point& otherPoint);
	//��Ա������get,set����
	double getX(){return x;}
	void setX(double xValue){x = xValue;}
	double getY(){return y;}
	void setY(double yValue){y = yValue;}
	//��������
	~Point(){}
private:
	double x;  //������ֵ
	double y;  //������ֵ
};

Point::Point(Point& otherPoint)
{
	x = otherPoint.getX();
	y = otherPoint.getY();
}

//��Line��
class Line
{
public:
	//��һ��Ĭ�ϲ����������������Ĺ��캯��
	Line(Point& startPoint, Point& endPoint, int newLabel = 0)
		:start(startPoint),end(endPoint),label(newLabel){}
	//���ݳ�Ա��get,set����
	Point getStart(){return start;}
	void setStart(Point& startPoint){start = startPoint;}
	Point getEnd(){return end;}
	void setEnd(Point& endPoint){end = endPoint;}
	int getLabel(){return label;}
	void setLabel(int newLabel){label = newLabel;}
	//��������
	double distance(); 
	//��������
	~Line(){};
private:
	Point start;  //���
	Point end;    //�յ�
	int label;    //���
};

double Line::distance()
{
	double xValue = start.getX() - end.getX();
	double yValue = start.getY() - end.getY();
	return sqrt(xValue * xValue + yValue * yValue);
}

#endif