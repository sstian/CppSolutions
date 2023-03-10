/*
	2018.12.11 13:19
	MFC CSocket类的测试使用：作为S，UDP连接
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <SDKDDKVer.h>

#include <iostream>
#include <afxsock.h>
using namespace std;

LPCTSTR LOCAL_ADDRESS = _T("127.0.0.1");	//本机IP地址
UINT LOCAL_PORT = 8010;						//本机端口号

//CString HOST_ADDRESS = _T("127.0.0.1");		//目标主机IP地址
//UINT HOST_PORT = 8011;						//目标主机端口号

CString address;	//接收目标主机IP地址
UINT port;			//接收目标主机端口号

const int BUFFER_SIZE = 1024;		//接收数据缓冲区

int main()
{
	wcout << "*** MFC CSocket Test - S UDP ***" << endl;
	// 初始化
	AfxSocketInit();
	CSocket socketS;	//服务端Socket对象
	// 创建
	BOOL result = socketS.Create(LOCAL_PORT, SOCK_DGRAM, LOCAL_ADDRESS);
	if (!result)
	{
		wcout << "CSocket Create is failed! Error Code: " << WSAGetLastError() << "-" << GetLastError() << endl;
		system("pause");
		return 0;
	}
	else
		wcout << "CSocket Creat is successful." << endl;
	// 接收 与 发送
	while (true)
	{
		char buf[BUFFER_SIZE];
		memset(buf, 0, BUFFER_SIZE);
		int recv = socketS.ReceiveFrom(buf, BUFFER_SIZE, address, port, 0);
		//int recv = socketS.Receive(buf, BUFFER_SIZE, 0);
		wcout << "->Receive data from Socket [" << address.GetString() << ":" << port << "]:\n" << buf << endl;
		
		strcat_s(buf, "[Host]");
		socketS.SendTo(buf, sizeof(buf), port, address.GetString(), 0);
		wcout << "->Send data to Socket [" << address.GetString() << ":" << port << "]:\n" << buf << endl;
	}
	socketS.Close();
	
	system("pause");
	return 0;
}