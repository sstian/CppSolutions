#include "Graph.h"

Graph::Graph(int capacity)
{
	m_iCapacity = capacity;
	m_iNodeCount = 0;
	m_pNodeArray = new Node[m_iCapacity];
	m_pMatrix = new int[m_iCapacity * m_iCapacity];

	memset(m_pMatrix, 0, m_iCapacity * m_iCapacity * sizeof(int));

	m_pEdge = new Edge[m_iCapacity - 1];
}

Graph::~Graph()
{
	delete[] m_pNodeArray;
	delete[] m_pMatrix;

	delete[] m_pEdge;
}

bool Graph::AddNode(Node * pNode)
{
	if (!pNode)
		return false;

	m_pNodeArray[m_iNodeCount].m_data = pNode->m_data;
	m_iNodeCount++;
	return true;
}

void Graph::ResetNode()
{
	for (int index = 0; index < m_iNodeCount; index++)
		m_pNodeArray[index].m_isVisited = false;
}

bool Graph::SetValueToMatrixForDirectedGraph(int row, int col, int val)
{
	if (row < 0 || row > m_iCapacity)
		return false;
	if (col < 0 || col > m_iCapacity)
		return false;

	m_pMatrix[row * m_iCapacity + col] = val;
	return true;
}

bool Graph::SetValueToMatrixForUndirectedGraph(int row, int col, int val)
{
	if (row < 0 || row > m_iCapacity)
		return false;
	if (col < 0 || col > m_iCapacity)
		return false;

	m_pMatrix[row * m_iCapacity + col] = val;
	m_pMatrix[col * m_iCapacity + row] = val;
	return true;
}

bool Graph::SetValueToMatrix(int** matrix)
{
	//*((int*)matrix + row * m_iCapacity + col) 才可以！
	for (int row = 0; row < m_iCapacity; row++)
		for (int col = 0; col < m_iCapacity; col++)
			m_pMatrix[row * m_iCapacity + col] = *((int*)matrix + row * m_iCapacity + col);	
	return true;
}

void Graph::PrintMatrix()
{
	for (int i = 0; i < m_iCapacity; i++)
	{
		for (int j = 0; j < m_iCapacity; j++)
		{
			cout << m_pMatrix[i * m_iCapacity + j] << " ";
		}
		cout << endl;
	}
}

void Graph::DepthFirstSearch(int indexNode)
{
	// 输出当前结点，并设置状态为已访问
	cout << m_pNodeArray[indexNode].m_data << " ";
	m_pNodeArray[indexNode].m_isVisited = true;

	// 通过邻接矩阵判断是否与其它的定点有连接
	int value = 0;
	for (int index = 0; index < m_iCapacity; index++)
	{
		this->GetValueFromMatrix(indexNode, index, value);
		// 判断连接边的顶点和点访问
		if(value != 0 && !m_pNodeArray[index].m_isVisited)
			this->DepthFirstSearch(index);
	}
}

void Graph::BreadthFirstSearch(int indexNode)
{
	cout << m_pNodeArray[indexNode].m_data << " ";
	m_pNodeArray[indexNode].m_isVisited = true;

	int value = 0;
	queue<int> que;
	que.push(indexNode);
	while (!que.empty())
	{
		int front = que.front();
		que.pop();
		for (int index = 0; index < m_iCapacity; index++)
		{
			this->GetValueFromMatrix(front, index, value);
			if (value != 0 && !m_pNodeArray[index].m_isVisited)
			{
				cout << m_pNodeArray[index].m_data << " ";
				m_pNodeArray[index].m_isVisited = true;
				que.push(index);
			}
		}
	}
}

void Graph::Floyd(int ** matrix, int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				if (matrix[i][k] == -1 || matrix[k][j] == -1)
					continue;
				matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}

	for (int a = 0; a < n; a++)
	{
		for (int b = 0; b < n; b++)
			cout << setw(2) << matrix[a][b] << " ";
		cout << endl;
	}
}

void Graph::PrimTree(int indexNode/*, const string* alpha*/)
{
	int value = 0;
	int countEdge = 0;
	vector<Edge> vecEdge;
	vector<int> vecNode;

	vecNode.push_back(indexNode);
	m_pNodeArray[indexNode].m_isVisited = true;

	while (countEdge < m_iCapacity - 1)
	{
		int temp = vecNode.back();
		for (int index = 0; index < m_iCapacity; index++)
		{
			this->GetValueFromMatrix(temp, index, value);
			if (value != 0 && !m_pNodeArray[index].m_isVisited)
			{
				Edge edge(temp, index, value);
				vecEdge.push_back(edge);
			}
		}

		// 从可选边集合中找到最小的边
		int indexEdge = this->GetMinEdge(vecEdge);
		Edge& edge = vecEdge[indexEdge];
		edge.m_isSelected = true;

		m_pEdge[countEdge++] = edge;

		int indexNodeNext = edge.m_indexNodeB;
		vecNode.push_back(indexNodeNext);
		m_pNodeArray[indexNodeNext].m_isVisited = true;

		cout << m_pNodeArray[edge.m_indexNodeA].m_data << " " << edge.m_indexNodeA 
			<< " - " << edge.m_indexNodeB << " " << m_pNodeArray[edge.m_indexNodeB].m_data
			<< " = " << edge.m_valueWeight << endl;
		//// 输出为标志
		//cout << alpha[edge.m_indexNodeA] << " - " << alpha[edge.m_indexNodeB] << " = "
		//	<< edge.m_valueWeight << endl;
	}
}

