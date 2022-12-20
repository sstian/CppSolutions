#pragma once

#include <iostream>
#include <string>
using namespace std;

// 结点类
class Node
{
public:
	Node(string data = "");
	~Node();

public:
	bool m_isVisited;		//访问标志
	string m_data;			//数据内容

//private:

};
