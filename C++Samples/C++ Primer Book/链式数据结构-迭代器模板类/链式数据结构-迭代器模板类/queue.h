//������һ���Ƚ��ȳ������ݽṹ��
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
		//��β����������end().current==NULL�����ʣ����ܷ����á�
		virtual ~Queue();
	private:
		Node<T> *front;        //ָ�������ͷ����Ԫ�ش�ͷ���Ƴ�
		Node<T> *back;         //ָ��������һ�˵Ľڵ㣬Ԫ�ش���һ�˼���
	};
}
#endif