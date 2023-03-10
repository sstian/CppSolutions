/*
	2018.12.11 22:14
	自定义封装类CSocketNet实现 TCP/	UDP Socket通讯并测试
*/
#include <iostream>
#include "../../CSocketNet/CSocketNet.h"

using namespace std;

const char* ADDRESS = "127.0.0.1";	//IP地址
const int PORT = 8086;				//端口号
const int BUFFER_SIZE = 1024;		//接收数据缓冲区

int main()
{
	wcout << "*** CSocketNet - Client TCP ***" << endl;
	// 初始化
	CSocketNet socketClient;	//客户端Socket对象
	// 创建
	int result = socketClient.Create(0, SOCK_STREAM, 0);
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

	char local_address[20];
	int local_port;
	socketClient.GetSockName(local_address, local_port);
	wcout << "Localhost: [" << local_address << ":" << local_port << "]" << endl;
	// 发送 与 接收
	while (true)
	{
		char buf[BUFFER_SIZE];	// = "123456790123456790123467901234567901234657890";
		memset(buf, 0, BUFFER_SIZE);
		wcout << "\nInput some message to send:" << endl;
		cin >> buf;
		/*int sendbytes = */socketClient.Send(buf, BUFFER_SIZE, 0);
		wcout << "<-Send data to Server [" << ADDRESS << ":" << PORT << "]:\n" << buf << endl;
		//wcout << "sendbytes = " << sendbytes << endl;

		memset(buf, 0, BUFFER_SIZE);
		/*int recvbytes = */socketClient.Receive(buf, BUFFER_SIZE, 0);
		wcout << "<-Receive data from Server [" << ADDRESS << ":" << PORT << "]:\n" << buf << endl;
		//wcout << "recvbytes = " << recvbytes << endl;
	}

	system("pause");
	return 0;
}