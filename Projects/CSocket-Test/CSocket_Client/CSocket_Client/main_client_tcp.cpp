/*
	2018.12.10 22:11
	MFC CSocket类的测试使用：作为客户端Client，TCP连接
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <SDKDDKVer.h>

#include <iostream>
#include <afxsock.h>
using namespace std;

LPCTSTR ADDRESS = _T("127.0.0.1");	//IP地址
const UINT PORT = 8086;				//端口号
const int BUFFER_SIZE = 1024;		//接收数据缓冲区

int main()
{
	wcout << "*** MFC CSocket Test - Client TCP ***" << endl;
	// 初始化
	AfxSocketInit();
	CSocket socketClient;	//客户端Socket对象
	// 创建
	BOOL result = socketClient.Create(0, SOCK_STREAM, 0);
	if (!result)
	{
		wcout << "CSocket Create is failed! Error Code: " << WSAGetLastError() << "-" << GetLastError() << endl;
		system("pause");
		return 0;
	}
	else
		wcout << "CSocket Creat is successful." << endl;
	// 连接
	result = socketClient.Connect(ADDRESS, PORT);
	if (!result)
	{
		wcout << "CSocket Connect is failed! Error Code: " << WSAGetLastError() << endl;
		system("pause");
		return 0;
	}
	else
		wcout << "CSocket Connect is successful." << endl;
	//连接为其自身分配的IP地址和端口号：
	////方法1.
	//SOCKADDR_IN addrClient;	
	//int addrlen = sizeof(SOCKADDR_IN);
	//getsockname(socketClient, (SOCKADDR*)&addrClient, &addrlen);
	//char* addrConn = inet_ntoa(addrClient.sin_addr);
	//u_short portConn = ntohs(addrClient.sin_port);
	//wcout << "Localhost: ["<< addrConn << ":" << portConn << "]" << endl;
	
	//方法2.
	CString local_address;
	UINT local_port;
	socketClient.GetSockName(local_address, local_port);
	wcout << "Localhost: [" << local_address.GetString() << ":" << local_port << "]" << endl;
	// 发送 与 接收
	while (true)
	{
		char buf[BUFFER_SIZE];	// = "123456790123456790123467901234567901234657890";
		memset(buf, 0, BUFFER_SIZE);
		wcout << "\nInput some message to send:" << endl;
		cin >> buf;
		socketClient.Send(buf, sizeof(buf), 0);
		wcout << "<-Send data to Server [" << ADDRESS << ":" << PORT << "]:\n" << buf << endl;

		memset(buf, 0, BUFFER_SIZE);
		socketClient.Receive(buf, BUFFER_SIZE, 0);
		wcout << "<-Receive data from Server [" << ADDRESS << ":" << PORT << "]:\n" << buf << endl;
	}
	// 关闭
	socketClient.Close();

	system("pause");
	return 0;
}

/***
// 获取连接的自身（如：客户端）的Socket
int getsockname(
_In_ SOCKET s,
_Out_writes_bytes_to_(*namelen,*namelen) struct sockaddr FAR * name,
_Inout_ int FAR * namelen
);
// 获取连接的对方（如：服务端）的Socket
int getpeername(
_In_ SOCKET s,
_Out_writes_bytes_to_(*namelen,*namelen) struct sockaddr FAR * name,
_Inout_ int FAR * namelen
);

ReceiveFrom() = Receive() + GetPeerName()
*/