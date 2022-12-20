#ifndef ITERATOR_H
#define ITERATOR_H

namespace ListNodeSavitch
{
	template <class T>
	class Node
	{
	public:
		Node(T theData, Node<T>* theLink) : data(theData), link(theLink) {}
		Node<T>* getLink() const { return link; }
		const T getData() const { return data;}
		void setData(const T& theData) { data = theData; }
		void setLink(Node<T>* pointer) { link = pointer; }
	private:
		T data;
		Node<T> *link;
	};

	template <class T>
	class ListIterator
	{
	public:
		ListIterator() : current(NULL) {}
		ListIterator(Node<T>* initial) : current(initial) {}
		const T operator *() const { return current->getData(); }
		ListIterator operator ++()                 //前缀形式
		{
			current = current->getLink();
			return *this;
		}
		ListIterator operator ++(int)             //后缀形式
		{
			ListIterator startVersion(current);
			current = current->getLink();
			return startVersion;
		}
		bool operator ==(const ListIterator& rightSide) const
		{
			return (current == rightSide.current);
		}
		bool operator !=(const ListIterator& rightSide) const
		{
			return (current != rightSide.current);
		}
	private:
		Node<T> *current;
	};
}
#endif