#include "CUserShort.h"



CUserShort::CUserShort()
{
}


CUserShort::~CUserShort()
{
}

void CUserShort::Start()
{
	if (this->Establish())
	{
		while (this->Menu());
	}
}

int CUserShort::Establish()
{
	// 登录
	wcout << L"*** Welcome to Worker Information Management System - Short Connect ***" << endl;
	while (!this->Login());
	// 进入系统等待时间
	for (int i = 3; i > 0; i--)
	{
		cout << "\rAfter " << i << " s into the system...";
		Sleep(1000);
	}
	return 1;
}

bool CUserShort::Login()
{
	//system("cls");
	cout << "请输入账户名：";
	cin >> m_account.username;
	cout << "请输入密码  ：";
	cin >> m_account.password;

	CSocketShort socketshort;

	//char name[20];
	//int port;
	//socketshort.GetSockName(name, port);
	//cout << name << "-" << port << endl;

	int type = EType::ADMIN_LOGIN;
	socketshort.Send(&type, sizeof(type));
	socketshort.Send(&m_account, sizeof(m_account));

	int find;
	socketshort.Receive(&find, sizeof(find));
	if (find)
	{
		socketshort.Receive(&m_account.authority, sizeof(m_account.authority));
		cout << "Login succeed." << endl;
	}
	else
		cout << "账户名或密码错误！请重试：" << endl;
	return find;
}

bool CUserShort::Menu()
{
	system("cls");
	setlocale(LC_ALL, "chs");
	wcout << "Username: " << m_account.username << ", Authority: " << (m_account.authority ? "advanced" : "normal") << endl;
	wcout << L"** Main Menu **" << endl;
	wcout << L"1. 浏览信息" << endl;
	wcout << L"2. 添加信息" << endl;
	wcout << L"3. 删除信息" << endl;
	wcout << L"4. 修改信息" << endl;
	wcout << L"5. 查找信息..." << endl;
	wcout << L"6. 排序信息..." << endl;
	wcout << L"7. 颜色设置" << endl;
	if (m_account.authority)
		wcout << L"8. 管理账户..." << endl;
	else
		wcout << L"8. 修改密码" << endl;
	wcout << L"0. 退出...\n" << endl;

	cout << "请选择：";
	switch (this->CheckNum())
	{
	case 1: DoBrowse(); break;
	case 2: DoInsert(); break;
	case 3: while (DoDelete()); break;
	case 4: while (DoModify()); break;
	case 5: while (this->FindMenu()); break; //DoFindin(); break;	case 2: DoInsert(); break;
	case 6: while (this->SortMenu()); break;
	case 7: ColorSet(); break;
	case 8:if (m_account.authority) while (this->AccountMenu());
		   else DoChangePassword();
		   break;
	case 0: cout << "System is exiting..." << endl; return false;
	default:
		break;
	}
	system("pause");
	return true;
}

bool CUserShort::FindMenu()
{
	system("cls");
	setlocale(LC_ALL, "chs");
	wcout << L"** Find Menu **" << endl;
	wcout << L"1. 按工号查找" << endl;
	wcout << L"2. 按姓名查找" << endl;
	wcout << L"3. 按性别查找" << endl;
	wcout << L"4. 按工资范围查找" << endl;
	wcout << L"5. 按年龄范围查找" << endl;
	wcout << L"6. 按电话号查找" << endl;
	wcout << L"7. 按身份证号查找" << endl;
	wcout << L"8. 按家庭住址模糊查找" << endl;
	wcout << L"0. 返回主菜单...\n" << endl;

	cout << "请选择：";
	switch (this->CheckNum())
	{
	case 1: DoFindNumber(); break;
	case 2: DoFindName(); break;
	case 3: DoFindSex(); break;
	case 4: DoFindSalary(); break;
		// ...
	case 5: DoFindAge(); break;
	case 6: DoFindPhone(); break;
	case 7: DoFindIdcard(); break;
	case 8: DoFindHome(); break;
	case 0: cout << "Exting Find Menu..." << endl; return false;
	default:
		break;
	}
	system("pause");
	return true;
}
// 使用表外排序
bool CUserShort::SortMenu()
{
	system("cls");
	setlocale(LC_ALL, "chs");
	wcout << L"** Sort Menu **" << endl;
	wcout << L"1. 按工号排序：升序" << endl;
	wcout << L"2. 按姓名排序：升序" << endl;
	wcout << L"3. 按性别排序：男-女" << endl;
	wcout << L"4. 按工资排序：升序" << endl;
	wcout << L"0. 返回主菜单...\n" << endl;

	cout << "请选择：";
	int num = this->CheckNum();
	switch (num)
	{
	case 1:
	case 2:
	case 3:
	case 4:  DoSort(num - 1); break;
	case 0: cout << "Exting Sort Menu..." << endl; return false;
	default:
		break;
	}
	system("pause");
	return true;
}

