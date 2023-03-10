/*
	2018.11.08 21:48 - 2018.11.09 20:22
	类模板-链表：单向链表（已实现），双向链表（已实现），循环链表
2018.11.15 10:03 - 13:12 增加双向链表类模板 DoublyList 的实现，测试均可正常运行，参照吕鑫课程与MFC CList的源代码设计；保存程序文件为“Unicode - 代码页 1200”。
2018 11.17 13:04 - 14:58 增加双向链表类模板 LinkedList 的实现，仿照STL List iterator迭代器，实质为类中类的外壳封装并重载运算符。
2018 11.19 10:05 - 11:45 增加链表外排序 ExternalOrder()，通过二级指针构建并排列序列且返回之，而原始链表结点次序保持不变，速度很快，通过 T*& 亦可交换指针指向。
*/
#pragma once

#include "DataIndex.h"

// 添加新行 枚举
enum AppendNewLine
{
	NoNewLine,	//以空格分隔
	AddNewLine	//以换行分隔
};


// 单向链表 类模板
template <class T>
class List
{
protected:
	// 结点结构体模板
	template <class T>
	struct Node
	{
		T data;			//数据域
		Node<T>* pNext;	//指针域
	};

public:
	List();
	~List();

	// 新建结点，仅填充数据域
	Node<T>* NewNode(const T& newData);
	// 释放结点
	void FreeNode(Node<T>* node);

	// 头插法
	void AddHead(const T& value);
	// 尾插法
	void AddTail(const T& value);
	// 中间插入，在索引之后
	bool InsertAfter(const int index, const T& value);

	// 删除第一个结点，out_value: 被删除的结点数据
	bool DeleteHead(T* out_value);
	// 删除最后一个结点，out_value: 被删除的结点数据
	bool DeleteTail(T* out_value);
	// 删除位置为position的结点，out_value: 被删除的结点数据
	bool DeleteAt(const int index, T* out_value);

	// 清空链表
	void ClearAll();

	// 修改位置为position结点的数据为in_value
	bool ModifyAt(const int index, const T& in_value);

	// 查找第一个数据值为key的结点，返回其在链表的索引位置
	int FindPosition(const T& key);

	// 对链表排序，升序，针对于数值型数据域
	void SortAscent(void);

	// 判断链表是否为空
	bool IsEmpty() { return NULL == m_pHeadNode->pNext; }

	// 获取链表大小（长度）
	int GetSize() const { return m_size; }
	// 获取链表名字
	std::string GetName() const { return m_name; }
	// 设置链表名字
	void SetName(const std::string& name) { m_name = name; }

	// 打印链表数据
	void PrintList(AppendNewLine addnl = AppendNewLine::NoNewLine);

private:
	Node<T> * m_pHeadNode;		//指向第一个结点（头指针）
	//Node<T> * m_pRearNode;		//指向最后一个结点（尾指针）
	int m_size;				//链表元素个数
	//int m_position;			//索引位置，默认从0开始，与数组相似
	std::string m_name;			//链表名字
};

template <class T>
List<T>::List()
{
	m_pHeadNode = NULL;
	//m_pRearNode = NULL;
	m_size = 0;
	//m_position = -1;
	m_name.clear();
}

template <class T>
List<T>::~List()
{
	ClearAll();
}

template<class T>
inline List<T>::Node<T>* List<T>::NewNode(const T & newData)
{
	Node<T>* newNode = new Node<T>;
	if (NULL == newNode)
	{
		std::cout << "Memory allocate failure!" << std::endl;
		system("pause");
		exit(1);
	}
		
	newNode->data = newData;
	return newNode;
}

template<class T>
inline void List<T>::FreeNode(Node<T>* node)
{
	delete node;
	node = NULL;
}

template<class T>
inline void List<T>::AddHead(const T & value)
{
	Node<T>* newNode = NewNode(value);
	newNode->pNext = this->m_pHeadNode;
	this->m_pHeadNode = newNode;

	this->m_size++;
}

