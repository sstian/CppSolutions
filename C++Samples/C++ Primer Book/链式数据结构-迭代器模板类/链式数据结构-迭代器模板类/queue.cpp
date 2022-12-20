#include <iostream>
#include <cstdlib>
#include <cstddef>
#include "queue.h"
using std::cout;
using namespace ListNodeSavitch;

namespace QueueSavitch
{
	template <class T>
	Queue<T>::Queue() : front(NULL), back(NULL) {}
	template <class T>
	Queue<T>::Queue(const Queue<T>& aQueue)
	{
		if (aQueue.isEmpty())
			front = back = NULL;
		else
		{
			Node<T> *temp = aQueue.front;
			back = new Node<T>(temp->getData(), NULL);
			front = back;
			temp = temp->getLink();
			while (temp != NULL)
			{
				back->setLink(new Node<T>(temp->getLink(), NULL));
				back = back->getLink();
				temp = temp->getLink();
			}
		}
	}
	template <class T>
	Queue<T>& Queue<T>::operator =(const Queue<T>& rightSide)
	{
		if (front == rightSide.front)
			return *this;
		else
		{
			t next;
			while (!isEmpty())
				next = remove();
		}
		if (rightSide.isEmpty())
		{
			front = back = NULL;
			return *this;
		}
		else
		{
			Node<T> *temp = rightSide.front;
			back = new Node<T>(temp->getData(), NULL);
			front = back;
			temp = temp->getLink();
			while (temp != NULL)
			{
				back->setLink(new Node<T>(temp->getLink(), NULL));
				back = back->getLink();
				temp = temp->getLink();
			}
			return *this;
		}
	}
	template <class T>
	void Queue<T>::add(T item)
	{
		if (isEmpty())
			front = back = new Node<T>(item, NULL);
		else
		{
			back->setLink(new Node<T>(item, NULL));
			back = back->getLink();
		}
	}
	template <class T>
	T Queue<T>::remove()
	{
		if (isEmpty())
		{
			cout << "Error: Removing an item from an empty queue.\n";
			exit(1);
		}
		T result = front->getData();
		Node<T> *discard;
		discard = front;
		front = front->getLink();
		if (front == NULL)
			back = NULL;
		delete discard;
		return result;
	}
	template <class T>
	bool Queue<T>::isEmpty() const
	{
		return (back == NULL);
	}
	template <class T>
	Queue<T>::~Queue()
	{
		T next;
		while (!isEmpty())
			next = remove();
	}
}