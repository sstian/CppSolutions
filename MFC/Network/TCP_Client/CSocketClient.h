#pragma once

// CSocketClient 命令目标

class CSocketClient : public CSocket
{
public:
	CSocketClient();
	virtual ~CSocketClient();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


