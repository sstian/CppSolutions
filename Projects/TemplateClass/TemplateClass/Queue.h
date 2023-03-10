/*
	2018.11.09 20:37 - 21:11
	类模板-队列：一般队列，循环队列（已实现）
	特点：先进先出，后进后出。
	基本状态：队空，队满，一般状态。
2018.11.15 22:03 - 23:20 修改队列空间可调节，内部实现通过动态数组指针
*/

#pragma once

#define QUEUE_SIZE 50	//默认循环队列空间

// 循环队列 类模板
template<class T>
class CircularQueue
{
public:
	~CircularQueue();

	CircularQueue(int size = QUEUE_SIZE);

	// 入队
	void QueuePush(const T& value);

	// 出队
	T QueuePop(void);

	// 清空队列
	void ClearQueue(void) { ~CircularQueue(); }

	// 访问队首元素
	T QueueFront(void) const { return m_qary[m_front]; }

	// 队列长度
	int QueueLength(void) const { return (m_size - m_front + m_rear) % m_size; }

	// 判断队空堆满通过牺牲一个存储空间
	// 判断是否队空
	bool IsEmpty(void) const { return m_front == m_rear; }

	// 判断是否队满
	bool IsFull(void) const { return (m_rear + 1) % m_size == m_front; }

private:
	int m_front;	//队头
	int m_rear;		//队尾
	int m_size;		//队列容量
	T* m_qary;		//队列指针，构建动态队列
};

template<class T>
CircularQueue<T>::CircularQueue(int size)
{
	m_front = m_rear =  0;
	m_size = size;
	m_qary = new T[m_size];
}

template<class T>
CircularQueue<T>::~CircularQueue()
{
	m_front = m_rear = m_size = 0;
	delete[] m_qary;
}

template<class T>
inline void CircularQueue<T>::QueuePush(const T & value)
{
	if (IsFull())	//QUEUE_SIZE == m_count
	{
		std::cerr << "Queue overflow!" << std::endl;
		system("pause");
		exit(1);
	}

	m_qary[m_rear] = value;			//队尾插入元素

	m_rear = (m_rear + 1) % m_size;	//取余实现循环队列
}

template<class T>
inline T CircularQueue<T>::QueuePop(void)
{
	if (IsEmpty())	//0 == m_count
	{
		std::cerr << "Empty queue!" << std::endl;
		system("pause");
		exit(1);
	}

	T temp = m_qary[m_front];

	m_front = (m_front + 1) % m_size;	//队首增1

	return temp;
}
