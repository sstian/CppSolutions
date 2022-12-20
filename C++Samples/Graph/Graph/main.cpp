/*  2017.5.21 21:06
	图形库 EasyX Library for C++
1、新建窗口：初始化initgraph(), 关闭closegraph()。
2、贴图  .jpg .bmp：1)加载图像loadimage(NULL)；2)loadimage(&image); putimage(&image)。
3、播放音乐  .mp3 .wav：1)mciSendString()；2)PlaySound()（要 wav 格式的！）。
4、资源打包 res：1)资源res文件夹放在与程序同一目录下；
				2)将资源内嵌到exe文件中：通过资源ID号或资源名称（要用英文双引号引起来！）
	图片 													资源ID				资源类型	资源路径及文件
(1)loadimage(_T("IMAGE"),MAKEINRESOURCE(资源ID))	JPG		IDR_IMAGE_BACK		IMAGE		"res\\back.jpg"
(2)loadimage(_T("IMAGE"),_T("资源名称"))			JPG		BACK                IMAGE       "res\\back.jpg"
													BMP		IDB_BITMAP_CLOUSE   IMAGE       "res\\clouse.bmp"
	音乐 PlaySound((LPCWSTR)资源ID,SND_RESOURCE)	WAVE	IDR_WAVE_BGM		WAVE        "res\\bgm.wav"
	
5、设置图标 icon：项目新建项->资源，ICON->Resource.rc，添加资源->Icon，导入。
6、使程序跨PC运行：项目属性->C/C++->代码生成->运行库：多线程（/MT）。
********** 小贴士 **********
1、_T("内容") <==> L"内容"  宽字符
2、文件路径：/ <==> \\ （绝对路径VS相对路径(OK)，路径英文字符不区分大小写）
3、加载资源：res文件夹放在与程序同一目录下，使用 L"res/1.jpg" 或 L"./res/1.jpg" 均可
*/

#include <graphics.h>  //图形库
#include <cstdlib>  //system()
#include "resource.h"  //资源打包时多需要的头文件
#include <mmsystem.h>  //System APIs for Multimedia多媒体  mciSendString() 
#pragma comment(lib, "winmm.lib")  //隐式链接调用方式，导入winmm.lib库，告诉编译器你要用到winmm.lib库  mciSendString()  PlaySound()
using namespace std;  //命名空间，解决函数重名问题

const int SOLOTION	= 960 * 540;	//窗口分辨率
const int WIDTH		= 960;			//窗口的宽
const int HEIGHT	= 540;			//窗口的高

void LoadImage521();  //加载图片
void PlayMusic521();  //播放音乐

int main(void)
{
	//初始化窗口
	initgraph(WIDTH, HEIGHT);

	LoadImage521();
	PlayMusic521();

	system("pause");
	//关闭窗口
	closegraph();
	return 0;
}
/* 加载图片 */
void LoadImage521()
{
//	loadimage(NULL, L"res/little_mermaid.jpg", WIDTH, HEIGHT);  //1920*1080 ==> 960*540 /* OK */
//	loadimage(NULL, L"res/little_mermaid.jpg");  //默认从窗口左上角开始贴图，可能只有一部分
//	loadimage(NULL, _T("res/little_mermaid.jpg"), 960, 540);
//	loadimage(NULL, L"./res/little_mermaid.jpg", 960, 540);
//	loadimage(NULL, L"res//little_mermaid.jpg", 960, 540);
//	loadimage(NULL, L"res\\little_mermaid.jpg", 960, 540);
//	loadimage(NULL, L".\\res\\little_mermaid.jpg", 960, 540);
/*
	IMAGE img;  //定义图片对象
	loadimage(&img, L"res/little_mermaid.jpg", WIDTH, HEIGHT);  //相对路径
	//loadimage(&img, L"D:\\Documents\\Desktop\\2.jpg", WIDTH, HEIGHT);  //绝对路径
	putimage(100, 100, &img);  //放置
*/
	/*图片资源打包*/
	//方法一、
	loadimage(NULL, _T("IMAGE"), _T("BACK"), WIDTH, HEIGHT);  //可以，没问题。I'm a genius!
	//方法二、
//	loadimage(NULL, _T("IMAGE"), MAKEINTRESOURCE(IDR_IMAGE_BACK), WIDTH, HEIGHT);  
//	loadimage(NULL, _T("IMAGE"), MAKEINTRESOURCE(IDB_BITMAP_CLOUSE), 400, 607, true);  /*bmp位图资源打包*/

}
/* 播放音乐*/
void PlayMusic521()
{
/*
//	mciSendString(_T("open res/overlap.mp3 alias bgm"), 0, 0, 0);  //打开音乐文件，起个别名为bgm
	mciSendString(_T("open res/family.wav alias bgm type MPEGVideo"), 0, 0, 0);  //wave文件加载需要type MPEGVideo命令
//	mciSendString(_T("open D:\\Documents\\Desktop\\overlap.mp3 alias bgm"), 0, 0, 0); 
	//音乐名不要有空格，路径要写对
	mciSendString(_T("play bgm repeat"), 0, 0, 0);  //播放音乐，重复
	Sleep(5000);  //等待5000毫秒，即5分钟
	mciSendString(_T("pause bgm"), 0, 0, 0);  //暂停音乐
	Sleep(5000);
	mciSendString(_T("play bgm"), 0, 0, 0);  //播放音乐
	Sleep(5000);
	mciSendString(_T("stop bgm "), 0, 0, 0);  //停止音乐
	mciSendString(_T("close bgm "), 0, 0, 0);  //关闭音乐
*/
//	PlaySound(_T("res//family.wav"), NULL, SND_LOOP | SND_ASYNC);  //要播放的是wave格式文件！

//	Sleep(5000);
//	PlaySound(_T("res//family.wav"), NULL, SND_PURGE);
	/*音乐文件打包*/
	PlaySound((LPCWSTR)IDR_WAVE_BGM, NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);
}

