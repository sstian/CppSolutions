/*  2017.3.17 14:43
	常对象调用的类成员函数
总结：普通对象 可以调用 普通/静态/常成员函数；
	  常对象   可以调用      静态/常成员函数，不能调用普通成员函数
*/
#include <iostream>
using namespace std;

class Book
{
public:
	Book(int newNumber, char* newTitle):number(newNumber),title(newTitle) { cout << "Constructor..." << endl; }
	int getNumber() const { return number;}
	char* getTitle() {return title;}
	void show() const {cout << "number: " << number << ", title: " << title << endl;}
	virtual ~Book() { cout << "Deconstructor." << endl; }
private:
	int number;
	char* title;
};

int main(void)
{
	cout << "aBook: ";  //普通对象
	Book aBook(10, "Harry Potter");
	aBook.show();
	cout << "constBook: ";
	const Book constBook(99, "Snow White");  //常对象
	constBook.show();
	//constBook.getTitle();//error C2662: 'getTitle' : cannot convert 'this' pointer from 'const class Book' 
						   //to 'class Book &'Conversion loses qualifiers
	return 0;
}