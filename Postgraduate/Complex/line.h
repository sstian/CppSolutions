/*组合类Line及Point定义的头文件*/
#ifndef LINE_H
#define LINE_H

#include <cmath>
//点Point类
class Point
{
public:
	//带两个默认参数的构造函数：默认点（0.0,0.0）
	Point(double xValue = 0.0, double yValue = 0.0):x(xValue),y(yValue){}
	//复制构造函数
	Point(Point& otherPoint);
	//成员变量的get,set方法
	double getX(){return x;}
	void setX(double xValue){x = xValue;}
	double getY(){return y;}
	void setY(double yValue){y = yValue;}
	//析构函数
	~Point(){}
private:
	double x;  //横坐标值
	double y;  //纵坐标值
};

Point::Point(Point& otherPoint)
{
	x = otherPoint.getX();
	y = otherPoint.getY();
}

//线Line类
class Line
{
public:
	//带一个默认参数的有三个参数的构造函数
	Line(Point& startPoint, Point& endPoint, int newLabel = 0)
		:start(startPoint),end(endPoint),label(newLabel){}
	//数据成员的get,set方法
	Point getStart(){return start;}
	void setStart(Point& startPoint){start = startPoint;}
	Point getEnd(){return end;}
	void setEnd(Point& endPoint){end = endPoint;}
	int getLabel(){return label;}
	void setLabel(int newLabel){label = newLabel;}
	//两点间距离
	double distance(); 
	//析构函数
	~Line(){};
private:
	Point start;  //起点
	Point end;    //终点
	int label;    //标号
};

double Line::distance()
{
	double xValue = start.getX() - end.getX();
	double yValue = start.getY() - end.getY();
	return sqrt(xValue * xValue + yValue * yValue);
}

#endif