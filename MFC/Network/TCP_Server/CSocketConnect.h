#pragma once

// CSocketConnect 命令目标
// 服务端连接Socket
class CSocketConnect : public CSocket
{
public:
	CSocketConnect();
	virtual ~CSocketConnect();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


