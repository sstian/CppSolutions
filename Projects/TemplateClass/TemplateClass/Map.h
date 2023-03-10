/*
	2018.11.19 15:46 - 16:47
	类模板-Map: 哈希表/散列表、二叉树
	实质：多条链表
2018.11.23 11:11 通讯测试C++-Java连通，以后新建项目选择：配置-Debug/Release，平台-x64，字符集-使用Unicode字符集 头文件： <strign> <locale>
				因此需要使用：字符 wchar_t wc = L'中'; 字符指针 const wchar_t* pwc = L"中国人"; 字符串 wstring wstr = L"中国的";
				输入输出-wcin/std::wcout，中文前面加上wcin.imbue(locale("chs"));/std::wcout.imbue(locale("chs"));
2018.11.23 19:37 - 2018.11.24 00:44 增加哈希表 HashMap (MFC CMap 原理) 和 二叉树 BinaryTreeMap (STL map 原理)，实现添加、查找、删除操作；
									采用抽象类Map，设计纯虚函数，其它从其派生，共用结点数据域。
2018.11.24 01:33 - 01:50 增加博大精深的二级指针和中序遍历、前序遍历、后序遍历（递归调用）。
*/
#pragma once

#define MAP_SIZE 17	//默认Map大小

// 映射 字典 抽象基类
template<class KEY, class VALUE, class ARG_KEY = const KEY&, class ARG_VALUE = const VALUE&>
class Map
{
protected:
	// 结点 结构体 数据域
	struct Node
	{
		KEY		key;
		VALUE	value;

	protected:
		// 构造结点
		Node() = default;
		Node(ARG_KEY newKey, ARG_VALUE newValue) : key(newKey), value(newValue) { }
		// 析构结点
		virtual ~Node() { }
	};

public:
	// 设置键值对（纯虚函数）
	virtual void SetAt(ARG_KEY newKey, ARG_VALUE newValue) = 0;

	// 根据键查询值
	virtual bool Lookup(ARG_KEY key, VALUE& value) const = 0;

	// 操作符[]重载
	virtual VALUE& operator[](ARG_KEY& key) = 0;

public:
	Map() { }
	virtual ~Map() { }
};

// 哈希表 类模板
template<class KEY, class VALUE, class ARG_KEY = const KEY&, class ARG_VALUE = const VALUE&>
class HashMap : public Map<KEY, VALUE, ARG_KEY, ARG_VALUE>
{
protected:
	// 结点 结构体
	struct SNode : public Map<KEY, VALUE, ARG_KEY, ARG_VALUE>::Node
	{
		SNode*	pNext;	//指针域
		
		SNode() = default;	//使用默认构造函数
		SNode(KEY newKey, VALUE newValue) : Map<KEY, VALUE, ARG_KEY, ARG_VALUE>::Node(newKey, newValue) { pNext = nullptr; }
		virtual ~SNode() { }
	};

	// 创建结点
	SNode* NewNode(ARG_KEY newKey, ARG_VALUE newValue);

	// 释放结点
	void FreeNode(SNode* deleteNode);

public:
	HashMap(int size = MAP_SIZE);
	~HashMap();

	// 设置键值对
	virtual void SetAt(ARG_KEY newKey, ARG_VALUE newValue);

	// 根据键查询值
	virtual bool Lookup(ARG_KEY key, VALUE& value) const;

	// 操作符[]重载
	virtual VALUE& operator[](ARG_KEY key);

	bool RemoveKey(ARG_KEY key);

