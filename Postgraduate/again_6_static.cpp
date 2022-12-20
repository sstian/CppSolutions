/*  2017.3.7 20:27
    ��̬���ݳ�Ա����̬��Ա����
�ܽ᣺
1��������/��Ԫ����/��Ԫ�����еĶ�����Է��ʸ����˽�г�Ա������������ܡ�
2����̬��Ա�����࣬�Ǿ�̬��Ա���ڶ���
   ��̬��Ա�������Ƕ����Ա�������亯��ʵ���в������÷Ǿ�̬��Ա��ֻ�����þ�̬���ݳ�Ա��
   ��̬���ݳ�Ա�����������������ⶨ����ʼ����
3������Ա��������ͨ��Ա����������������ͨ/��̬/�����ݳ�Ա��
4��������ֻ�ܵ��ó���Ա�����;�̬��Ա������ͬ��������Ա����ֻ�ܱ���������á�
5��"const" modifiers not allowed on static member functions
6����Ա��������Ԫ��1����B�ĳ�Ա����Ҫ����A����Ԫ����������BҪ�ȶ��壡
					2��ǰ����������������Aδ���壬ʹ����A�Ķ���ĺ���ֻ�����������ܶ��壡
7����Ԫ����������ݳ�Աͨ�������ֻ�ǿ���ֱ�ӷ��ʡ�
*/
#include <iostream>
using namespace std;

//#ifndef STATIC_H  //�ȼ���#if !defined(STATIC_H)
#if !defined(STATIC_H)
#define	STATIC_H

//class Paper;  //ǰ������������ʹ���ڶ���ǰ
class Book;

class Paper
{
public:
	void getBook(Book& rBook) const;  //Book��δ���壬��Ա����ֻ������
//	friend void Book::getPaper(Paper& rPaper);  //error C2027: use of undefined type 'Book'
private:
	int number;
};


class Book
{
public:
	Book(int newId = 0);
	void setId(int newId){id = newId;}
	void show(const Book& newBook);  //��Ա����,�����β�Ϊconst�������ö����ܱ�����
	void show(const Book& newBook) const;  //����Ա������������Ϊconst�����ݳ�Ա���ܱ�����
	static void count()  //��̬��Ա���� 
		{cout << "num = " << num << endl; }  
	friend void read(Book& rBook);  //111����ͨ��������Ԫ���ʣ�������.��Ա��
	friend void Paper::getBook(Book& rBook) const;  //222����Ա��������Ԫ
//	void getPaper(Paper& rPaper){cout << "Paper: number = " << rPaper.number << endl;}
	friend class Size;  //333����Ԫ��
	~Book();
private:
	int id;
	static int num;  //1���鼮��������̬���ݳ�Ա�����������ⶨ����ʼ��
	const int type;  //2�������ݳ�Ա
	static const int no;  //3����̬�����ݳ�Ա
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

int Book::num = 0;  //1����̬����Ĭ��ֵΪ0
const int Book::no = 888;  //3��
Book::Book(int newId):type(newId)  //2��
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
void Book::show(const Book& newBook)  //�����ã������ö����ܱ��ı�
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
	aBook.show(aBook);  //�����Լ��������Լ�Ϊʵ�εĺ�����ţ

	const Book cBook;  //const����������뱻��ʼ�������Զ����Ĭ�ϲ����Ĺ��캯��
	cBook.show(cBook);  //������ֻ�ܵ��ó���Ա�����;�̬��Ա����
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

/*��VC++6.0�е����н����
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