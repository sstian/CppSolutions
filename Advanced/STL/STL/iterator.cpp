#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

const int SIZE = 50;
int g_array[SIZE];
vector<int> g_vector(50);

int main()
{
	///指针迭代器
	g_array[20] = 100;
	int* pa = find(g_array, g_array + SIZE, 100);
	if (pa != g_array + SIZE)
		cout << "Find " << *pa << endl;
	else
		cout << "not found! " << endl;
	///容器迭代器
	g_vector[20] = 100;
	vector<int>::iterator it = find(g_vector.begin(), g_vector.end(), 100);
	if (it != g_vector.end())
		cout << "Vector contains value " << *it << endl;
	else
		cout << "Vector don't contain value" << endl;
	//at()
	vector<int> v(5, 1);
	for (int i = 0; i < 5; i++)
		//cout << "element " << i << " is " << v[i] << endl; //ERROR!数组越界
		//cout << "element " << i << " is " << v.at(i) << endl; //抛出异常 
		cout << "element " << i << " is " << v.at(i) << endl; 
	//pop_back()
	vector<char> alphaVector;
	for (int i = 0; i < 10; i++)
		alphaVector.push_back(i + 65);
	int size = alphaVector.size();
	vector<char>::iterator theIterator;
	for (int j = 0; j < size; j++)
	{
		for (theIterator = alphaVector.begin(); theIterator != alphaVector.end(); theIterator++)
			cout << *theIterator;
		cout << endl;
		alphaVector.pop_back();
	}
	//集合set
	set<int> s1;
	s1.insert(1);
	s1.insert(5);
	s1.insert(1); //1已经存在，此处者不会插入
	s1.insert(100);
	set<int>::iterator ite;
	for (ite = s1.begin(); ite != s1.end(); ite++) //遍历结果为有序排列
		cout << *ite << "  ";
	cout << endl;
	cout << s1.size() << endl;
	//set自定义排序
	struct Entity	//自定义数据类型
	{
		int id;
		int score;
		string name;
	};
	struct Compare	//自定义比较策略
	{
		bool operator()(const Entity& e1, const Entity& e2) const
		{
			if (e1.score < e2.score)	return true;
			else if (e1.score == e2.score)
				if (e1.id < e2.id)	return true;
			return false;
		}
	};
	set<Entity, Compare> s_test;
	Entity a, b, c;
	a.id = 123;	a.score = 90;	a.name = "Jack";
	b.id = 234; b.score = 60;	b.name = "Mary";
	c.id = 340;	c.score = 60;	c.name = "Tom";
	s_test.insert(a);
	s_test.insert(b);
	s_test.insert(c);
	set<Entity>::iterator sit;	 //迭代器可以不用说明Compare
//	set<Entity, Compare>::iterator sit; 
	cout << "score list ordered by score:\n";
	for (sit = s_test.begin(); sit != s_test.end(); sit++)
		cout << sit->score << "--" << sit->id << "--" << sit->name << endl;
	//set运算：并、交、差、对称差
	//s1: 1 5 100
	//s2: 3 5 10
	set<int> s2, s3;
	s2.insert(3);
	s2.insert(5);
	s2.insert(10);
	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), insert_iterator<set<int>>(s3, s3.begin()));	//并
	copy(s3.begin(), s3.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	s3.clear();
	set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), insert_iterator<set<int>>(s3, s3.begin()));	//交
	copy(s3.begin(), s3.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	s3.clear();
	set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), insert_iterator<set<int>>(s3, s3.begin()));	//差
	copy(s3.begin(), s3.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	s3.clear();
	set_symmetric_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), insert_iterator<set<int>>(s3, s3.begin()));	//对称差=AUB-AnB
	copy(s3.begin(), s3.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	//映射map
	map<int, string> mapstu;
	mapstu.insert(pair<int,string>(1,"one"));
	mapstu.insert(map<int, string>::value_type(2,"two"));
//	mapstu[1] = "three";  //会覆盖
	mapstu[-1] = "three";
	map<int, string>::iterator mit;
	for (mit = mapstu.begin(); mit != mapstu.end(); mit++)
		cout << mit->first << "==" << mit->second << endl;
	//map自定义排序
	//1、仿函数
//	typedef struct tagStudentinfo	//自定义类型
//	{
//		int id;
//		string name;
//	}Studentinfo, *pStudentinfo;
//	class Sort	//排序策略
//	{
//	public:
//		bool operator()(const Studentinfo& si1, const Studentinfo& si2) const
//		{
//			if (si1.id < si2.id)	return true;
//			else if (si1.id == si2.id)	return si1.name.compare(si2.name) < 0;
//			return false;
//		}
//	};
//	map<Studentinfo, int, Sort> mstu;
//	Studentinfo st1, st2;
//	st1.id = 12;	st1.name = "Tom";
//	st2.id = 12;	st2.name = "Jerry";
//	mstu.insert(pair<Studentinfo, int>(st1, 10));
//	mstu.insert(map<Studentinfo, int>::value_type(st2, 20));
////	map<Studentinfo, int>::iterator msit;  //不说明排序策略也对
//	map<Studentinfo, int, Sort>::iterator msit;
//	for (msit = mstu.begin(); msit != mstu.end(); msit++)
//		cout << msit->first.id << " " << msit->first.name << "..." << msit->second << endl;
	//2、重载小于<函数
	typedef struct tagStudentinfo	//自定义类型+重载排序策略
	{
		int id;
		string name;
		bool operator<(const tagStudentinfo& rsi) const
		{
			if (id < rsi.id)	return true;
			else if (id == rsi.id)	return name.compare(rsi.name) < 0;
			return false;
		}
	}Studentinfo, *pStudentinfo;
	map<Studentinfo, int> mstu;
	Studentinfo st1, st2;
	st1.id = 12;	st1.name = "Tom";
	st2.id = 12;	st2.name = "Jerry";
	mstu.insert(pair<Studentinfo, int>(st1, 10));
	mstu.insert(map<Studentinfo, int>::value_type(st2, 20));
	//	map<Studentinfo, int>::iterator msit;  //不说明排序策略也对
	map<Studentinfo, int>::iterator msit;
	for (msit = mstu.begin(); msit != mstu.end(); msit++)
		cout << msit->first.id << " " << msit->first.name << "..." << msit->second << endl;

	return 0;
}

/*==============================================================================================
Find 100
Vector contains value 100
element 0 is 1
element 1 is 1
element 2 is 1
element 3 is 1
element 4 is 1
ABCDEFGHIJ
ABCDEFGHI
ABCDEFGH
ABCDEFG
ABCDEF
ABCDE
ABCD
ABC
AB
A
1  5  100
3
score list ordered by score:
60--234--Mary
60--340--Tom
90--123--Jack
1 3 5 10 100
5
1 100
1 3 10 100
-1==three
1==one
2==two
12 Jerry...20
12 Tom...10
请按任意键继续. . .
================================================================================================*/
