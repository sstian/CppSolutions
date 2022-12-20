/*�����ļ�д��ʵ���ļ�*/
#include "INIWriter.h"
#include <iostream>
#include <windows.h>

INIWriter::INIWriter(char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));  //��strlen()���ַ������ȶ�����sizeof
}

void INIWriter::WriteInteger(char* szSection, char* szKey, int iValue)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileString(szSection, szKey, szValue, m_szFileName);
}

void INIWriter::WriteFloat(char* szSection, char* szKey, float fValue)
{
	char szValue[255];
	sprintf(szValue, "%f" ,fValue);
	WritePrivateProfileString(szSection, szKey, szValue, m_szFileName);
}

void INIWriter::WriteBoolean(char* szSection, char* szKey, bool bValue)
{
	char szValue[255];
	sprintf(szValue, "%s", bValue ? "True" : "False");
	WritePrivateProfileString(szSection, szKey, szValue, m_szFileName);
}

void INIWriter::WriteString(char* szSection, char* szKey, char* szValue)
{
	WritePrivateProfileString(szSection, szKey, szValue, m_szFileName);
}

/******����ԭ���빦��˵��******
*1����ʼ��������void *memset(void *s, int ch, size_t n);
*�������ܣ���s�е�ǰλ�ú����n���ֽ� ��typedef unsigned int size_t ���� ch �滻������ s ��
*��Ҫͷ�ļ���<memory.h>��<string.h>
*
*2���ڴ濽��������void *memcpy(void *dest, const void *src, size_t n);
*�������ܣ���Դsrc��ָ���ڴ��ַ����ʼλ�ÿ�ʼ����n���ֽڵ�Ŀ��dest��ָ���ڴ��ַ����ʼλ���У�
*	��������ָ��dest��ָ�롣
*��Ҫͷ�ļ���#include<cstring>
*
*3���ַ�����ʽ�����=string print format
*int sprintf( char *buffer, const char *format, [ argument] �� );
*�������ܣ��Ѹ�ʽ��������д��ĳ���ַ�����������
*	����д��buffer ���ַ����������򷵻�-1. ��� buffer �� format �ǿ�ָ�룬�Ҳ����������������������-1��
*	���� errno �ᱻ����Ϊ EINVAL��sprintf ���ر�д��buffer ���ֽ����������ַ���\0���������ڡ�
*	���������Hello����д��ռ��㹻���buffer�󣬺���sprintf ����5��
*buffer��char��ָ�룬ָ��Ҫд����ַ����Ļ�������
*format����ʽ���ַ�����
*[argument]...����ѡ�������������κ����͵����ݡ�
*��Ҫͷ�ļ���stdio.h
*
*4������Ϣд��.INI�ļ���
*BOOL WritePrivateProfileString(
LPCTSTR lpAppName,  //INI�ļ��е�һ���ֶ���
LPCTSTR lpKeyName,  //lpAppName�µ�һ������,ͨ�׽����Ǳ�����
LPCTSTR lpString,  //��ֵ,��������ֵ,��������ΪLPCTSTR�ͻ�CString��
LPCTSTR lpFileName  //������INI�ļ��������û��ָ������·�����������windowsĿ¼��Ĭ�ϣ������ļ���
					//����ļ�û���ҵ�����������windowsĿ¼������
);
*
*5��������Ϣ��
*1.INI�ļ���·����������,�ļ���ǰ��ĸ���Ŀ¼�������,����д�벻�ɹ�,�ú������� FALSE ֵ��
*2.�ļ�����·���б���Ϊ \\ ,��Ϊ��VC++��, \\ �ű�ʾһ�� \ ��
*3.Ҳ�ɽ�INI�ļ����ڳ�������Ŀ¼,��ʱ lpFileName ����Ϊ: ".\\student.ini"��
*/