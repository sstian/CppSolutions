// �������ƣ�ͬʱ�����������ƽ����������ķ���
// ���뻷����Visual C++ 6.0 / 2010��EasyX ���ݰ�
//
#include <graphics.h>

/////////////////////////////////////////////
// ���峣����ö�������ṹ�塢ȫ�ֱ���
/////////////////////////////////////////////

#define	CMD_UP			1	//0000 0001
#define	CMD_DOWN		2	//0000 0010
#define	CMD_LEFT		4	//0000 0100
#define	CMD_RIGHT		8	//0000 1000
#define	CMD_ZOOMIN		16	//0001 0000
#define	CMD_ZOOMOUT		32	//0010 0000
#define	CMD_QUIT		64  //0100 0000

// ����Բ������Ͱ뾶
int g_x, g_y, g_r;



/////////////////////////////////////////////
// ��������
/////////////////////////////////////////////

void Init();						// ��ʼ��
void Quit();						// �˳�
int  GetCommand();					// ��ȡ��������
void DispatchCommand(int _cmd);		// �ַ���������
void OnUp();						// ����
void OnDown();						// ����
void OnLeft();						// ����
void OnRight();						// ����
void OnZoomIn();					// �Ŵ�
void OnZoomOut();					// ��С



									/////////////////////////////////////////////
									// ��������
									/////////////////////////////////////////////

									// ������
void main()
{
	Init();

	int c;
	do
	{
		c = GetCommand();
		DispatchCommand(c);
		Sleep(10);
	} while (!(c & CMD_QUIT));

	Quit();
}

// ��ʼ��
void Init()
{
	// ���û�ͼ��Ļ�ͻ�ͼģʽ
	initgraph(640, 480);
	setwritemode(R2_XORPEN);

	// ����Բ�ĳ�ʼλ�úʹ�С
	g_x = 320;
	g_y = 240;
	g_r = 20;

	// ��ʾ����˵��
	setfont(14, 0, _T("����"));
	outtextxy(20, 270, _T("����˵��"));
	outtextxy(20, 290, _T("�ϣ�����"));
	outtextxy(20, 310, _T("�£�����"));
	outtextxy(20, 330, _T("������"));
	outtextxy(20, 350, _T("�ң�����"));
	outtextxy(20, 370, _T("�� Shift���Ŵ�"));
	outtextxy(20, 390, _T("�� Ctrl����С"));
	outtextxy(20, 410, _T("ESC���˳�"));
	outtextxy(20, 450, _T("ע������ͬʱ�������������ͬʱ���µļ����������ܼ���Ӳ������"));

	// ��Բ
	circle(g_x, g_y, g_r);
}

// �˳�
void Quit()
{
	closegraph();
}

// ��ȡ��������
int GetCommand()
{
	int c = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)		c |= CMD_DOWN;
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)	c |= CMD_ZOOMIN;
	if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)	c |= CMD_ZOOMOUT;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)	c |= CMD_QUIT;

	return c;
}

// �ַ���������
void DispatchCommand(int _cmd)
{
	if (_cmd & CMD_UP)			OnUp();
	if (_cmd & CMD_DOWN)		OnDown();
	if (_cmd & CMD_LEFT)		OnLeft();
	if (_cmd & CMD_RIGHT)		OnRight();
	if (_cmd & CMD_ZOOMIN)		OnZoomIn();
	if (_cmd & CMD_ZOOMOUT)		OnZoomOut();
}

// ����
void OnUp()
{
	circle(g_x, g_y, g_r);
	if (g_y <= 0) g_y = 480; else g_y -= 2;
	circle(g_x, g_y, g_r);
}

// ����
void OnDown()
{
	circle(g_x, g_y, g_r);
	if (g_y >= 480) g_y = 0; else g_y += 2;
	circle(g_x, g_y, g_r);
}

// ����
void OnLeft()
{
	circle(g_x, g_y, g_r);
	if (g_x <= 0) g_x = 640; else g_x -= 2;
	circle(g_x, g_y, g_r);
}

// ����
void OnRight()
{
	circle(g_x, g_y, g_r);
	if (g_x >= 640) g_x = 0; else g_x += 2;
	circle(g_x, g_y, g_r);
}

// �Ŵ�
void OnZoomIn()
{
	circle(g_x, g_y, g_r);
	if (g_r < 100) g_r++;
	circle(g_x, g_y, g_r);
}

// ��С
void OnZoomOut()
{
	circle(g_x, g_y, g_r);
	if (g_r > 10) g_r--;
	circle(g_x, g_y, g_r);
}

/*************************************************************************************************
GetAsyncKeyState() �жϺ�������ʱָ���������״̬������ԭ�ͣ�
SHORT GetAsyncKeyState(
	int vKey		// virtual-key code Ҫ���İ������������
);
���ص� SHORT ֵ��������λΪ 1����ʾ�ü������£������ʾ�ü�����
�ú��������λ������������⿪�ؼ��������Сд����������״̬��
��Ϊ��������������ʹ�� GetKeyState��GetKeyboardState �Ⱥ���
//���� 26 ����ĸ�ļ��룬����ֱ��д 'A'��'B'����������Ҫд VK_A��VK_B�����ּ�Ҳ�ǣ���ֱ��д '0'��'1'������
���ü���VKֵ��
VK_SHIFT		Shift��
VK_LSHIFT		��Shift��
VK_RSHIFT		��Shift��
VK_CONTROL		Ctrl��
VK_LCONTROL		��Ctrl��
VK_RCONTROL		��Ctril��
VK_MENU			Alt��
VK_LMENU		��Alt��
VK_RMENU		��Alt��
VK_LBUTTON		������
VK_RBUTTON		����Ҽ�
VK_ESCAPE		ESC��
VK_RETURN		�س���
VK_TAB			TAB��
VK_SPACE		�ո��
VK_NUMLOCK		NUM LOCK key
VK_CAPITAL		CAPS LOCK key
VK_SCROLL		SCROLL LOCK key
VK_F1			F1 key ����
VK_PRIOR		PAGE UP key
VK_NEXT			PAGE DOWN key
VK_END			END key
VK_HOME			HOME key
VK_SNAPSHOT		PRINT SCREEN key
VK_INSERT		INS key
VK_DELETE		DEL key
VK_LWIN			Left Windows key (Natural keyboard)
VK_RWIN			Right Windows key (Natural keyboard)
VK_NUMPAD0		Numeric keypad 0 key ����
VK_ADD			Add key
VK_SUBTRACT		Subtract key
VK_MULTIPLY		Multiply key
VK_DIVIDE		Divide key
0x30			0 key ����
0x41			A key ����
**************************************************************************************************/