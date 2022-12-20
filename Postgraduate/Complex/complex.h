/*��Complex�����ͷ�ļ�*/
/*****************************************************************************************************/
/* ��Ԫ���� ���������� ��ģ��:                                                                      **
/* 1��ע�⣡��vc++6.0�У���Ԫ��������ģ�������������Ҫ��".h"ͷ�ļ�                                 **    
/* 2�����ڲ�ʵ��ֱ��д�����ⲿʵ����Ҫд��������֮ǰ                                                **
/* 3��������Ҫ���ǰ����������                                                                      ** 
/* 4�����ⲿʵ��������ʱ���ù��캯��Ҫ����<T>�����ڲ�ʵ������Ҫ���磺return Complex<T>(......);   ** 
/*****************************************************************************************************/
#ifndef COMPLEX_H
#define COMPLEX_H
//ģ������Ϊ��������δ֪��������������ʵ�ֱ���д��ͬһ���ļ���
//ģ����Complex
#include <cmath>
/*****************************************************************************************
template <class T>
class Complex;  //���ǰ����������

template <class T>
Complex<T> operator -(const Complex<T>& oneComplex, const Complex<T>& subtractorComplex)
{  //��Ԫ��������ģ����������ص����ⲿʵ��
	Complex<T> differenceComplex;
	differenceComplex.real = oneComplex.real - subtractorComplex.real;
	differenceComplex.imag = oneComplex.imag - subtractorComplex.imag;
	return Complex<T>(differenceComplex.real, differenceComplex.imag);
}
********************************************************************************************/
template <class T>
class Complex;
//����*
template <class T>
Complex<T> operator *(const Complex<T>& faciendComplex, const Complex<T>& multiplierComplex)
{
	Complex<T> productComplex;  //������
	productComplex.real 
		= faciendComplex.real * multiplierComplex.real - faciendComplex.imag * multiplierComplex.imag;
	productComplex.imag 
		= faciendComplex.real * multiplierComplex.imag + faciendComplex.imag * multiplierComplex.real;
	return productComplex;
}
//����/
template <class T>
Complex<T> operator /(const Complex<T>& dividendComplex, const Complex<T>& divisorComplex)
{
	Complex<T> quotientComplex;  //�̸���
	T numeratorReal
		= dividendComplex.real * divisorComplex.real + dividendComplex.imag * divisorComplex.imag;  //����ʵ��
 	T numeratorImag
		= dividendComplex.imag * divisorComplex.real - dividendComplex.real * divisorComplex.imag;  //�����鲿
	T denominator  
		= divisorComplex.real * divisorComplex.real + divisorComplex.imag * divisorComplex.imag;  //��ĸ
	quotientComplex.real = numeratorReal / denominator;
	quotientComplex.imag = numeratorImag / denominator;
	return quotientComplex;
}
//����--ǰ��
template <class T>
Complex<T> operator --(Complex<T>& rcomplex)
{
	rcomplex.real--;
	rcomplex.imag--;
	return rcomplex;
}
//��������--
template <class T>
Complex<T> operator --(Complex<T>& rcomplex, int ignoreMe)
{
	T tempReal = rcomplex.real--;
	T tempImag = rcomplex.imag--;
	return Complex<T>(tempReal, tempImag);
}
//����<<
template <class T>
ostream& operator <<(ostream& output, const Complex<T>& rcomplex)
{
	output << "(" << rcomplex.real << " , " << rcomplex.imag << ")" << endl;
	return output;
}
//����>>
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
//���캯��������ͬ�����޷���ֵ�����ж������������
	//�޲���
//	Complex(){}
	//������Ĭ���βΣ���������ֵ��Ĭ���β�ֵ�ڵ���ǰ��������ȱʡ��ʵ������ȱʡ
	//����ʱ���Դ�0,1,2�����������Բ���Ҫ�޲������캯��
	Complex(T newReal = 0, T newImag = 0):real(newReal),imag(newImag) {}

//���ƹ��캯��������A��ֵ������B
	//����Ϊ���ã�������ֻ�ܳ�ʼ��
	//��ʾ��������������ʱ�ں������ô�����չ��
	inline Complex(const Complex<T>& rcomplex);

//��ʽ�������������г�Ա����������ͬʱ��ʵ��
	//��ȡ����ʵ��
	T getReal() const { return real; }
	//���ø���ʵ��
	void setReal(T newReal) { real = newReal; }
	//��ȡ�����鲿
	T getImag() const { return imag; }
	//���ø����鲿
	void setImag(T newImag) { imag = newImag; }
	//���������ʵ�����鲿
	void show() const { cout << "(" << real << " , " << imag << ")" << endl; }
