#pragma once

// ±ﬂ¿‡
class Edge
{
public:
	Edge(int indexNodeA = 0, int indexNodeB = 0, int valueWeight = 0);
	~Edge();

public:
	int m_indexNodeA;
	int m_indexNodeB;
	int m_valueWeight;
	bool m_isSelected;
};

