#pragma once

// CSocketListen 命令目标
// 服务端监听Socket
class CSocketListen : public CSocket
{
public:
	CSocketListen();
	virtual ~CSocketListen();
	virtual void OnAccept(int nErrorCode);
};


