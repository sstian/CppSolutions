#include "stdafx.h"
#include "student.h"
#include <conio.h>

// 欢迎界面
void CStudent::Welcome()
{
	cout << "    ****************************\n";

	cout << "    ****************************\n";
	cout << "    **         欢迎使用       **\n";
	cout << "    **                        **\n";
	cout << "    **    学生信息管理系统    **\n";
	cout << "    **                        **\n";
	cout << "    ****************************\n";
	cout << "    ****************************\n";
	cout << "****    请按任意键继续...    ****" << endl;
	while (!_kbhit());	//int _kbhit(void); 执行时,检测是否有按键按下,有按下返回非0值，没有按下则返回0，是非阻塞函数；
	_getch();	// int _getch(void); 从控制台读取一个字符，但不显示在屏幕上
	while (MainMenu());
}


// 主菜单
int CStudent::MainMenu()
{
	int num;
	string strNum;
	system("cls");
	system("color 3f");
	cout << "  1>浏览信息\n";
	cout << "  2>添加信息\n";
	cout << "  3>删除信息\n";
	cout << "  4>修改信息\n";
	cout << "  5>查找信息\n";
	cout << "  6>保存...\n";
	cout << "  0>退出...\n";

	cout << "请选择编号：";
	cin >> strNum;
	while(!CheckNum(strNum));
	num = atoi(strNum.c_str());
	switch (num)
	{
	case 1:
		Lookup();
		break;
	case 2:
		Insert();
		break;
	case 3:
		Remove();
		break;
	case 4:
		Modify();
		break;
	case 5:
		Find();
		break;
	case 6:
		Save();
		break;
	default:
		break;
	}
	return num;
}


// 浏览信息
void CStudent::Lookup()
{
	////C++方式读取文件
	////Save();
	//ifstream ifb(FILENAME, ios::binary);
	//ifb.seekg(0, ios::end);
	//streampos len = ifb.tellg();
	//if (len <= 0)
	//{
	//	ofstream ofb(FILENAME, ios::binary);
	//	ofb.close();
	//}
	//else
	//{
	//	if (!ifb)
	//	{
	//		cout << "Cann't open the file!" << endl;
	//		exit(1);
	//	}

	//	DATA data;
	//	//ifb.seekg(SEEK_END);
	//	m_list.RemoveAll();
	//	while (!ifb.eof())
	//	{
	//		ifb.read((char*)&data, sizeof(data));
	//		m_list.AddTail(data);
	//	}
	//	ifb.close();
		//屏幕显示
		cout << "\n学号        \t姓名\t性别\t学校\t        院系\t                专业\t        家乡\n" << endl;
		POSITION pos = m_list.GetHeadPosition();
		while (pos)
		{
			Print(pos);
			m_list.GetNext(pos);
		}
	//}
	system("pause");
}


// 添加信息
void CStudent::Insert()
{
	DATA NewData;
	string str;
	cout << "请输入学生的相关信息：" << endl;
	cout << "学号 >> ";
	cin >> str;
	while (!CheckNum(str));
	NewData.number = str.c_str();
	cout << "姓名 >>";
	cin >> str;
	NewData.name = str.c_str();
	//cout << "性别（男/女）>> ";
	NewData.sex = InputSex();
	cout << "学校>>";
	cin >> str;
	NewData.info.school = str.c_str(); 
	cout << "院系 >> "; 
	cin >> str;
	NewData.info.college = str.c_str();
	cout << "专业 >> "; 
	cin >> str;
	NewData.info.major = str.c_str();
	cout << "家乡 >> ";
	cin >> str;
	NewData.info.hometown = str.c_str(); 
	cout << "成绩录入（课程名称中输入0结束）： \n";
	CString course;		//课程名
	string strGrade;	//分数值   
	cout << "课程名称 >> ";
	cin >> str;
	while ("0" != str)
	{
		course = str.c_str();
		cout << "分数 >> ";
		cin >> strGrade;
		while(!CheckNum(strGrade));
		NewData.score.SetAt(course, (float)atof(strGrade.c_str()));
		cout << "课程名称 >> ";
		cin >> str;
	}
	m_list.AddTail(NewData);


}


