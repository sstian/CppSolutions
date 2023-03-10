#pragma once
#include "CNetwork.h"

// 员工类 用于操作
// 多重继承，共用一个m_socket，使用虚基类
class CWorker : virtual public CNetwork
{
public:
	CWorker();
	virtual ~CWorker();

	// 消息处理函数
	bool OnBrowse(CSocketNet& rsocket);
	bool OnInsert(CSocketNet& rsocket);
	bool OnDelete(CSocketNet& rsocket);
	bool OnModify(CSocketNet& rsocket);
	bool OnFindin(CSocketNet& rsocket);

	bool OnFindNumber(CSocketNet& rsocket);
	bool OnFindName(CSocketNet& rsocket);
	bool OnFindSex(CSocketNet& rsocket);
	bool OnFindSalary(CSocketNet& rsocket);
	// ...
	bool OnFindAge(CSocketNet& rsocket);
	bool OnFindPhone(CSocketNet& rsocket);
	bool OnFindIdcard(CSocketNet& rsocket);
	bool OnFindHome(CSocketNet& rsocket);

	bool OnSort(CSocketNet& rsocket);

	// 加载保存文件，以二进制的形式。程序首次运行可加个判断：先保存再加载，解决读取文件错误的问题
	bool LoadFile();
	void SaveFile();

public:
	vector<DATA> m_vecdata;		//员工数据
};

