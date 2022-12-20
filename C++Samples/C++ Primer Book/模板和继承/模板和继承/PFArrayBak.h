//ģ��̳���PFArrayBak�Ľӿ��ļ�
//���ϴα��������Ԫ�ؽ��б��ݺͻָ�
#ifndef PFArrayBAK_H
#define PFArrayBAK_H
#include "PFArray.h"

namespace PFArraySavitch
{
	template <class T>
	class PFArrayBak : public PFArray < T >
	{
	public:
		PFArrayBak();                              //����ĳ�ʼ��СΪ50��
		PFArrayBak(int capacityValue);
		PFArrayBak(const PFArrayBak<T>& oldObject);
		void backup();
		//���ݲ�����������Ԫ�ء�
		void restore();
		//�ָ��ϴα���Ĳ�����������Ԫ�أ���δ���ݹ����������Ԫ�ء�
		PFArrayBak<T>& operator =(const PFArrayBak<T>& rightSide);
		virtual ~PFArrayBak();
	private:
		T *b;                //����������
		int usedB;           //���ݼ̳еĳ�Ա����
	};
}                           //PFArraySavitch
#endif                      //PFArrayBAK_H