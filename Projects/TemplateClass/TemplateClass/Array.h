/*
	2018.11.08 15:06 - 17:02
	类模板-动态数组：
	特点：位置连续，任意数量类型相同的元素。
	优点：元素个数可在程序运行时改变。
2018.11.17 15:03 - 17:48 扩展动态数组功能，可以根据存储空间动态扩充容量为两倍 Remalloc(), 添加插入/删除指定个数的函数 InsertAt() / RemoveAt()。
*/
#pragma once

#include <cassert>

#ifndef NULL

const int NULL = 0;

#endif // !NULL

#define ARRAY_SIZE 50	//默认动态数组大小


// 错误类型 枚举与信息
enum ErrorType
{
	InvalidArraySize,		//不合法的数组大小
	MemoryAllocateError,	//内存分配错误
	IndexOutOfRange			//数组下标越界
};

const char* errorInfo[] = {
	"Invalid Array Size",
	"Memory Allocate Error",
	"Invalid index: "
};


// 动态数组 类模板
template <class T>
class Array
{
public:
	~Array();

	// 构造函数
	Array(int size = ARRAY_SIZE);
	// 复制构造函数
	Array(const Array<T>& ra);

	// 重载赋值=操作符
	Array<T>& operator=(const Array<T>& ra);

	// 重载数组索引[]操作符
	T& operator[](int index);
	// 只读对象专用，如：const Array<int> a;
	T operator[](int index) const;

	// 重载指针转换操作符，对象名类似数组名（首地址）
	operator T*(void) { return m_ary; }

	// 返回指定索引数组元素的引用
	T& GetAt(int index);
	// 只读对象专用
	T GetAt(int index) const;

	// 设置数据
	void SetAt(int index, const T& value);

	// 当前数组大小
	int GetCount(void) const { return m_count; }

	// 数组容量
	int GetSize(void) const { return m_size; }
	// 重设数组容量
	void SetSize(const int newSize);

	// 添加元素
	void Add(const T& value);

	// 插入元素
	void InsertAt(int index, const T& value, int count = 1);

	// 移除元素
	void RemoveAt(int index, int count = 1);

	// 返回数组指针
	T* GetData() { return m_ary; }
	// 只读
	const T* GetData() const { return m_ary; }

	// 清空数组
	void Clear(void) { this->~Array(); }

private:
	// 错误信息
	void Error(ErrorType error, int badIndex = 0);

	// 重新分配内存空间
	void Remalloc(const int size);

private:
	int m_size;		//动态数组容量
	int m_count;	//数组元素计数
	T* m_ary;		//动态数组首地址指针
};

template <class T>
Array<T>::~Array()
{
	m_size = 0;
	m_count = 0;
	delete[] m_ary;	//释放内存堆内空间
}

template<class T>
inline Array<T>::Array(int size)
{
	// 欲分配的数组元素<=0则输出错误信息
	if (size <= 0)
		Error(ErrorType::InvalidArraySize);

	// 动态分配size个类型的元素空间
	m_size = size;
	m_ary = new T[m_size];
	if (NULL == m_ary)
		Error(ErrorType::MemoryAllocateError);

	m_count = 0;
}

template<class T>
inline Array<T>::Array(const Array<T>& ra)
{
	// 从对象ra中取得数组大小赋值给当前对象
	this->m_count = ra.count;
	this->m_size = ra.m_size;
	int size = ra.m_size;

	// 申请内存
	this->m_ary = new T[size];
	if (NULL == this->m_ary)
		Error(ErrorType::MemoryAllocateError);

	// 深层复制
	T* srcptr = ra.m_ary;		//对象ra的数组首地址
	T* dstptr = this->m_ary;	//本对象中的数组首地址
	while (size--)
	{
		*dstptr++ = *srcptr++;	//逐个复制数组元素
	}
}

template<class T>
inline Array<T>& Array<T>::operator=(const Array<T>& ra)
{
	this->m_count = ra.m_count;
	int size = ra.m_size;

	// 如果大小不同，则删除数组原有内存重新分配
	if (this->m_size != size)
	{
		this->m_size = ra.m_size;
		delete[] m_ary;

		this->m_ary = new T[size];
		if (NULL == this->m_ary)
			Error(ErrorType::MemoryAllocateError);
	}

	T* srcptr = ra.m_ary;
	T* dstptr = this->m_ary;
	while (size--)
	{
		*dstptr++ = *srcptr++;
	}
	
	return *this;
}

