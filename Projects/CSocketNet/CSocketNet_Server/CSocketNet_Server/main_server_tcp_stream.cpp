/*
	2018.12.11 22:11 - 2018.12.13 00:00
	自定义封装类CSocketNet实现 TCP/	UDP Socket通讯并测试
*/
#include <iostream>
#include <locale>
#include "../../CSocketNet/CSocketNet.h"
using namespace std;

const char* ADDRESS = "127.0.0.1";	//IP地址
const int PORT = 8086;				//端口号
const int BUFFER_SIZE = 1024;		//接收数据缓冲区

int main()
{
	setlocale(LC_ALL, "chs");
	wcout << "*** CSocketNet - Server TCP ***" << endl;
	// 初始化
	CSocketNet socketServer;	//服务端Socket对象
	// 创建
	int result = socketServer.Create(PORT, SOCK_STREAM, ADDRESS);
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
	CSocketNet socketConnect;	//连接的Socket对象
	char addrConn[20] = { 0 };
	//string addrConn;
	int portConn = 0;
	while (true)	
	{
		//result = socketServer.Accept(socketConnect, addrConn, &portConn);
		result = socketServer.Accept(socketConnect);
		if (!result)
		{
			wcout << "CSocket Accept is failed! Error Code: " << WSAGetLastError() << endl;
			system("pause");
			return 0;
		}
		else
		{
			socketConnect.GetPeerName(addrConn, portConn);
			wcout << "CSocket Accept is successful." << endl;
			cout << "Client [" << addrConn << ":" << portConn << "] connected." << endl << endl;
		}
		// 接收 与 发送
		while (true)
		{
			char buf[BUFFER_SIZE];
			memset(buf, 0, BUFFER_SIZE);
			int recv = socketConnect.Receive(buf, BUFFER_SIZE, 0);
			if (recv <= 0)
			{
				cout << "Client [" << addrConn << ":" << portConn << "] has disconnected!" << endl;
				break;
			}
			cout << "->Receive data from Client [" << addrConn << ":" << portConn << "]:\n" << buf << endl;

			strcat_s(buf, "[Server]");
			socketConnect.Send(buf, sizeof(buf), 0);
			cout << "->Send data to Client [" << addrConn << ":" << portConn << "]:\n" << buf << endl;
		}
	}

	system("pause");
	return 0;
}