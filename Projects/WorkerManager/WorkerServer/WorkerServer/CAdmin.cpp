#include "CAdmin.h"

CAdmin::CAdmin()
{
	m_listacc.clear();
}


CAdmin::~CAdmin()
{
	m_listacc.clear();
}

bool CAdmin::OnLogin(CSocketNet & rsocket)
{
	ACCOUNT data;
	rsocket.Receive(&data, sizeof(data));
	
	// 搜索账户
	for (auto& at : m_listacc)
		if (!strcmp(at.username, data.username) && !strcmp(at.password, data.password))
		{
			data.authority = at.authority;
			stringstream stream;
			stream << data.username << " has logined.";
			ShowLog(rsocket, stream.str().c_str());
			rsocket.Send(&data.authority, sizeof(data.authority));
			return true;
		}
	rsocket.Send(&NOT_FOUND, sizeof(int));
	return false;
}

bool CAdmin::OnBrowse(CSocketNet & rsocket)
{
	int size = (int)m_listacc.size();
	rsocket.Send(&size, sizeof(size));		//先发送数据总数
	if (size)
	{
		for_each(m_listacc.begin(), m_listacc.end(), [&](auto& in)->void {rsocket.Send(&in, sizeof(in)); });
		stringstream stream;
		stream << "has browsed " << size << " ACCOUNT.";
		ShowLog(rsocket, stream.str().c_str());
		return true;
	}
	return false;
}

bool CAdmin::OnInsert(CSocketNet & rsocket)
{
	int size;
	rsocket.Receive(&size, sizeof(size));
	if (size)
	{
		ACCOUNT data;
		for (int i = 0; i < size; i++)
		{
			rsocket.Receive(&data, sizeof(data));	//!需要使用传递过来建立连接的rsocket进行Send()，用m_socketnet肯定会未连接，尴尬ing
			m_listacc.push_back(data);
		}
		stringstream stream;
		stream << "has inserted " << size << " ACCOUNT.";
		ShowLog(rsocket, stream.str().c_str());
		return true;
	}
	return false;
}

bool CAdmin::OnDelete(CSocketNet & rsocket)
{
	char name[20] = { 0 };
	rsocket.Receive(&name, sizeof(name));

	list<ACCOUNT>::iterator it;
	for (it = m_listacc.begin(); it != m_listacc.end(); it++)
	{
		if (!strcmp(name, it->username))
		{
			m_listacc.erase(it);
			ShowLog(rsocket, "has deleted a DATA.");
			return true;				//break;		//！删完就要退出，见好就收，不然后面乱码，程序崩溃
		}
	}
	rsocket.Send(&FAILURE, sizeof(int));				//发送操作失败的消息
	return false;
}

bool CAdmin::OnModify(CSocketNet & rsocket)
{
	char name[20] = { 0 };
	rsocket.Receive(&name, sizeof(name));
	ACCOUNT data;
	rsocket.Receive(&data, sizeof(data));

	for (auto& at : m_listacc)
		if (!strcmp(name, at.username))
		{
			at = data;
			ShowLog(rsocket, "has modified a ACCOUNT.");
			return true;
		}
	rsocket.Send(&NOT_FOUND, sizeof(int));
	return false;
}

bool CAdmin::OnFindin(CSocketNet & rsocket)
{
	char name[20] = { 0 };
	//memset(name, 0, sizeof(name));
	rsocket.Receive(&name, sizeof(name));

	for (auto& at : m_listacc)
		if (!strcmp(name, at.username))
		{
			ShowLog(rsocket, "has found the ACCOUNT by username.");
			rsocket.Send(&at, sizeof(struct SAdmin));
			return true;
		}
	rsocket.Send(&NOT_FOUND, sizeof(int));
	return false;
}

bool CAdmin::OnSort(CSocketNet & rsocket)
{
	// 发送过去全部数据，在客户端排序
	int size = (int)m_listacc.size();
	rsocket.Send(&size, sizeof(size));
	if (size)
	{
		for (auto& at : m_listacc)
			rsocket.Send(&at, sizeof(at));
		ShowLog(rsocket, "has been sent all ACCOUNT as sort.");
	}
	return true;
}

bool CAdmin::OnChangePassword(CSocketNet & rsocket)
{
	ACCOUNT data;
	rsocket.Receive(&data, sizeof(data));

	for (auto& at : m_listacc)
	{
		if (!strcmp(at.username, data.username))
		{
			strcpy_s(at.password, data.password);
			ShowLog(rsocket, "has changed password of the ACCOUNT.");
			return true;
		}
	}
	rsocket.Send(&NOT_FOUND, sizeof(int));
	return false;
}

bool CAdmin::LoadFile()
{
	// 读取文件
	ifstream infile;
	infile.open("admins.dat", ios::in | ios::binary);
	if (!infile)
	{
		//cout << "Loading... Open file failed!" << endl;
		//system("pause");
		return false;
	}
	ACCOUNT data;
	while (infile.read((char*)&data, sizeof(data)))
	{
		m_listacc.push_back(data);
	}
	infile.close();
	return true;
}

void CAdmin::SaveFile()
{
	//	写入文件
	ofstream outfile;
	outfile.open("admins.dat", ios::out | ios::binary);
	if (outfile.fail())
	{
		cout << "Saving... Open file failed!" << endl;
		system("pause");
	}
	for (auto& at : m_listacc)
		outfile.write((char*)&at, sizeof(at));
	outfile.close();
}