template<class T>
inline void List<T>::AddTail(const T & value)
{
	Node<T>* newNode = NewNode(value);
	newNode->pNext = NULL;
	if (!this->m_pHeadNode)
	{
		this->m_pHeadNode = newNode;

		this->m_size++;

		return;
	}

	Node<T>* tmpNode = this->m_pHeadNode;
	while (tmpNode->pNext != NULL)
	{
		tmpNode = tmpNode->pNext;
	}
	tmpNode->pNext = newNode;

	this->m_size++;
}

template<class T>
inline bool List<T>::InsertAfter(const int index, const T & value)
{
	int position = 0;
	Node<T>* prevNode = this->m_pHeadNode;

	if (index <= 0)
	{
		AddHead(value);
		return true;
	}

	while (prevNode != NULL && position < index - 1)
	{
		prevNode = prevNode->pNext;
		position++;
	}
	if (NULL == prevNode || position > index - 1)
		return false;

	Node<T>* newNode = NewNode(value);
	newNode->pNext = prevNode->pNext;
	prevNode->pNext = newNode;

	this->m_size++;

	return true;
}

template<class T>
inline bool List<T>::DeleteHead(T * out_value)
{
	if (NULL == this->m_pHeadNode)
		return false;
	
	Node<T>* deletedNode = this->m_pHeadNode;
	*out_value = deletedNode->data;
	this->m_pHeadNode = this->m_pHeadNode->pNext;
	FreeNode(deletedNode);
	
	this->m_size--;

	return true;
}

template<class T>
inline bool List<T>::DeleteTail(T * out_value)
{
	if (NULL == this->m_pHeadNode)
		return false;

	Node<T>* prevNode = NULL;
	Node<T>* currNode = this->m_pHeadNode;
	while (currNode->pNext != NULL)
	{
		prevNode = currNode;
		currNode = currNode->pNext;
	}
	*out_value = currNode->data;
	FreeNode(currNode);
	prevNode->pNext = NULL;

	this->m_size--;

	return true;
}

template<class T>
inline bool List<T>::DeleteAt(const int index, T * out_value)
{
	int position = 1;
	Node<T>* prevNode = this->m_pHeadNode;

	if (index <= 1)
	{
		DeleteHead(out_value);
		return true;
	} 

	while (prevNode != NULL && position < index - 1)
	{
		prevNode = prevNode->pNext;
		position++;
	}
	if (NULL == prevNode || position > index - 1)
		return false;

	Node<T>* deletedNode = prevNode->pNext;
	*out_value = deletedNode->data;			//取出被删除结点的数据
	prevNode->pNext = deletedNode->pNext;
	
	FreeNode(deletedNode);

	this->m_size--;

	return true;
}

template<class T>
inline void List<T>::ClearAll()
{
	Node<T>* prevNode = nullptr;
	Node<T>* currNode = this->m_pHeadNode;
	while (currNode != NULL)
	{
		prevNode = currNode;

		currNode = currNode->pNext;

		FreeNode(prevNode);
	}
	this->m_pHeadNode = NULL;

	this->m_size = 0;
}

template<class T>
inline bool List<T>::ModifyAt(const int index, const T & in_value)
{
	int position = 1;
	Node<T>* currNode = this->m_pHeadNode;

	while (currNode != NULL && position < index)
	{
		currNode = currNode->pNext;
		position++;
	}
	if (NULL == currNode || position > index)
		return false;

	currNode->data = in_value;

	return true;
}

template<class T>
inline int List<T>::FindPosition(const T & key)
{
	int position = 1;
	Node<T>* currNode = this->m_pHeadNode;
	while (currNode != NULL)
	{
		if (key == currNode->data)
			return position;

		currNode = currNode->pNext;
		position++;
	}

	return -1;
}

