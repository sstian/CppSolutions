#pragma once
#include "../../Commons/CSocketNet.h"
#include "../../Commons/type.h"

// 作为短连接的CSocketnet
class CSocketShort : public CSocketNet
{
public:
	CSocketShort();
	CSocketShort(const char* hostAddress, int hostPort);
	virtual ~CSocketShort();

//protected:
//	CSocketNet m_socketnet;
};

