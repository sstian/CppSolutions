/*
	2018.12.12 23:10
	自定义封装类CSocketNet实现 TCP/	UDP Socket通讯并测试
*/

#include <iostream>
#include "../../CSocketNet/CSocketNet.h"
using namespace std;

const char* LOCAL_ADDRESS = "127.0.0.1";			//本机IP地址
const int LOCAL_PORT = 8011;						//本机端口号

const char* HOST_ADDRESS = "127.0.0.1";			//目标主机IP地址
const int HOST_PORT = 8010;						//目标主机端口号

char address[ADDRESS_SIZE] = { 0 };	//接收目标主机IP地址
int port = 0;						//接收目标主机端口号

const int BUFFER_SIZE = 1024;		//接收数据缓冲区

int main()
{
	setlocale(LC_ALL, "chs");
	wcout << "*** CSocketNet - C UDP ***" << endl;
	CSocketNet socketC;	//Socket对象
	// 创建
	int result = socketC.Create(LOCAL_PORT, SOCK_DGRAM, LOCAL_ADDRESS);
	if (!result)
	{
		wcout << "CSocket Create is failed! Error Code: " << WSAGetLastError() << "-" << GetLastError() << endl;
		system("pause");
		return 0;
	}
	else
		wcout << "CSocket Creat is successful." << endl;
	wcout << "Localhost: [" << LOCAL_ADDRESS << ":" << LOCAL_PORT << "]" << endl;
	// 发送 与 接收
	while (true)
	{
		char buf[BUFFER_SIZE];	// = "123456790123456790123467901234567901234657890";
		memset(buf, 0, BUFFER_SIZE);
		wcout << "\nInput some message to send (with # to end):" << endl;
		cin >> buf;
		if (buf[0] == '#')
			break;
		socketC.SendTo(buf, sizeof(buf), HOST_ADDRESS, HOST_PORT, 0);
		wcout << "<-Send data to Host [" << HOST_ADDRESS << ":" << HOST_PORT << "]:\n" << buf << endl;

		memset(buf, 0, BUFFER_SIZE);
		int recv = socketC.ReceiveFrom(buf, BUFFER_SIZE, address, port, 0);
		wcout << "->Receive data from Host [" << address << ":" << port << "]:\n" << buf << endl;
	}
	socketC.Close();

	system("pause");
	return 0;
}