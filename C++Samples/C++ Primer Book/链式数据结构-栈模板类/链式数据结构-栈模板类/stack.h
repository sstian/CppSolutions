//ջ����һ�ֺ���ȳ������ݽṹ��
//��ջ(pushing)����ջ������һ��Ԫ��;
//��ջ(poping)����ջ���Ƴ�һ��Ԫ�ء�
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
		Stack(const Stack<T>& aStack);      //���ƹ��캯��
		void push(T stackFrame);
		T pop();                            //ǰ��������ջ��Ϊ�ա�����ջ��Ԫ�أ��������ջ���Ƴ���
		bool isEmpty() const;               //ջΪ�գ�����true�����򷵻�false��
		Stack<T>& operator =(const Stack<T>& rightSide);
		virtual ~Stack();                   //������������ջ�������е��ڴ潻�����ɶ�
	private:
		Node<T> *top;
	};
}
#endif