template<class T>
inline T & Array<T>::operator[](int index)
{
	// 检查数组下标是否越界
	if (index < 0 || index > this->m_size - 1)
		Error(ErrorType::IndexOutOfRange, index);

	// 返回下标为index的数组元素
	if (m_count <= index)
		m_count = index + 1;
	return this->m_ary[index];
}

template<class T>
inline T Array<T>::operator[](int index) const
{
	// 检查数组下标是否越界
	if (index < 0 || index > this->m_size - 1)
		Error(ErrorType::IndexOutOfRange, index);

	// 返回下标为index的数组元素
	if (m_count <= index)
		m_count = index +1 ;
	return this->m_ary[index];
}

template<class T>
inline T & Array<T>::GetAt(int index)
{
	// 检查数组下标是否越界
	if (index < 0 || index > this->m_size - 1)
		Error(ErrorType::IndexOutOfRange, index);

	// 返回下标为index的数组元素
	if (m_count <= index)
		m_count = index + 1;
	return this->m_ary[index];
}

template<class T>
inline T Array<T>::GetAt(int index) const
{
	// 检查数组下标是否越界
	if (index < 0 || index > this->m_size - 1)
		Error(ErrorType::IndexOutOfRange, index);

	// 返回下标为index的数组元素
	if (m_count <= index)
		m_count = index + 1;
	return this->m_ary[index];
}

template<class T>
inline void Array<T>::SetAt(int index, const T & value)
{
	// 检查数组下标是否越界
	if (index < 0 || index > this->m_size - 1)
		Error(ErrorType::IndexOutOfRange, index);

	if (m_count <= index)
		m_count = index + 1;

	this->m_ary[index] = value;
}

template<class T>
inline void Array<T>::SetSize(const int newSize)
{
	// 检查重设数组大小是否正常
	if (newSize <= 0)
		Error(ErrorType::InvalidArraySize);

	// 如果与原来数组大小一致，什么都不做，直接返回
	if (newSize == this->m_size)
		return;

	// 重设大小，取两者较小值
	T* newary = new T[newSize];
	if (NULL == newary)
		Error(ErrorType::MemoryAllocateError);

	int size = ((newSize <= this->m_size) ? newSize : this->m_size);
	T* srcptr = this->m_ary;
	T* dstptr = newary;
	while (size--)
	{
		*dstptr++ = *srcptr++;
	}

	// 使m_ary指向新数组，并更新m_size
	this->m_ary = newary;
	this->m_size = newSize;	

}

template<class T>
inline void Array<T>::Add(const T & value)
{
	if (m_count >= m_size)
		Remalloc(m_size * 2);
	m_ary[m_count++] = value;
}

template<class T>
inline void Array<T>::InsertAt(int index, const T & value, int count)
{
	if (count <= 0)
		return;
	// 判断索引下标的位置
	if (index < 0)
		index = 0;
	else if (index > m_count)
	{
		if (index + count > m_size)
			Remalloc((index + count) * 2);
		m_count = index + count;

	}
	else
	{
		if (count + m_count > m_size)
			Remalloc((count + m_count) * 2);
		memmove(m_ary + index + count, m_ary + index, sizeof(T)*(m_count - index));
		m_count += count;
	}
	// 填充数据
	while (count--)
		m_ary[index++] = value;
}

template<class T>
inline void Array<T>::RemoveAt(int index, int count)
{
	// 检查数组下标是否越界
	assert(index >= 0 || index <= this->m_size - 1);
	if (index < 0 || index > this->m_size - 1)
		Error(ErrorType::IndexOutOfRange, index);
	// 移除后面全部元素
	if (count >= m_count - index)
	{
		m_count = index;
		return;
	}

	memmove(m_ary + index, m_ary + index + count, sizeof(T)*(m_count - index - count));
	m_count -= count;
}

template<class T>
inline void Array<T>::Error(ErrorType error, int badIndex)
{
	//根据错误类型，输出相应的错误信息
	std::wcout << errorInfo[error];
	
	if (ErrorType::IndexOutOfRange == error)
		std::wcout << badIndex;						//下标越界，输出错误的下标

	std::wcout << std::endl;
}

template<class T>
inline void Array<T>::Remalloc(const int size)
{
	T* pary = new T[size];
	if (NULL == pary)
		Error(ErrorType::MemoryAllocateError);

	if(m_count > 0)
		memcpy(pary, m_ary, sizeof(T)*m_count);
	delete[] m_ary;

	m_ary = pary;
	m_size = size;
}
