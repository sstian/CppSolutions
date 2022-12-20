/*
	2019.11.02 18:28 - 19:40
	����������תΪ���Ĵ�д����
eg.	200.00	����Ԫ��
	201.15	������ҼԪҼ�����
	1015	ҼǪ��Ҽʰ��Ԫ��
	200001010200	��Ǫ����Ҽ����Ҽ���㷡��Ԫ��
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  
#include <string>  

using namespace std;

// ��ʾ�������ֵı�־  
const int INT_ONLY = 1;
// ��ʾС�����ֵı�־  
const int SMALL_ONLY = 2;

// ���Ҵ�д��ʽ  
string bigLetter[] = { "��", "Ҽ", "��", "��", "��", "��", "½", "��", "��", "��" };
// ���ҵ�λ  
string unit[] = { "Ԫ", "ʰ", "��", "Ǫ", "��",		// ��λ��������
				"ʰ", "��", "Ǫ",					// ʰ��λ��Ǫ��λ  
				"��", "ʰ", "��", "Ǫ", "��" };		// ��λ������λ 
string small[] = { "��", "��" };

/**
 * �������н���һ�����������е��� checkNum() �������������֤����������Ӧ��ֵ
 * @return �������Ϸ�����������������
 */
string getNum() 
{
	string s;
	cout << "������һ�����֣���ȷ��С�������λ����" << endl;
	cin >> s;													// ���������������������  
	cin.clear();												// ���������״̬��־  
	return s;
}

/**
* �ж��û�����������Ƿ�Ϸ����û�ֻ���������������֣��������������ַ�
* @param s string
* @return ����û��������ݺϷ������� true�����򷵻� false
*/
bool checkNum(string s) 
{
	double d = atof(s.c_str());
	if (d > 0)							// ֻ�е��û�����һ������0����ʱ���Ż᷵��true  
		return true;
	return false;
}

/**
 * �Դ���������������������
 * @param s string����������������Ǹ���
 * @return ������������ֵ
 */
string roundString(string s) 
{
	// �������ת���� double ���ͣ���������������������  
	// ��ת�����������������  
	// atof(s.c_str()) �����Ĺ����ǽ��ַ��� s ת����һ��˫������ֵ�����ؽ��  
	// c_str()��������һ��ָ������C�ַ�����ָ��, �����뱾�ַ�����ͬ  
	double d = atof(s.c_str());
	// ������������������룬������С�������λ  
	// �ٽ������ת�����ַ������ȴ�ת��  
	int dec, sign;
	// ע�⣺�������ת�����ַ����Ժ󲻻���ʾС���㣬���һ��������������ʽֻ����С�������λ  
	s = _fcvt(d, 2, &dec, &sign);
	// �涨��ֵ����󳤶�ֻ����15λ��������λ��  
	if (s.length() > 15) 
	{
		cout << "�������ݹ��󣡣������������13λ����" << endl;
		return "";
	}
	return s;
}

/**
 * �Ѵ������ת��Ϊ���Ľ���д��ʽ
 * @param flag int ��־λ��1 ��ʾת���������֣�0 ��ʾת��С������
 * @param s string Ҫת�����ַ���
 * @return ת���õĴ���λ�����Ľ���д��ʽ
 */
string formatChinese(int flag, string s) 
{
	int sLength = (int)s.length();			// �������ת��������ַ���  
	if (flag == SMALL_ONLY && s == "00")
		return "��";

	// ��λ�滻Ϊ���Ĵ�д��ʽ  
	string newS = "";
	for (int i = 0; i < sLength; i++)
	{
		if (flag == INT_ONLY) 
		{
			// ת����������Ϊ���Ĵ�д��ʽ������λ��  
			newS += bigLetter[s.at(i) - 48] + unit[sLength - i - 1];
		}
		else if (flag == SMALL_ONLY) 
		{
			// ת��С�����֣�����λ��  
			newS += bigLetter[s.at(i) - 48] + small[sLength - i - 1];
		}
	}
	return newS;
}

/**
 * ���û����������С����Ϊ��ָ���������� numFormat() ����
 * ������Ӧ�����Ľ���д��ʽ��ת��
 * ע������������Ӧ���Ǿ��� roundString() �����������������������
 * @param s string
 * @return ת���õ����Ľ���д��ʽ���ַ���
 */
