/*类Complex定义的头文件*/
/*****************************************************************************************************/
/* 友元函数 操作符重载 类模板:                                                                      **
/* 1、注意！在vc++6.0中，友元函数作类模板操作符重载需要用".h"头文件                                 **    
/* 2、类内部实现直接写；类外部实现需要写在类声明之前                                                **
/* 3、于是需要类的前向引用声明                                                                      ** 
/* 4、类外部实现若返回时调用构造函数要加上<T>，类内部实现则不需要。如：return Complex<T>(......);   ** 
/*****************************************************************************************************/
#ifndef COMPLEX_H
#define COMPLEX_H
//模板类因为数据类型未知，函数的声明和实现必须写在同一个文件中
//模板类Complex
#include <cmath>
/*****************************************************************************************
template <class T>
class Complex;  //类的前向引用声明

template <class T>
Complex<T> operator -(const Complex<T>& oneComplex, const Complex<T>& subtractorComplex)
{  //友元函数作类模板操作符重载的类外部实现
	Complex<T> differenceComplex;
	differenceComplex.real = oneComplex.real - subtractorComplex.real;
	differenceComplex.imag = oneComplex.imag - subtractorComplex.imag;
	return Complex<T>(differenceComplex.real, differenceComplex.imag);
}
********************************************************************************************/
template <class T>
class Complex;
//复数*
template <class T>
Complex<T> operator *(const Complex<T>& faciendComplex, const Complex<T>& multiplierComplex)
{
	Complex<T> productComplex;  //积复数
	productComplex.real 
		= faciendComplex.real * multiplierComplex.real - faciendComplex.imag * multiplierComplex.imag;
	productComplex.imag 
		= faciendComplex.real * multiplierComplex.imag + faciendComplex.imag * multiplierComplex.real;
	return productComplex;
}
//复数/
template <class T>
Complex<T> operator /(const Complex<T>& dividendComplex, const Complex<T>& divisorComplex)
{
	Complex<T> quotientComplex;  //商复数
	T numeratorReal
		= dividendComplex.real * divisorComplex.real + dividendComplex.imag * divisorComplex.imag;  //分子实部
 	T numeratorImag
		= dividendComplex.imag * divisorComplex.real - dividendComplex.real * divisorComplex.imag;  //分子虚部
	T denominator  
		= divisorComplex.real * divisorComplex.real + divisorComplex.imag * divisorComplex.imag;  //分母
	quotientComplex.real = numeratorReal / denominator;
	quotientComplex.imag = numeratorImag / denominator;
	return quotientComplex;
}
//复数--前置
template <class T>
Complex<T> operator --(Complex<T>& rcomplex)
{
	rcomplex.real--;
	rcomplex.imag--;
	return rcomplex;
}
//复数后置--
template <class T>
Complex<T> operator --(Complex<T>& rcomplex, int ignoreMe)
{
	T tempReal = rcomplex.real--;
	T tempImag = rcomplex.imag--;
	return Complex<T>(tempReal, tempImag);
}
//复数<<
template <class T>
ostream& operator <<(ostream& output, const Complex<T>& rcomplex)
{
	output << "(" << rcomplex.real << " , " << rcomplex.imag << ")" << endl;
	return output;
}
//复数>>
template <class T>
istream& operator >>(istream& input, Complex<T>& rcomplex)
{
	input >> rcomplex.real >> rcomplex.imag;
	return input;
}

template <class T>
class Complex
{
public:
//构造函数：与类同名，无返回值；可有多个，创建对象
	//无参数
//	Complex(){}
	//带两个默认形参：从右往左赋值；默认形参值在调用前，声明已缺省，实现无需缺省
	//调用时可以带0,1,2个参数，所以不需要无参数构造函数
	Complex(T newReal = 0, T newImag = 0):real(newReal),imag(newImag) {}

//复制构造函数：对象A赋值给对象B
	//参数为引用，别名，只能初始化
	//显示内联函数：编译时在函数调用处代码展开
	inline Complex(const Complex<T>& rcomplex);

//隐式内联函数：类中成员函数声明的同时并实现
	//获取复数实部
	T getReal() const { return real; }
	//设置复数实部
	void setReal(T newReal) { real = newReal; }
	//获取复数虚部
	T getImag() const { return imag; }
	//设置复数虚部
	void setImag(T newImag) { imag = newImag; }
	//输出复数的实部与虚部
	void show() const { cout << "(" << real << " , " << imag << ")" << endl; }
//	
	//计算复数绝对值：|r+ij| = sqrt(r*r+i*i),j*j = -1
	T absComplex() const;  
	//计算两个复数的和：函数形参、返回值均为类对象（引用），会调用复制构造函数
	Complex<T> addComplex(const Complex<T>& otherComplex) const;