bool CUserShort::AccountMenu()
{
	system("cls");
	setlocale(LC_ALL, "chs");
	wcout << L"** Account Menu **" << endl;
	wcout << L"1. 浏览账户" << endl;
	wcout << L"2. 添加账户" << endl;
	wcout << L"3. 删除账户" << endl;
	wcout << L"4. 修改账户" << endl;
	wcout << L"5. 查找账户" << endl;
	wcout << L"6. 排序账户..." << endl;
	wcout << L"0. 返回主菜单...\n" << endl;

	cout << "请选择：";
	int num = this->CheckNum();
	switch (num)
	{
	case 1: DoBrowseAccount(); break;
	case 2: DoInsertAccount(); break;
	case 3: while (this->DoDeleteAccount()); break;
	case 4: while (this->DoModifyAccount()); break;
	case 5: DoFindinAccount(); break;
	case 6: while (this->AccountSortMenu()); break;
	case 0: cout << "Exting Account Menu..." << endl; return false;
	default:
		break;
	}
	system("pause");
	return true;
}

bool CUserShort::AccountSortMenu()
{
	system("cls");
	setlocale(LC_ALL, "chs");
	wcout << L"** Account Sort Menu **" << endl;
	wcout << L"1. 按用户名排序：升序" << endl;
	wcout << L"2. 按权限排序：advanced-normal" << endl;
	wcout << L"0. 返回Account Menu...\n" << endl;

	cout << "请选择：";
	int num = this->CheckNum();
	switch (num)
	{
	case 1:
	case 2: DoSortAccount(num - 1); break;
	case 0: cout << "Exting Account Sort Menu..." << endl; return false;
	default:
		break;
	}
	system("pause");
	return true;
}

int CUserShort::CheckNum()
{
	int num;
	string strnum;
	int flag;
	while (true)
	{
		flag = true;
		cin >> strnum;
		for_each(strnum.begin(), strnum.end(), [&](auto& at)->void {if (at < '0' || at > '9') flag = false; return; });
		if (flag)
		{
			num = atoi(strnum.c_str());
			break;
		}
		else
			cout << "存在非数字形式！请重试：";
	}
	return num;
}

bool CUserShort::ShowStatus(CSocketShort& socketshort, const char* success, const char* failure)
{
	int status = 0;
	socketshort.Receive(&status, sizeof(int));
	if (status)
		cout << success << endl;
	else
		cout << failure << endl;

	return status;
}

bool CUserShort::DoBrowse()
{
	CSocketShort socketshort;

	//char name[20];
	//int port;
	//socketshort.GetSockName(name, port);
	//cout << name << "-" << port << endl;

	int type = EType::REQ_BROWSE;
	socketshort.Send(&type, sizeof(type));

	int size = 0;
	socketshort.Receive(&size, sizeof(size));
	cout << "worker size = " << size << endl;
	//cout << cworker[WORKER_NUMBER] << "\t" << cworker[WORKER_NAME] << "\t" << cworker[WORKER_SEX] << endl;
	DATA  data;
	if (size)
	{
		OutWorkerTitle();
		for (int i = 0; i < size; i++)
		{
			socketshort.Receive(&data, sizeof(data));
			cout << data << endl;
		}
		this->ShowStatus(socketshort, "Browse succeed.", "Browse failed!");
		return true;
	}
	return false;
}

bool CUserShort::DoInsert()
{
	vector<DATA> vecdata;
	vecdata.clear();
	//插入数据工号的唯一性，可由数据库id的唯一性保持
	//此处通过程序判断
	while (this->InputData(vecdata));

	CSocketShort socketshort;
	int type = EType::REQ_INSERT;
	socketshort.Send(&type, sizeof(type));
	int size = (int)vecdata.size();
	socketshort.Send(&size, sizeof(size));
	if (size)
	{
		for (auto& at : vecdata)
			socketshort.Send(&at, sizeof(at));
		this->ShowStatus(socketshort, "Insert succeed.", "Insert failure!");
		//DoBrowse();
	}

	return true;
}

bool CUserShort::DoDelete()
{
	this->CinClear();
	cout << "请输入要删除的Worker" << cworker[WORKER_NUMBER] << ": ";
	int number = this->CheckNum();
	if (this->FindData(number))
	{
		this->CinClear();
		cout << "确定要删除吗？(1=Y/0=N): ";
		char sure;
		cin >> sure;
		if ('1' != sure)
			return false;	//由客户端判断执不执行协议
							// 消息传送
		CSocketShort socketshort;
		int type = EType::REQ_DELETE;
		socketshort.Send(&type, sizeof(type));
		socketshort.Send(&number, sizeof(number));
		this->ShowStatus(socketshort, "Delete succeed.", "Delete failure!");

		this->CinClear();
		cout << "要继续删除吗？(0 to over OR any key): ";
		char over;
		cin >> over;
		if ('0' == over)
			return false;
		return true;
	}
	return false;
}

