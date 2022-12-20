//Style.cpp  ��ʽ ʵ���ļ�
#include <graphics.h>
#include <ctime>
#include <vector>
#include <string>
#include <mmsystem.h>
#include "Constant.h"
#include "Style.h"
#include "Duel.h"
#include "Option.h"
#include "Help.h"

#pragma comment(lib,"winmm.lib")
//using namespace std;

/* ���˵����� */
void MainMenu()
{	
	mciSendString(_T("stop bgm"), 0, 0, 0);
	mciSendString(_T("close bgm"), 0, 0, 0);

	mciSendString(_T("open res/sounds/overlap.mp3 alias theme"), 0, 0, 0);
	mciSendString(_T("play theme repeat"), 0, 0, 0);

	//�����л���ʼ��׼��
	cleardevice();
	HWND hWnd = Button::MouseShape(MOUSE_ARROW);
	SetWindowText(hWnd, _T("Machete -- �ö���"));	//���ڱ���
	SetWindowRgn(hWnd, NULL, true);	 //�ָ�Ĭ�ϵľ��δ��ڣ����˵��������

	MenuButton mbutton[NUMBERS];	//�˵���ť�������� 4

	//����ͼ
	loadimage(NULL, _T("res/images/main.jpg"));

	//����
	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight = 100;
	font.lfWidth = 60;
	wcscpy_s(font.lfFaceName, _T("���Ŀ���"));
	font.lfQuality = ANTIALIASED_QUALITY;	//���ÿ��������
	settextstyle(&font);					

	//settextstyle(100, 60, _T("���Ŀ���"));	//�ı���ʽ����ȡ��߶ȡ�����
	setbkmode(TRANSPARENT);					//���ֱ���͸��
	settextcolor(RGB(8, 246, 221));			//���ⱳ��ɫ��ƫ��ɫ
	outtextxy(105, 45, g_title);			//����ı�λ�ü�����
	settextcolor(RGB(4, 132, 251));			//����ǰ��ɫ��ƫ��ɫ
	outtextxy(100, 40, g_title);	
	//Ӣ�ĸ����⼰�汾��
	settextstyle(40, 20, _T("Times New Roman"));
	settextcolor(RGB(221, 25, 250));		//ƫ��ɫ
	outtextxy(340, 150, g_subtitle);
	//�˵���ť
	int y = 0;  //������
	RECT rect;	//��ʱ���δ洢��
	for (int i = 0; i < NUMBERS; i++)
	{
		rect = { g_coordinate[i][y], g_coordinate[i][y + 1],
			 g_coordinate[i][y] + RECT_WIDTH, g_coordinate[i][y + 1] + RECT_HEIGHT };  //��������
		setlinestyle(PS_SOLID, 3);	//���ͣ�ʵ�ߡ����
		roundrect(rect.left, rect.top, rect.right, rect.bottom, ELLIPSE_WIDTH, ELLIPSE_HEIGHT);  //����Բ�Ǿ���
		setfillcolor(RGB(226, 224, 225));  //���ɫ��ƫ��ɫ
		fillroundrect(rect.left, rect.top, rect.right, rect.bottom, ELLIPSE_WIDTH, ELLIPSE_HEIGHT);  //���Բ�Ǿ���

		mbutton[i].SetRect(rect);  //��ʼ���˵���ť��������

		//�˵���ť�ı�
		font.lfHeight = 45;
		font.lfWidth = 25;
		wcscpy_s(font.lfFaceName, _T("����"));
		settextstyle(&font);
		//settextstyle(45, 25, _T("����"));
		settextcolor(RGB(249, 80, 80));  //ƫ��ɫ
		drawtext(g_menutext[i], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //ˮƽ��ֱ���С�����
	}

	//�˵���ťѡ��Ч��
	while (true)
	{
		//��ȡ�����Ϣ
		switch (MenuButton::MouseMsg().uMsg)
		{
		case WM_MOUSEMOVE:		//����ƶ���ʾ��Ч
			BeginBatchDraw();
				 if (mbutton[0].IsWithin())		mbutton[0].MouseMove(g_menutext[0]);
			else if (mbutton[1].IsWithin())		mbutton[1].MouseMove(g_menutext[1]);
			else if (mbutton[2].IsWithin())		mbutton[2].MouseMove(g_menutext[2]);
			else if (mbutton[3].IsWithin())		mbutton[3].MouseMove(g_menutext[3]);
			else
			{
				mbutton[0].MouseLeave(g_menutext[0]);
				mbutton[1].MouseLeave(g_menutext[1]);
				mbutton[2].MouseLeave(g_menutext[2]);
				mbutton[3].MouseLeave(g_menutext[3]);
			}
			EndBatchDraw();
			break;
		case WM_LBUTTONDOWN:	//��������ѡ����
				 if (mbutton[0].IsWithin())		StartGame();		//��ʼ
			else if (mbutton[1].IsWithin())		OptionSetting();	//ѡ��
			else if (mbutton[2].IsWithin())		HelpDoc();			//����
			else if (mbutton[3].IsWithin())		ExitProgram();		//�˳�
			break;
		case WM_RBUTTONUP:		//������Ҽ��˳�����
			ExitProgram(1);
			break;	
		}
	}
}

/* �˳�����Ĭ��Ϊ0��
//��������������Ĭ���β�ֵ���䶨���в�������Ĭ���β�ֵ��*/
void ExitProgram(int status)
{
	HWND hWnd = GetHWnd();
	int msgboxID;
	switch (status)
	{
	case 0:
		msgboxID = MessageBox(hWnd, _T("���Ҫ�˳���"), _T("�������"),
			MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1);				//ȷ�� ȡ����ѯ��ͼ�꣬Ĭ�ϰ�ť��һ��
		if (IDOK == msgboxID)
			exit(0);
		break;
	case 1:
		msgboxID = MessageBox(hWnd, _T("����֮Ѫ��\n���Խ��գ�\nҪ�뿪���������"), _T("��Ԫ������"),
			MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON1);				//ȷ�� ȡ��������ͼ�꣬Ĭ�ϰ�ť��һ��
		if (IDOK == msgboxID)
			exit(0);
		break;
	default:
		break;
	}
}

/* ��������������м���С������չ���� */
void StarBloom()
{
	POINT pts_pentagon[5];
	for (LONG REDUCE = 0; REDUCE < 300; REDUCE += 10)
	{
		//�������ǽǵ�����
		pts_pentagon[0] = { (LONG)(HALFW - REDUCE * cos(RAD(18))), (LONG)(HALFH - REDUCE * sin(RAD(18))) };//14
		pts_pentagon[1] = { (LONG)(HALFW + REDUCE * cos(RAD(18))), (LONG)(HALFH - REDUCE * sin(RAD(18))) };//11
		pts_pentagon[2] = { (LONG)(HALFW - REDUCE * sin(RAD(36))), (LONG)(HALFH + REDUCE * cos(RAD(36))) };//13
		pts_pentagon[3] = { (LONG)(HALFW)						 , (LONG)(HALFH - REDUCE)                };//10
		pts_pentagon[4] = { (LONG)(HALFW + REDUCE * sin(RAD(36))), (LONG)(HALFH + REDUCE * cos(RAD(36))) };//12
		//srand((unsigned int )time(NULL));					//�Ե�ǰʱ���ʼ�����������������
		setlinecolor(HSLtoRGB((float)(rand()%360), 1, 0.5));	//���������ɫֵ
		polygon(pts_pentagon, 5);								//���������
		Sleep(20);												//��ʱ50���루0.05�룩
	}
}

/* ���������ľ���ֵ */
int calc_abs(int value)
{
	if (value < 0)
		value *= -1;
	return value;
}
/* copy img2 to img1 */
void copy_image(IMAGE* img1, IMAGE* img2)
{
	IMAGE* now_working = GetWorkingImage();
	Resize(img1, img2->getwidth(), img2->getheight());
	SetWorkingImage(img2);
	getimage(img1, 0, 0, img1->getwidth(), img1->getheight());
	SetWorkingImage(now_working);
}
/* ͼ��͸������ 
�ų���ɫΪavoid_color���ݲ�Ϊdeviation��͸����tp(transparency)��0��100 */
void transp_image(int dstX, int dstY, IMAGE *pimg, int avoid_color, int deviation, int tp)
{
	int x, y, num;
	int R, G, B;	//��¼��ͼĳ��ɫ��
					//��¼�ų���ɫɫ��
	int avoid_r = GetRValue(avoid_color);
	int avoid_g = GetGValue(avoid_color);
	int avoid_b = GetBValue(avoid_color);
	IMAGE pSrcImg;	//����ͼ
	IMAGE tempimg;	//��ʱ��ͼ
	copy_image(&tempimg, pimg);
	SetWorkingImage(NULL);//��Ĭ�ϻ�ͼ���ڵĻ�ͼ����
	getimage(&pSrcImg, dstX, dstY, pimg->getwidth(), pimg->getheight());

	//͸�����ݴ�
	if (tp < 0)
	{
		tp = 0;
	}
	else if (tp > 100)
	{
		tp = 100;
	}

	// ��ȡ����ָ���Դ��ָ��
	DWORD* bk_pMem = GetImageBuffer(&pSrcImg);
	//��ͼָ���Դ��ָ��
	DWORD* pMem = GetImageBuffer(&tempimg);

	for (y = 0; y < pimg->getheight(); y++)
	{
		for (x = 0; x < pimg->getwidth(); x++)
		{
			num = y * pimg->getwidth() + x;
			R = GetRValue(pMem[num]);
			G = GetGValue(pMem[num]);
			B = GetBValue(pMem[num]);
			if ((calc_abs(R - avoid_r) <= deviation) && (calc_abs(G - avoid_g) <= deviation) && (calc_abs(B - avoid_b) <= deviation))
			{
				pMem[num] = bk_pMem[num];
			}
			else
			{
				pMem[num] = RGB((R*tp + GetRValue(bk_pMem[num])*(100 - tp)) / 100, (G*tp + GetGValue(bk_pMem[num])*(100 - tp)) / 100, (B*tp + GetBValue(bk_pMem[num])*(100 - tp)) / 100);
			}
		}
	}
	putimage(dstX, dstY, &tempimg);
}

/***********************************************************************************************************/

/* * ���������״ */
HWND Button::MouseShape(int shape)
{
	HWND hWnd = GetHWnd();							//��ȡ���ھ��
	HCURSOR hCursor;
	switch (shape)
	{
	case MOUSE_HAND:			//�������ָ��
		hCursor = LoadCursor(NULL, IDC_HAND);			//���ع����Դ
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);	//���ù������
		break;
	case MOUSE_ARROW:			//��ͷ���ָ��
		hCursor = LoadCursor(NULL, IDC_ARROW);
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);
		break;
	case MOUSE_CROSS:			//ʮ�����ָ��
		hCursor = LoadCursor(NULL, IDC_CROSS);
		SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);
		break;
	default:
		break;
	}
	return hWnd;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

