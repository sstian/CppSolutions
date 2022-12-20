/*
	2018.12.11 15:19 - 21:02
	�Զ���ʵ�֣������ֽ���תΪ�����ֽ��򣨴�ˣ� host to network u_short/u_long��inet��ַת��
ԭ������Э��涨���յ��õ�һ���ֽ��Ǹ��ֽڣ���ŵ��͵�ַ�����Է���ʱ������ȥ�͵�ַȡ���ݵĸ��ֽڣ�����ˡ�
    "���"��"С��"��ʾ���ֽ�ֵ����һ�˴洢�ڸ�ֵ����ʼ��ַ����
С�˴洢����ʼ��ַ��,����С���ֽ���;��˴洢����ʼ��ַ��,���Ǵ���ֽ���
����˵: 

1.С�˷�(Little-Endian)���ǵ�λ�ֽ��ŷ����ڴ�ĵ͵�ַ��(����ֵ����ʼ��ַ)����λ�ֽ��ŷ����ڴ�ĸߵ�ַ��; 
2.��˷�(Big-Endian)���Ǹ�λ�ֽ��ŷ����ڴ�ĵ͵�ַ��(����ֵ����ʼ��ַ),��λ�ֽ��ŷ����ڴ�ĸߵ�ַ�ˡ�

*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <locale>
#include <string>
#include <WinSock2.h>

using namespace std;

// Host �����壬ռ��4���ֽ�
union Host
{
	ULONG lhost;
	USHORT shost[2];
	UCHAR chost[4];
};
// �������� UCHAR = unsigned char
void swap_t(UCHAR& cone, UCHAR& ctwo)
{
	UCHAR temp = cone;
	cone = ctwo;
	ctwo = temp;
}
// host to network: ULONG = unsigned long
ULONG htonl_t(ULONG in_lhost)
{
	//union Host host;
	//host.lhost = in_lhost;
	union Host host = { in_lhost };
	swap_t(host.chost[0], host.chost[3]);
	swap_t(host.chost[1], host.chost[2]);
	return host.lhost;
}
// host to network: USHORT = unsigned short
USHORT htons_t(USHORT in_shost)
{
	//union Host host;
	//host.shost[0] = in_shost;
	union Host host = { in_shost };
	swap_t(host.chost[0], host.chost[1]);
	return host.shost[0];
}
// internet address to unsigned long: e.g. "192.168.1.100"
unsigned long inet_addr_t(const char* cp)
{
	unsigned long lhost = 0;
	char* plhost = (char*)&lhost;
	
	char str[100] = { 0 };			//�����Ҫ�ָ���ַ������ַ�������
	char seps[] = ".";				//��ŷָ������磺,.!@#$%%^&*()\t\n��//���߶���Ϊָ�� const char* seps = ".";
	char* next_token = nullptr;		//��ű��ָ�����ַ���
	char* token = nullptr;
	strcpy_s(str, cp);
	token = strtok_s(str, seps, &next_token);
	while (token)
	{
		*plhost++ = atoi(token);
		token = strtok_s(nullptr, seps, &next_token);
	}

	return lhost;
}
// internet net to alpha
char* inet_ntoa_t(struct in_addr in)
{
	static char sz[100];
	sprintf_s(sz, "%d.%d.%d.%d", 
		in.S_un.S_un_b.s_b1, in.S_un.S_un_b.s_b2, in.S_un.S_un_b.s_b3, in.S_un.S_un_b.s_b4);
	return sz;
}

// �������ַ����洢ת��
// �������洢Ϊ4���ֽ�
void SetAbsoluteInteger(char bytes[], int size, int startpos, int value)
{
	if ( size >= startpos + 4)
	{
		bytes[startpos] = (char)(value >> 24 & 0xFF);
		bytes[startpos + 1] = (char)(value >> 16 & 0xFF);
		bytes[startpos + 2] = (char)(value >> 8 & 0xFF);
		bytes[startpos + 3] = (char)(value & 0xFF);
	}
}
// �洢�ַ���
void SetAbsoluteString(char bytes[], int size, int startpos, const char* value, int length)
{
	if (size >= startpos + length)
	{
		for (int i = 0; i < length; i++)
		{
			if (value != nullptr && i < strlen(value))
				bytes[startpos + i] = value[i];
			else
				bytes[startpos + i] = 0;
		}
	}
}
// ��ȡ��������
int GetAbsoluteInteger(char bytes[], int size, int startpos)
{
	int value = -1;
	if (size >= startpos + 4) 
	{
		int first = 0xFF & bytes[startpos];
		int second = 0xFF & bytes[startpos + 1];
		int third = 0xFF & bytes[startpos + 2];
		int fourth = 0xFF & bytes[startpos + 3];

		value = first << 24 | second << 16 | third << 8 | fourth;
	}
	return value;
}
// ��ȡ�ַ���
string GetAbsoluteString(char bytes[], int size, int startpos, int length)
{
	string value;
	if (size >= startpos + length)
	{
		for (int i = 0; (i < length) && (bytes[startpos + i] != 0); i++)
			value += bytes[startpos + i];
	}
	return value;
}

int main()
{
	setlocale(LC_ALL, "chs");
	wcout << "*** host to net & inet - Transfer ***" << endl;

	USHORT shost = 0x1234;
	ULONG lhost = 0x12345678;
	wcout << hex << showbase;
	wcout << "USHORT shost = " << shost << endl;
	wcout << "htons_t(shost) = " << htons_t(shost) << endl;
	wcout << "ULONG lhost = " << lhost << endl;
	wcout << "htonl_t(lhost) = " << htonl_t(lhost) << endl;

	const char* cp = "192.168.1.100";
	wcout << dec << endl;
	wcout << "const char* cp = " << cp << endl;
	wcout << "inet_addr_t(cp) = " << inet_addr_t(cp) << endl;
	// �ԱȲ���
	union Host host;
	host.chost[0] = 192;
	host.chost[1] = 168;
	host.chost[2] = 1;
	host.chost[3] = 100;
	wcout << "host.lhost = " << host.lhost << endl << endl;

	in_addr in{ 192, 168, 1, 100 };
	inet_ntoa_t(in);
	wcout << "in_addr in = "
		<< in.S_un.S_un_b.s_b1 << " " << in.S_un.S_un_b.s_b2 << " "
		<< in.S_un.S_un_b.s_b3 << " " << in.S_un.S_un_b.s_b4 << endl;
	wcout << "inet_ntoa_t(in) = " << inet_ntoa_t(in) << endl << endl;

	char bytes[100] = { 0 };
	SetAbsoluteInteger(bytes, 100, 0, 0x30313233);
	int value = GetAbsoluteInteger(bytes, 100, 0);
	wcout << "value = " << hex << showbase << value << endl;
	SetAbsoluteString(bytes, 100, 4, "sender", 10);
	string str = GetAbsoluteString(bytes, 100, 4, 10);
	wcout << "str = " << str.c_str() << endl;
	
	system("pause");
	return 0;
}
/*== ��VS2017������Ϊ��==
*** host to net & inet - Transfer ***
USHORT shost = 0x1234
htons_t(shost) = 0x3412
ULONG lhost = 0x12345678
htonl_t(lhost) = 0x78563412

const char* cp = 192.168.1.100
inet_addr_t(cp) = 1677830336
host.lhost = 1677830336

in_addr in = 192 168 1 100
inet_ntoa_t(in) = 192.168.1.100

value = 0x30313233
str = sender
�밴���������. . .
===========================*/