template<class T>
inline void List<T>::SortAscent(void)
{
	int i, j, temp;
	int size = this->m_size;
	Node<T>* prevNode;
	Node<T>* nextNode;
	
	for(i = 0, prevNode = this->m_pHeadNode; i < size - 1; i++, prevNode = prevNode->pNext)
		for (j = i + 1, nextNode = prevNode->pNext; j < size; j++, nextNode = nextNode->pNext)
		{
			if (prevNode->data > nextNode->data)
			{
				temp = prevNode->data;
				prevNode->data = nextNode->data;
				nextNode->data = temp;
			}
		}

	return;
}

template<class T>
inline void List<T>::PrintList(AppendNewLine addnl)
{
	Node<T>* currNode = this->m_pHeadNode;
	while (currNode != NULL)
	{
		if (AppendNewLine::NoNewLine == addnl)
			std::cout << currNode->data << " ";
		else
			std::cout << currNode->data << std::endl;

		currNode = currNode->pNext;

	}
}


typedef void* POSITION;

// 双向链表 类模板 仿照MFC CList POSITION
template<class T>
class DouBlyList
{
protected:
	// 结点 结构体模板
	template<class T>
	struct SNode
	{
		T data;				//数据域
		SNode<T>* pPrev;	//前驱指针
		SNode<T>* pNext;	//后继指针
	};

	// 新建结点
	SNode<T>* NewNode(const T& newData);

	// 释放结点
	void FreeNode(SNode<T>* deleteNode);

public:
	DouBlyList();
	~DouBlyList();

	// 头部插入（口式）
	POSITION AddHead(T value);
	// 尾部插入（门式）
	POSITION AddTail(T value);

	// 当前结点之前插入（上下式）
	POSITION InsertBefore(POSITION pos, T value);

	// 当前结点之后插入（后入式）
	POSITION InsertAfter(POSITION pos, T value);

	// 判断链表是否为空
	bool IsEmpty() const { return 0 == m_count; }

	// 链表结点计数
	int GetCount()	const { return m_count; }
	// 头指针
	POSITION GetHeadPosition() const { return (POSITION)m_pHead; }
	// 尾指针
	POSITION GetTailPosition() const { return (POSITION)m_pTail; }

	// 返回当前结点指针数据，同时指针向前游走
	T GetPrev(POSITION &pos);
	// 返回当前结点指针数据，同时指针向前游走
	T GetNext(POSITION &pos);
	// 返回当前结点指针数据
	T& GetAt(POSITION pos) { return ((SNode<T>*)pos)->data; }
	// 返回当前结点指针数据，const只读成员函数
	const T& GetAt(POSITION pos) const { return ((SNode<T>*)pos)->data; }

	// 修改当前结点指针数据
	void SetAt(POSITION pos, T value) { ((SNode<T>*)pos)->data = value; }

	// 移除当前结点
	void RemoveAt(POSITION pos);
	// 移除全部结点
	void RemoveAll();

	// 查找结点：根据数值，返回第一个查到的结点
	POSITION Find(POSITION startAfter, const T& value) const;
	// 查找结点：根据索引，从0开始
	POSITION FindIndex(int index) const;

private:
	int m_count;		//链表结点计数器
	SNode<T>* m_pHead;	//头指针
	SNode<T>* m_pTail;	//尾指针
};

template<class T>
inline DouBlyList<T>::SNode<T>* DouBlyList<T>::NewNode(const T & newData)
{
	SNode<T>* newNode = new SNode<T>;
	if (NULL == newNode)
	{
		std::wcout << "Memory allocate failure!" << std::endl;
		system("pause");
		exit(1);
	}

	newNode->data = newData;
	return newNode;
}

template<class T>
inline void DouBlyList<T>::FreeNode(SNode<T>* deleteNode)
{
	delete deleteNode;
	deleteNode = nullptr;
}

template<class T>
DouBlyList<T>::DouBlyList()
{
	m_count = 0;
	m_pHead = m_pTail = nullptr;
}

