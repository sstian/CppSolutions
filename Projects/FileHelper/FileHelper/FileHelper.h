/*	2018.09.20 
	�ļ���ȡ���Զ���FileHelper�࣬��̬��Ա����
	txt, csv��
	Excel: xlsx [������̨Ӧ�ó��� ExportExcel ] , 
	xml [����], 
	database...  [����]
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
#include "tinyxml2.h"	//C++ XML�� TinyXML2

using namespace std; 
using namespace tinyxml2;

//����Ԫ�����ԣ���=ֵ ӳ��
using mapss = map<string, string>;
using pairss = pair<string, string>;

class FileHelper
{
public:
	// ��ȡTXT�ļ������ж�ȡ��
	// in_file: ����������ļ�����out_strs: ����������ַ����������洢����
	static void ReadTXT(const string& in_file, vector<string>& out_strs);

	// ��ȡCSV=Comma-Separated Values ���ŷָ�ֵ����ʵ�����ı��ļ���ÿ���ֶ��ö��ŷָ���
	// ihn_file: ����������ļ�����out_strss: ��ɶ�ά�ַ�������ʽ�����ն��ŷָ����������ţ���in_seperated: �ָ�����Ĭ��Ϊ','
	static void ReadCSV(const string& in_file, vector<vector<string>>& out_strss, char in_seperated = ',');

	//static void ReadXLS (const string& in_file, vector<string>& out_strs);

	
	static void ReadXML (const string& in_xmlfile);

	// д��TXT�ļ���һ���Ը���д�롣
	// in_file: ����������ļ�����in_data: ���������Ҫд����ַ���
	static void WriteTXT(const string& in_file, string& in_data);
};

class XMLParser
{
public:
	XMLParser() { };
	virtual ~XMLParser() { };
	
	//XML��ʼ����filename: .xml�ļ�
	XMLError XMLInit(const string& filename);

	//��������
	void ParseOperate();

	//������Ԫ��
	void ResoveChildren(const XMLElement* in_xmlchild);

	void ResoveChildren2(const XMLElement* in_xmlchild);

	//��ȡԪ������
	const char* ElementName(const XMLElement* in_xmlelement);

	//��ȡԪ���ı�
	const char* ElementText(const XMLElement* in_xmlelement);

	//��ȡԪ�����ԣ���=ֵ ӳ���
	bool AttributeMap(const XMLElement* in_xmlelement, mapss& out_mapss);

///������Ԫ��
public:

	static void output_mapss(mapss& in_mapss);

	static list<mapss> t_attributes;
	static 	vector<string> t_vs;
	static list<vector<string>> t_text;
///

private:
	string m_filename;		//XML�ļ���
	XMLDocument m_xmldoc;	//XML�ļ���
	XMLElement* m_xmlroot;	//XML��Ԫ��
	XMLElement* m_xmlchild;	//XML��Ԫ��
};