MOUSEMSG MenuButton::mouse_;

/* ���þ�������RECT���� */
void Button::SetRect(const RECT& rect)
{
	left_	= rect.left;
	top_	= rect.top;
	right_	= rect.right;
	bottom_ = rect.bottom;
}

/* ���þ������򣨵�����꣩*/
void Button::SetRect(int left, int top, int right, int bottom)
{
	left_	= left;
	top_	= top;
	right_	= right;
	bottom_ = bottom;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

///* ���þ�������RECT���� */
//void MenuButton::SetRect(const RECT& rect)
//{
//	Button::SetRect(rect);	//���ø���ķ���
//	//setLeft(rect.left);
//	//setTop(rect.top);
//	//setRight(rect.right);
//	//setBottom(rect.bottom);
//}
//
///* ���þ������򣨵�����꣩*/
//void MenuButton::SetRect(int left, int top, int right, int bottom)
//{
//	Button::SetRect(left, top, right, bottom);  //���ø���ķ���
//	//setLeft(left);
//	//setTop(top);
//	//setRight(right);
//	//setBottom(bottom);
//}

/* * ��ȡ��������Ϣ�ӿ� */
MOUSEMSG& MenuButton::MouseMsg()
{
	mouse_ = GetMouseMsg();
	return mouse_;
}

/* �ж�����Ƿ��ڷ�Χ�ڣ��������߽磩����Ҫ�ȵ���MouseMsg()�Ի�ȡ�����Ϣ */
bool MenuButton::IsWithin()
{
	int x = mouse_.x;	//���ָ��x������
	int y = mouse_.y;	//���ָ��x������
	//�ڷ�Χ�ڣ�left_ <= x <= right_ �� top_ <= y <= bottom_
	if ((x > getLeft() && x < getRight()) && (y > getTop() && y < getBottom()))
		return true;
	else
		return false;
}

/* ���������ʽ��������꣬��ɫ��䣬������ɫ�����зŴ� 
	menutext: �˵��ı� */
void MenuButton::MouseMove(const TCHAR* menutext)
{
	Button::MouseShape(MOUSE_HAND);

	RECT rect = { getLeft(), getTop(), getRight(), getBottom() };								//�Զ������Խ�������
	setlinestyle(PS_SOLID, 1);			//���ͣ�ʵ�ߡ����1
	roundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);		//Բ�Ǿ���
	
	setfillcolor(YELLOW);				//���ɫ����ɫ
	fillroundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);	//���Բ�Ǿ���

	settextstyle(47, 27, _T("����"));	//����Ŵ�2����
	settextcolor(GREEN);				//������ɫ����ɫ
	drawtext(menutext, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);						//ˮƽ��ֱ���С�����
}

