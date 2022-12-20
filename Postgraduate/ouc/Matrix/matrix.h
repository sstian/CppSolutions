/*  ������ģ�壨��ά����ͷ�ļ� */
/******************************************************************
*1�����캯������ֵ���캯��û�з���ֵ
*2���������ݳ�Ա�ж�̬�����ڴ�ռ�ʱҪ�Զ��帴�ƹ��캯��
********************************************************************/
#include <iostream.h>
#include <stdlib.h>
#include <time.h>

template <class T>
class Matrix;

//����>>
template <class T>
istream& operator >>(istream& input, Matrix<T>& rm)
{
	cout << "Input " << rm.row_ << " X " << rm.col_ << " Matrix:" << endl;
	for(int i = 0; i < rm.row_; i++)
	{
		cout << "row " << i+1 << ": ";
		for(int j = 0; j < rm.col_; j++)
			input >> rm.ptr_[i][j];
	}
	return input;
}
//����<<
template <class T>
ostream& operator <<(ostream& output, const Matrix<T>& rm)
{
	for(int i = 0; i < rm.row_; i++)
	{
		for(int j = 0; j < rm.col_; j++)
			output << rm.ptr_[i][j] << " ";
		output << endl;
	}	
	return output;
}

template <class T>
class Matrix
{
public:
	//���캯��
	Matrix(int row = 3, int col = 3);  //Ĭ�ϲ������������3X3����
	//���ƹ��캯��
	Matrix(const Matrix<T>& rm);  //��㸴��
	//����������
	virtual ~Matrix();
	//���������+����
	Matrix operator +(const Matrix<T>& rm);
	//���������-����
	Matrix operator -(const Matrix<T>& rm);
	//���������*����
	Matrix operator *(const Matrix<T>& rm);
	//���������=����
	Matrix operator =(const Matrix<T>& rm);
	//����ת��
	Matrix transpose();
	//�������������>>����Ԫ��������
	friend istream& operator >>(istream& input, Matrix<T>& rm);
	//������������<<����Ԫ��������
	friend ostream& operator <<(ostream& output, const Matrix<T>& rm);
private:
	int row_;  //����
	int col_;  //����
	T** ptr_;  //�����ά�����ָ��
};
//���󴴽�
template <class T>
Matrix<T>::Matrix(int row, int col):row_(row),col_(col)
{  //��̬�����ά����
//	row_ = row;
//	col_ = col;
	ptr_ = new T*[row_];
	for(int i = 0; i < row_; i++)
		ptr_[i] = new T[col_];
//	srand((unsigned)time(NULL));
//	srand(static_cast<unsigned>(time(NULL)));
	for(int j = 0; j < row_; j++)
		for(int k = 0; k < col_; k++)
			ptr_[j][k] = rand() % 20;
}
//����ɾ��
template <class T>
Matrix<T>::~Matrix()
{  //�ͷŶ�ά����
	for(int i = 0; i < row_; i++)
		delete[] ptr_[i];
	delete[] ptr_;
}
//������
template <class T>
Matrix<T>::Matrix(const Matrix<T>& rm)
{	
/*	//�ͷ�ԭ������ռ�
	//��δ��벻��Ҫ���������л������
	//���Ƶ��ø��ƹ��캯��ʱ���ͷ�ԭ�пռ�ᱻ������ݣ�
	for(int i = 0; i < row_; i++)
		delete[] ptr_[i];
	delete[] ptr_;
*/	//����ͬ�;���
	row_ = rm.row_;
	col_ = rm.col_;
	ptr_ = new T*[row_];
	for(int i = 0; i < row_; i++)
		ptr_[i] = new T[col_];
	//��ֵ
	for(int j = 0; j < row_; j++)
		for(int k = 0; k < col_; k++)
			this->ptr_[j][k] = rm.ptr_[j][k];	
}
//����+
template <class T>
Matrix<T> Matrix<T>::operator +(const Matrix<T>& rm)
{
	if((this->row_ != rm.row_) || (this->col_ != rm.col_))
	{
		cout << "Not the same type matrix!" << endl;
		exit(1);  //�����˳�
	}
	else
	{
		Matrix<T> resultMatrix(row_, col_);  //����֮��
		for(int i = 0; i < row_; i++)
			for(int j = 0; j < col_; j++)
			{
				resultMatrix.ptr_[i][j] = this->ptr_[i][j] + rm.ptr_[i][j];
			}
		return resultMatrix;
	}
}
//����-
template <class T>
Matrix<T> Matrix<T>::operator -(const Matrix<T>& rm)
{
	if((this->row_ != rm.row_) || (this->col_ != rm.col_))
	{
		cout << "Rows or columns are inconsistent!" << endl;
//		return *this;  //���ر���������̫�к�ʵ����Ҫ
		exit(1);  //�����˳�
	}
	Matrix<T> resultMatrix(row_, col_);  //����֮��
	for(int i = 0; i < row_; i++)
		for(int j = 0; j < col_; j++)
			resultMatrix.ptr_[i][j] = this->ptr_[i][j] - rm.ptr_[i][j];
	return resultMatrix;
}
//����*
template <class T>
Matrix<T> Matrix<T>::operator *(const Matrix<T>& rm)
{

	if(this->col_ != rm.row_)
	{
		cout << "The first matrix's col is not equal the second's row!" << endl;
	//	return *this;
		exit(1);
	}
	else
	{
		Matrix<T> resultMatrix(this->row_, rm.col_);  //����֮��
		T sum = 0.0;  //��һ������һ����˵ĺ�
		for(int i = 0; i < this->row_; i++)
		{
			for(int j = 0; j < rm.col_; j++)
			{
				sum = 0.0;
				for(int k = 0; k < this->col_; k++)
					sum += this->ptr_[i][k] * rm.ptr_[k][j];
				resultMatrix.ptr_[i][j] = sum;	
			}
		}
		return resultMatrix;
	}

}
//����=
template <class T>
Matrix<T> Matrix<T>::operator =(const Matrix<T>& rm)
{	//�ͷ�ԭ������ռ�
	for(int i = 0; i < row_; i++)
		delete[] ptr_[i];
	delete[] ptr_;
	//����ͬ�;���
	row_ = rm.row_;
	col_ = rm.col_;
	ptr_ = new T*[row_];
	for(i = 0; i < row_; i++)
		ptr_[i] = new T[col_];
	//��ֵ
	for(int j = 0; j < row_; j++)
		for(int k = 0; k < col_; k++)
			this->ptr_[j][k] = rm.ptr_[j][k];
	return *this;
}
//����T
template <class T>
Matrix<T> Matrix<T>::transpose()
{
	Matrix<T> transMatrix(col_, row_);
	for(int i = 0; i < row_; i++)
		for(int j = 0; j < col_; j++)
			transMatrix.ptr_[j][i] = this->ptr_[i][j];
		return transMatrix;
}
