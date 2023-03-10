/*
	2018.12.11 13:34
	MFC CSocket类的测试使用：作为C，UDP连接
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <SDKDDKVer.h>

#include <iostream>
#include <afxsock.h>
using namespace std;

LPCTSTR LOCAL_ADDRESS = _T("127.0.0.1");	//本机IP地址
UINT LOCAL_PORT = 8011;						//本机端口号

CString HOST_ADDRESS = _T("127.0.0.1");		//目标主机IP地址
UINT HOST_PORT = 8010;						//目标主机端口号

CString address;	//接收目标主机IP地址
UINT port;			//接收目标主机端口号

const int BUFFER_SIZE = 1024;		//接收数据缓冲区

int main()
{
	wcout << "*** MFC CSocket Test - C UDP ***" << endl;
	// 初始化
	AfxSocketInit();
	CSocket socketC;	//服务端Socket对象
	// 创建
	BOOL result = socketC.Create(LOCAL_PORT, SOCK_DGRAM, LOCAL_ADDRESS);
	if (!result)
	{
		wcout << "CSocket Create is failed! Error Code: " << WSAGetLastError() << "-" << GetLastError() << endl;
		system("pause");
		return 0;
	}
	else
		wcout << "CSocket Creat is successful." << endl;
	// 发送 与 接收
	while (true)
	{
		char buf[BUFFER_SIZE];	// = "123456790123456790123467901234567901234657890";
		memset(buf, 0, BUFFER_SIZE);
		wcout << "\nInput some message to send (with # to end):" << endl;
		cin >> buf;
		if (buf[0] == '#')
			break;
		socketC.SendTo(buf, sizeof(buf), HOST_PORT, HOST_ADDRESS, 0);
		wcout << "<-Send data to Host [" << HOST_ADDRESS.GetString() << ":" << HOST_PORT << "]:\n" << buf << endl;

		memset(buf, 0, BUFFER_SIZE);
		int recv = socketC.ReceiveFrom(buf, BUFFER_SIZE, address, port, 0);
		wcout << "->Receive data from Host [" << address.GetString() << ":" << port << "]:\n" << buf << endl;
	}
	socketC.Close();

	system("pause");
	return 0;
}