bool CUserShort::DoModify()
{
	this->CinClear();
	cout << "\n修改 Worker Info ('*'保留，'#'清空)" << endl;
	cout << "请输入要修改的Worker" << cworker[WORKER_NUMBER] << ": ";
	int number = this->CheckNum();
	DATA data;
	if (FindData(number, true, &data))
	{
		for (int index = 0; index < SWORKER_SIZE; index++)
		{
			if (EWorker::WORKER_SEX == index)
				cout << "新的" << cworker[index] << " (1/0): ";
			else
				cout << "新的" << cworker[index] << ": ";
			this->ModifyData(data, index);						//不支持空格间隔！
		}
		//cout << "新的" << cworker[WORKER_NUMBER] << ": ";
		//this->ModifyData(data, EWorker::WORKER_NUMBER);
		//cout << "新的" << cworker[WORKER_NAME] << ": ";
		//this->ModifyData(data, EWorker::WORKER_NAME);
		//cout << "新的" << cworker[WORKER_SEX] << " (1/0): ";
		//this->ModifyData(data, EWorker::WORKER_SEX);
		//cout << "新的" << cworker[WORKER_SALARY] << ": ";
		//this->ModifyData(data, EWorker::WORKER_SALARY);
		//// ...
		//cout << "新的" << cworker[WORKER_AGE] << ": ";
		//this->ModifyData(data, EWorker::WORKER_AGE);
		//cout << "新的" << cworker[WORKER_PHONE] << ": ";
		//this->ModifyData(data, EWorker::WORKER_PHONE);
		//cout << "新的" << cworker[WORKER_IDCARD] << ": ";
		//this->ModifyData(data, EWorker::WORKER_IDCARD);
		//cout << "新的" << cworker[WORKER_HOME] << ": ";
		//this->ModifyData(data, EWorker::WORKER_HOME);

		cout << "\nNew Worker Info as follows: " << endl;
		OutWorkerTitle();
		cout << data << endl;
		this->CinClear();
		cout << "确定要修改吗？(1=Y/0=N): ";
		char sure;
		cin >> sure;
		if ('1' != sure)
			return false;

		CSocketShort socketshort;
		int type = EType::REQ_MODIFY;
		socketshort.Send(&type, sizeof(type));
		socketshort.Send(&number, sizeof(number));	//原始数据工号
		socketshort.Send(&data, sizeof(data));		//新的数据
		this->ShowStatus(socketshort, "Modify succeed.", "Modify failed!");

		this->CinClear();
		cout << "要继续修改吗？(0 to over OR any key): ";
		char over;
		cin >> over;
		if ('0' == over)
			return false;
	}
	else
		return false;
	return true;
}

bool CUserShort::DoSort(int serial)
{
	///不区分大小写比较 int __cdecl _stricmp(_In_z_ char const* _String1,_In_z_ char const* _String2);
	// 函数指针类模板+lambda匿名函数
	function<bool(DATA&, DATA&)> func[4];	//保存lambda函数
	func[0] = [](DATA& data1, DATA& data2)->bool {return data1.number < data2.number; };
	func[1] = [](DATA& data1, DATA& data2)->bool {return (_stricmp(data1.name, data2.name) < 0); };
	func[2] = [](DATA& data1, DATA& data2)->bool {return data1.sex > data2.sex; };
	func[3] = [](DATA& data1, DATA& data2)->bool {return data1.salary < data2.salary; };

	CSocketShort socketshort;
	int type = EType::REQ_SORT;
	socketshort.Send(&type, sizeof(type));

	int size = 0;
	socketshort.Receive(&size, sizeof(size));
	cout << "size = " << size << endl;
	if (size)
	{
		vector<DATA> vecdata;
		vecdata.clear();
		DATA data;
		for (int s = 0; s < size; s++)
		{
			socketshort.Receive(&data, sizeof(data));
			vecdata.push_back(data);
		}

		// 选择排序 表外排序：索引下标
		int* pOrder = new int[size];
		for (int index = 0; index < size; index++)
			pOrder[index] = index;

		int i, j, m;
		for (i = 0; i < size - 1; i++)
		{
			m = i;
			for (j = i + 1; j < size; j++)
				if (func[serial](vecdata.at(j), vecdata.at(m)))
					//if(vecdata.at(j).number < vecdata.at(m).number)
					m = j;
			if (m != i)
			{
				int temp = pOrder[m]; pOrder[m] = pOrder[i]; pOrder[i] = temp;
			}
			//DATA temp = vecdata[m]; vecdata[m] = vecdata[i]; vecdata[i] = temp;
		}
		// 打印输出
		OutWorkerTitle();
		for (int t = 0; t < size; t++)
			cout << vecdata.at(pOrder[t]) << endl;
		delete[]pOrder;
		//for (auto& at : vecdata)
		//	cout << at << endl;
		this->ShowStatus(socketshort, "Sort DATA succeed.", "Sort DATA failed!");	//!再次强调，消息要对等
	}
	else
		cout << "DATA is empty!" << endl;
	return false;
}

