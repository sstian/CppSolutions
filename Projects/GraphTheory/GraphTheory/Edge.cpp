#include "Edge.h"

Edge::Edge(int indexNodeA, int indexNodeB, int valueWeight)
{
	m_indexNodeA = indexNodeA;
	m_indexNodeB = indexNodeB;
	m_valueWeight = valueWeight;
	m_isSelected = false;
}


Edge::~Edge()
{
}
