#pragma once
#include "../../Commons/type.h"

using mapnet = map<SOCKET, SNet>;

// 共有需要继承的基类，建立Socket
class CNetwork
{
public:
	CNetwork();
	virtual ~CNetwork();

	mapnet& getmapnet() { return m_mapnet; }

	// 显示操作记录
	void ShowLog(CSocketNet& rsocket, const char* info);

protected:
	CSocketNet m_socketnet;	//服务端监听的Socket
	//vector<SNetwork> m_vecnet;
	mapnet m_mapnet;
};