template<class T>
DouBlyList<T>::~DouBlyList()
{
	RemoveAll();
}

template<class T>
inline POSITION DouBlyList<T>::AddHead(T value)
{
	SNode<T>* newNode = NewNode(value);
	// 考虑头结点指针是否存在
	if (m_pHead)
		m_pHead->pPrev = newNode;
	else
		m_pTail = newNode;

	newNode->pPrev = nullptr;
	newNode->pNext = m_pHead;
	m_pHead = newNode;

	m_count++;

	return (POSITION)newNode;
}

template<class T>
inline POSITION DouBlyList<T>::AddTail(T value)
{
	SNode<T>* newNode = NewNode(value);
	// 考虑尾结点是否存在
	if (m_pTail)
		m_pTail->pNext = newNode;
	else
		m_pHead = newNode;

	newNode->pPrev = m_pTail;
	newNode->pNext = nullptr;
	m_pTail = newNode;

	m_count++;

	return (POSITION)newNode;
}

template<class T>
inline POSITION DouBlyList<T>::InsertBefore(POSITION pos, T value)
{
	if (nullptr == pos)
		return AddHead(value);			//头插法

	SNode<T>* newNode = NewNode(value);
	SNode<T>* oldNode = (SNode<T>*)pos;
	if (nullptr == oldNode->pPrev)
	{
		newNode->pPrev = nullptr;
		m_pHead = newNode;
	}
	else
	{
		newNode->pPrev = oldNode->pPrev;
		oldNode->pPrev->pNext = newNode;		
	}

	newNode->pNext = oldNode;
	oldNode->pPrev = newNode;

	m_count++;

	return (POSITION)newNode;
}

template<class T>
inline POSITION DouBlyList<T>::InsertAfter(POSITION pos, T value)
{
	// 判断插入之处是否为空（处子情结）
	if (nullptr == pos)
		return AddTail(value);			//尾插法

	SNode<T>* newNode = NewNode(value);
	SNode<T>* oldNode = (SNode<T>*)pos;
	// 判断插入之后是否为空（初次情结）
	if (nullptr == oldNode->pNext)
	{
		newNode->pNext = nullptr;
		m_pTail = newNode;
	}
	else
	{
		newNode->pNext = oldNode->pNext;
		oldNode->pNext->pPrev = newNode;
	}

	newNode->pPrev = oldNode;
	oldNode->pNext = newNode;

	m_count++;

	return (POSITION)newNode;
}


template<class T>
inline void DouBlyList<T>::RemoveAt(POSITION pos)
{
	SNode<T>* pSNode = (SNode<T>*)pos;

	// 如果删除的是头结点
	if (pSNode == m_pHead)
		m_pHead = pSNode->pNext;
	else
		pSNode->pPrev->pNext = pSNode->pNext;

	// 如果删除的是尾结点
	if (pSNode == m_pTail)
		m_pTail = pSNode->pPrev;
	else
		pSNode->pNext->pPrev = pSNode->pPrev;

	FreeNode(pSNode);

	m_count--;
}

template<class T>
inline void DouBlyList<T>::RemoveAll()
{
	SNode<T>* pCurr = m_pHead;	//当前结点指针
	SNode<T>* pTemp = nullptr;	//临时结点指针
	while (pCurr)
	{
		pTemp = pCurr;
		pCurr = pCurr->pNext;

		FreeNode(pTemp);
	}

	m_count = 0;
	m_pHead = m_pTail = nullptr;
}

template<class T>
inline POSITION DouBlyList<T>::Find(POSITION startAfter, const T & value) const
{
	SNode<T>* pNode = (SNode<T>*)startAfter;
	if (nullptr == startAfter)
		pNode = m_pHead;		//从头开始
	else
		pNode = pNode->pNext;	//从下一个结点开始

	for (; pNode != nullptr; pNode = pNode->pNext)
		if (pNode->data == value)
			return (POSITION)pNode;

	// 没找到
	return nullptr;
}