/* ����뿪��ʽ���ָ�ԭ��Ч������ͷ��꣬��ɫ��䣬�����ɫ�� 
	menutext: �˵��ı� */
void MenuButton::MouseLeave(const TCHAR* menutext)
{
	Button::MouseShape(MOUSE_ARROW);

	RECT rect = { getLeft(), getTop(), getRight(), getBottom() };								//�Զ������Խ�������
	setlinestyle(PS_SOLID, 3);			//���ͣ�ʵ�ߡ����3
	roundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);		//Բ�Ǿ���

	setfillcolor(RGB(226, 224, 225));	//���ɫ��ƫ��ɫ
	fillroundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);	//���Բ�Ǿ���

	settextstyle(45, 25, _T("����"));	//�����С�ָ�
	settextcolor(RGB(249, 80, 80));		//������ɫ��ƫ��ɫ
	drawtext(menutext, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);						//ˮƽ��ֱ���С�����
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* �ǰ�ť���캯��������㣬������һ��ȡ3����*/
//StarButton::StarButton(const POINT* pPoints, int num)
//{
//	for (int i = 0; i < num; i++)
//	{
//		switch (i)
//		{
//		case 0:
//			first_  = pPoints->x;
//			second_ = pPoints->y;
//			break;
//		case 1:
//			setLeft(pPoints->x);
//			setTop(pPoints->y);
//			break;
//		case 2:
//			setRight(pPoints->x);
//			setBottom(pPoints->y);
//			break;
//		default:
//			break;
//		}
//	}
//}

/* ��������������ΰ�ť������㣬������Ĭ��Ϊ3���� */
void StarButton::SetStar(const POINT* pPoints, int num)
{
	for (int i = 0; i < num; i++)
	{
		switch (i)
		{
		case 0:
			firstpt_.x  = pPoints[0].x;
			firstpt_.y  = pPoints[0].y;
			break;
		case 1:
			secondpt_.x = pPoints[1].x;
			secondpt_.y = pPoints[1].y;
			break;
		case 2:
			thirdpt_.x  = pPoints[2].x;
			thirdpt_.y  = pPoints[2].y;
			break;
		default:
			break;
		}
	}
}

