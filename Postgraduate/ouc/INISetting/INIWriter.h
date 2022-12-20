/*配置文件写类接口文件*/
#ifndef INIWRITER_H
#define INIWRITER_H

class INIWriter
{
public:
	//构造函数
	INIWriter(char* szFileName);
	//写入整型数据
	void WriteInteger(char* szSection, char* szKey, int iValue);
	//写入单精度浮点数据
	void WriteFloat(char* szSection, char* szKey, float fValue);
	//写入布尔型数据
	void WriteBoolean(char* szSection, char* szKey, bool bValue);
	//写入字符串数据
	void WriteString(char* szSection, char* szKey, char* szValue);
private:
	char m_szFileName[255];  //文件名
};

#endif  //INIWRITER_H