//bool CUserShort::DoFindin()
//{
//	//int type = EType::REQ_FINDIN;
//	//socketshort.Send(&type, sizeof(type));
//	return this->DoFindNumber();
//}

// as example of int return one
bool CUserShort::DoFindNumber()
{
	cout << "请输入要查找的Worker" << cworker[WORKER_NUMBER] << ": ";
	//int number; 
	//cin >> number;
	int number = this->CheckNum();
	this->FindData(number);
	return true;
}
// as example of string return mutiple / one
bool CUserShort::DoFindName()
{
	cout << "请输入要查找的Worker" << cworker[WORKER_NAME] << ": ";
	string strtemp;
	cin >> strtemp;

	CSocketShort socketshort;
	int type = EType::REQ_FIND_NAME;
	socketshort.Send(&type, sizeof(type));
	socketshort.Send(strtemp.c_str(), (int)strtemp.length());	//send char*/string.c_str()
	int size = 0;
	socketshort.Receive(&size, sizeof(int));
	if (size)
	{
		cout << "\nHas Found " << size << " DATA as follows:" << endl;
		OutWorkerTitle();
		DATA data;
		for (int i = 0; i < size; i++)
		{
			socketshort.Receive(&data, sizeof(struct SWorker));
			cout << data << endl;
		}
		this->ShowStatus(socketshort, "Find by name succeed.", "Find by name failed!");
	}
	else
		cout << "Not Found!" << endl;

	return true;
}
// as example of bool retrun mutiple / one
bool CUserShort::DoFindSex()
{
	cout << "请输入要查找的Worker" << cworker[WORKER_SEX] << "(1/0): ";
	char sex;
	cin >> sex;
	bool bsex = ('1' == sex) ? true : false;

	CSocketShort socketshort;
	int type = EType::REQ_FIND_SEX;
	socketshort.Send(&type, sizeof(type));
	socketshort.Send(&bsex, sizeof(bsex));		// send bool
	int size = 0;
	socketshort.Receive(&size, sizeof(int));
	if (size)
	{
		cout << "\nHas Found " << size << " DATA as follows:" << endl;
		OutWorkerTitle();
		DATA data;
		for (int i = 0; i < size; i++)
		{
			socketshort.Receive(&data, sizeof(struct SWorker));
			cout << data << endl;
		}
		this->ShowStatus(socketshort, "Find by sex succeed.", "Find by sex failed!");
	}
	else
		cout << "Not Found!" << endl;

	return true;
}
// as example of double range return multiple / one
bool CUserShort::DoFindSalary()
{
	cout << "请输入要查找的Worker" << cworker[WORKER_SALARY] << "范围(eg. 1000 2000): ";
	double sal[2];
	cin >> sal[0] >> sal[1];

	CSocketShort socketshort;
	int type = EType::REQ_FIND_SALARY;
	socketshort.Send(&type, sizeof(type));
	socketshort.Send(sal, sizeof(sal));		//send int[]
	int size = 0;
	socketshort.Receive(&size, sizeof(int));
	if (size)
	{
		cout << "\nHas Found " << size << " DATA as follows:" << endl;
		OutWorkerTitle();
		DATA data;
		for (int i = 0; i < size; i++)
		{
			socketshort.Receive(&data, sizeof(struct SWorker));
			cout << data << endl;
		}
		this->ShowStatus(socketshort, "Find by salary succeed.", "Find by salary failed!");
	}
	else
		cout << "Not Found!" << endl;

	return true;
}
// as example of int range return multiple / one
bool CUserShort::DoFindAge()
{
	cout << "请输入要查找的Worker" << cworker[WORKER_AGE] << "范围(eg. 20 45): ";
	int lowhigh[2];
	cin >> lowhigh[0] >> lowhigh[1];

	CSocketShort socketshort;
	int type = EType::REQ_FIND_AGE;
	socketshort.Send(&type, sizeof(type));
	socketshort.Send(lowhigh, sizeof(lowhigh));		//send int[]
	int size = 0;
	socketshort.Receive(&size, sizeof(int));
	if (size)
	{
		cout << "\nHas Found " << size << " DATA as follows:" << endl;
		OutWorkerTitle();
		DATA data;
		for (int i = 0; i < size; i++)
		{
			socketshort.Receive(&data, sizeof(struct SWorker));
			cout << data << endl;
		}
		this->ShowStatus(socketshort, "Find by age succeed.", "Find by age failed!");
	}
	else
		cout << "Not Found!" << endl;

	return true;
}