	//类成员函数操作符重载：参数 = 原操作数个数-1 （后置++、--操作符除外）
	//复数相加+、相减-、前置自增++、后置自增++
	// + 加数复数：(r1+i1j) + (r2+i2j) = (r1+r2)+(i1+i2)j
	Complex<T> operator +(const Complex<T> addentComplex) const;
	// - 减数复数：(r1+i1j) - (r2+i2j) = (r1-r2)+(i1-i2)j
	Complex<T> operator -(const Complex<T>& subtractorComplex) const;
	//前置自增++
	Complex<T> operator ++();
	//后置自增++，带一个参数以示区分
	Complex<T> operator ++(int);
	//友元函数操作符重载：参数 = 原操作数，且至少有一个自定义的类型
	//复数相乘*、相除/、前置自减++、后置自减--
	//被乘数复数 * 乘数复数：(r1+i1j) * (r2+i2j) = (r1*r2-i1*i2)+(r1*i2+i1*r2)j
	friend Complex<T> operator *(const Complex<T>& faciendComplex, const Complex<T>& multiplierComplex);
	//被除数复数 / 除数复数：(r1+i1j) / (r2+i2j) = (r1*r2+i1*i2)+(i1*r2-r1*i2)j
	friend Complex<T> operator /(const Complex<T>& dividendComplex, const Complex<T>& divisorComplex);
	//前置自减--
	friend Complex<T> operator --(Complex<T>& rcomplex);
	//后置自减--，带一个参数以示区分
	friend Complex<T> operator --(Complex<T>& rcomplex, int ignoreMe);
	//重载输入输出运算符，参数左边是流，右边是类的对象，只能作为友元函数！
	//重载输入运算符
	friend istream& operator >>(istream& input, Complex<T>& rcomplex);
	//重载输出运算符
	friend ostream& operator <<(ostream& output, const Complex<T>& rcomplex);

/******************************************************************************************************
 *	friend Complex<T> operator -(const Complex<T>& oneComplex, const Complex<T>& subtractorComplex)
 *	{  //友元函数作类模板操作符重载的类内部实现
 *		Complex<T> differenceComplex;
 *		differenceComplex.real = oneComplex.real - subtractorComplex.real;
 *		differenceComplex.imag = oneComplex.imag - subtractorComplex.imag;
 *		return Complex(differenceComplex.real, differenceComplex.imag);
 *	}
******************************************************************************************************/
//析构函数：与类同名，无返回值；无参数，一个类仅一个，销毁对象。通常为虚函数
	virtual ~Complex(){}
private:
	T real;  //实部
	T imag;  //虚部
};
//复制构造函数
template <class T>
inline Complex<T>::Complex(const Complex<T>& rcomplex)
{
	real = rcomplex.real;
	imag = rcomplex.imag;
}
//复数绝对值
template <class T>
T Complex<T>::absComplex() const  
{
	T temp = real * real + imag * imag;
	return sqrt(temp);
}
//复数加
template <class T>
Complex<T> Complex<T>::addComplex(const Complex<T>& otherComplex) const
{
	Complex<T> sumComplex;
	sumComplex.real = real + otherComplex.real;
	sumComplex.imag = imag + otherComplex.imag;
	return sumComplex;
}
//复数+
template <class T>
Complex<T> Complex<T>::operator +(const Complex<T> addentComplex) const
{
	Complex<T> sumComplex;  //和复数
	sumComplex.real = this->real + addentComplex.real;
	sumComplex.imag = this->imag + addentComplex.imag;
	return Complex(sumComplex.real, sumComplex.imag);
}
//复数-
template <class T>
Complex<T> Complex<T>::operator -(const Complex<T>& subtractorComplex) const
{
	Complex<T> differenceComplex;  //差复数
	differenceComplex.real = this->real + subtractorComplex.real;
	differenceComplex.imag = this->imag + subtractorComplex.imag;
	return Complex(differenceComplex.real, differenceComplex.imag);
}
//复数++前置
template <class T>	
Complex<T> Complex<T>::operator ++()
{
	real++;
	imag++;
	return Complex(real, imag);
}
//复数后置++
template <class T>
Complex<T> Complex<T>::operator ++(int ignoreMe)
{
	T tempReal = real++;
	T tempImag = imag++;
//	real++;
//	imag++;
	return Complex(tempReal, tempImag);
}

#endif