// 删除信息 
bool CStudent::Remove()
{
	string strNum;
	CString csNum;
	cout << "请输入要删除学生的学号：" << endl;
	cin >> strNum;
	csNum = strNum.c_str();
	DATA data;
	POSITION pos = m_list.GetHeadPosition();
	while (pos)
	{
		data = m_list.GetAt(pos);
		if (data.number == csNum)
		{
			m_list.RemoveAt(pos);
			break;
		}
		m_list.GetNext(pos);
	}
	return false;
}


// 修改信息 ?
bool CStudent::Modify()
{
	return false;
}


// 查找信息 
bool CStudent::Find()
{
	string strNum;
	CString csNum;
	cout << "请输入要查找学生的学号：" << endl;
	cin >> strNum;
	csNum = strNum.c_str();
	DATA data;
	POSITION pos = m_list.GetHeadPosition();
	while (pos)
	{
		data = m_list.GetAt(pos);
		if (data.number == csNum)
		{
			cout << "学号\t        姓名\t性别\t学校\t        院系\t                专业\t        家乡" << endl;
			Print(pos);
			fflush(stdin);
			system("pause");
			break;
		}
		m_list.GetNext(pos);
	}
	return false;
}



// 保存信息
bool CStudent::Save()
{
	//C++方式写入文件
	ofstream ofb(FILENAME,ios::binary|ios::ate|ios::app);
	if (ofb.fail())
	{
		cout << "Can't Write the file!"<< endl;
		exit(1);
	}

	DATA data;
	POSITION pos = m_list.GetHeadPosition();
	while (pos)
	{
		data = m_list.GetAt(pos);
		ofb.write((char*)&data, sizeof(data));
		m_list.GetNext(pos);
	}
	ofb.close();
	return true;
}


// 打印输出一位学生信息
void CStudent::Print(POSITION pos)
{
	DATA data = m_list.GetAt(pos); 
	//cout << "学号\t        姓名\t性别\t学校\t        院系\t                专业\t        家乡" << endl;
	wcout.imbue(std::locale("chs"));	//CString输出中文
	wcout << data.number.GetBuffer() << "\t" << data.name.GetString() << "\t";
	if (BOY == data.sex)
		cout << "男";
	else if (GIRL == data.sex)
		cout << "女";
	else if (OTHER == data.sex)
		cout << "其它";
	wcout << "\t" << (LPCTSTR)data.info.school << "\t" << (LPCTSTR)data.info.college << "\t" << (LPCTSTR)data.info.major 
		<< "\t" << (LPCTSTR)data.info.hometown << endl;
	cout << "  成绩：";
	CMap_SF::CPair* pair = data.score.PGetFirstAssoc();
	while (NULL != pair)
	{
		wcout << " " << pair->key.GetString() << " " << pair->value << ",";
		pair = data.score.PGetNextAssoc(pair);
	}
	cout << endl << endl;
}


// 输入性别
SexEnum CStudent::InputSex()
{
	SexEnum sex = (SexEnum)-1;
	string str;
	int sexno;
	do
	{
		cout << "性别（男(1)/女(0)/TA(2)）>> ";
		cin >> str;
		while (!CheckNum(str));
		sexno = atoi(str.c_str());
		switch (sexno)
		{
		case 1:
			sex = BOY;
			break;
		case 0:
			sex = GIRL;
			break;
		case 2:
			sex = OTHER;
			break;
		default:
			cout << "请输入相应编号" << endl;
			break;
		}
		//if ("男" == str)
		//	sex = BOY;
		//else if ("女" == str)
		//	sex = GIRL;
		//else if ("TA" == str)
		//	sex = OTHER;
	} while (-1 == sex);
	return sex;
}


// 数字校验
bool CStudent::CheckNum(string& strNum)
{
	bool flag = false;
	size_t i;
	while (!flag)
	{
		for (i= 0; i < strNum.size(); i++)
		{
			char ch = strNum.at(i);
			if (ch < '0' || ch > '9')
			{
				cout << "存在非法数字！请重试" << endl;
				break;
			}
		}
		if (i >= strNum.size())
			flag = true;
		else
			cin >> strNum;
	}
	return flag;
}
