/*�����ļ�д��ӿ��ļ�*/
#ifndef INIWRITER_H
#define INIWRITER_H

class INIWriter
{
public:
	//���캯��
	INIWriter(char* szFileName);
	//д����������
	void WriteInteger(char* szSection, char* szKey, int iValue);
	//д�뵥���ȸ�������
	void WriteFloat(char* szSection, char* szKey, float fValue);
	//д�벼��������
	void WriteBoolean(char* szSection, char* szKey, bool bValue);
	//д���ַ�������
	void WriteString(char* szSection, char* szKey, char* szValue);
private:
	char m_szFileName[255];  //�ļ���
};

#endif  //INIWRITER_H