bool CUserShort::DoFindPhone()
{
	return this->ExDoFindChars(cworker[WORKER_PHONE], EType::REQ_FIND_PHONE, "phone");
}

bool CUserShort::DoFindIdcard()
{
	return this->ExDoFindChars(cworker[WORKER_IDCARD], EType::REQ_FIND_IDCARD, "idcard");
}

bool CUserShort::DoFindHome()
{
	return this->ExDoFindChars(cworker[WORKER_HOME], EType::REQ_FIND_HOME, "home");
}

bool CUserShort::DoChangePassword()
{
	string oldpass;
	string newpass, newconf;
	cout << "请输入旧密码(# to interrupt)：";
	cin >> oldpass;
	if ('#' == oldpass.at(0))
		return false;
	if (oldpass != m_account.password)
	{
		cout << "旧密码错误！" << endl;
		return false;
	}
	cout << "请输入新密码：";
	cin >> newpass;
	cout << "请再输入新密码：";
	cin >> newconf;
	if (newpass != newconf)
	{
		cout << "两次输入的新密码不相同！" << endl;
		return false;
	}

	strcpy_s(m_account.password, newpass.c_str());
	//请求服务端修改
	CSocketShort socketshort;
	int type = EType::ADMIN_CHANGE_PASSWORD;
	socketshort.Send(&type, sizeof(type));
	socketshort.Send(&m_account, sizeof(m_account));
	this->ShowStatus(socketshort, "Account Change Password succeed.", "Account Change Password failed!");
	return true;
}

bool CUserShort::DoBrowseAccount()
{
	CSocketShort socketshort;
	int type = EType::ADMIN_BROWSE;
	socketshort.Send(&type, sizeof(type));

	int size = 0;
	socketshort.Receive(&size, sizeof(size));
	cout << "admins size = " << size << endl;
	ACCOUNT  data;
	if (size)
	{
		OutAdminTitle();
		for (int i = 0; i < size; i++)
		{
			socketshort.Receive(&data, sizeof(data));
			cout << data << " " << data.authority << endl;
		}
		this->ShowStatus(socketshort, "Account Browse succeed.", "Account Browse failed!");
		return true;
	}
	return false;
}

bool CUserShort::DoInsertAccount()
{
	list<ACCOUNT> listacc;
	listacc.clear();
	while (this->InputAccount(listacc));

	CSocketShort socketshort;
	int type = EType::ADMIN_INSERT;
	socketshort.Send(&type, sizeof(type));
	int size = (int)listacc.size();
	socketshort.Send(&size, sizeof(size));
	if (size)
	{
		for (auto& at : listacc)
			socketshort.Send(&at, sizeof(at));
		this->ShowStatus(socketshort, "Account Insert succeed.", "Account Insert failure!");
		return true;
	}
	return false;
}

bool CUserShort::DoDeleteAccount()
{
	this->CinClear();
	cout << "请输入要删除的Admin" << cadmin[ADMIN_USERNAME] << ": ";
	char name[20] = { 0 };
	cin >> name;
	if (this->FindAccount(name))
	{
		this->CinClear();
		cout << "确定要删除吗？(1=Y/0=N): ";
		char sure;
		cin >> sure;
		if ('1' != sure)
			return false;	//由客户端判断执不执行协议
							// 消息传送
		CSocketShort socketshort;
		int type = EType::ADMIN_DELETE;
		socketshort.Send(&type, sizeof(type));
		socketshort.Send(&name, sizeof(name));
		this->ShowStatus(socketshort, "Account Delete succeed.", "Account Delete failure!");

		this->CinClear();
		cout << "要继续删除吗？(0 to over OR any key): ";
		char over;
		cin >> over;
		if ('0' == over)
			return false;
		return true;
	}
	return false;
}

bool CUserShort::DoModifyAccount()
{
	this->CinClear();
	cout << "\n修改 Admin Account ('*'保留)" << endl;
	cout << "请输入要修改的Admin" << cadmin[ADMIN_USERNAME] << ": ";
	char name[20] = { 0 };
	cin >> name;
	ACCOUNT data;
	if (FindAccount(name, true, &data))
	{
		for (int index = 0; index < SAdmin_SIZE; index++)
		{
			if (EAdmin::ADMIN_AUTHORITY == index)
				cout << "新的" << cadmin[index] << " (1-高级/0-普通): ";
			else
				cout << "新的" << cadmin[index] << ": ";
			this->ModifyAccount(data, index);						//不支持空格间隔！
		}

		cout << "\nNew Admin Account as follows: " << endl;
		OutAdminTitle();
		cout << data << endl;
		this->CinClear();
		cout << "确定要修改吗？(1=Y/0=N): ";
		char sure;
		cin >> sure;
		if ('1' != sure)
			return false;

		CSocketShort socketshort;
		int type = EType::ADMIN_MODIFY;
		socketshort.Send(&type, sizeof(type));
		socketshort.Send(name, sizeof(name));	//原始数据工号
		socketshort.Send(&data, sizeof(data));		//新的数据
		this->ShowStatus(socketshort, "Modify succeed.", "Modify failed!");

		this->CinClear();
		cout << "要继续修改吗？(0 to over OR any key): ";
		char over;
		cin >> over;
		if ('0' == over)
			return false;
	}
	else
		return false;
	return true;
}

