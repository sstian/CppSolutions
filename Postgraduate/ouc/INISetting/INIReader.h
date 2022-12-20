/*�����ļ�����ӿ��ļ�*/
#ifndef INIREADER_H
#define INIREADER_H

class INIReader
{
public:
	//���캯��
	INIReader(char* szFileName);
	//��ȡ��������
	int ReadInteger(char* szSection, char* szKey, int iDefaultValue);
	//��ȡ�����ȸ���������
	float ReadFloat(char* szSection, char* szKey, float fDefaultValue);
	//��ȡ����������
	bool ReadBoolean(char* szSection, char* szKey, bool bDefaultValue);
	//��ȡ�ַ�������
	char* ReadSring(char* szSection, char* szKey, const char* szDefaultValue);
private:
	char m_szFileName[255];  //�ļ���
};

#endif  //INIREADER_H