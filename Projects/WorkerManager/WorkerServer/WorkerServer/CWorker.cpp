#include "CWorker.h"

CWorker::CWorker()
{
	m_vecdata.clear();
}

CWorker::~CWorker()
{
	m_vecdata.clear();
}

bool CWorker::OnBrowse(CSocketNet & rsocket)
{
	int size = (int)m_vecdata.size();
	rsocket.Send(&size, sizeof(size));		//先发送数据总数
	if (size)
	{
		//// 方法1. 普通for_loop
		//DATA data;
		//for (int i = 0; i < size; i++)
		//{
		//	data = m_vecdata.at(i);
		//	rsocket.Send(&data, sizeof(data));	
		//}

		//// 方法2. 迭代器for_loop
		////DATA data2;
		//vector<DATA>::iterator it;
		//for (it = m_vecdata.begin(); it != m_vecdata.end(); it++)
		//	rsocket.Send(&*it, sizeof(*it));	//data2 = *it;

		//// 方法3. auto + 列表 for_loop
		//for (auto& at : m_vecdata)
		//	rsocket.Send(&at, sizeof(at));

		// 方法4. 正则匿名函数 + for_each loop
		//再逐个发送每条数据，消息收发要对等
		for_each(m_vecdata.begin(), m_vecdata.end(), [&](auto& in)->void {rsocket.Send(&in, sizeof(in)); });
		stringstream stream;
		stream << "has browsed " << size << " DATA.";
		ShowLog(rsocket, stream.str().c_str());
		return true;
	}
	return false;
}

bool CWorker::OnInsert(CSocketNet & rsocket)
{
	int size;
	rsocket.Receive(&size, sizeof(size));

	if (size)
	{
		DATA data;
		for (int i = 0; i < size; i++)
		{
			rsocket.Receive(&data, sizeof(data));	//!需要使用传递过来建立连接的rsocket进行Send()，用m_socketnet肯定会未连接，尴尬ing
			m_vecdata.push_back(data);
		}
		//rsocket.Send(&SUCCESS, sizeof(int));		//发送操作成功的好消息
		// 显示操作记录
		stringstream stream;
		stream << "has inserted " << size << " DATA.";
		ShowLog(rsocket, stream.str().c_str());
	}
	return true;
}

bool CWorker::OnDelete(CSocketNet & rsocket)
{
	int number;
	rsocket.Receive(&number, sizeof(number));
	//cout << "OnDelete: number = " << number << endl;
	//system("pause");
	vector<DATA>::iterator it;
	for (it = m_vecdata.begin(); it != m_vecdata.end(); it++)
	{
		//cout << *it << endl;
		if (number == it->number)
		{
			m_vecdata.erase(it);
			ShowLog(rsocket, "has deleted a DATA.");
			return true;				//break;		//！删完就要退出，见好就收，不然后面乱码，程序崩溃
		}
	}
	rsocket.Send(&FAILURE, sizeof(int));				//发送操作失败的消息
	return false;
}

bool CWorker::OnModify(CSocketNet & rsocket)
{
	int number;
	rsocket.Receive(&number, sizeof(number));
	DATA data;
	rsocket.Receive(&data, sizeof(data));

	for (auto& at : m_vecdata)
		if (number == at.number)
		{
			at = data;
			ShowLog(rsocket, "has modified a DATA.");
			return true;
		}
	return false;
}

bool CWorker::OnFindin(CSocketNet & rsocket)
{
	int number;
	rsocket.Receive(&number, sizeof(number));	//recv int

	for (auto& at : m_vecdata)
		if (number == at.number)
		{
			ShowLog(rsocket, "has found the DATA by number.");
			rsocket.Send(&at, sizeof(struct SWorker));
			return true;
		}

	rsocket.Send(&NOT_FOUND, sizeof(int));
	return false;
}

bool CWorker::OnFindNumber(CSocketNet & rsocket)
{
	return OnFindin(rsocket);
}