bool CUserShort::DoFindinAccount()
{
	this->CinClear();
	cout << "请输入要查找的Admin" << cadmin[ADMIN_USERNAME] << ": ";
	char name[20] = { 0 };
	cin >> name;
	return this->FindAccount(name);
}

bool CUserShort::DoSortAccount(int serial)
{
	wcout << "serial = " << serial << endl;
	function<bool(ACCOUNT&, ACCOUNT&)> func[2];	//保存lambda函数
	func[0] = [](ACCOUNT& data1, ACCOUNT& data2)->bool {return strcmp(data1.username, data2.username) < 0; };
	func[1] = [](ACCOUNT& data1, ACCOUNT& data2)->bool {return data1.authority > data2.authority; };

	CSocketShort socketshort;
	int type = EType::ADMIN_SORT;
	socketshort.Send(&type, sizeof(type));

	int size = 0;
	socketshort.Receive(&size, sizeof(size));
	cout << "admins size = " << size << endl;
	if (size)
	{
		vector<ACCOUNT> vecdata;
		vecdata.clear();
		ACCOUNT data;
		for (int s = 0; s < size; s++)
		{
			socketshort.Receive(&data, sizeof(data));
			vecdata.push_back(data);
		}

		// 选择排序 表外排序：索引下标 ?不大能行的通
		//int* pOrder = new int[size];
		//for (int index = 0; index < size; index++)
		//	pOrder[index] = index;

		int i, j, m;
		for (i = 0; i < size - 1; i++)
		{
			m = i;
			for (j = i + 1; j < size; j++)
				if (func[serial](vecdata.at(j), vecdata.at(m)))
					//if(vecdata.at(j).authority > vecdata.at(m).authority)
					//if(strcmp(vecdata.at(j).username, vecdata.at(m).username) < 0)
					m = j;
			if (m != i)
			{
				//int temp = pOrder[m]; pOrder[m] = pOrder[i]; pOrder[i] = temp;
				ACCOUNT data = vecdata[m]; vecdata[m] = vecdata[i]; vecdata[i] = data;
			}
		}
		// 打印输出
		OutAdminTitle();
		for (auto& at : vecdata)
			cout << at << endl;
		//for (int k = 0; k < size; k++)
		//	wcout << pOrder[k] << " ";
		//wcout << endl;

		//for (int t = 0; t < size; t++)
		//	cout << vecdata.at(pOrder[t]) << " " << vecdata.at(pOrder[t]).authority << endl;
		//delete[]pOrder;
		this->ShowStatus(socketshort, "Sort ACCOUNT succeed.", "Sort ACCOUNT failed!");	//!再次强调，消息要对等
	}
	else
		cout << "ACCOUNT is empty!" << endl;
	return false;
}

bool CUserShort::InputData(vector<DATA>& vecdata)
{
	DATA data;
	this->CinClear();
	cout << "请输入Worker的相关信息：\n";
	cout << cworker[WORKER_NUMBER] << ": ";
	cin >> data.number;
	if (this->FindData(data.number, false))
	{
		cout << "[number = " << data.number << "] has existed! Please retry." << endl;
		return true;
	}
	cout << cworker[WORKER_NAME] << "(# to interrupt): ";
	cin >> data.name;
	if ('#' == data.name[0])
		return false;
	cout << cworker[WORKER_SEX] << " (1/0): ";
	char sex;
	cin >> sex;
	data.sex = ('1' == sex) ? true : false;
	cout << cworker[WORKER_SALARY] << ": ";
	cin >> data.salary;
	// ...
	cout << cworker[WORKER_AGE] << ": ";
	cin >> data.age;
	cout << cworker[WORKER_PHONE] << "(# to interrupt): ";
	cin >> data.phone;
	if ('#' == data.phone[0])
		return false;
	cout << cworker[WORKER_IDCARD] << "(# to interrupt): ";
	cin >> data.idcard;
	if ('#' == data.idcard[0])
		return false;
	this->CinClear();
	cout << cworker[WORKER_HOME] << "(# to interrupt): ";
	cin.getline(data.home, 50, '\n');
	if ('#' == data.home[0])
		return false;

	cout << "\nTo insert as follows: " << endl;
	//cout << cworker[WORKER_NUMBER] << "\t" << cworker[WORKER_NAME] << "\t" << cworker[WORKER_SEX] << endl;
	OutWorkerTitle();
	cout << data << endl;
	this->CinClear();
	cout << "确定要添加吗？(1=Y/0=N): ";
	char sure;
	cin >> sure;
	if ('1' != sure)
		return false;

	vecdata.push_back(data);

	this->CinClear();
	cout << "要继续添加吗？(0 to over OR any key): ";
	char over;
	cin >> over;
	if ('0' == over)
		return false;

	return true;
}

