//模板继承类PFArrayBak的接口文件
//对上次保存的数组元素进行备份和恢复
#ifndef PFArrayBAK_H
#define PFArrayBAK_H
#include "PFArray.h"

namespace PFArraySavitch
{
	template <class T>
	class PFArrayBak : public PFArray < T >
	{
	public:
		PFArrayBak();                              //数组的初始大小为50。
		PFArrayBak(int capacityValue);
		PFArrayBak(const PFArrayBak<T>& oldObject);
		void backup();
		//备份部分填充数组的元素。
		void restore();
		//恢复上次保存的部分填充数组的元素，若未备份过则清空数组元素。
		PFArrayBak<T>& operator =(const PFArrayBak<T>& rightSide);
		virtual ~PFArrayBak();
	private:
		T *b;                //备份主数组
		int usedB;           //备份继承的成员变量
	};
}                           //PFArraySavitch
#endif                      //PFArrayBAK_H