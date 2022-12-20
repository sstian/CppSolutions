//队列是一种先进先出的数据结构。
#ifndef QUEUE_H
#define QUEUE_H
#include "iterator.h"
using namespace ListNodeSavitch;

namespace QueueSavitch
{
	template <class T>
	class Queue
	{
	public:
		typedef ListIterator<T> Iterator;
		Queue();
		Queue(const Queue<T>& aQueue);
		Queue<T>& operator =(const Queue<T>& rightSide);
		void add(T item);
		T remove();
		bool isEmpty() const;
		Iterator begin() const { return Iterator(front); }
		Iterator end() const { return Iterator(); }
		//结尾迭代器具有end().current==NULL的性质，不能反引用。
		virtual ~Queue();
	private:
		Node<T> *front;        //指向链表的头部，元素从头部移除
		Node<T> *back;         //指向链表另一端的节点，元素从这一端加入
	};
}
#endif