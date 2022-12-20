#include "FileHelper.h"

///���������ݳ�Ա
list<map<string, string>> XMLParser::t_attributes;
vector<string> XMLParser::t_vs;
list<vector<string>> XMLParser::t_text;


void FileHelper::ReadTXT(const string& in_file, vector<string>& out_strs)
{
	fstream infile;							//�����ļ�����
	infile.open(in_file.data(), ios::in);	//���ļ�����ȡģʽ
	assert(infile.is_open());				//���ԣ��ļ��򿪴�������ж��쳣
	//if (infile.fail())
	//{
	//	cout << "cann't open file! Exit." << endl;
	//	exit(1);
	//}

	string strline;
	out_strs.clear();
	//<string>�е�ȫ�ֺ��� istream& getline ( istream& is, string& str, [char delim] )��
	//��istream�ĳ�Ա���� istream& getline (char* s, streamsize n, [char delim] )��
	//!����ȡ���ַ����洢��char�����ж������Խ��ò�������Ϊstring����
	while (::getline(infile, strline))		//���ж�ȡ
	{
		out_strs.push_back(strline);			//�洢�ַ���
	}

	infile.close();							//�ر��ļ�
}

void FileHelper::ReadCSV(const string & in_file, vector<vector<string>>& out_strss, char in_seperated)
{
	fstream infile;							//�����ļ�����
	infile.open(in_file.data(), ios::in);	//���ļ�����ȡģʽ
	assert(infile.is_open());				//���ԣ��ļ��򿪴�������ж��쳣

	string strline;
	out_strss.clear();
	while (::getline(infile, strline))		//���ж�ȡ
	{
		stringstream ss(strline);
		string strval;
		vector<string> strArray;
		strArray.clear();
		while (::getline(ss, strval, ','))
			strArray.push_back(strval);

		out_strss.push_back(strArray);		//�洢�ַ���
	}

	infile.close();							//�ر��ļ�

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

	//����XML�ļ�
	XMLError error = m_xmldoc.LoadFile(filename.c_str());
	//��ȡ��Ԫ��
	m_xmlroot = m_xmldoc.RootElement();

	return error;
}

void XMLParser::ParseOperate()
{
	cout << ElementName(m_xmlroot) << "  ";	//

	mapss ss;
	if (AttributeMap(m_xmlroot, ss))
		cout << endl;						//	

	//��ȡ��һ����Ԫ��
	m_xmlchild = m_xmlroot->FirstChildElement();

	//�ݹ����������Ԫ�ػ�����Ӽ�Ԫ��
	//ResoveChildren(m_xmlchild);
	ResoveChildren2(m_xmlchild);

}

void XMLParser::ResoveChildren(const XMLElement * in_xmlchild)
{
	mapss ss;

	while (in_xmlchild)
	{
		//Ԫ������
		const char* name = ElementName(in_xmlchild);
		cout << name << " "; 

		//Ԫ������
		if (AttributeMap(in_xmlchild, ss))
			cout << endl;	//

		//Ԫ���ı�
		const char* content = ElementText(in_xmlchild);
		if (content)
			cout << content << endl;				//

		//��Ԫ����һ��Ԫ��
		const XMLElement* xmlchildren = in_xmlchild->FirstChildElement();
		if (xmlchildren)
			ResoveChildren(xmlchildren);

		//��һ���ֵ�Ԫ��
		in_xmlchild = in_xmlchild->NextSiblingElement();
	}

}

void XMLParser::ResoveChildren2(const XMLElement * in_xmlchild)
{
	mapss ss;

	while (in_xmlchild)
	{
		//Ԫ������
		const char* name = ElementName(in_xmlchild);
		cout << name << " ";

		//Ԫ������
		if (AttributeMap(in_xmlchild, ss))
			cout << endl;	//
		t_attributes.push_back(ss);

		//Ԫ���ı�
		const char* content = ElementText(in_xmlchild);
		if (content)
		{
			cout << content << endl;				//
			t_vs.push_back(content);
		}

		//��Ԫ����һ��Ԫ��
		const XMLElement* xmlchildren = in_xmlchild->FirstChildElement();
		if (xmlchildren)
			ResoveChildren2(xmlchildren);

		t_text.push_back(t_vs);
		t_vs.clear();

		//��һ���ֵ�Ԫ��
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
		//���ԣ���ֵ�Բ���
		out_mapss.insert(pairss(attribute->Name(), attribute->Value()));
		//��Ԫ����һ������
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