/***
// �ַ����ָ�
char*  __cdecl strtok_s(
_Inout_opt_z_                 char*       _String,
_In_z_                        char const* _Delimiter,
_Inout_ _Deref_prepost_opt_z_ char**      _Context
);


typedef struct sockaddr {

#if (_WIN32_WINNT < 0x0600)
	u_short sa_family;
#else
	ADDRESS_FAMILY sa_family;           // Address family.
#endif //(_WIN32_WINNT < 0x0600)

	CHAR sa_data[14];                   // Up to 14 bytes of direct address.
} SOCKADDR, *PSOCKADDR, FAR *LPSOCKADDR;


typedef struct sockaddr_in {

#if(_WIN32_WINNT < 0x0600)
	short   sin_family;
#else //(_WIN32_WINNT < 0x0600)
	ADDRESS_FAMILY sin_family;
#endif //(_WIN32_WINNT < 0x0600)

	USHORT sin_port;
	IN_ADDR sin_addr;
	CHAR sin_zero[8];
} SOCKADDR_IN, *PSOCKADDR_IN;


typedef struct in_addr {
	union {
		struct { UCHAR s_b1, s_b2, s_b3, s_b4; } S_un_b;
		struct { USHORT s_w1, s_w2; } S_un_w;
		ULONG S_addr;
	} S_un;
#define s_addr  S_un.S_addr			// can be used for most tcp & ip code 
#define s_host  S_un.S_un_b.s_b2    // host on imp
#define s_net   S_un.S_un_b.s_b1    // network
#define s_imp   S_un.S_un_w.s_w2    // imp
#define s_impno S_un.S_un_b.s_b4    // imp #
#define s_lh    S_un.S_un_b.s_b3    // logical host
} IN_ADDR, *PIN_ADDR, FAR *LPIN_ADDR;
*/