template<class T>
inline POSITION DouBlyList<T>::FindIndex(int index) const
{
	if (index < 0 || index > m_count - 1)
		return nullptr;

	SNode<T>* pNode = m_pHead;
	while (index--)
	{
		pNode = pNode->pNext;
	}

	return (POSITION)pNode;
}

template<class T>
inline T DouBlyList<T>::GetPrev(POSITION & pos)
{
	T value = ((SNode<T>*)pos)->data;
	pos = ((SNode<T>*)pos)->pPrev;
	return value;
}

template<class T>
inline T DouBlyList<T>::GetNext(POSITION & pos)
{
	T value = ((SNode<T>*)pos)->data;
	pos = ((SNode<T>*)pos)->pNext;
	return value;
}


 // 双向链表 类模板 仿照STL List iterator
template<class T, class AT = const T&>
class LinkedList
{
protected:
	// 结点 结构体模板
	struct SNode
	{
		T data;			//数据域
		SNode* pPrev;	//前驱指针
		SNode* pNext;	//后继指针
	};

	// 新建结点
	SNode* NewNode(AT newData);

	// 释放结点
	void FreeNode(SNode* deleteNode);

public:
	// 迭代器
	class Iterator
	{
	public:
		Iterator() { }
		~Iterator() { }

		Iterator(SNode* pNode) { m_pNode = pNode; }

		// 类型自动转换为SNode*，返回值相同则可省
		operator SNode*() { return m_pNode; }

		// 取内容获得数据。！返回值类型为引用可以做左值
		T& operator*() { return m_pNode->data; }

		// ++前置，返回当前对象则可以使用引用作为左值
		Iterator& operator++()
		{
			m_pNode = m_pNode->pNext;
			return *this;
		}

		// 后置++，返回的是临时变量故不能返回引用作为左值
		Iterator operator++(int ignore)
		{
			Iterator it(m_pNode);
			m_pNode = m_pNode->pNext;
			return it;
		}

		// --前置
		Iterator& operator--()
		{
			m_pNode = m_pNode->pPrev;
			return *this;
		}

		// 后置--
		Iterator operator--(int ignore)
		{
			Iterator it(m_pNode);
			m_pNode = m_pNode->pPrev;
			return it;
		}

	private:
		SNode * m_pNode;
	};

public:
	LinkedList();
	~LinkedList();

	// 头部插入
	Iterator push_front(AT value);
	// 尾部插入
	Iterator push_back(AT value);

	// 判断链表是否为空
	bool empty() const { return 0 == m_count; }

	// 链表结点计数
	int size()	const { return m_count; }
	// 返回第一个元素的位置
	Iterator begin() const { return m_pHead; }
	// 返回最后一个元素的下一个位置
	Iterator end() const { return m_pTail->pNext; }

	// 修改当前结点指针数据，通过 *Iterator = value;
	// 指针移动，通过 Iterator++ / ++Iterator / Iterator-- / --Iterator

	// 移除当前结点
	void earse(Iterator it);
	// 移除全部结点
	void clear();

public:
	// 表外排序回调函数指针
	using OrderCallback = bool(*)(T, T);

	// 链表表外排序：返回保存顺序的二级指针，原始数据次序保持不变
	//SNode * * ExternalOrder(OrderCallback function);
	Iterator * ExternalOrder(OrderCallback function);


	// 外部排序打印
	//void ExternalPrint(const SNode** pOrder);
	void ExternalPrint(const Iterator* in_pOrder);

private:
	int m_count;		//链表结点计数器
	SNode* m_pHead;		//头指针
	SNode* m_pTail;		//尾指针
};

template<class T, class AT>
typename LinkedList<T, AT>::SNode * 
LinkedList<T, AT>::NewNode(AT newData)
{
	SNode* newNode = new SNode;
	if (NULL == newNode)
	{
		std::wcout << "Memory allocate failure!" << std::endl;
		system("pause");
		exit(1);
	}

	newNode->data = newData;
	return newNode;
}