bool CUserShort::InputAccount(list<ACCOUNT>& listacc)
{
	ACCOUNT data;
	this->CinClear();
	cout << "请输入Admin的相关信息(# to interrupt)：\n";
	cout << cadmin[ADMIN_USERNAME] << ": ";
	cin >> data.username;
	if ('#' == data.username[0])
		return false;
	// 判断 用户名 是否存在，保持唯一性！
	if (this->FindAccount(data.username, false))
	{
		cout << "[username = " << data.username << "] has existed! Please retry." << endl;
		return true;
	}
	cout << cadmin[ADMIN_PASSWORD] << "  : ";
	cin >> data.password;
	if ('#' == data.password[0])
		return false;
	cout << cadmin[ADMIN_AUTHORITY] << " (1-advanced/0-normal): ";
	int au = 0;
	cin >> au;
	if (1 == au)
		data.authority = 1;
	else
		data.authority = 0;

	cout << "\nTo account insert as follows: " << endl;
	OutAdminTitle();
	cout << data << endl;
	this->CinClear();
	cout << "确定要添加吗？(1=Y/0=N): ";
	char sure;
	cin >> sure;
	if ('1' != sure)
		return false;

	listacc.push_back(data);

	this->CinClear();
	cout << "要继续添加吗？(0 to over OR any key): ";
	char over;
	cin >> over;
	if ('0' == over)
		return false;

	return true;
}

void CUserShort::ModifyData(DATA& data, int field)
{
	string str;
	str.clear();
	cin >> str;
	if ('*' == str.at(0))		//保留
		;
	else if ('#' == str.at(0))	//清空
	{
		switch (field)
		{
		case EWorker::WORKER_NUMBER: data.number = 0; break;
		case EWorker::WORKER_NAME: memset(data.name, 0, sizeof(data.name)); break;
		case EWorker::WORKER_SEX: data.sex = false; break;
		case EWorker::WORKER_SALARY: data.salary = 0; break;

		case EWorker::WORKER_AGE: data.age = 0; break;
		case EWorker::WORKER_PHONE: memset(data.phone, 0, sizeof(data.phone)); break;
		case EWorker::WORKER_IDCARD: memset(data.idcard, 0, sizeof(data.idcard)); break;
		case EWorker::WORKER_HOME: memset(data.home, 0, sizeof(data.home)); break;
		default:
			break;
		}
	}
	else						//赋值
	{
		switch (field)
		{
		case EWorker::WORKER_NUMBER: data.number = atoi(str.c_str()); break;
		case EWorker::WORKER_NAME: strcpy_s(data.name, sizeof(data.name), str.c_str()); break;
		case EWorker::WORKER_SEX: data.sex = ("1" == str ? true : false); break;
		case EWorker::WORKER_SALARY: data.salary = atof(str.c_str()); break;

		case EWorker::WORKER_AGE: data.age = atoi(str.c_str()); break;
		case EWorker::WORKER_PHONE: strcpy_s(data.phone, sizeof(data.phone), str.c_str()); break;
		case EWorker::WORKER_IDCARD: strcpy_s(data.idcard, sizeof(data.idcard), str.c_str()); break;
		case EWorker::WORKER_HOME: strcpy_s(data.home, sizeof(data.home), str.c_str()); break;
		default:
			break;
		}
	}
}

void CUserShort::ModifyAccount(ACCOUNT & data, int field)
{
	string str;
	str.clear();
	cin >> str;
	int au = 0;
	if ('*' == str.at(0))		//保留
		;
	else						//赋值
	{
		switch (field)
		{
		case EAdmin::ADMIN_USERNAME: strcpy_s(data.username, sizeof(data.username), str.c_str()); break;
		case EAdmin::ADMIN_PASSWORD: strcpy_s(data.password, sizeof(data.password), str.c_str()); break;
		case EAdmin::ADMIN_AUTHORITY:
			au = atoi(str.c_str());
			if (1 == au) data.authority = 1;
			else data.authority = 0;
			break;
		default:
			break;
		}
	}
}