/* �ж�����Ƿ��ڷ�Χ�ڣ��������߽磩
	mode: ��Ϸģʽ
�������꣺(x1,y1),(x2,y2) 
-> y = (y2 - y1) / (x2 - x1) * (x - x1) + y1 �� y = (y2 - y1) / (x2 - x1) * (x - x2) + y2 
*/
bool StarButton::IsWithin(int mode)
{
	MOUSEMSG m = MouseMsg();
	bool flag = false;		//�жϱ�־
//							//����ֱ�߷��̼������Ӧ������x��������ֵ
//	LONG y = (thirdpt_.y - secondpt_.y) / (thirdpt_.x - secondpt_.x) * (m.x - secondpt_.x) + secondpt_.y;
	//LONG y1 = (thirdpt_.y - secondpt_.y) / (thirdpt_.x - secondpt_.x) * (m.x - secondpt_.x) + secondpt_.y;
	//LONG y2 = (thirdpt_.y - firstpt_.y) / (thirdpt_.x - firstpt_.x) * (m.x - firstpt_.x) + firstpt_.y;
	//LONG y3 = (secondpt_.y - firstpt_.y) / (secondpt_.x - firstpt_.x) * (m.x - firstpt_.x) + firstpt_.y;
	switch (mode)
	{						//�޶�������xΪ���ķ�Χ
	case SELECT:
		if (m.y < thirdpt_.y)	flag = true;
		else					flag = false;
		break;
	case SINGLE:	
		//if ((m.x > secondpt_.x && m.x < thirdpt_.x && m.y < y1)
		//	&& (m.x > firstpt_.x && m.x < thirdpt_.x && m.y > y2)
		//	&& (m.x > firstpt_.x && m.x < secondpt_.x && m.y < y3))
		//ͨ���ֲ����������ж�
		if ((m.x > firstpt_.x && m.x < secondpt_.x) && (m.y > firstpt_.y && m.y < secondpt_.y))
			flag = true;
		else
			flag = false;
		break;
	case COUPLE:
		if ((m.x > thirdpt_.x && m.x < firstpt_.x) && (m.y > firstpt_.y && m.y < thirdpt_.y))
			flag = true;
		else
			flag = false;
		break;
	case TRIPLE:
		if ((m.x > secondpt_.x && m.x < firstpt_.x) && (m.y > secondpt_.y && m.y < firstpt_.y))
			flag = true;
		else
			flag = false;
		break;
	case TEAM:
		if ((m.x > firstpt_.x && m.x < thirdpt_.x) && (m.y > thirdpt_.y && m.y < firstpt_.y))
			flag = true;
		else
			flag = false;
		break;
	case BLANK:
		if ((m.x > g_stars[8].x && m.x < g_stars[6].x) && (m.y > g_stars[9].y && m.y < g_stars[7].y))
			flag = true;
		else
			flag = false;
		break;
	default:
		break;
	}
	return flag;
}

/* ���������ʽ��������꣬��������ɫ
		mode: ��Ϸģʽ 
*/
void StarButton::MouseMove(int mode)
{
	HWND hWnd = GetHWnd();							//��ȡ���ھ��
	HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);	//���ع����Դ
	SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);	//���ù������

	settextcolor(RGB(36, 250, 232));		//���壺ƫ����ɫ
	switch (mode)
	{						
	case SINGLE:
		outtextxy(180, 215, g_mode[mode][0]);		//"��"
		outtextxy(240, 240, g_mode[mode][1]);		//"��"
		break;
	case COUPLE:
		outtextxy(490, 240, g_mode[mode][0]);		//"˫"
		outtextxy(550, 215, g_mode[mode][1]);		//"��"
		break;
	case TRIPLE:
		outtextxy(440, 375, g_mode[mode][0]);		//"��"
		outtextxy(470, 430, g_mode[mode][1]);		//"ս"
		break;
	case TEAM:
		outtextxy(285, 375, g_mode[mode][0]);		//"��"
		outtextxy(250, 430, g_mode[mode][1]);		//"��"
		break;
	//case BLANK:
	//	Button::MouseShape(MOUSE_CROSS);
	//	break;
	default:
		break;
	}

}