	void RemoveAll();

private:
	int		m_size;		//哈希表的链表条数
	SNode** m_pHash;	//每条哈希链表的指针，栈内指针数组
};

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
typename HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::SNode *
HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::NewNode(ARG_KEY newKey, ARG_VALUE newValue)
{
	SNode* newNode = new SNode(newKey, newValue);
	if (NULL == newNode)
	{
		std::wcout << "Memory allocate failure!" << std::endl;
		system("pause");
		exit(1);
	}
	return newNode;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::FreeNode(SNode * deleteNode)
{
	delete deleteNode;
	deleteNode = nullptr;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::HashMap(int size)
{
	assert(size > 0);
	m_size = size;
	m_pHash = new SNode*[m_size];
	memset(m_pHash, 0, sizeof(SNode*) * m_size);
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::~HashMap()
{
	RemoveAll();
	delete[] m_pHash;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::SetAt(ARG_KEY newKey,  ARG_VALUE newValue)
{
	// 方法3. 调用下标符号
	//// 方法3.1
	//this->operator[](newKey) = newValue;
	// 方法3.2
	(*this)[newKey] = newValue;

	//// 根据键取余选择值存储在哪一条链表上
	//int n = newKey % m_size;	

	//// 新建结点并填充键值对，插入结点
	//// 方法1. 头插法
	//SNode* pNewNode = NewNode(newKey, newValue);
	//pNewNode->pNext = m_pHash[n];
	//m_pHash[n] = pNewNode;

	//// 方法2.尾插法
	//SNode* pCurr = m_pHash[n];
	//SNode* pPrev = nullptr;
	////结点为空
	//if (!pCurr)
	//{
	//	SNode* pData = NewNode(newKey, newValue);
	//	pData->pNext = m_pHash[n];
	//	m_pHash[n] = pNewNode;
	//}
	//while (pCurr)
	//{
	//	pPrev = pCurr;
	//	pCurr = pCurr->pNext;
	//}
	//SNode* pData = NewNode(newKey, newValue);
	//pData->pNext = nullptr;
	//pPrev->pNext = pData;
}
template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline bool HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::Lookup(ARG_KEY key, VALUE& value) const
{
	// 确定键值所在的链表
	SNode* pNode = m_pHash[key % m_size];

	while (pNode)
	{
		// 已找到
		if (key == pNode->key)
		{
			value = pNode->value;
			return true;
		}
		pNode = pNode->pNext;
	}
	// 未找到
	return false;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline VALUE & HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::operator[](ARG_KEY key)
{	
	// 最博大精深的算法，二级指针
	SNode** pNode = &m_pHash[key % m_size];
	while (*pNode)
	{
		if ((*pNode)->key == key)
			return (*pNode)->value;
		pNode = &((*pNode)->pNext);
	}
	//SNode* pData = new SNode(key, VALUE());	//构建无名对象
	SNode* pData = NewNode(key, VALUE());
	*pNode = pData;
	return pData->value;

	//int n = key % m_size;

	//SNode* pNode = m_pHash[n];
	//// 当前链表没有结点，则新建结点，作为左值传递值
	//if (!pNode)
	//{
	//	SNode* pData = new SNode;
	//	pData->key = key;
	//	pData->pNext = nullptr;
	//	m_pHash[n] = pData;
	//	
	//	return pData->value;
	//}
	//// 当前链表存在结点，遍历是否存在对应的键值对
	//SNode* pPrev = nullptr;		//指向前一个结点
	//while (pNode)
	//{
	//	// 存在对应的键值对，则返回值
	//	if (key == pNode->key)
	//		return pNode->value;

	//	pPrev = pNode;
	//	pNode = pNode->pNext;
	//}
	//// 没找到，表示不存在对应的键值对，则新建结点并插入
	//// 方法1. 头插法
	//SNode* pData = new SNode;
	//pData->key = key;
	//pData->pNext = m_pHash[n];
	//m_pHash[n] = pData;

	////// 方法2. 尾插法
	////SNode* pData = new SNode;
	////pData->key = key;
	////pData->pNext = nullptr;
	////pPrev = pData;

	//return pData->value;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline bool HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::RemoveKey(ARG_KEY key)
{
	// 博大精深的二级指针算法
	SNode** pNode = &m_pHash[key % m_size];
	while (*pNode)
	{
		if ((*pNode)->key == key)
		{
			SNode* pTemp = *pNode;
			*pNode = (*pNode)->pNext;
			//delete pTemp;
			FreeNode(pTemp);
			return true;
		}
		pNode = &((*pNode)->pNext);
	}
	return false;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void HashMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::RemoveAll()
{
	SNode* pCurr = nullptr;
	SNode* pPrev = nullptr;
	for (int i = 0; i < m_size; i++)
	{
		pCurr = m_pHash[i];
		while (pCurr)
		{
			pPrev = pCurr;
			pCurr = pCurr->pNext;
			//delete pPrev;
			FreeNode(pPrev);
		}
		m_pHash[i] = nullptr;
	}
	m_size = 0;
}


// 二叉树 类模板
template<class KEY, class VALUE, class ARG_KEY = const KEY&, class ARG_VALUE = const VALUE&>
class BinaryTreeMap :public Map<KEY, VALUE, ARG_KEY, ARG_VALUE>
{
protected:
	// 结点 结构体
	struct SNode : public Map<KEY, VALUE, ARG_KEY, ARG_VALUE>::Node
	{
		SNode*	pLeft;	//左结点指针
		SNode*	pRight;	//右结点指针

		SNode() = default;
		SNode(KEY newKey, VALUE newValue) : Map<KEY, VALUE, ARG_KEY, ARG_VALUE>::Node(newKey, newValue) { pLeft = pRight = nullptr; }
		virtual ~SNode() { }
	};

	// 创建结点
	SNode* NewNode(ARG_KEY newKey, ARG_VALUE newValue);

	// 释放结点
	void FreeNode(SNode* deleteNode);


public:
	BinaryTreeMap() { m_pRoot = nullptr; }
	~BinaryTreeMap() { RemoveAll(); }

	// 设置键值对
	virtual void SetAt(ARG_KEY newKey, ARG_VALUE newValue);

	// 根据键查询值
	virtual  bool Lookup(ARG_KEY key, VALUE& value) const;

	// 操作符[]重载
	virtual  VALUE& operator[](ARG_KEY key);

	void RemoveKey(SNode* pNode);

	void RemoveAll();

	SNode* GetData() const { return m_pRoot; }
	// 前序遍历 DLR D=根结点，L=左子结点，R=右子结点
	void Preorder(SNode* pNode);
	// 中序遍历
	void Inorder(SNode* pNode);
	// 后序遍历
	void Postorder(SNode* pNode);

private:
	SNode * m_pRoot;	//根结点指针
};

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
typename BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::SNode * 
BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::NewNode(ARG_KEY newKey, ARG_VALUE newValue)
{
	SNode* newNode = new SNode(newKey, newValue);
	if (NULL == newNode)
	{
		std::wcout << "Memory allocate failure!" << std::endl;
		system("pause");
		exit(1);
	}
	return newNode;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::FreeNode(SNode * deleteNode)
{
	delete deleteNode;
	deleteNode = nullptr;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::SetAt(ARG_KEY newKey, ARG_VALUE newValue)
{
	(*this)[newKey] = newValue;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline bool BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::Lookup(ARG_KEY key, VALUE & value) const
{
	SNode* pCurr = m_pRoot;
	while (pCurr)
	{
		if (key == pCurr->key)
		{
			value = pCurr->value;
			return true;
		}
		if (key < pCurr->key)
			pCurr = pCurr->pLeft;
		else						// key > pCurr->key
			pCurr = pCurr->pRight;
	}
	return false;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline VALUE & BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::operator[](ARG_KEY key)
{
	// 再一次见证了博大精深的二级指针
	SNode** pNode = &m_pRoot;
	while (*pNode)
	{
		if (key == (*pNode)->key)
			return (*pNode)->value;
		if (key < (*pNode)->key)
			pNode = &(*pNode)->pLeft;
		else
			pNode = &(*pNode)->pRight;
	}
	*pNode = NewNode(key, VALUE());
	return (*pNode)->value;

	// 搜索二叉树：左结点 < 根结点 < 右结点
	//SNode* pCurr = m_pRoot;
	//if (!pCurr)
	//{
	//	m_pRoot = pCurr = NewNode(key, VALUE()); 
	//	return pCurr->value;
	//}

	//while (pCurr)
	//{
	//	if (key == pCurr->key)
	//		break;
	//	if (key < pCurr->key)
	//	{
	//		if (pCurr->pLeft)
	//			pCurr = pCurr->pLeft;
	//		else
	//		{
	//			pCurr->pLeft = NewNode(key, VALUE()); 
	//			return pCurr->pLeft->value;			//辣鸡视频吕，害我改到半夜零点！！！返回值都搞错了
	//		}
	//	}
	//	else											// key > pCurr->key
	//	{
	//		if (pCurr->pRight)
	//			pCurr = pCurr->pRight;
	//		else
	//		{
	//			pCurr->pRight = NewNode(key, VALUE());
	//			return pCurr->pRight->value;		//辣鸡视频吕，害我改到半夜零点！！！返回值都搞错了
	//		}
	//	}
	//}
	//return pCurr->value;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::RemoveKey(SNode * pNode)
{
	// 后序遍历删除各个结点
	if (pNode->pLeft)
		RemoveKey(pNode->pLeft);
	if (pNode->pRight)
		RemoveKey(pNode->pRight);
	//delete pNode;
	FreeNode(pNode);
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::RemoveAll()
{
	if (m_pRoot)
		RemoveKey(m_pRoot);
	m_pRoot = nullptr;
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::Preorder(SNode * pNode)
{
	if(!pNode)
		return;
	std::wcout << pNode->key << " ";
	Preorder(pNode->pLeft);
	Preorder(pNode->pRight);
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::Inorder(SNode * pNode)
{
	if(!pNode)
		return;
	Inorder(pNode->pLeft);
	std::wcout << pNode->key << " ";
	Inorder(pNode->pRight);
}

template<class KEY, class VALUE, class ARG_KEY, class ARG_VALUE>
inline void BinaryTreeMap<KEY, VALUE, ARG_KEY, ARG_VALUE>::Postorder(SNode * pNode)
{
	if(!pNode)
		return;
	Postorder(pNode->pLeft);
	Postorder(pNode->pRight);
	std::wcout << pNode->key << " ";
}