bool CWorker::OnFindName(CSocketNet & rsocket)
{
	char buff[BUFFER_SIZE];
	memset(buff, 0, BUFFER_SIZE);		//！即使定义了缓冲区字符串数组要将其清零
	rsocket.Receive(buff, BUFFER_SIZE);	//recv char*

	vector<DATA> vecdata;
	vecdata.clear();
	for (auto& at : m_vecdata)
	{
		if (strcmp(buff, at.name) == 0)
			vecdata.push_back(at);
	}
	int size = (int)vecdata.size();
	rsocket.Send(&size, sizeof(size));	//先发送数据数目
	if (size)
	{
		//rsocket.Send(&size, sizeof(size));	//先发送数据数目
		for (auto& av : vecdata)
			rsocket.Send(&av, sizeof(av));	//再发送各个数据
		stringstream stream;
		stream << "has found " << size << " DATA by name.";
		ShowLog(rsocket, stream.str().c_str());
	}
	//else
	//	rsocket.Send(&NOT_FOUND, sizeof(int));	//没有找到发送0，保持消息对等！
	return true;
}

bool CWorker::OnFindSex(CSocketNet & rsocket)
{
	//char buff[BUFFER_SIZE];
	//memset(buff, 0, BUFFER_SIZE);		//！即使定义了缓冲区字符串数组要将其清零
	//rsocket.Receive(buff, BUFFER_SIZE);

	bool sex;
	rsocket.Receive(&sex, sizeof(sex));	//recv bool

	vector<DATA> vecdata;
	vecdata.clear();
	for (auto& at : m_vecdata)
	{
		if (sex == at.sex)
			vecdata.push_back(at);
	}
	int size = (int)vecdata.size();
	rsocket.Send(&size, sizeof(size));	//先发送数据数目
	if (size)
	{
		for (auto& av : vecdata)
			rsocket.Send(&av, sizeof(av));	//再发送各个数据
		stringstream stream;
		stream << "has found " << size << " DATA by sex.";
		ShowLog(rsocket, stream.str().c_str());
	}
	//else
	//	rsocket.Send(&NOT_FOUND, sizeof(int));
	return true;
}

bool CWorker::OnFindSalary(CSocketNet & rsocket)
{
	double sal[2] = { 0 };					//！看来凡是接收为数组均需要清空啊
	rsocket.Receive(sal, sizeof(sal));	//recv int[]

	vector<DATA> vecdata;
	vecdata.clear();
	for (auto& at : m_vecdata)
	{
		if (at.salary >= sal[0] && at.salary <= sal[1])
			vecdata.push_back(at);
	}
	int size = (int)vecdata.size();
	rsocket.Send(&size, sizeof(size));	//先发送数据数目
	if (size)
	{
		for (auto& av : vecdata)
			rsocket.Send(&av, sizeof(av));	//再发送各个数据
		stringstream stream;
		stream << "has found " << size << " DATA by salary.";
		ShowLog(rsocket, stream.str().c_str());
	}
	//else
	//	rsocket.Send(&NOT_FOUND, sizeof(int));
	return true;
}

bool CWorker::OnFindAge(CSocketNet & rsocket)
{
	int lowhigh[2] = { 0 };
	rsocket.Receive(lowhigh, sizeof(lowhigh));	//recv int[]

	vector<DATA> vecdata;
	vecdata.clear();
	for (auto& at : m_vecdata)
	{
		if (at.age >= lowhigh[0] && at.age <= lowhigh[1])
			vecdata.push_back(at);
	}
	int size = (int)vecdata.size();
	rsocket.Send(&size, sizeof(size));	//先发送数据数目
	if (size)
	{
		for (auto& av : vecdata)
			rsocket.Send(&av, sizeof(av));	//再发送各个数据
		stringstream stream;
		stream << "has found " << size << " DATA by age.";
		ShowLog(rsocket, stream.str().c_str());
	}
	//else
	//	rsocket.Send(&NOT_FOUND, sizeof(int));
	return true;
}

