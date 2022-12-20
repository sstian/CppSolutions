#include "FileHelper.h"

///测试类数据成员
list<map<string, string>> XMLParser::t_attributes;
vector<string> XMLParser::t_vs;
list<vector<string>> XMLParser::t_text;


void FileHelper::ReadTXT(const string& in_file, vector<string>& out_strs)
{
	fstream infile;							//创建文件对象
	infile.open(in_file.data(), ios::in);	//打开文件，读取模式
	assert(infile.is_open());				//断言，文件打开错误产生中断异常
	//if (infile.fail())
	//{
	//	cout << "cann't open file! Exit." << endl;
	//	exit(1);
	//}

	string strline;
	out_strs.clear();
	//<string>中的全局函数 istream& getline ( istream& is, string& str, [char delim] )；
	//非istream的成员函数 istream& getline (char* s, streamsize n, [char delim] )，
	//!将读取的字符串存储在char数组中而不可以将该参数声明为string类型
	while (::getline(infile, strline))		//逐行读取
	{
		out_strs.push_back(strline);			//存储字符流
	}

	infile.close();							//关闭文件
}

void FileHelper::ReadCSV(const string & in_file, vector<vector<string>>& out_strss, char in_seperated)
{
	fstream infile;							//创建文件对象
	infile.open(in_file.data(), ios::in);	//打开文件，读取模式
	assert(infile.is_open());				//断言，文件打开错误产生中断异常

	string strline;
	out_strss.clear();
	while (::getline(infile, strline))		//逐行读取
	{
		stringstream ss(strline);
		string strval;
		vector<string> strArray;
		strArray.clear();
		while (::getline(ss, strval, ','))
			strArray.push_back(strval);

		out_strss.push_back(strArray);		//存储字符流
	}

	infile.close();							//关闭文件

}

void FileHelper::ReadXML(const string & in_xmlfile)
{
	XMLParser xmlparser;
	xmlparser.XMLInit(in_xmlfile);
	xmlparser.ParseOperate();
}

void FileHelper::WriteTXT(const string& in_file, string& in_data)
{
	fstream outfile;
	outfile.open(in_file, ios::out);
	assert(outfile.is_open());

	outfile << in_data;

	outfile.close();
}


XMLError XMLParser::XMLInit(const string & filename)
{
	m_filename = filename;

	//加载XML文件
	XMLError error = m_xmldoc.LoadFile(filename.c_str());
	//获取根元素
	m_xmlroot = m_xmldoc.RootElement();

	return error;
}

void XMLParser::ParseOperate()
{
	cout << ElementName(m_xmlroot) << "  ";	//

	mapss ss;
	if (AttributeMap(m_xmlroot, ss))
		cout << endl;						//	

	//获取第一个子元素
	m_xmlchild = m_xmlroot->FirstChildElement();

	//递归遍历其它子元素或更深子级元素
	//ResoveChildren(m_xmlchild);
	ResoveChildren2(m_xmlchild);

}

void XMLParser::ResoveChildren(const XMLElement * in_xmlchild)
{
	mapss ss;

	while (in_xmlchild)
	{
		//元素名称
		const char* name = ElementName(in_xmlchild);
		cout << name << " "; 

		//元素属性
		if (AttributeMap(in_xmlchild, ss))
			cout << endl;	//

		//元素文本
		const char* content = ElementText(in_xmlchild);
		if (content)
			cout << content << endl;				//

		//该元素下一级元素
		const XMLElement* xmlchildren = in_xmlchild->FirstChildElement();
		if (xmlchildren)
			ResoveChildren(xmlchildren);

		//下一个兄弟元素
		in_xmlchild = in_xmlchild->NextSiblingElement();
	}

}

void XMLParser::ResoveChildren2(const XMLElement * in_xmlchild)
{
	mapss ss;

	while (in_xmlchild)
	{
		//元素名称
		const char* name = ElementName(in_xmlchild);
		cout << name << " ";

		//元素属性
		if (AttributeMap(in_xmlchild, ss))
			cout << endl;	//
		t_attributes.push_back(ss);

		//元素文本
		const char* content = ElementText(in_xmlchild);
		if (content)
		{
			cout << content << endl;				//
			t_vs.push_back(content);
		}

		//该元素下一级元素
		const XMLElement* xmlchildren = in_xmlchild->FirstChildElement();
		if (xmlchildren)
			ResoveChildren2(xmlchildren);

		t_text.push_back(t_vs);
		t_vs.clear();

		//下一个兄弟元素
		in_xmlchild = in_xmlchild->NextSiblingElement();
	}

}

const char * XMLParser::ElementName(const XMLElement * in_xmlelement)
{
	return in_xmlelement->Name();
}

const char * XMLParser::ElementText(const XMLElement * in_xmlelement)
{
	return in_xmlelement->GetText();
}

bool XMLParser::AttributeMap(const XMLElement * in_xmlelement, mapss & out_mapss)
{
	out_mapss.clear();
	const XMLAttribute* attribute = in_xmlelement->FirstAttribute();
	while (attribute)
	{
		//属性：名值对插入
		out_mapss.insert(pairss(attribute->Name(), attribute->Value()));
		//该元素下一个属性
		attribute = attribute->Next();
	}

	if (out_mapss.empty())
		return false;
	else
	{
		output_mapss(out_mapss); //

		return true;
	}
}

void XMLParser::output_mapss(mapss & in_mapss)
{
	mapss::iterator iter;
	for (iter = in_mapss.begin(); iter != in_mapss.end(); iter++)
		cout << iter->first << " = " << iter->second << "  ";		//
}
