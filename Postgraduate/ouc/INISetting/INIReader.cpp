/*�����ļ�����ʵ���ļ�*/
#include "INIReader.h"
#include <iostream>
#include <windows.h>

INIReader::INIReader(char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));  //��strlen()���ַ������ȶ�����sizeof
}

int INIReader::ReadInteger(char* szSection, char* szKey, int iDefaultValue)
{
		char szSpaceKey[255];  
	strcpy(szSpaceKey, szKey);  //������ӿո�

	int iResult = GetPrivateProfileInt(szSection, strcat(szSpaceKey, " "), iDefaultValue, m_szFileName);
	return iResult;
}

float INIReader::ReadFloat(char* szSection, char* szKey, float fDefaultValue)
{
	char szDefault[255];
	char szResult[255];
	sprintf(szDefault, "%f", fDefaultValue);
	GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_szFileName);
	float fResult = atof(szResult);
	return fResult;
}

bool INIReader::ReadBoolean(char* szSection, char* szKey, bool bDefaultValue)
{
	char szDefault[255];
	char szResult[255];
	sprintf(szDefault, "%s", bDefaultValue ? "True" : "False");
	GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_szFileName);
	bool bResult = (strcmp(szResult, "true") == 0 || strcmp(szResult, "True") == 0) ? true : false;
	return bResult;
}

char* INIReader::ReadSring(char* szSection, char* szKey, const char* szDefaultValue)
{
	char* szResult = new char[255];  //ע���������
//	char szResult[255];
	memset(szResult, 0x00, 255);
	GetPrivateProfileString(szSection, szKey, szDefaultValue,szResult,255,m_szFileName);
	return szResult;
}

/******����ԭ���빦��˵��******
*1��Ϊ��ʼ���ļ���ָ������Ŀ��ȡ��������ֵ��
*UINT WINAPI GetPrivateProfileInt
(
_In_LPCTSTR lpAppName,  //ָ�������в�����Ŀ��С�ڡ�ע������ִ��ǲ����ִ�Сд��
_In_LPCTSTR lpKeyName,  //����ȡ�����������Ŀ�����֧�ֲ����ִ�Сд
_In_INT nDefault,  //ָ����Ŀδ�ҵ�ʱ���ص�Ĭ��ֵ
_In_LPCTSTR lpFileName  //��ʼ���ļ������֡����û��ָ��������·������windows�ͻ���WindowsĿ¼�������ļ�
);
*��������ֵ��Long���ҵ�����Ŀ��ֵ����ָ������Ŀδ�ҵ����ͷ���Ĭ��ֵ��
*	���ҵ������ֲ���һ���Ϸ��������������᷵�����кϷ���һ���֡�

*2��Ϊ��ʼ���ļ���ָ������Ŀȡ���ִ���
*DWORD GetPrivateProfileString(
LPCTSTR lpAppName,  //�����ļ���section��
LPCTSTR lpKeyName,  //�����ļ���key��
LPCTSTR lpDefault,  //���INI�ļ���û��ǰ��������ָ�����ֶ��������,�򽫴�ֵ��������
LPTSTR lpReturnedString,  //����INI�ļ��е�ֵ��CString����,��Ŀ�Ļ�����
DWORD nSize,  //Ŀ�Ļ������Ĵ�С
LPCTSTR lpFileName  //������INI�ļ���
);
*��������ֵ��Long�����Ƶ�lpReturnedString���������ֽ����������в�������ЩNULL��ֹ�ַ���
*	��lpReturnedString�����������󣬲�������ȫ����Ϣ���ͷ���nSize-1
*	����lpApplicationName��lpKeyNameΪNULL���򷵻�nSize-2��
*
*3��typedef unsigned int UINT;
*UINT������WINDOWS API���ж��壬����Ӧ��32λ�޷���������

*4��typedef unsigned long DWORD;
*DWORD ���� Double Word�� ÿ��wordΪ2���ֽڵĳ��ȣ�DWORD ˫�ּ�Ϊ4���ֽڣ�ÿ���ֽ���8λ����32λ��

*/