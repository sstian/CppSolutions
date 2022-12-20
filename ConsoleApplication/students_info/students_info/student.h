#pragma once
#include <string>
using namespace std;

//文件名
#define FILENAME "students.dat"
//性别 枚举
enum SexEnum { BOY = 1, GIRL = 0, OTHER = 2 };
//学校 家乡信息
struct SInfo
{
	CString school;		//学校
	CString college;	//院系
	CString major;		//专业
	CString hometown;	//家乡
};
typedef CMap<CString, LPCTSTR, float, float> CMap_SF;
//学生用户数据
typedef struct SUser
{
	CString number;	//学号
	CString name;	//姓名
	SexEnum sex;	//性别
	SInfo info;		//学校信息
	//MFC只是实际了LPCSTR和LPCWSTR的专门化，并没有实现CStringA和CStringW的专门化,
	//若使用CString作为CMap的键类型，要声明为CMap<CString, LPCTSTR, ……>。
	CMap_SF score;	//专业成绩
	SUser() {}
	SUser(const SUser& suser)
	{
		number = suser.number;
		name = suser.name;
		sex = suser.sex;
		info = suser.info;
		const CMap_SF::CPair *pair = suser.score.PGetFirstAssoc();
		while (NULL != pair)
		{
			score.SetAt(pair->key, pair->value);
			pair = suser.score.PGetNextAssoc(pair);
		}
	}
	SUser& operator = (const SUser& suser)
	{
		number = suser.number;
		name = suser.name;
		sex = suser.sex;
		info = suser.info;
		const CMap_SF::CPair *pair = suser.score.PGetFirstAssoc();
		while (NULL != pair)
		{
			score.SetAt(pair->key, pair->value);
			pair = suser.score.PGetNextAssoc(pair);
		}
		return *this;
	}
} DATA, *PDATA;
//学生信息操作
class CStudent
{
public:
	CStudent() 
	{ 
		//DATA d;
		//d.number = "21170231262";
		//d.name = "田继辉";
		//d.sex = BOY;
		//d.info.school = "中国海洋大学";
		//d.info.college = "信息科学与技术学院";
		//d.info.major = "计算机技术";
		//d.info.hometown = "河南洛阳";
		//d.score.SetAt(_T("专业英语演说"), 95.6f);
		//d.score.SetAt(_T("自然辨证法"), 97.3f);
		//m_list.AddTail(d);

		//d.number = "21170231262";
		//d.name = "张三丰";
		//d.sex = BOY;
		//d.info.school = "中国海洋大学";
		//d.info.college = "信息科学与技术学院";
		//d.info.major = "计算机技术";
		//d.info.hometown = "河南洛阳";
		//d.score.SetAt(_T("专业英语演说"), 95.6f);
		//d.score.SetAt(_T("自然辨证法"), 97.3f);
		//m_list.AddTail(d);

	}
	virtual ~CStudent() {}
private:
	CList<DATA> m_list;
public:
	// 欢迎界面
	void Welcome();
	// 主菜单
	int MainMenu();
	// 浏览信息
	void Lookup();
	// 添加信息
	void Insert();
	// 删除信息
	bool Remove();
	// 修改信息
	bool Modify();
	// 查找信息
	bool Find();
	//保存信息
	bool Save();
	// 打印输出一位学生信息
	void Print(POSITION pos);
private:
	// 输入性别
	SexEnum InputSex();
	// 数字校验
	bool CheckNum(string& strNum);
};
