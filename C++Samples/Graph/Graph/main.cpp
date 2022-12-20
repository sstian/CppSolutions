/*  2017.5.21 21:06
	ͼ�ο� EasyX Library for C++
1���½����ڣ���ʼ��initgraph(), �ر�closegraph()��
2����ͼ  .jpg .bmp��1)����ͼ��loadimage(NULL)��2)loadimage(&image); putimage(&image)��
3����������  .mp3 .wav��1)mciSendString()��2)PlaySound()��Ҫ wav ��ʽ�ģ�����
4����Դ��� res��1)��Դres�ļ��з��������ͬһĿ¼�£�
				2)����Դ��Ƕ��exe�ļ��У�ͨ����ԴID�Ż���Դ���ƣ�Ҫ��Ӣ��˫��������������
	ͼƬ 													��ԴID				��Դ����	��Դ·�����ļ�
(1)loadimage(_T("IMAGE"),MAKEINRESOURCE(��ԴID))	JPG		IDR_IMAGE_BACK		IMAGE		"res\\back.jpg"
(2)loadimage(_T("IMAGE"),_T("��Դ����"))			JPG		BACK                IMAGE       "res\\back.jpg"
													BMP		IDB_BITMAP_CLOUSE   IMAGE       "res\\clouse.bmp"
	���� PlaySound((LPCWSTR)��ԴID,SND_RESOURCE)	WAVE	IDR_WAVE_BGM		WAVE        "res\\bgm.wav"
	
5������ͼ�� icon����Ŀ�½���->��Դ��ICON->Resource.rc�������Դ->Icon�����롣
6��ʹ�����PC���У���Ŀ����->C/C++->��������->���п⣺���̣߳�/MT����
********** С��ʿ **********
1��_T("����") <==> L"����"  ���ַ�
2���ļ�·����/ <==> \\ ������·��VS���·��(OK)��·��Ӣ���ַ������ִ�Сд��
3��������Դ��res�ļ��з��������ͬһĿ¼�£�ʹ�� L"res/1.jpg" �� L"./res/1.jpg" ����
*/

#include <graphics.h>  //ͼ�ο�
#include <cstdlib>  //system()
#include "resource.h"  //��Դ���ʱ����Ҫ��ͷ�ļ�
#include <mmsystem.h>  //System APIs for Multimedia��ý��  mciSendString() 
#pragma comment(lib, "winmm.lib")  //��ʽ���ӵ��÷�ʽ������winmm.lib�⣬���߱�������Ҫ�õ�winmm.lib��  mciSendString()  PlaySound()
using namespace std;  //�����ռ䣬���������������

const int SOLOTION	= 960 * 540;	//���ڷֱ���
const int WIDTH		= 960;			//���ڵĿ�
const int HEIGHT	= 540;			//���ڵĸ�

void LoadImage521();  //����ͼƬ
void PlayMusic521();  //��������

int main(void)
{
	//��ʼ������
	initgraph(WIDTH, HEIGHT);

	LoadImage521();
	PlayMusic521();

	system("pause");
	//�رմ���
	closegraph();
	return 0;
}
/* ����ͼƬ */
void LoadImage521()
{
//	loadimage(NULL, L"res/little_mermaid.jpg", WIDTH, HEIGHT);  //1920*1080 ==> 960*540 /* OK */
//	loadimage(NULL, L"res/little_mermaid.jpg");  //Ĭ�ϴӴ������Ͻǿ�ʼ��ͼ������ֻ��һ����
//	loadimage(NULL, _T("res/little_mermaid.jpg"), 960, 540);
//	loadimage(NULL, L"./res/little_mermaid.jpg", 960, 540);
//	loadimage(NULL, L"res//little_mermaid.jpg", 960, 540);
//	loadimage(NULL, L"res\\little_mermaid.jpg", 960, 540);
//	loadimage(NULL, L".\\res\\little_mermaid.jpg", 960, 540);
/*
	IMAGE img;  //����ͼƬ����
	loadimage(&img, L"res/little_mermaid.jpg", WIDTH, HEIGHT);  //���·��
	//loadimage(&img, L"D:\\Documents\\Desktop\\2.jpg", WIDTH, HEIGHT);  //����·��
	putimage(100, 100, &img);  //����
*/
	/*ͼƬ��Դ���*/
	//����һ��
	loadimage(NULL, _T("IMAGE"), _T("BACK"), WIDTH, HEIGHT);  //���ԣ�û���⡣I'm a genius!
	//��������
//	loadimage(NULL, _T("IMAGE"), MAKEINTRESOURCE(IDR_IMAGE_BACK), WIDTH, HEIGHT);  
//	loadimage(NULL, _T("IMAGE"), MAKEINTRESOURCE(IDB_BITMAP_CLOUSE), 400, 607, true);  /*bmpλͼ��Դ���*/

}
/* ��������*/
void PlayMusic521()
{
/*
//	mciSendString(_T("open res/overlap.mp3 alias bgm"), 0, 0, 0);  //�������ļ����������Ϊbgm
	mciSendString(_T("open res/family.wav alias bgm type MPEGVideo"), 0, 0, 0);  //wave�ļ�������Ҫtype MPEGVideo����
//	mciSendString(_T("open D:\\Documents\\Desktop\\overlap.mp3 alias bgm"), 0, 0, 0); 
	//��������Ҫ�пո�·��Ҫд��
	mciSendString(_T("play bgm repeat"), 0, 0, 0);  //�������֣��ظ�
	Sleep(5000);  //�ȴ�5000���룬��5����
	mciSendString(_T("pause bgm"), 0, 0, 0);  //��ͣ����
	Sleep(5000);
	mciSendString(_T("play bgm"), 0, 0, 0);  //��������
	Sleep(5000);
	mciSendString(_T("stop bgm "), 0, 0, 0);  //ֹͣ����
	mciSendString(_T("close bgm "), 0, 0, 0);  //�ر�����
*/
//	PlaySound(_T("res//family.wav"), NULL, SND_LOOP | SND_ASYNC);  //Ҫ���ŵ���wave��ʽ�ļ���

//	Sleep(5000);
//	PlaySound(_T("res//family.wav"), NULL, SND_PURGE);
	/*�����ļ����*/
	PlaySound((LPCWSTR)IDR_WAVE_BGM, NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);
}