//	
	//���㸴������ֵ��|r+ij| = sqrt(r*r+i*i),j*j = -1
	T absComplex() const;  
	//�������������ĺͣ������βΡ�����ֵ��Ϊ��������ã�������ø��ƹ��캯��
	Complex<T> addComplex(const Complex<T>& otherComplex) const;

	//���Ա�������������أ����� = ԭ����������-1 ������++��--���������⣩
	//�������+�����-��ǰ������++����������++
	// + ����������(r1+i1j) + (r2+i2j) = (r1+r2)+(i1+i2)j
	Complex<T> operator +(const Complex<T> addentComplex) const;
	// - ����������(r1+i1j) - (r2+i2j) = (r1-r2)+(i1-i2)j
	Complex<T> operator -(const Complex<T>& subtractorComplex) const;
	//ǰ������++
	Complex<T> operator ++();
	//��������++����һ��������ʾ����
	Complex<T> operator ++(int);
	//��Ԫ�������������أ����� = ԭ����������������һ���Զ��������
	//�������*�����/��ǰ���Լ�++�������Լ�--
	//���������� * ����������(r1+i1j) * (r2+i2j) = (r1*r2-i1*i2)+(r1*i2+i1*r2)j
	friend Complex<T> operator *(const Complex<T>& faciendComplex, const Complex<T>& multiplierComplex);
	//���������� / ����������(r1+i1j) / (r2+i2j) = (r1*r2+i1*i2)+(i1*r2-r1*i2)j
	friend Complex<T> operator /(const Complex<T>& dividendComplex, const Complex<T>& divisorComplex);
	//ǰ���Լ�--
	friend Complex<T> operator --(Complex<T>& rcomplex);
	//�����Լ�--����һ��������ʾ����
	friend Complex<T> operator --(Complex<T>& rcomplex, int ignoreMe);
	//��������������������������������ұ�����Ķ���ֻ����Ϊ��Ԫ������
	//�������������
	friend istream& operator >>(istream& input, Complex<T>& rcomplex);
	//������������
	friend ostream& operator <<(ostream& output, const Complex<T>& rcomplex);

/******************************************************************************************************
 *	friend Complex<T> operator -(const Complex<T>& oneComplex, const Complex<T>& subtractorComplex)
 *	{  //��Ԫ��������ģ����������ص����ڲ�ʵ��
 *		Complex<T> differenceComplex;
 *		differenceComplex.real = oneComplex.real - subtractorComplex.real;
 *		differenceComplex.imag = oneComplex.imag - subtractorComplex.imag;
 *		return Complex(differenceComplex.real, differenceComplex.imag);
 *	}
******************************************************************************************************/
//��������������ͬ�����޷���ֵ���޲�����һ�����һ�������ٶ���ͨ��Ϊ�麯��
	virtual ~Complex(){}
private:
	T real;  //ʵ��
	T imag;  //�鲿
};
//���ƹ��캯��
template <class T>
inline Complex<T>::Complex(const Complex<T>& rcomplex)
{
	real = rcomplex.real;
	imag = rcomplex.imag;
}
//��������ֵ
template <class T>
T Complex<T>::absComplex() const  
{
	T temp = real * real + imag * imag;
	return sqrt(temp);
}
//������
template <class T>
Complex<T> Complex<T>::addComplex(const Complex<T>& otherComplex) const
{
	Complex<T> sumComplex;
	sumComplex.real = real + otherComplex.real;
	sumComplex.imag = imag + otherComplex.imag;
	return sumComplex;
}
//����+
template <class T>
Complex<T> Complex<T>::operator +(const Complex<T> addentComplex) const
{
	Complex<T> sumComplex;  //�͸���
	sumComplex.real = this->real + addentComplex.real;
	sumComplex.imag = this->imag + addentComplex.imag;
	return Complex(sumComplex.real, sumComplex.imag);
}
//����-
template <class T>
Complex<T> Complex<T>::operator -(const Complex<T>& subtractorComplex) const
{
	Complex<T> differenceComplex;  //���
	differenceComplex.real = this->real + subtractorComplex.real;
	differenceComplex.imag = this->imag + subtractorComplex.imag;
	return Complex(differenceComplex.real, differenceComplex.imag);
}
//����++ǰ��
template <class T>	
Complex<T> Complex<T>::operator ++()
{
	real++;
	imag++;
	return Complex(real, imag);
}
//��������++
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