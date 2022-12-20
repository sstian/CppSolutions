/*  矩阵类模板（二维）的头文件 */
/******************************************************************
*1、构造函数、赋值构造函数没有返回值
*2、类中数据成员有动态分配内存空间时要自定义复制构造函数
********************************************************************/
#include <iostream.h>
#include <stdlib.h>
#include <time.h>

template <class T>
class Matrix;

//矩阵>>
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
//矩阵<<
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
	//构造函数
	Matrix(int row = 3, int col = 3);  //默认产生随机整数的3X3矩阵
	//复制构造函数
	Matrix(const Matrix<T>& rm);  //深层复制
	//虚析构函数
	virtual ~Matrix();
	//矩阵运算符+重载
	Matrix operator +(const Matrix<T>& rm);
	//矩阵运算符-重载
	Matrix operator -(const Matrix<T>& rm);
	//矩阵运算符*重载
	Matrix operator *(const Matrix<T>& rm);
	//矩阵运算符=重载
	Matrix operator =(const Matrix<T>& rm);
	//矩阵转置
	Matrix transpose();
	//矩阵输入运算符>>作友元函数重载
	friend istream& operator >>(istream& input, Matrix<T>& rm);
	//矩阵输出运算符<<作友元函数重载
	friend ostream& operator <<(ostream& output, const Matrix<T>& rm);
private:
	int row_;  //行数
	int col_;  //列数
	T** ptr_;  //矩阵二维数组的指针
};
//矩阵创建
template <class T>
Matrix<T>::Matrix(int row, int col):row_(row),col_(col)
{  //动态分配二维数组
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
//矩阵删除
template <class T>
Matrix<T>::~Matrix()
{  //释放二维数组
	for(int i = 0; i < row_; i++)
		delete[] ptr_[i];
	delete[] ptr_;
}
//矩阵复制
template <class T>
Matrix<T>::Matrix(const Matrix<T>& rm)
{	
/*	//释放原来矩阵空间
	//这段代码不需要，否则运行会崩溃，
	//估计调用复制构造函数时若释放原有空间会被清空数据？
	for(int i = 0; i < row_; i++)
		delete[] ptr_[i];
	delete[] ptr_;
*/	//创建同型矩阵
	row_ = rm.row_;
	col_ = rm.col_;
	ptr_ = new T*[row_];
	for(int i = 0; i < row_; i++)
		ptr_[i] = new T[col_];
	//赋值
	for(int j = 0; j < row_; j++)
		for(int k = 0; k < col_; k++)
			this->ptr_[j][k] = rm.ptr_[j][k];	
}
//矩阵+
template <class T>
Matrix<T> Matrix<T>::operator +(const Matrix<T>& rm)
{
	if((this->row_ != rm.row_) || (this->col_ != rm.col_))
	{
		cout << "Not the same type matrix!" << endl;
		exit(1);  //程序退出
	}
	else
	{
		Matrix<T> resultMatrix(row_, col_);  //矩阵之和
		for(int i = 0; i < row_; i++)
			for(int j = 0; j < col_; j++)
			{
				resultMatrix.ptr_[i][j] = this->ptr_[i][j] + rm.ptr_[i][j];
			}
		return resultMatrix;
	}
}
//矩阵-
template <class T>
Matrix<T> Matrix<T>::operator -(const Matrix<T>& rm)
{
	if((this->row_ != rm.row_) || (this->col_ != rm.col_))
	{
		cout << "Rows or columns are inconsistent!" << endl;
//		return *this;  //返回被减数，不太切合实际需要
		exit(1);  //程序退出
	}
	Matrix<T> resultMatrix(row_, col_);  //矩阵之差
	for(int i = 0; i < row_; i++)
		for(int j = 0; j < col_; j++)
			resultMatrix.ptr_[i][j] = this->ptr_[i][j] - rm.ptr_[i][j];
	return resultMatrix;
}
//矩阵*
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
		Matrix<T> resultMatrix(this->row_, rm.col_);  //矩阵之积
		T sum = 0.0;  //左一行与右一列相乘的和
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
//矩阵=
template <class T>
Matrix<T> Matrix<T>::operator =(const Matrix<T>& rm)
{	//释放原来矩阵空间
	for(int i = 0; i < row_; i++)
		delete[] ptr_[i];
	delete[] ptr_;
	//创建同型矩阵
	row_ = rm.row_;
	col_ = rm.col_;
	ptr_ = new T*[row_];
	for(i = 0; i < row_; i++)
		ptr_[i] = new T[col_];
	//赋值
	for(int j = 0; j < row_; j++)
		for(int k = 0; k < col_; k++)
			this->ptr_[j][k] = rm.ptr_[j][k];
	return *this;
}
//矩阵T
template <class T>
Matrix<T> Matrix<T>::transpose()
{
	Matrix<T> transMatrix(col_, row_);
	for(int i = 0; i < row_; i++)
		for(int j = 0; j < col_; j++)
			transMatrix.ptr_[j][i] = this->ptr_[i][j];
		return transMatrix;
}