/******************************************************************************************************
MCI=Media Control Interface ý����ƽӿ�
mciSendString() ���������ֻ����������ӿڷ�ʽ������в����ִ�Сд��,����ԭ�ͣ�
MCIERROR mciSendString(			// �����ط���ֵ��������룩������mciGetErrorString��ô�����ı�����
	LPCTSTR lpszCommand,		// ָ����null��β�������ַ����������� �豸[����]��
	LPTSTR lpszReturnString,	// ָ����շ�����Ϣ�Ļ�������ΪNULLʱ��������Ϣ
	UINT cchReturn,				// �����������Ĵ�С
	HANDLE hwndCallback			// ������к�notifyʱ����ָ��һ���ص����ڵľ����һ��ΪNULL
);
��ý�����

��ͷ���� xxx��								"play xxx from 0"
ѭ������ .mp3 �ļ�(.wma / .mid ͬ������)��	"open xxx.mp3" �� "play xxx.mp3 repeat"
ѭ������ .wav �ļ���						"open xxx.wav type MPEGVideo" �� "play xxx.wav repeat"
�رյ�ǰ����򿪵����ж�ý���ļ���			"close all"
����ļ������пո���Ҫ��˫�����������ļ�����ע��ת�壩��
			mciSendString("open \"D:\\My Music\\������ ��ף ����.mp3\" alias mymusic", NULL, 0, NULL);
**********************************************************************************************************
PlaySound() Windows API�������ڲ������֣�����ԭ�ͣ�
//��vs2010���ϰ汾��Ҫ����#pragma comment(lib, "winmm.lib")����ʹ��
BOOL PlaySound(
	LPCSTR pszSound,	//ָ����Ҫ�����������ַ������ò���������WAVE�ļ������֣�����WAV��Դ�����֣�
						//�����ڴ����������ݵ�ָ�룬������ϵͳע���WIN.INI�ж����ϵͳ�¼�������
						//����ò���ΪNULL��ֹͣ���ڲ��ŵ�������
	HMODULE hmod,		//Ӧ�ó����ʵ�����������pszSound��ָ��һ����Դ��ʶ������fdwSound������ΪSND_RESOURCE����
						//�����������ΪNULL��
	DWORD fdwSound		//��־����ϣ����ɹ���������TRUE�����򷵻�FALSE��
);
���ű�־��
SND_APPLICATION		//��Ӧ�ó���ָ���Ĺ���������������
SND_ALIAS			//pszSound����ָ����ע����WIN.INI�е�ϵͳ�¼��ı�����
SND_ALIAS_ID		//pszSound����ָ����Ԥ�����������ʶ����
SND_ASYNC  ////			//���첽��ʽ����������PlaySound�����ڿ�ʼ���ź��������ء�
SND_FILENAME		//pszSound����ָ����WAVE�ļ�����
SND_LOOP  ////			//�ظ�����������������SND_ASYNC��־һ��ʹ�á�
SND_MEMORY			//�������뵽�ڴ��е���������ʱpszSound��ָ���������ݵ�ָ�롣
SND_NODEFAULT		//������ȱʡ���������޴˱�־����PlaySound��û�ҵ�����ʱ�Ქ��ȱʡ������
SND_NOSTOP			//PlaySound�����ԭ����������������������FALSE��
SND_NOWAIT			//�������������æ�����Ͳ������������������ء�
SND_PURGE			//ֹͣ��������������йص�������������pszSoundΪNULL����ֹͣ���е�����������ֹͣpszSoundָ����������
SND_RESOURCE  ////		//pszSound������WAVE��Դ�ı�ʶ������ʱҪ�õ�hmod������
SND_SYNC			//ͬ�������������ڲ������PlaySound�����ŷ��ء�
SND_SYSTEM			//��������,��������־�����ã������Ƿ��䵽��Ƶ����ϵͳ֪ͨ��������
					//ϵͳ�������Ƴ���sndvol����ʾ�����������ϵͳ֪ͨ�����������øñ�־�������������顣
*******************************************************************************************************/