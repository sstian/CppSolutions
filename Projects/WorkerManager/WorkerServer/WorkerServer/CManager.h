#pragma once
#include "CWorker.h"
#include "CAdmin.h"

// 服务端管理操作类
class CManager : public CWorker, public CAdmin
{
public:
	CManager();
	virtual ~CManager();

	void Startup();
	// 接收消息协议编号，转给相应的处理函数
	bool InReceive(CSocketNet & rsocket);

	
	// 多线程
	static unsigned __stdcall ServerThread(void* arglist);

public:
	static CManager m_man;	//static函数通过static本类类型的变量调用其它非静态函数

//protected:
//	//继承的两个父类的对象，用于调用父类方法
//	CWorker m_worker;
//	CAdmin m_admin;
};