template<class T, class AT>
inline void LinkedList<T, AT>::FreeNode(SNode * deleteNode)
{
	delete deleteNode;
	deleteNode = nullptr;
}

template<class T, class AT>
inline LinkedList<T, AT>::LinkedList()
{
	m_count = 0;
	m_pHead = m_pTail = nullptr;
}

template<class T, class AT>
inline LinkedList<T, AT>::~LinkedList()
{
	clear();
}

//让编译器明白LikedList<T, AT>::Iterator是个类型而非LikedList<T, AT>的成员
template<class T, class AT>
typename LinkedList<T, AT>::Iterator 
LinkedList<T, AT>::push_front(AT value)
{
	SNode* newNode = NewNode(value);
	// 考虑头结点指针是否存在
	if (m_pHead)
		m_pHead->pPrev = newNode;
	else
		m_pTail = newNode;

	newNode->pPrev = nullptr;
	newNode->pNext = m_pHead;
	m_pHead = newNode;

	m_count++;

	return newNode;

}

template<class T, class AT>
typename LinkedList<T, AT>::Iterator
LinkedList<T, AT>::push_back(AT value)
{
	SNode* newNode = NewNode(value);
	// 考虑尾结点是否存在
	if (m_pTail)
		m_pTail->pNext = newNode;
	else
		m_pHead = newNode;

	newNode->pPrev = m_pTail;
	newNode->pNext = nullptr;
	m_pTail = newNode;

	m_count++;

	return newNode;

}

template<class T, class AT>
inline void LinkedList<T, AT>::earse(Iterator it)
{
	SNode* pSNode = (SNode*)it;

	// 如果删除的是头结点
	if (pSNode == m_pHead)
		m_pHead = pSNode->pNext;
	else
		pSNode->pPrev->pNext = pSNode->pNext;

	// 如果删除的是尾结点
	if (pSNode == m_pTail)
		m_pTail = pSNode->pPrev;
	else
		pSNode->pNext->pPrev = pSNode->pPrev;

	FreeNode(pSNode);

	m_count--;

}

template<class T, class AT>
inline void LinkedList<T, AT>::clear()
{
	SNode* pCurr = m_pHead;	//当前结点指针
	SNode* pTemp = nullptr;	//临时结点指针
	while (pCurr)
	{
		pTemp = pCurr;
		pCurr = pCurr->pNext;

		FreeNode(pTemp);
	}

	m_count = 0;
	m_pHead = m_pTail = nullptr;

}

template<class T, class AT>
typename LinkedList<T, AT>::Iterator*
LinkedList<T, AT>::ExternalOrder(OrderCallback function)
{
	// 创建指向结点个数+1的结点指针
	SNode** pOrder = new SNode*[this->m_count + 1];	
	SNode* pCurr = this->m_pHead;
	int n = this->m_count;
	// 指向各个结点
	int index = 0;
	while (pOrder[index++] = pCurr)
		pCurr = pCurr->pNext;

	// 选择排序
	int i, j, m;
	for (i = 0; i < n - 1; i++)
	{
		m = i;
		for (j = i + 1; j < n; j++)
			if (function(pOrder[j]->data , pOrder[m]->data))
				m = j;
		if (m != i)
			DataIndex<SNode*>::Swap(pOrder[m], pOrder[i]);
	//	{
	//		SNode* pTemp = pOrder[m];
	//		pOrder[m] = pOrder[i];
	//		pOrder[i] = pTemp;
	//	}
	}

	return (Iterator*)pOrder;
}

template<class T, class AT>
inline void LinkedList<T, AT>::ExternalPrint(const Iterator* in_pOrder)
{
	SNode** pOrder = (SNode**)in_pOrder;
	for (int i = 0; i < m_count; i++)
	{
		std::wcout << pOrder[i]->data << " ";
	}
	std::wcout << std::endl;
}
