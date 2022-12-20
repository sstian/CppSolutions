//栈是以一种后进先出的数据结构。
//入栈(pushing)：向栈中增加一个元素;
//出栈(poping)：从栈中移除一个元素。
#ifndef STACK_H
#define STACK_H

namespace StackSavitch
{
	template <class T>
	class Node
	{
	public:
		Node(T theData, Node<T>* theLink) :data(theData), link(theLink) {}
		Node<T>* getlink() const { return link; }
		const T getdata() const { return data;}
		void setData(const T& theData) { data = theData; }
		void setlink(Node<T>* pointer) { link = pointer; }
	private:
		T data;
		Node<T> *link;
	};
	template <class T>
	class Stack
	{
	public:
		Stack(); 
		Stack(const Stack<T>& aStack);      //复制构造函数
		void push(T stackFrame);
		T pop();                            //前提条件：栈不为空。返回栈顶元素，并将其从栈中移除。
		bool isEmpty() const;               //栈为空，返回true，否则返回false。
		Stack<T>& operator =(const Stack<T>& rightSide);
		virtual ~Stack();                   //析构函数销毁栈并将所有的内存交还自由堆
	private:
		Node<T> *top;
	};
}
#endif