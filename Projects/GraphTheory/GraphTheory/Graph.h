#pragma once

#include <queue>
#include <iomanip>
#include "Node.h"
#include "Edge.h"

// ͼ��
class Graph
{
public:
	Graph(int capacity);
	~Graph();

	// ��ͼ�м��붥�㣨��㣩
	bool AddNode(Node* pNode);
	// ���ö���
	void ResetNode();
	// Ϊ����ͼ�����ڽӾ���
	bool SetValueToMatrixForDirectedGraph(int row, int col, int val = 1);
	// Ϊ����ͼ�����ڽӾ���
	bool SetValueToMatrixForUndirectedGraph(int row, int col, int val = 1);
	// �����ڽӾ���
	bool SetValueToMatrix(int** matrix);
	
	// ��ӡ�ڽӾ���
	void PrintMatrix();

	// ������ȱ���
	void DepthFirstSearch(int indexNode);
	// ������ȱ���
	void BreadthFirstSearch(int indexNode);

	// ��Դ���·��
	static void Floyd(int** matrix, int n);


	// ��С�������㷨��Prim
	void PrimTree(int indexNode/*, const string* alpha*/);
	// ��С�������㷨��Kruskal
	void KruskalTree(int indexNode);

private:
	// �Ӿ����л�ȡȨֵ
	bool GetValueFromMatrix(int row, int col, int& val);

	// �ӿ�ѡ�߼������ҵ���С�ı�
	int GetMinEdge(vector<Edge>& vecEdge);
	// �ж϶����Ƿ��ڵ㼯����
	bool IsInSet(vector<int>& vecNode, int target);
	// �ϲ��������㼯��
	void MergeNodeSet(vector<int>& nodeSetA, vector<int>& nodeSetB);

private:
	int m_iCapacity;		//ͼ�����������ɵĶ�����
	int m_iNodeCount;		//�Ѿ���ӵĶ��㣨��㣩����
	Node* m_pNodeArray;		//��Ŷ�������
	int* m_pMatrix;			//����ڽӾ���

	Edge* m_pEdge;			//�߼���
};


