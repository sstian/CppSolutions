#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include "stack.h"
using std::cout;

namespace StackSavitch
{
	template <class T>
	Stack<T>::Stack() :top(NULL)
	{/*函数体有意为空*/}
	template <class T>
	Stack<T>::Stack(const Stack<T>& aStack)
	{
		if (aStack.isEmpty())
			top = NULL;
		else
		{
			Node<T> *temp = aStack.top;
			Node<T> *end;
			end = new Node<T>(temp->getdata(), NULL);
			top = end;
			temp = temp->getlink();
			while (temp != NULL)
			{
				end->setLink(new Node<T>(temp->getData(), NULL));
				temp = temp->getlink();
				end = end->getLink();
			}
		}
	}
	template <class T>
	void Stack<T>::push(T stackFrame)
	{
		top = new Node<T>(stackFrame, top);
	}
	template <class T>
	T Stack<T>::pop()
	{
		if (isEmpty())
		{
			cout << "Error: popping an empty stack.\n";
			exit(1);
		}
		T result = top->getdata();
		Node<T> *discard;
		discard = top;
		top = top->getlink();
		delete discard;
		return result;
	}
	template <class T>
	bool Stack<T>::isEmpty() const
	{
		return (top == NULL);
	}
	template <class T>
	Stack<T>& Stack<T>::operator =(const Stack<T>& rightSide)
	{
		if (top == rightSide.top)
			return *this;
		else
		{
			T next;
			while (!isEmpty())
				next = pop();
		}
		if (rightSide.isEmpty())
		{
			top = NULL;
			return *this;
		}
		else
		{
			Node<T> *temp = rightSide.top;
			Node<T> *end;
			end = new Node<T>(temp->getData(), NULL);
			top = end;;
			temp = temp->getlink();
			while (temp != NULL)
			{
				end->setLink(new Node<T>(temp->getData(), NULL));
				temp = temp->getlink();
				end = end->getLink();
			}
			return *this;
		}
	}
	template <class T>
	Stack<T>::~Stack()
	{
		T next;
		while (!isEmpty())
			next = pop();
	}
}