bool CWorker::OnFindPhone(CSocketNet & rsocket)
{
	char buff[BUFFER_SIZE];
	memset(buff, 0, BUFFER_SIZE);
	rsocket.Receive(buff, BUFFER_SIZE);

	vector<DATA> vecdata;
	vecdata.clear();
	for (auto& at : m_vecdata)
	{
		if (strcmp(buff, at.phone) == 0)	//at.
			vecdata.push_back(at);
	}
	int size = (int)vecdata.size();
	rsocket.Send(&size, sizeof(size));	//先发送数据数目
	if (size)
	{
		for (auto& av : vecdata)
			rsocket.Send(&av, sizeof(av));	//再发送各个数据
		stringstream stream;
		stream << "has found " << size << " DATA by idcard.";
		ShowLog(rsocket, stream.str().c_str());
	}
	//else
	//	rsocket.Send(&NOT_FOUND, sizeof(int));
	return true;
}

bool CWorker::OnFindIdcard(CSocketNet & rsocket)
{
	char buff[BUFFER_SIZE];
	memset(buff, 0, BUFFER_SIZE);
	rsocket.Receive(buff, BUFFER_SIZE);

	vector<DATA> vecdata;
	vecdata.clear();
	for (auto& at : m_vecdata)
	{
		if (strcmp(buff, at.idcard) == 0)	//at.
			vecdata.push_back(at);
	}
	int size = (int)vecdata.size();
	rsocket.Send(&size, sizeof(size));	//先发送数据数目
	if (size)
	{
		for (auto& av : vecdata)
			rsocket.Send(&av, sizeof(av));	//再发送各个数据
		stringstream stream;
		stream << "has found " << size << " DATA by idcard.";
		ShowLog(rsocket, stream.str().c_str());
	}
	//else
	//	rsocket.Send(&NOT_FOUND, sizeof(int));
	return true;
}

bool CWorker::OnFindHome(CSocketNet & rsocket)
{
	char buff[BUFFER_SIZE];
	memset(buff, 0, BUFFER_SIZE);
	rsocket.Receive(buff, BUFFER_SIZE);
	string str;

	vector<DATA> vecdata;
	vecdata.clear();
	for (auto& at : m_vecdata)
	{
		if (strstr(at.home, buff))	//at. //只要存在即可
			vecdata.push_back(at);
	}
	int size = (int)vecdata.size();
	rsocket.Send(&size, sizeof(size));	//先发送数据数目
	if (size)
	{
		for (auto& av : vecdata)
			rsocket.Send(&av, sizeof(av));	//再发送各个数据
		stringstream stream;
		stream << "has found " << size << " DATA by idcard.";
		ShowLog(rsocket, stream.str().c_str());
	}
	//else
	//	rsocket.Send(&NOT_FOUND, sizeof(int));
	return true;
}

bool CWorker::OnSort(CSocketNet & rsocket)
{
	// 发送过去全部数据，在客户端排序
	int size = (int)m_vecdata.size();
	rsocket.Send(&size, sizeof(size));
	if (size)
	{
		for (auto& at : m_vecdata)
			rsocket.Send(&at, sizeof(at));
		ShowLog(rsocket, "has been sent all DATA as sort.");
	}
	//else
	//	rsocket.Send(&NOT_FOUND, sizeof(int));
	return true;
}

bool CWorker::LoadFile()
{
	// 读取文件
	ifstream infile;
	infile.open("workers.dat", ios::in | ios::binary);
	if (!infile)
	{
		//cout << "Loading... Open file failed!" << endl;
		//system("pause");
		return false;
	}
	DATA data;
	while (infile.read((char*)&data, sizeof(data)))
	{
		m_vecdata.push_back(data);
	}
	infile.close();
	return true;
}

void CWorker::SaveFile()
{
	//	写入文件
	ofstream outfile;
	outfile.open("workers.dat", ios::out | ios::binary);
	if (outfile.fail())
	{
		cout << "Saving... Open file failed!" << endl;
		system("pause");
	}
	for (auto& at : m_vecdata)
		outfile.write((char*)&at, sizeof(at));
	outfile.close();
}

