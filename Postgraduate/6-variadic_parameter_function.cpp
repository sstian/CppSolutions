/*	2017.5.11 14:01
	可变参数的设计
细节：
typedef char * va_list;

#define _INTSIZEOF(n) ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define _crt_va_start(ap,v) ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
//va_start宏的第一个参数是va_list变量指针,
//第二个参数应该传可变参函数的最后一个固定形参,其作用是使va_list类型的指针指向变参函数的第一个可变形参。

#define _crt_va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
//va_arg宏的第一个参数是va_list变量,第二个参数是待获取的参数的数据类型。
//作用：1、使va_list类型的指针指向下一个可变参数；2、获取va_list类型指针指向的值.

#define _crt_va_end(ap) ( ap = (va_list)0 )
//va_end宏主要是对资源释放,使va_list类型的指针不指向任何内存。
*/
#include <iostream>
#include <cstdlib>
#include <cstdarg>  //stdandard argument(标准参数)
using namespace std;

int sum(int count, ...);
//int sum2(initializer_list<int> il);  //需要C++11支持！

int main(void)
{
	int count = 7;
	cout << sum(count, 1,2,3,7,8,5,4) << endl;
//	print("str1", 12 ,3.14f, 0.618, "strover");
//	print("str1");
	system("pause");
	return 0;
}

/*方法一：继承自C语言，形参声明为省略符，函数实现时用参数列表宏访问参数*/
/* 接受任意个数的整形实参，返回这些实参的和。（忽略可能存在的整形溢出）
count: 表示可变参数的个数；1、原型中使用省略号*/
int sum(int count, ...)  
{	
	int sum = 0;
	va_list ap;  //2、定义va_list变量
	va_start(ap, count);  //3、初始化va_list变量，第二个参数为最后一个确定的形参
	for(int i = 0; i < count; i++)  //4、访问参数列表，第二个参数为可变参数的类型
		sum += va_arg(ap, int);
	va_end(ap);  //5、完成清理工作
	return sum;
}
/*注意：
1、函数原型中，省略号必须在参数列表的末尾。即：在函数原型中参数列表省略号的右边不能再出现确定参数。
2、运行时，函数必须能够根据已有信息（既有约定或确定实参）确定可变参数的具体个数与类型。
   函数定义需要知道可变参数的具体类型、个数，这些信息是在运行时确定的，那么显然应该由实参来确定。
3、使用完成时需要用va_end()做清理工作，可变参数宏可能使用了动态分配的内存，忘记执行清理操作可能导致内存泄漏。
4、可变参数宏只能实现顺序访问可变参数，无法后退访问，
   但是可以在清理操作完成后重新使用va_start初始化va_list变量，重新遍历形参表。
*/

/*方法二：将函数形参声明为 C++11 新标准中的initializer_list标准库类型*/
/* 1、函数原型中使用实例化initializer_list模板代表可变参数列表 */
/*int sum2(initializer_list<int> il)
{
	int sum = 0;
	for(auto p = il.begin(); p != il.end(); p++)  //2、使用迭代器访问initializer_list中的参数
		sum += *p;
	return sum;
}*/
/*注意：
1、initializer_list在C++11中才被引入，即在编译时可能需要加上选项 -std=c++11 才能成功编译。auto关键字亦如此。
2、参数必须放在一组'{}'（大括号）内，编译器通过大括号来将这组参数转化为initializer_list，
   大括号的的一组实参与initializer_list形参对应。
3、函数原型initializer_list与普通形参无异，表明形参列表中可以包含其他类型参数且位置不限。
   如：void func(char c, initializer_list il, double d);
4、同一个initializer_list中的参数具有相同的类型。
   本质上initializer_list是一个编译器支持的容器类模板，同其他容器一样，容器中的元素具有相同的类型。
   使用这种方法的一个实例是C++11中vector的列表初始化构造函数。
*/

/*方法三：利用C++泛型特性，声明一个可变参数模板来实现*/

//处理边界情况（参数包含有零个参数）的模板
//1、用来终止递归并处理包中最后一个元素
/*template <typename T>
void print(const T& t)
{
	cout << t;
}
///莫名其妙就有错误存在，都不能好好玩耍了！抓狂ING
//2、含有模板参数包和函数参数包的模板函数
template <typename T, typename... Args>
void print(const T& t, const Args&... rest)
{	//3、函数定义递归调用自己，每一步递归参数包中参数减一
	cout << t << " ";  //打印第一个实参
	print(rest...);  //递归调用，打印其它实参
}*/
/*
模板参数包：零个或多个类型参数的集合。
	模板参数列表中，class...或typename...表明其后的类型参数是一个模板参数包；
函数参数包：零个或多个非类型参数的集合。
	函数形参列表中，类型名...表明其后的参数是一个函数参数包。
sizeof...()运算符用于参数包，返回参数包中的参数个数。

注意：
1、必须处理边界情况，且应当首先定义处理边界情况的模板。
2、参数包在参数列表最右侧，参数包只能从左至右展开。
3、参数包能够实现更加复杂的模板。
这种实现方式的根本原理与重载一致，通过定义模板，让编译器根据实参类型自动生成对应的重载函数。
*/