/* ����뿪��ʽ���ָ�ԭ��Ч������ͷ��꣬������ɫ��
	mode: ��Ϸģʽ
*/
void StarButton::MouseLeave(int mode)
{
	HWND hWnd = GetHWnd();
	HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);
	SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);

	settextcolor(RGB(242, 250, 36));		//������ɫ��ƫ���ɫ
	switch (mode)
	{						
	case SINGLE:
		outtextxy(180, 215, g_mode[mode][0]);		//"��"
		outtextxy(240, 240, g_mode[mode][1]);		//"��"
		break;
	case COUPLE:
		outtextxy(490, 240, g_mode[mode][0]);		//"˫"
		outtextxy(550, 215, g_mode[mode][1]);		//"��"
		break;
	case TRIPLE:
		outtextxy(440, 375, g_mode[mode][0]);		//"��"
		outtextxy(470, 430, g_mode[mode][1]);		//"ս"
		break;
	case TEAM:
		outtextxy(285, 375, g_mode[mode][0]);		//"��"
		outtextxy(250, 430, g_mode[mode][1]);		//"��"
		break;
	//case BLANK:
	//	Button::MouseShape(MOUSE_ARROW);
	//	break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* �������
������������꣬�ӿ�  //�����ϸ�
�Է�����ͷ��꣨���䣩���ӿ�  //�����¸�
���飺�������  //����Բ */
void CardButton::MouseMove()
{
	if (getLeft() > 200 && getBottom() > HEIGHT / 2)		//�ڼ�������
	{
		if (true == exit_)	//��������
		{
			Button::MouseShape(MOUSE_HAND);
			//poker_.PlaceCard(getLeft(), getTop() - DRIFT);
			//transp_image(getLeft(), getTop() - DRIFT, &GetImage(), WHITE, 200, 100);
			setlinestyle(PS_SOLID, 5);
			rectangle(getLeft() + 2, getTop() + 2, getRight() - 3, getBottom() - 3);
		}
	}
	else if (getLeft() > 200 && getBottom() < HEIGHT / 2)	//�ڶԷ�����
	{
		Button::MouseShape(MOUSE_ARROW);
		//poker_.PlaceCard(getLeft(), getTop() + DRIFT);
		setlinestyle(PS_SOLID, 5);
		rectangle(getLeft() + 2, getTop() + 2, getRight() - 3, getBottom() - 3);
	}
	else													//��������
	{
		Button::MouseShape(MOUSE_HAND);
		//setlinestyle(PS_SOLID, 5);
		//ellipse(getLeft() + 15, getTop() + 15, getRight() - 15, getBottom() - 15);
	}
}

/* ����뿪
�Է������������飨���ָ�������ͷ��꣬���ƹ�λ */
void CardButton::MouseLeave()
{
	Button::MouseShape(MOUSE_ARROW);
	MOUSEMSG m = MenuButton::MouseMsg();
	if (m.x > 200)
	{
		if (m.y > HEIGHT / 2)
		{
			poker_.PlaceCard(getLeft(), getTop());
			if (down_ && exit_)
			{
				circle((getLeft() + getRight()) / 2, (getTop() + getBottom()) / 2, 30);
			}
		}		
	}
	for (int m = 0; m < FIELD; m++)
	{
		g_pokers[0].PlaceCard(g_cbOtherHand[m]);
	}
}

/* ���������£���ʾ�˿��Ʊ�ѡ��
�������ڿ������Ļ���Բ���ٴΰ�����������ͼ��
�Է�����Ч
���飺����Ͷ������������Ի��� */
void CardButton::LeftDown()
{
	if (getLeft() > 200 && getBottom() > HEIGHT / 2)		//�ڼ�������
	{
		if (exit_)	//��������
		{
			Button::MouseShape(MOUSE_HAND);
			if (!down_)		//����δ��ѡ�е�״̬�±�ѡ����
			{
				down_ = true;
				setlinestyle(PS_SOLID, 5);
				circle((getLeft() + getRight()) / 2, (getTop() + getBottom()) / 2, 30);
			}
			else			//��ѡ�е�״̬���ٴ�ѡ�б�ʾδѡ��
			{
				down_ = false;
				poker_.PlaceCard(getLeft(), getTop());
			}
		}
	}
	else if (getLeft() < 200)
	{
		HWND hWnd = GetHWnd();
		int msgboxID = MessageBox(hWnd, _T("  ��һʱ��ƽ�˾���\n  ��һ��������ա�\n\nȷ��Ҫ����Ͷ����"), 
			_T("��ʮ������Ϊ��"),
			MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON2);				//ȷ�� ȡ��������ͼ�꣬Ĭ�ϰ�ť�ڶ���
		if (IDOK == msgboxID)
		{
			setlinestyle(PS_SOLID, 0);
			LifeValue(Self, 0);
			RECT givein = { 100, 100, 700, 500 };
			settextstyle(70, 35, _T("������κ"));
			drawtext(g_result[2], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU LOSE
			Sleep(2000);	//����ͣ��2��
			MainMenu();
		}
	}
}

/* ���ظ�ֵ=��������ʵ�ֿ��ƵĿ��ٷ��� 
//ֱ��ͨ�� g_cbSelfHand[2] = g_pokers[53] ����ʹ��*/
void CardButton::operator =(const Poker& rPoker) 
{ 
	poker_ = rPoker;
	poker_.PlaceCard(*(this)); 
}

/* �����������������ɫ������� */
void CardButton::ClearCard()
{
	setPoker(g_pokers[55]);				//����������ͼ��
	setfillcolor(RGB(6, 4, 51));		//�����ɫ��ƫ����ɫ
	solidrectangle(getLeft(), getTop(), getRight(), getBottom());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* �����������ɫ������Ŵ� */
void OutButton::MouseMove(const TCHAR* outtext)
{
	Button::MouseShape(MOUSE_HAND);

	RECT rect = { getLeft(), getTop(), getRight(), getBottom() };								//�Զ������Խ�������
	setlinestyle(PS_SOLID, 1);			//���ͣ�ʵ�ߡ����1
	roundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);		//Բ�Ǿ���

	setfillcolor(YELLOW);				//���ɫ����ɫ
	fillroundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);	//���Բ�Ǿ���

	settextstyle(32, 22, _T("����"));	//����Ŵ�2����
	settextcolor(GREEN);				//������ɫ����ɫ
	drawtext(outtext, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);						//ˮƽ��ֱ���С�����
}

/* ����뿪 */
void OutButton::MouseLeave(const TCHAR* outtext)
{
	Button::MouseShape(MOUSE_ARROW);

	RECT rect = { getLeft(), getTop(), getRight(), getBottom() };								//�Զ������Խ�������
	setlinestyle(PS_SOLID, 3);			//���ͣ�ʵ�ߡ����3
	roundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);		//Բ�Ǿ���

	setfillcolor(RGB(226, 224, 225));	//���ɫ��ƫ��ɫ
	fillroundrect(getLeft(), getTop(), getRight(), getBottom(), ELLIPSE_WIDTH, ELLIPSE_HEIGHT);	//���Բ�Ǿ���

	settextstyle(30, 20, _T("����"));	//�����С�ָ�
	settextcolor(RGB(249, 80, 80));		//������ɫ��ƫ��ɫ
	drawtext(outtext, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);						//ˮƽ��ֱ���С�����
}

