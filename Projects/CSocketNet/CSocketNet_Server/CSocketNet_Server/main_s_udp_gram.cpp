/*
	2018.12.12 23:01
	自定义封装类CSocketNet实现 TCP/	UDP Socket通讯并测试
*/
#include <iostream>
#include "../../CSocketNet/CSocketNet.h"
using namespace std;

const char* LOCAL_ADDRESS = "127.0.0.1";	//本机IP地址
const int LOCAL_PORT = 8010;						//本机端口号

char address[ADDRESS_SIZE] = { 0 };	//接收目标主机IP地址
int port = 0;						//接收目标主机端口号

const int BUFFER_SIZE = 1024;		//接收数据缓冲区

int main()
{
	setlocale(LC_ALL, "chs");
	wcout << "*** CSocketNet - S UDP ***" << endl;
	CSocketNet socketS;	//服务端Socket对象
	// 创建
	int result = socketS.Create(LOCAL_PORT, SOCK_DGRAM, LOCAL_ADDRESS);
	if (!result)
	{
		wcout << "CSocket Create is failed! Error Code: " << WSAGetLastError() << "-" << GetLastError() << endl;
		system("pause");
		return 0;
	}
	else
		wcout << "CSocket Creat is successful." << endl;
	wcout << "Localhost: [" << LOCAL_ADDRESS << ":" << LOCAL_PORT << "]" << endl << endl;
	// 接收 与 发送
	while (true)
	{
		char buf[BUFFER_SIZE];
		memset(buf, 0, BUFFER_SIZE);
		int recv = socketS.ReceiveFrom(buf, BUFFER_SIZE, address, port, 0);
		//int recv = socketS.Receive(buf, BUFFER_SIZE, 0);
		wcout << "->Receive data from Socket [" << address << ":" << port << "]:\n" << buf << endl;

		strcat_s(buf, "[Host]");
		socketS.SendTo(buf, sizeof(buf), address, port, 0);
		wcout << "->Send data to Socket [" << address << ":" << port << "]:\n" << buf << endl;
	}
	socketS.Close();

	system("pause");
	return 0;
}