#include "CNetwork.h"

CNetwork::CNetwork()
{
	//m_socketnet.Create(PORT, SOCK_STREAM, ADDRESS);
	m_mapnet.clear();
}


CNetwork::~CNetwork()
{
	m_mapnet.clear();
}

void CNetwork::ShowLog(CSocketNet & rsocket, const char * info)
{
	rsocket.Send(&SUCCESS, sizeof(int));		//发送操作成功的好消息

	// 方式1. vector
	//for (auto& at : m_vecnet)					//记录操作日志
	//	if (rsocket == at.socketConnect)
	//	{
	//		cout << "Client [" << at.addrConn << ":" << at.portConn << "] " << info << endl;
	//		break;
	//	}

	// 方式2. tree-map
	struct SNet net = m_mapnet[rsocket.getSocket()];
	cout << "Client [" << net.addrConn << ":" << net.portConn << "] " << info << endl;
}
