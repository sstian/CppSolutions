/*
	2018.11.08 17:13 - 18:03
	类模板-栈（静态数组）
	特点：先进后出，后进先出。
	应用：函数调用，表达式处理。
	基本状态：栈空，栈满，一般状态。
2018.11.15 22:03 - 23:20 修改栈空间可调节，内部实现通过动态数组指针
*/
#pragma once

#define STACK_SIZE 50

// 栈 类模板
template<class T>
class Stack
{
public:
	Stack(int size = STACK_SIZE);
	~Stack();

	// 压栈
	void Push(const T& value);

	// 出栈
	T Pop(void);

	// 清空栈，只需要将栈索引设置为-1即可
	void Clear(void) { m_top = -1; }

	// 读取栈顶元素
	T Peek(void) const;

	// 栈元素数量
	int GetCount(void) const { return m_top + 1; }

	// 判断是否为栈空
	bool IsEmpty(void) { return m_top < 0; }

	// 判断是否为栈满
	bool IsFull(void) { return m_top > m_size - 1; }

private:
	int m_top;		//栈索引，0 ~ m_size - 1
	int m_size;		//栈容量，默认为STACK_SIZE
	T* m_sary;		//栈指针，构建动态栈
};

template<class T>
inline Stack<T>::Stack(int size)
{
	m_top = -1;
	m_size = size;
	m_sary = new T[m_size];
}

template<class T>
inline Stack<T>::~Stack()
{
	delete m_sary;
}

template<class T>
inline void Stack<T>::Push(const T & value)
{
	if (IsFull())	//m_top >= m_size - 1
	{
		std::cerr << "Stack overflow!" << std::endl;
		system("pause");
		exit(1);
	}
	else
	{
		m_top++;
		m_sary[m_top] = value;
	}
}

template<class T>
inline T Stack<T>::Pop(void)
{
	if (IsEmpty())	//m_top < 0
	{
		std::cerr << "Empty stack!" << std::endl;
		system("pause");
		exit(1);
	}
	else
	{
		T temp = m_sary[m_top];
		m_top--;
		return temp;
	}
}

template<class T>
inline T Stack<T>::Peek(void) const
{
	if (m_top < 0)	//m_top < 0
	{
		std::cerr << "Attempt to peek at an empty stack!" << std::endl;
		system("pause");
		exit(1);
	}
	else
	{
		return m_sary[m_top];
	}
}