void Graph::KruskalTree(int indexNode)
{
	int value = 0;
	int countEdge = 0;

	// 定义存放结点集合的数组
	vector<vector<int>> vecsNode;

	// 第一步：取出所有边
	vector<Edge> vecEdge;
	for (int i = 0; i < m_iCapacity; i++)
	{
		for (int j = i + 1; j < m_iCapacity; j++)
		{
			GetValueFromMatrix(i, j, value);
			if (value != 0)
			{
				Edge edge(i, j, value);
				vecEdge.push_back(edge);
			}
		}
	}

	// 第二步：从所有边中取出组成最小生成树的边
	//1. 找到算法结束条件
	while (countEdge < m_iCapacity - 1)
	{
		//2. 从边集合中找到最小边
		int indexEdgeMin = this->GetMinEdge(vecEdge);
		vecEdge[indexEdgeMin].m_isSelected = true;

		//3. 找出最小边连接的点
		int indexNodeA = vecEdge[indexEdgeMin].m_indexNodeA;
		int indexNodeB = vecEdge[indexEdgeMin].m_indexNodeB;

		bool isInSetNodeA = false;
		bool isInSetNodeB = false;

		int inSetLabelNodeA = -1;
		int inSetLabelNodeB = -1;

		//4. 找出点所在的点集合
		int size = (int)vecsNode.size();
		for (int index = 0; index < size; index++)
		{
			isInSetNodeA = this->IsInSet(vecsNode[index], indexNodeA);
			if (isInSetNodeA)
				inSetLabelNodeA = index;
		}

		for (int index = 0; index < size; index++)
		{
			isInSetNodeB = this->IsInSet(vecsNode[index], indexNodeB);
			if (isInSetNodeB)
				inSetLabelNodeB = index;
		}

		//5. 根据点所在集合的不同做出不同处理
		if (inSetLabelNodeA == -1 && inSetLabelNodeB == -1)
		{
			vector<int> vec;
			vec.push_back(indexNodeA);
			vec.push_back(indexNodeB);
			vecsNode.push_back(vec);
		}
		else if (inSetLabelNodeA == -1 && inSetLabelNodeB != -1)
		{
			vecsNode[inSetLabelNodeB].push_back(indexNodeA);
		}
		else if (inSetLabelNodeA != -1 && inSetLabelNodeB == -1)
		{
			vecsNode[inSetLabelNodeA].push_back(indexNodeB);
		}
		else if (inSetLabelNodeA != -1 && inSetLabelNodeB != -1 && inSetLabelNodeA != inSetLabelNodeB)
		{
			this->MergeNodeSet(vecsNode[inSetLabelNodeA], vecsNode[inSetLabelNodeB]);
			int size = (int)vecsNode.size() - 1;
			for (int k = inSetLabelNodeB; k < size; k++)
			{
				vecsNode[k] = vecsNode[k + 1];
			}
		}
		else if (inSetLabelNodeA != -1 && inSetLabelNodeB != -1 && inSetLabelNodeA == inSetLabelNodeB)
		{
			continue;
		}

		m_pEdge[countEdge++] = vecEdge[indexEdgeMin];
		
		Edge& edge = vecEdge[indexEdgeMin];
		cout << m_pNodeArray[edge.m_indexNodeA].m_data << " " << edge.m_indexNodeA
			<< " - " << edge.m_indexNodeB << " " << m_pNodeArray[edge.m_indexNodeB].m_data
			<< " = " << edge.m_valueWeight << endl;
	}
}

bool Graph::GetValueFromMatrix(int row, int col, int& val)
{
	if (row < 0 || row > m_iCapacity)
		return false;
	if (col < 0 || col > m_iCapacity)
		return false;

	val = m_pMatrix[row * m_iCapacity + col];
	return true;
}

int Graph::GetMinEdge(vector<Edge>& vecEdge)
{
	int minWeight = 0;
	int indexEdge = 0;
	int index = 0;
	
	// 先找到未选择过的边的权重
	int size = (int)vecEdge.size();
	for (; index < size; index++)
	{
		if (!vecEdge[index].m_isSelected)
		{
			minWeight = vecEdge[index].m_valueWeight;
			indexEdge = index;
			break;
		}
	}

	// 失败了
	if (0 == minWeight)
		return -1;

	// 搜索比较寻找权值最小的边，及其索引
	for (; index < size; index++)
	{
		Edge& edge = vecEdge[index];
		if (!edge.m_isSelected && minWeight > edge.m_valueWeight)
		{
			minWeight = edge.m_valueWeight;
			indexEdge = index;
		}
	}

	return indexEdge;
	
}

bool Graph::IsInSet(vector<int>& vecNode, int target)
{
	for (auto& at : vecNode)
		if (at == target)
			return true;
	return false;
}

void Graph::MergeNodeSet(vector<int>& nodeSetA, vector<int>& nodeSetB)
{
	for (auto& at : nodeSetB)
		nodeSetA.push_back(at);
}
