/*配置文件读类接口文件*/
#ifndef INIREADER_H
#define INIREADER_H

class INIReader
{
public:
	//构造函数
	INIReader(char* szFileName);
	//读取整型数据
	int ReadInteger(char* szSection, char* szKey, int iDefaultValue);
	//读取单精度浮点型数据
	float ReadFloat(char* szSection, char* szKey, float fDefaultValue);
	//读取布尔型数据
	bool ReadBoolean(char* szSection, char* szKey, bool bDefaultValue);
	//读取字符串数据
	char* ReadSring(char* szSection, char* szKey, const char* szDefaultValue);
private:
	char m_szFileName[255];  //文件名
};

#endif  //INIREADER_H