//Help.cpp  ���� Դ�ļ�
#include <graphics.h>

/* �����ĵ� */
void HelpDoc()
{
	HWND hWnd = GetHWnd();
	int msgboxID = MessageBox(hWnd, _T("��꣺\n  ���ѡ��\n   �Ҽ� - �����桢ģʽѡ�����Ϊ���أ�\n          - ��Ϸ��������Ϊ�����ơ�\nϣ���������á�"),
		_T("����"), MB_OK | MB_ICONQUESTION);				//ȷ����ѯ��ͼ��

}