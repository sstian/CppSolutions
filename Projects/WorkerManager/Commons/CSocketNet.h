#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define ADDRESS_SIZE 20		//储存地址的内存空间大小

class CSocketNet
{
public:
	CSocketNet();
	virtual~CSocketNet();

	//返回：1-成功；0-失败
	int Create(int socketPort = 0, int socketType = SOCK_STREAM, const char* socketAddress = nullptr);
	// TCP
	int Listen(int backlog = SOMAXCONN);

	int Accept(CSocketNet& socketConn, char* addrConn = nullptr, int* portConn = nullptr);
	int Connect(const char* hostAddress, int hostPort);

	int Send(const void* buf, int buflen, int flags = 0);

	int Receive(void* buf, int buflen, int flags = 0);

	// UDP
	int SendTo(const void * buf, int buflen, const char * hostAddress, int hostPort, int flags = 0);
	int ReceiveFrom(void * buf, int buflen, char * socketAddress, int& socketPort, int flags = 0);

	int GetSockName(char* socketAddress, int& socketPort);
	int GetPeerName(char* peerAddress, int& peerPort);

	void Close();

	// map键需要
	SOCKET getSocket(void) const;
	//bool operator<(const CSocketNet & rsocket) const;

	bool operator == (const CSocketNet& rsocket) const;

protected:
	SOCKET m_socket;
};

/***
int WSAStartup(					//返回：0-成功；WSASYSNOTREADY | WSAVERNOTSUPPORTED WSAEINVAL - 错误
_In_ WORD wVersionRequested,
_Out_ LPWSADATA lpWSAData
);

SOCKET socket(					//返回：SOCKET-成功；INVALID_SOCKET-失败，可使用WSAGetLastError()获得错误代码
_In_ int af,
_In_ int type,
_In_ int protocol
);

int bind(						//返回：0-无错误；SOCKET_ERROR == -1-错误，可使用WSAGetLastError()获得错误代码
_In_ SOCKET s,
_In_reads_bytes_(namelen) const struct sockaddr FAR * name,
_In_ int namelen
);

int listen(						//返回：0-无错误；SOCKET_ERROR == -1-错误，可使用WSAGetLastError()获得错误代码
_In_ SOCKET s,
_In_ int backlog
);

SOCKET accept(					//返回：SOCKET-成功；INVALID_SOCKET-失败，可使用WSAGetLastError()获得错误代码
_In_ SOCKET s,
_Out_writes_bytes_opt_(*addrlen) struct sockaddr FAR * addr,
_Inout_opt_ int FAR * addrlen
);

int connect(					//返回：0-无错误；SOCKET_ERROR-错误，可使用WSAGetLastError()获得错误代码
_In_ SOCKET s,
_In_reads_bytes_(namelen) const struct sockaddr FAR * name,
_In_ int namelen
);

int send(						//返回：len-无错误；SOCKET_ERROR-错误，可使用WSAGetLastError()获得错误代码
_In_ SOCKET s,
_In_reads_bytes_(len) const char FAR * buf,
_In_ int len,
_In_ int flags
);

int recv(						//返回：len-无错误；SOCKET_ERROR-错误；0-在等待协议接收数据时网络中断
_In_ SOCKET s,
_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR * buf,
_In_ int len,
_In_ int flags
);

int sendto(						//返回：len-成功；SOCKET_ERROR-失败
_In_ SOCKET s,
_In_reads_bytes_(len) const char FAR * buf,
_In_ int len,
_In_ int flags,
_In_reads_bytes_(tolen) const struct sockaddr FAR * to,
_In_ int tolen
);

int recvfrom(				//返回：len-成功；SOCKET_ERROR-失败
_In_ SOCKET s,
_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR * buf,
_In_ int len,
_In_ int flags,
_Out_writes_bytes_to_opt_(*fromlen, *fromlen) struct sockaddr FAR * from,
_Inout_opt_ int FAR * fromlen
);

int getsockname(		//返回：0-无错误；SOCKET_ERROR-错误，可使用WSAGetLastError()获得错误代码
_In_ SOCKET s,
_Out_writes_bytes_to_(*namelen,*namelen) struct sockaddr FAR * name,
_Inout_ int FAR * namelen
);

int getpeername(		//返回：0-无错误；SOCKET_ERROR-错误，可使用WSAGetLastError()获得错误代码
_In_ SOCKET s,
_Out_writes_bytes_to_(*namelen,*namelen) struct sockaddr FAR * name,
_Inout_ int FAR * namelen
);
*/