/* ���������£����ơ�ս�� */
void OutButton::LeftDown(int putout)
{
	bool out, attack;
	int field = 0;		//�����Ƴ�����
	int zone = 0;		//�Է��Ƴ�����
	switch (putout)
	{
	case Ensure:	//����
		if (0 == g_respond.size())	//��ʾ�Լ��ȳ�
		{
			out = CheckOut(g_check);
			if (g_check.size() != 0)
			{
				if (out)
				{
					//�����򳡵��ƶ�	
					for (size_t out = 0; out < g_check.size(); out++)
					{
						g_cbSelfField[field++] = g_check.at(out).getPoker();
					}
					for (int hand = 0; hand < FIELD; hand++)		//�Ƴ�ȥ�����ƿ������ñ�־λ
					{
						if (true == g_cbSelfHand[hand].getDown())
						{
							g_cbSelfHand[hand].setDown(false);
							g_cbSelfHand[hand].setExit(false);
							g_cbSelfHand[hand].ClearCard();
						}
					}
					//ը�� YOU WIN
					if (5 == g_check.size())
					{
						RECT bomb[3];
						for (int blast = 0; blast < 3; blast++)
						{
							bomb[blast].left = g_cbSelfField[blast + 1].getLeft();
							bomb[blast].top = g_cbSelfField[blast + 1].getTop();
							bomb[blast].right = g_cbSelfField[blast + 1].getRight();
							bomb[blast].bottom = g_cbSelfField[blast + 1].getBottom();
						}
						Sleep(500);
						drawtext(_T("ը"), &bomb[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						drawtext(_T("��"), &bomb[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						drawtext(_T("��"), &bomb[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						setlinestyle(PS_SOLID, 0);
						LifeValue(Other, 0);
						RECT givein = { 100, 100, 700, 500 };
						settextstyle(70, 35, _T("������κ"));
						drawtext(g_result[1], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU WIN
						Sleep(2000);	//����ͣ��2��
						MainMenu();
					}

					//�Է�ѹ��
					if (OtherProduce(g_check, g_respond))
					{
						Sleep(200);
						for (size_t play = 0; play < g_respond.size(); play++)		//�Է������򳡵��ƶ�
						{
							g_cbOtherField[zone++] = g_respond.at(play).getPoker();
						}
						for (int h = 0; h < FIELD; h++)		//�Է��Ƴ�ȥ�����ƿ������ñ�־λ
						{
							if (false == g_cbOtherHand[h].getExit())
							{
								g_cbOtherHand[h].ClearCard();
							}
						}

					}
					else
					{
						RECT pass = { g_cbOtherField[0].getLeft(), g_cbOtherField[0].getTop(), g_cbOtherField[0].getRight(), g_cbOtherField[0].getBottom() };
						settextcolor(RGB(247, 121, 157));	//������ɫ��ƫ��ɫ
						drawtext(_T("��"), &pass, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						g_check.clear();
						g_respond.clear();
						Sleep(1000);
						DealCards(Before);	//����
					}

					//�������ѳ����ƻ��ɷ���
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//�������ѳ����ƻ��ɷ���
					for (int m = 0; m < zone; m++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbOtherField[m]);
					}

				}
				else
				{
					HWND hWnd = GetHWnd();
					int msgboxID = MessageBox(hWnd, _T("  ��������\n�����ԡ�����"), _T("���ͣ�"),
						MB_OK | MB_ICONERROR);				//ȷ��������ͼ��
					//settextcolor(RGB(248, 16, 21));		//������ɫ��ƫ�ʺ�ɫ
					//settextstyle(30, 12, _T("������κ"));
					//drawtext(_T("�������������ԣ�"), &g_rectSelfHint, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
		else	//����Ҫ������Ӧ
		{
			out = CheckOut(g_check);
			//ը�� YOU WIN
			if (5 == g_check.size())
			{
				RECT bomb[3];
				for (int blast = 0; blast < 3; blast++)
				{
					bomb[blast].left = g_cbSelfField[blast + 1].getLeft();
					bomb[blast].top = g_cbSelfField[blast + 1].getTop();
					bomb[blast].right = g_cbSelfField[blast + 1].getRight();
					bomb[blast].bottom = g_cbSelfField[blast + 1].getBottom();
				}
				Sleep(500);
				drawtext(_T("ը"), &bomb[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext(_T("��"), &bomb[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext(_T("��"), &bomb[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				setlinestyle(PS_SOLID, 0);
				LifeValue(Other, 0);
				RECT givein = { 100, 100, 700, 500 };
				settextstyle(70, 35, _T("������κ"));
				drawtext(g_result[1], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU WIN
				Sleep(2000);	//����ͣ��2��
				MainMenu();
			}
			if (g_check.size() != 0)
			{
				if (out && CheckProduce(g_respond, g_check))
				{
					//�����򳡵��ƶ�	
					for (size_t out = 0; out < g_check.size(); out++)
					{
						g_cbSelfField[field++] = g_check.at(out).getPoker();
					}
					for (int hand = 0; hand < FIELD; hand++)		//�Ƴ�ȥ�����ƿ������ñ�־λ
					{
						if (true == g_cbSelfHand[hand].getDown())
						{
							g_cbSelfHand[hand].setDown(false);
							g_cbSelfHand[hand].setExit(false);
							g_cbSelfHand[hand].ClearCard();
						}
					}
					//�Է�ѹ��
					if (OtherProduce(g_check, g_respond))
					{
						Sleep(200);
						for (size_t play = 0; play < g_respond.size(); play++)		//�Է������򳡵��ƶ�
						{
							g_cbOtherField[zone++] = g_respond.at(play).getPoker();
						}
						for (int h = 0; h < FIELD; h++)		//�Է��Ƴ�ȥ�����ƿ������ñ�־λ
						{
							if (false == g_cbOtherHand[h].getExit())
							{
								g_cbOtherHand[h].ClearCard();
							}
						}

					}
					else
					{
						RECT pass = { g_cbOtherField[0].getLeft(), g_cbOtherField[0].getTop(), g_cbOtherField[0].getRight(), g_cbOtherField[0].getBottom() };
						settextcolor(RGB(247, 121, 157));	//������ɫ��ƫ��ɫ
						drawtext(_T("��"), &pass, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						Sleep(1000);
						DealCards(Before);	//����
					}

					//�������ѳ����ƻ��ɷ���
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//�������ѳ����ƻ��ɷ���
					for (int m = 0; m < zone; m++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbOtherField[m]);
					}

				}
				else
				{
					HWND hWnd = GetHWnd();
					int msgboxID = MessageBox(hWnd, _T("  ���Ʋ���Ŷ��\n��רעһ�㡣����"), _T("�����㣡"),
						MB_OK | MB_ICONERROR);				//ȷ��������ͼ��
															//settextcolor(RGB(248, 16, 21));		//������ɫ��ƫ�ʺ�ɫ
															//settextstyle(30, 12, _T("������κ"));
															//drawtext(_T("�������������ԣ�"), &g_rectSelfHint, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
		break;
	case Attack:	//ս��
		g_check.clear();
		if (0 == g_respond.size())
		{
			attack = CheckAttack(g_check);
			if (g_check.size() != 0)
			{
				if (attack)
				{
					for (int hand = 0; hand < FIELD; hand++)		//�Ƴ�ȥ�����ƿ������ñ�־λ
					{
						if (true == g_cbSelfHand[hand].getDown())
						{
							g_cbSelfHand[hand].setDown(false);
							g_cbSelfHand[hand].setExit(false);
							g_cbSelfField[field++] = g_cbSelfHand[hand].getPoker();
							g_cbSelfHand[hand].ClearCard();
						}
					}
					//�������ѳ����ƻ��ɷ���
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//�Է�����
					if (OtherAgainst(g_check, g_respond))
					{
						Sleep(200);
						for (size_t play = 0; play < g_respond.size(); play++)		//�Է������򳡵��ƶ�
						{
							g_cbOtherField[zone++] = g_respond.at(play).getPoker();
						}
						for (int h = 0; h < FIELD; h++)		//�Է��Ƴ�ȥ�����ƿ������ñ�־λ
						{
							if (false == g_cbOtherHand[h].getExit())
							{
								g_cbOtherHand[h].ClearCard();
							}
						}
					}
					else
					{
						g_OtherLife -= g_hurt;
						if (g_OtherLife <= 0)
						{
							g_OtherLife = 0;
							LifeValue(Other, g_OtherLife);
							RECT givein = { 100, 100, 700, 500 };
							settextstyle(70, 35, _T("������κ"));
							drawtext(g_result[1], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU WIN
							Sleep(2000);	//����ͣ��2��
							MainMenu();

						}
						LifeValue(Other, g_OtherLife);
						Sleep(1000);
						DealCards(Before);	//����
					}

				}
				else
				{
					HWND hWnd = GetHWnd();
					int msgboxID = MessageBox(hWnd, _T("  ���ڷǹ����Ϳ��ƣ�\n�����������������"), _T("����"),
						MB_OK | MB_ICONERROR);				//ȷ��������ͼ��
				}
			}
		}
		else
		{
			attack = CheckAgainst(g_check);
			if (g_check.size() != 0)
			{
				if (attack)
				{
					for (int hand = 0; hand < FIELD; hand++)		//�Ƴ�ȥ�����ƿ������ñ�־λ
					{
						if (true == g_cbSelfHand[hand].getDown())
						{
							g_cbSelfHand[hand].setDown(false);
							g_cbSelfHand[hand].setExit(false);
							g_cbSelfField[field++] = g_cbSelfHand[hand].getPoker();
							g_cbSelfHand[hand].ClearCard();
						}
					}
					//�������ѳ����ƻ��ɷ���
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//�Է�����
					if (OtherAgainst(g_check, g_respond))
					{
						Sleep(200);
						for (size_t play = 0; play < g_respond.size(); play++)		//�Է������򳡵��ƶ�
						{
							g_cbOtherField[zone++] = g_respond.at(play).getPoker();
						}
						for (int h = 0; h < FIELD; h++)		//�Է��Ƴ�ȥ�����ƿ������ñ�־λ
						{
							if (false == g_cbOtherHand[h].getExit())
							{
								g_cbOtherHand[h].ClearCard();
							}
						}
					}
					else
					{
						g_OtherLife -= g_hurt;
						g_check.clear();
						g_respond.clear();
						if (g_OtherLife <= 0)
						{
							g_OtherLife = 0;
							LifeValue(Other, g_OtherLife);
							RECT givein = { 100, 100, 700, 500 };
							settextstyle(70, 35, _T("������κ"));
							drawtext(g_result[1], &givein, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//YOU WIN
							Sleep(2000);	//����ͣ��2��
							MainMenu();

						}
						LifeValue(Other, g_OtherLife);
						Sleep(1000);
						DealCards(Before);	//����
					}
					//�������ѳ����ƻ��ɷ���
					for (int n = 0; n < field; n++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbSelfField[n]);
					}
					//�������ѳ����ƻ��ɷ���
					for (int m = 0; m < zone; m++)
					{
						Sleep(300);
						g_pokers[0].PlaceCard(g_cbOtherField[m]);
					}

				}
				else
				{
					HWND hWnd = GetHWnd();
					int msgboxID = MessageBox(hWnd, _T("  ������Ч��\n�Ͻ����ȡ�����"), _T("�������ˣ�"),
						MB_OK | MB_ICONERROR);				//ȷ��������ͼ��
				}
			}
		}
		break;

	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����ʱ��ȡͼ��Ĭ�Ͽ�ȡ��߶Ⱦ�Ϊ0���������� 
	��Ĭ���βεĺ���������ʱ˵��������ʱ�������� */
Poker::Poker(LPCTSTR pImgFile, int nWidth, int nHeight)
{	
	//���ؿ���
	//pImageFile_ = pImgFile;
	loadimage(&image_, pImgFile, nWidth, nHeight);

	wstring wcs = pImgFile;
	//��ȡ���Ƶ���
	TCHAR wcsPoints[15][10] = {														//�����ַ���
		_T("4_"), _T("5_"), _T("6_"), _T("7_"), _T("8_"), _T("9_"), _T("0_"),
		_T("j_"), _T("q_"), _T("k_"),
		_T("1_"), _T("2_"), _T("3_"),
		_T("joker_s"), _T("joker_l") };
	int nPoints[15] = { P4, P5, P6, P7, P8, P9, P10, J, Q, K, A, B, C, SMALL, LARGE };	//�������Ӧ��ϵ
	int i;
	for (i = 0; i < 15; i++)
	{
		if (wcs.find(wcsPoints[i]) != wstring::npos)
		{
			point_ = nPoints[i];
			break;
		}
	}
	if (i >= 15)
		point_ = 0;
	//��ȡ���ƻ�ɫ
	//if (wcs.find(_T("spade")) != wstring::npos) color_ = Spade;
	//else if (wcs.find(_T("heart")) != wstring::npos) color_ = Heart;
	//else if (wcs.find(_T("club")) != wstring::npos) color_ = Club;
	//else if (wcs.find(_T("diamond")) != wstring::npos) color_ = Diamond;
	TCHAR wcsColors[4][10] = { _T("spade"), _T("heart"), _T("club"), _T("diamond") };	//��ɫ�ַ���
	int nColors[4] = { Spade, Heart, Club, Diamond };									//�뻨ɫ��Ӧ��ϵ
	for (int i = 0; i < 4; i++)
	{
		if (wcs.find(wcsColors[i]) != wstring::npos)
		{
			color_ = nColors[i];
			break;
		}
	}
}

/* ��ȡ���ƣ�Ĭ�Ͽ�ȡ��߶Ⱦ�Ϊ0����������*/
void Poker::ObtainCard(LPCTSTR pImgFile, int nWidth, int nHeight)
{
	loadimage(&image_, pImgFile, nWidth, nHeight);
}

/* ���ÿ��ƣ�ָ��Ĭ�Ͽ��80���߶�120������λ�õľ��ο��С�� */
void Poker::PlaceCard(int dstX, int dstY, int dstWidth, int dstHeight)
{
	//putimage(dstX, dstY, &image_);
	putimage(dstX, dstY, dstWidth, dstHeight, &image_, 0, 0);
}

/* ���ÿ��ƣ�ָ��Ĭ�Ͽ��80���߶�120������λ�õľ��ο��С����CardButotn����*/
void Poker::PlaceCard(const CardButton& rCbutton, int dstWidth, int dstHeight)
{
	putimage(rCbutton.getLeft(),rCbutton.getTop(), dstWidth, dstHeight, &image_, 0, 0);
}

///* ����==���������أ�ʵ��ͼ��ƥ��*/
//bool Poker::operator ==(const Poker& rPoker)
//{
//	if (0 == wcscmp(pImageFile_, rPoker.getImageFile()))
//		return true;
//	else
//		return false;
//}

