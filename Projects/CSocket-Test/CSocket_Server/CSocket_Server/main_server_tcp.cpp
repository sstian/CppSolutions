/*
	2018.12.10 21:29
	MFC CSocket类的测试使用：作为服务端Server，TCP连接
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
	wcout << "*** MFC CSocket Test - Server TCP ***" << endl;
	// 初始化
	AfxSocketInit();
	CSocket socketServer;	//服务端Socket对象
	// 创建
	BOOL result = socketServer.Create(PORT, SOCK_STREAM, ADDRESS);
	if (!result)
	{
		wcout << "CSocket Create is failed! Error Code: " << WSAGetLastError() << "-" << GetLastError() << endl;
		system("pause");
		return 0;
	}
	else
		wcout << "CSocket Creat is successful." << endl;
	// 监听
	result = socketServer.Listen(SOMAXCONN);
	if (!result)
	{
		wcout << "CSocket Listen is failed! Error Code: " << WSAGetLastError() << endl;
		system("pause");
		return 0;
	}
	else
		wcout << "CSocket Listen is successful." << endl;
	// 接受
	CSocket socketConnect;	//连接的Socket对象
	while (result = socketServer.Accept(socketConnect, nullptr, nullptr))
	{
		//获取连接的客户端的IP地址和端口号：
		////方法1.
		//SOCKADDR_IN addrClient;
		//int addrlen = sizeof(SOCKADDR_IN);
		//result = socketServer.Accept(socketConnect, (SOCKADDR*)&addrClient, &addrlen);
		//char* addrConn = inet_ntoa(addrClient.sin_addr);
		//u_short portConn = ntohs(addrClient.sin_port);

		// 方法2.
		CString address;
		UINT port;
		socketConnect.GetPeerName(address, port);
		if (!result)
		{
			system("pause");
			wcout << "CSocket Accept is failed! Error Code: " << WSAGetLastError() << endl;
		}
		else
		{
			wcout << "CSocket Accept is successful." << endl;
			//wcout << "Client [" << addrConn << ":" << portConn << "] connected." << endl;
			wcout << "Client [" << address.GetString() << ":" << port << "] connected." << endl;
		}
		// 接收 与 发送
		while (true)
		{
			char buf[BUFFER_SIZE];
			memset(buf, 0, BUFFER_SIZE);
			int recv = socketConnect.Receive(buf, BUFFER_SIZE, 0);
			if (recv < 0)
			{
				//wcout << "Client [" << addrConn << ":" << portConn << " has disconnected!" << endl;
				wcout << "Client [" << address.GetString() << ":" << port << " has disconnected!" << endl;

				break;
			}
			//wcout << "->Receive data from Client [" << addrConn << ":" << portConn << "]:\n" << buf << endl;
			wcout << "->Receive data from Client [" << address.GetString() << ":" << port << "]:\n" << buf << endl;

			strcat_s(buf, "[Server]");
			socketConnect.Send(buf, sizeof(buf), 0);
			//wcout << "->Send data from Client [" << addrConn << ":" << portConn << "]:\n" << buf << endl;
			wcout << "->Send data to Client [" << address.GetString() << ":" << port << "]:\n" << buf << endl;
		}
	}
	// 关闭
	socketServer.Close();

	system("pause");
	return 0;
}