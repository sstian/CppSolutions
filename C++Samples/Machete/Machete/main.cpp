/****************************************************************************
 * �������ƣ�������Machete v1.0��ֽ����Ϸ
 * ���뻷����Microsoft Visual Studio Professional 2017, EasyX 20170421(beta)
 * ��    �ߣ��ö��� <st.tian@foxmail.com>
 * ���ʱ�䣺2017-06-01 ~ 06-11
 ***************************************************************************/
#include <graphics.h>
#include <cstdlib>
#include "Constant.h"
#include "Style.h"
using namespace std;

/* ������ */
int main(void)
{
	initgraph(WIDTH, HEIGHT);	//��ʼ������

	MainMenu();	//���˵�

	system("pause");			//ϵͳ��ͣ
	closegraph();				//�رմ���
	return 0;
}
