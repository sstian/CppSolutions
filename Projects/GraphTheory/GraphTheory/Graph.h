#pragma once

#include <queue>
#include <iomanip>
#include "Node.h"
#include "Edge.h"

// 图类
class Graph
{
public:
	Graph(int capacity);
	~Graph();

	// 向图中加入顶点（结点）
	bool AddNode(Node* pNode);
	// 重置顶点
	void ResetNode();
	// 为无向图设置邻接矩阵
	bool SetValueToMatrixForDirectedGraph(int row, int col, int val = 1);
	// 为有向图设置邻接矩阵
	bool SetValueToMatrixForUndirectedGraph(int row, int col, int val = 1);
	// 设置邻接矩阵
	bool SetValueToMatrix(int** matrix);
	
	// 打印邻接矩阵
	void PrintMatrix();

	// 深度优先遍历
	void DepthFirstSearch(int indexNode);
	// 广度优先遍历
	void BreadthFirstSearch(int indexNode);

	// 多源最短路径
	static void Floyd(int** matrix, int n);


	// 最小生成树算法：Prim
	void PrimTree(int indexNode/*, const string* alpha*/);
	// 最小生成树算法：Kruskal
	void KruskalTree(int indexNode);

private:
	// 从矩阵中获取权值
	bool GetValueFromMatrix(int row, int col, int& val);

	// 从可选边集合中找到最小的边
	int GetMinEdge(vector<Edge>& vecEdge);
	// 判断顶点是否在点集合中
	bool IsInSet(vector<int>& vecNode, int target);
	// 合并两个顶点集合
	void MergeNodeSet(vector<int>& nodeSetA, vector<int>& nodeSetB);

private:
	int m_iCapacity;		//图中最多可以容纳的定点数
	int m_iNodeCount;		//已经添加的定点（结点）个数
	Node* m_pNodeArray;		//存放顶点数组
	int* m_pMatrix;			//存放邻接矩阵

	Edge* m_pEdge;			//边集合
};


