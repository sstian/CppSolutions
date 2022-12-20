/*  2017.3.7 20:27
    静态数据成员、静态成员函数
总结：
1、本类中/友元类中/友元函数中的对象可以访问该类的私有成员，其它情况则不能。
2、静态成员属于类，非静态成员属于对象；
   静态成员函数不是对象成员，则在其函数实现中不能引用非静态成员，只能引用静态数据成员；
   静态数据成员在类中声明，在类外定义或初始化。
3、常成员函数和普通成员函数均可以引用普通/静态/常数据成员。
4、常对象只能调用常成员函数和静态成员函数；同样，常成员函数只能被常对象调用。
5、"const" modifiers not allowed on static member functions
6、成员函数作友元：1）类B的成员函数要作类A的友元函数，则类B要先定义！
					2）前向引用声明，因类A未定义，使用类A的对象的函数只能声明而不能定义！
7、友元访问类的数据成员通过类对象，只是可以直接访问。
*/
#include <iostream>
using namespace std;

//#ifndef STATIC_H  //等价于#if !defined(STATIC_H)
#if !defined(STATIC_H)
#define	STATIC_H

//class Paper;  //前向引用声明：使用在定义前
class Book;

class Paper
{
public:
	void getBook(Book& rBook) const;  //Book类未定义，成员函数只能声明
//	friend void Book::getPaper(Paper& rPaper);  //error C2027: use of undefined type 'Book'
private:
	int number;
};


class Book
{
public:
	Book(int newId = 0);
	void setId(int newId){id = newId;}
	void show(const Book& newBook);  //成员函数,函数形参为const，被引用对象不能被更改
	void show(const Book& newBook) const;  //常成员函数，函数体为const，数据成员不能被更改
	static void count()  //静态成员函数 
		{cout << "num = " << num << endl; }  
	friend void read(Book& rBook);  //111、普通函数作友元访问：对象名.成员名
	friend void Paper::getBook(Book& rBook) const;  //222、成员函数作友元
//	void getPaper(Paper& rPaper){cout << "Paper: number = " << rPaper.number << endl;}
	friend class Size;  //333、友元类
	~Book();
private:
	int id;
	static int num;  //1、书籍数量，静态数据成员，必须在类外定义或初始化
	const int type;  //2、常数据成员
	static const int no;  //3、静态常数据成员
};

class Size
{
public:
	void calBook(Book& rBook)
	{
		cout << "calBook: ";
		cout << "id = " << rBook.id << ", num = " << rBook.num;
		cout << ", type = " << rBook.type << ", no = " << rBook.no << endl;
		rBook.show(rBook);
	}
private:
	int bound;
};

void Paper::getBook(Book& rBook) const
{
	cout << "getBook: ";
	cout << "id = " << rBook.id << ", num = " << rBook.num;
	cout << ", type = " << rBook.type << ", no = " << rBook.no << endl;
}

int Book::num = 0;  //1、静态数据默认值为0
const int Book::no = 888;  //3、
Book::Book(int newId):type(newId)  //2、
{
	cout << "Create one book...\n";
	num++;
	id = 130701200 + newId;
	cout << "Book id: " << id << endl;
}
Book::~Book()
{
	cout << "Destructor one book.\n";
	num--;

}
void Book::show(const Book& newBook)  //常引用：被引用对象不能被改变
{
	cout << newBook.id << endl;
		cout << "type = " << type << ", num = " << num << ", id = " << id << endl; 
}
void Book::show(const Book& newBook) const
{
	cout << "const: ";
	cout << newBook.id << endl;
	cout << "type = " << type << ", num = " << num << ", id = " << id << endl; 
	cout << "static const int no = " << no << endl;
}

void read(Book& rBook)
{
	cout << "read: ";
	cout << "id = " << rBook.id << ", num = " << rBook.num;
	cout << ", type = " << rBook.type << ", no = " << rBook.no << endl;
}

int main(void)
{
	Book::count();
	Book aBook(13);
	aBook.setId(100);
	aBook.show(aBook);  //对象自己调用以自己为实参的函数！牛

	const Book cBook;  //const常量对象必须被初始化，可以定义带默认参数的构造函数
	cBook.show(cBook);  //常对象只能调用常成员函数和静态成员函数
	cout << "cBook.count(): ";
	cBook.count();

	read(aBook);
	Paper pa;
	pa.getBook(aBook);
//	cout << "friend static: ";
//	Paper::getBook(aBook);
	Paper const cPaper;
	cout << "friend const: ";
	cPaper.getBook(aBook);

	Size mm;
	mm.calBook(aBook);
	return 0;
}

#endif

/*在VC++6.0中的运行结果：
======================================================================
num = 0
Create one book...
Book id: 130701213
100
type = 13, num = 1, id = 100
Create one book...
Book id: 130701200
const: 130701200
type = 0, num = 2, id = 130701200
static const int no = 888
cBook.count(): num = 2
read: id = 100, num = 2, type = 13, no = 888
getBook: id = 100, num = 2, type = 13, no = 888
friend const: getBook: id = 100, num = 2, type = 13, no = 888
calBook: id = 100, num = 2, type = 13, no = 888
100
type = 13, num = 2, id = 100
Destructor one book.
Destructor one book.
Press any key to continue
======================================================================*/