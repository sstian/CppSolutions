/*
	2019.09.11 22:59 - 23:54
	×Ö·û´®½âÎö
	string str = "A={1,12,130}";
	string str2 = "{A=12,B=13,C=14}";

	char*  __cdecl strtok_s(
	_Inout_opt_z_                 char*       _String,
	_In_z_                        char const* _Delimiter,
	_Inout_ _Deref_prepost_opt_z_ char**      _Context
	);
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// ×Ö·û´®·Ö¸î
// string str = "A={1,12,130}";
void strsplit(string& str, vector<string>& vs)
{
	int left = (int)str.find("{");
	int right = (int)str.find("}");
	string src = str.substr(left + 1, right - left - 1);

	char* content;
	char* token = strtok_s(const_cast<char*>(src.c_str()), "=,", &content);
	while (token != nullptr)
	{
		vs.push_back(token);
		token = strtok_s(nullptr, "=,", &content);
	}
}

using mapsn = std::map<string, int>;
// ×Ö·û´®½âÎö
// string str2 = "{A=12,B=13,C=14}";
void strhandle(string& str, mapsn& msn)
{
	int left = (int)str.find('{') + 1;
	int right = (int)str.find('}');
	while (left < right)
	{
		int equal = (int)str.find('=', left);
		int comma = (int)str.find(',', left);
		if (string::npos == equal)
			break;
		if (string::npos == comma)
			comma = right;

		string key = str.substr(left, equal - left);
		int value = stoi(str.substr(equal + 1, comma - equal - 1));
		msn.insert(std::make_pair(key, value));

		left = comma + 1;
	}
}


int main()
{
	//string str1 = "A={1,12,130}";
	//vector<string> vs;
	//strsplit(str1, vs);
	//cout << str1 << endl;
	//for (auto& at : vs)
	//	cout << at << " ";
	//cout << endl;

	//cout << "==============" << endl;
	//string str2 = "{A=12,B=13,C=14}";
	//mapsn msn;
	//strhandle(str2, msn);
	//cout << str2 << endl;
	//for (auto& at2 : msn)
	//	cout << at2.first << " " << at2.second << endl;
	//cout << endl;

	//string str = "{A=12,B=13,C=14}";
	string str = ": # A:12#B:13#C:14";
	cout << "str: " << str << endl;

	std::vector<string> vecs;
	std::map<string, int> mapsn;

	// Ö§³Ö "A={1,12,130}" ºÍ "{A=12,B=13,C=14}"
	//int left = (int)str.find("{");
	//int right = (int)str.find("}");
	//string src = str.substr(left + 1, right - left - 1);	//Ô´×Ö·û´®
	string src = str.substr(4, str.size() - 4);
	string del = ":#";										//·Ö¸ô·û

	char* content;
	char* token = strtok_s(const_cast<char*>(src.c_str()), del.c_str(), &content);
	while (token)
	{
		//cout << token << endl;
		vecs.push_back(token);			//´æ´¢Îªvector¶¯Ì¬Êý×é
		token = strtok_s(nullptr, del.c_str(), &content);
	}

	// ´æ´¢ÎªmapÓ³Éä
	int size = (int)vecs.size();
	for (int index = 0; index < size; index += 2)
		mapsn.insert(std::make_pair(vecs.at(index), stoi(vecs.at(index + 1))));

	// Êä³öÏÔÊ¾
	for (auto& at : mapsn)
		cout << at.first << " " << at.second << endl;
	cout << endl;
	
	return 0;
}

/*** VS2017 output:
str: {A=12,B=13,C=14}
A 12
B 13
C 14

***/