bool CUserShort::FindData(int number, bool show, PDATA out_data)
{
	CSocketShort socketshort;
	//int type = EType::REQ_FINDIN;
	int type = EType::REQ_FIND_NUMBER;
	socketshort.Send(&type, sizeof(type));

	socketshort.Send(&number, sizeof(number));	//send int
	int find = 0;
	socketshort.Receive(&find, sizeof(int));		//recv int
	DATA data;
	if (show)
	{
		if (find)
		{
			cout << "\nHas Found as follows:" << endl;
			socketshort.Receive(&data, sizeof(struct SWorker));
			//cout << cworker[WORKER_NUMBER] << "\t" << cworker[WORKER_NAME] << "\t" << cworker[WORKER_SEX] << endl;
			OutWorkerTitle();
			cout << data << endl;
			if (out_data)
				*out_data = data;
		}
		else
			cout << "Not Found!" << endl;
	}
	else
	{
		if (find)
		{
			socketshort.Receive(&data, sizeof(struct SWorker));
			//cout << cworker[WORKER_NUMBER] << "\t" << cworker[WORKER_NAME] << "\t" << cworker[WORKER_SEX] << endl;
			if (out_data)
				*out_data = data;
		}
	}
	return find;
}

bool CUserShort::FindAccount(const char* username, bool show, PACCOUNT out_acc)
{
	CSocketShort socketshort;
	int type = EType::ADMIN_FINDIN;
	socketshort.Send(&type, sizeof(type));
	socketshort.Send(username, (int)strlen(username));

	int find = 0;
	socketshort.Receive(&find, sizeof(int));
	ACCOUNT data;
	if (show)
	{
		if (find)
		{
			cout << "\nHas Found Account as follows:" << endl;
			socketshort.Receive(&data, sizeof(struct SAdmin));
			OutAdminTitle();
			cout << data << endl;
			if (out_acc)
				*out_acc = data;
		}
		else
			cout << "Not Found!" << endl;
	}
	else
	{
		if (find)
		{
			socketshort.Receive(&data, sizeof(struct SAdmin));
			if (out_acc)
				*out_acc = data;
		}
	}
	return find;
}

bool CUserShort::ExDoFindChars(const char * hint, int type, const char * status)
{
	cout << "请输入要查找的Worker" << hint << ": ";
	string strtemp;
	cin >> strtemp;

	CSocketShort socketshort;
	socketshort.Send(&type, sizeof(type));
	socketshort.Send(strtemp.c_str(), (int)strtemp.length());	//send char*/string.c_str()
	int size = 0;
	socketshort.Receive(&size, sizeof(int));
	if (size)
	{
		cout << "\nHas Found " << size << " DATA as follows:" << endl;
		OutWorkerTitle();
		DATA data;
		for (int i = 0; i < size; i++)
		{
			socketshort.Receive(&data, sizeof(struct SWorker));
			cout << data << endl;
		}
		string shows = "Find by  succeed.";
		string showf = "Find by  failed!";
		shows.insert(8, status);
		showf.insert(8, status);
		this->ShowStatus(socketshort, shows.c_str(), showf.c_str());
		//this->ShowStatus("Find by name succeed.", "Find by name failed!");
	}
	else
		cout << "Not Found!" << endl;

	return true;
}

void CUserShort::CinClear()
{
	cin.clear();
	cin.ignore(1024, '\n');
}

void CUserShort::ColorSet()
{
	cout << "设置默认的控制台前景和背景颜色。" << endl;
	cout << "\
	0 = 黑色       8 = 灰色     \n\
	1 = 蓝色       9 = 淡蓝色   \n\
	2 = 绿色       A = 淡绿色   \n\
	3 = 浅绿色     B = 淡浅绿色 \n\
	4 = 红色       C = 淡红色   \n\
	5 = 紫色       D = 淡紫色   \n\
	6 = 黄色       E = 淡黄色   \n\
	7 = 白色       F = 亮白色\n" << endl;
	char back;	//背景色代码
	char fore;	//前景色代码
	cout << "(Input '00' to see the color change.)\n";
	cout << "请输入 背景色 和 前景色 的代码（eg. fc）: ";
	cin >> back >> fore;

	// 隐藏的小彩蛋(=_=)
	if ('0' == back && '0' == fore)
	{
		//while (true)
		{
			string colorset = "0123456789ABCDEF";
			string colorcmd;
			for (auto& backcc : colorset)
				for (auto& forecc : colorset)
				{
					if (forecc != backcc)
					{
						colorcmd.clear();
						colorcmd = "color ";
						colorcmd += backcc;
						colorcmd += forecc;
						//Sleep(DWORD(1.0 / 25));
						Sleep(100);
						cout << "\r" << colorcmd << " ";
						system(colorcmd.c_str());
					}
				}
			cout << "\rdefault: color 07\n";
			system("color 07");
		}
	}
	else
	{
		string color = "color ";
		color += back;
		color += fore;
		//cout << "color = " << color << endl;
		system(color.c_str());
	}
}