string splitNum(string s) 
{
	// ���������ǿմ���������ؿմ�  
	if ("" == s) 
		return "";

	// ��ȡ�������ֵ���������  
	string intOnly = s.substr(0, s.size() - 2);
	string intPart = formatChinese(1, intOnly);

	// ��ȡ�������С������  
	string smallOnly = s.substr(s.size() - 2, s.size());
	string smallPart = formatChinese(2, smallOnly);

	// ��ת�����˵��������ֺ�С����������ƴ��һ���µ��ַ���  
	string newS = intPart + smallPart;

	return newS;
}

/**
 * ʹ�ø����� replacement �滻���ַ�������ƥ������� regex �����ַ�����
 * @param src - ��������Դ�ַ���
 * @param regex - ����ƥ����ַ�����������ʽ
 * @param replacement - �����滻ÿ��ƥ������ַ���
 * @return �滻����ַ���
 */
string replaceAll(string src, string regex, string replacement) 
{
	int length = (int)regex.length();
	while (src.find(regex) < src.length()) 
	{
		// �滻 src �ַ����дӵ�һ��ƥ�� regex ���ַ���������ʼ�� length ���ַ�Ϊ replacement �ַ���          
		src.replace(src.find(regex), length, replacement);
	}
	return src;
}

/**
 * ���Ѿ�ת���õ����Ľ���д��ʽ���ԸĽ�����������ַ������������㣬������ַ�����ø��ӿɹ�
 * ע������������Ӧ���Ǿ��� splitNum() �������д�������ַ���Ӧ���Ѿ��������Ľ���д��ʽ��ʾ��
 * @param s string �Ѿ�ת���õ��ַ���
 * @return �Ľ�����ַ���
 */
string cleanZero(string s) 
{
	// ���������ǿմ���������ؿմ�  
	if ("" == s) 
		return "";

	// �ַ����д��ڶ��'��'��һ���ʱ��ֻ����һ��'��'����ʡ�Զ���ĵ�λ  
	/* ���ڱ��˶��㷨���о�̫���ˣ�ֻ����4��������ʽȥת���ˣ���λ��Ϻ������... */
	string regex1[] = { "��Ǫ", "���", "��ʰ" };
	string regex2[] = { "����", "����", "��Ԫ" };
	string regex3[] = { "��", "��", "Ԫ" };
	string regex4[] = { "���", "���" };

	// ��һ��ת���� "��Ǫ", ���","��ʰ"���ַ����滻��һ��"��"  
	for (int i = 0; i < 3; i++)
	{
		s = replaceAll(s, regex1[i], "��");
	}
	// �ڶ���ת������ "����","����","��Ԫ"�����  
	// "��","��","Ԫ"��Щ��λ��Щ����ǲ���ʡ�ģ���Ҫ��������  
	for (int i = 0; i < 3; i++) 
	{
		// ����һ��ת�������п����кܶ�������һ��  
		// Ҫ�Ѻܶ���ظ�������һ����  
		s = replaceAll(s, "������", "��");
		s = replaceAll(s, "����", "��");
		s = replaceAll(s, regex2[i], regex3[i]);
	}
	// ������ת����"���","���"�ַ���ʡ��  
	for (int i = 0; i < 2; i++) 
		s = replaceAll(s, regex4[i], "");
	// ��"��"��"��"֮��ȫ����"��"��ʱ�򣬺���"����"��λ��ֻ����һ��"��"  
	s = replaceAll(s, "����", "��");
	return s;
}

int main() 
{
	cout << "\n------------������ת�������Ľ��Ĵ�д��ʽ��C++��------------\n" << endl;
	while (true)
	{
		string s = getNum();
		if (checkNum(s))
		{
			s = roundString(s);
			s = splitNum(s);
			s = cleanZero(s);
			cout << "->" << s << endl << endl;
		}
		else
		{
			cout << "�Ƿ����룬���򼴽��˳�" << endl;
			cout << "\n--------------------------------------------------------------" << endl;
			return 0;
		}
	}
}

/*** in:200001010200 out:

------------������ת�������Ľ��Ĵ�д��ʽ��C++��------------

������һ�����֣���ȷ��С�������λ����
200001010200
->��Ǫ����Ҽ����Ҽ���㷡��Ԫ��

������һ�����֣���ȷ��С�������λ����
***/