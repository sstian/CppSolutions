/*  2017.3.17 14:43
	��������õ����Ա����
�ܽ᣺��ͨ���� ���Ե��� ��ͨ/��̬/����Ա������
	  ������   ���Ե���      ��̬/����Ա���������ܵ�����ͨ��Ա����
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
	cout << "aBook: ";  //��ͨ����
	Book aBook(10, "Harry Potter");
	aBook.show();
	cout << "constBook: ";
	const Book constBook(99, "Snow White");  //������
	constBook.show();
	//constBook.getTitle();//error C2662: 'getTitle' : cannot convert 'this' pointer from 'const class Book' 
						   //to 'class Book &'Conversion loses qualifiers
	return 0;
}