/******************************************************************************************************
MCI=Media Control Interface 媒体控制接口
mciSendString() 发送命令串（只适用于命令串接口方式，命令串中不区分大小写）,函数原型：
MCIERROR mciSendString(			// 出错返回非零值（错误代码），可用mciGetErrorString获得错误的文本描述
	LPCTSTR lpszCommand,		// 指向以null结尾的命令字符串：”命令 设备[参数]”
	LPTSTR lpszReturnString,	// 指向接收返回信息的缓冲区，为NULL时不返回信息
	UINT cchReturn,				// 上述缓冲区的大小
	HANDLE hwndCallback			// 在命令串中含notify时，它指定一个回调窗口的句柄，一般为NULL
);
多媒体命令：

从头播放 xxx：								"play xxx from 0"
循环播放 .mp3 文件(.wma / .mid 同样可以)：	"open xxx.mp3" ， "play xxx.mp3 repeat"
循环播放 .wav 文件：						"open xxx.wav type MPEGVideo" ， "play xxx.wav repeat"
关闭当前程序打开的所有多媒体文件：			"close all"
如果文件名中有空格，需要用双引号引起来文件名（注意转义）：
			mciSendString("open \"D:\\My Music\\俞丽拿 梁祝 化蝶.mp3\" alias mymusic", NULL, 0, NULL);
**********************************************************************************************************
PlaySound() Windows API函数用于播放音乐，函数原型：
//在vs2010以上版本需要加入#pragma comment(lib, "winmm.lib")才能使用
BOOL PlaySound(
	LPCSTR pszSound,	//指定了要播放声音的字符串，该参数可以是WAVE文件的名字，或是WAV资源的名字，
						//或是内存中声音数据的指针，或是在系统注册表WIN.INI中定义的系统事件声音；
						//如果该参数为NULL则停止正在播放的声音。
	HMODULE hmod,		//应用程序的实例句柄，除非pszSound的指向一个资源标识符（即fdwSound被定义为SND_RESOURCE），
						//否则必须设置为NULL。
	DWORD fdwSound		//标志的组合：若成功则函数返回TRUE，否则返回FALSE。
);
播放标志：
SND_APPLICATION		//用应用程序指定的关联来播放声音。
SND_ALIAS			//pszSound参数指定了注册表或WIN.INI中的系统事件的别名。
SND_ALIAS_ID		//pszSound参数指定了预定义的声音标识符。
SND_ASYNC  ////			//用异步方式播放声音，PlaySound函数在开始播放后立即返回。
SND_FILENAME		//pszSound参数指定了WAVE文件名。
SND_LOOP  ////			//重复播放声音，必须与SND_ASYNC标志一块使用。
SND_MEMORY			//播放载入到内存中的声音，此时pszSound是指向声音数据的指针。
SND_NODEFAULT		//不播放缺省声音，若无此标志，则PlaySound在没找到声音时会播放缺省声音。
SND_NOSTOP			//PlaySound不打断原来的声音播出并立即返回FALSE。
SND_NOWAIT			//如果驱动程序正忙则函数就不播放声音并立即返回。
SND_PURGE			//停止所有与调用任务有关的声音。若参数pszSound为NULL，就停止所有的声音，否则，停止pszSound指定的声音。
SND_RESOURCE  ////		//pszSound参数是WAVE资源的标识符，这时要用到hmod参数。
SND_SYNC			//同步播放声音，在播放完后PlaySound函数才返回。
SND_SYSTEM			//背景窗口,如果这个标志被设置，声音是分配到音频会议系统通知的声音。
					//系统音量控制程序（sndvol）显示音量滑块控制系统通知的声音。设置该标志将控制音量滑块。
*******************************************************************************************************/