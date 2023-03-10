#pragma once
#include "CNetwork.h"

// 管理员类
// !分离类成员的声明和实现才不会导致“LK2005:多重定义”的错误实现，即class的.h和.cpp文件
class CAdmin : virtual public CNetwork
{
public:
	CAdmin();
	virtual ~CAdmin();

	// 消息处理函数
	bool OnLogin(CSocketNet & rsocket);
	bool OnBrowse(CSocketNet & rsocket);
	bool OnInsert(CSocketNet & rsocket);
	bool OnDelete(CSocketNet & rsocket);
	bool OnModify(CSocketNet & rsocket);
	bool OnFindin(CSocketNet & rsocket);

	bool OnSort(CSocketNet & rsocket);

	bool OnChangePassword(CSocketNet & rsocket);

	bool LoadFile();
	void SaveFile();

protected:
	list<ACCOUNT> m_listacc;	//账户数据
};

