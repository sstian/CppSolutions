/*	2018.09.20 
	文件读取：自定义FileHelper类，静态成员函数
	txt, csv，
	Excel: xlsx [见控制台应用程序 ExportExcel ] , 
	xml [待定], 
	database...  [待定]
*/
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <cassert>
#include <string>
#include <sstream>
#include "tinyxml2.h"	//C++ XML库 TinyXML2

using namespace std; 
using namespace tinyxml2;

//定义元素属性：名=值 映射
using mapss = map<string, string>;
using pairss = pair<string, string>;

class FileHelper
{
public:
	// 读取TXT文件，逐行读取。
	// in_file: 输入参数，文件名；out_strs: 输出参数，字符串向量，存储各行
	static void ReadTXT(const string& in_file, vector<string>& out_strs);

	// 读取CSV=Comma-Separated Values 逗号分隔值，其实就是文本文件，每行字段用逗号分隔。
	// ihn_file: 输入参数，文件名；out_strss: 存成二维字符串表形式，按照逗号分隔（不含逗号）；in_seperated: 分隔符，默认为','
	static void ReadCSV(const string& in_file, vector<vector<string>>& out_strss, char in_seperated = ',');

	//static void ReadXLS (const string& in_file, vector<string>& out_strs);

	
	static void ReadXML (const string& in_xmlfile);

	// 写入TXT文件，一次性覆盖写入。
	// in_file: 输入参数，文件名；in_data: 输入参数，要写入的字符串
	static void WriteTXT(const string& in_file, string& in_data);
};

class XMLParser
{
public:
	XMLParser() { };
	virtual ~XMLParser() { };
	
	//XML初始化：filename: .xml文件
	XMLError XMLInit(const string& filename);

	//解析操作
	void ParseOperate();

	//解析子元素
	void ResoveChildren(const XMLElement* in_xmlchild);

	void ResoveChildren2(const XMLElement* in_xmlchild);

	//获取元素名称
	const char* ElementName(const XMLElement* in_xmlelement);

	//获取元素文本
	const char* ElementText(const XMLElement* in_xmlelement);

	//获取元素属性：名=值 映射对
	bool AttributeMap(const XMLElement* in_xmlelement, mapss& out_mapss);

///测试友元类
public:

	static void output_mapss(mapss& in_mapss);

	static list<mapss> t_attributes;
	static 	vector<string> t_vs;
	static list<vector<string>> t_text;
///

private:
	string m_filename;		//XML文件名
	XMLDocument m_xmldoc;	//XML文件类
	XMLElement* m_xmlroot;	//XML根元素
	XMLElement* m_xmlchild;	//XML子元素
};