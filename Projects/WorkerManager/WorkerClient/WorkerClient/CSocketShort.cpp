#include "CSocketShort.h"

CSocketShort::CSocketShort()
{
	// 调用父类成员函数
	if (!Create())	//TCP
		return;
	if (!Connect(ADDRESS, PORT))
		return;
}

CSocketShort::CSocketShort(const char * hostAddress, int hostPort)
{
	if (!Create())	//TCP
		return;
	if (!Connect(hostAddress, hostPort))
		return;
}


CSocketShort::~CSocketShort()
{
	Close();
}
