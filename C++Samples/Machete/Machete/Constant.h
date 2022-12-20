//Constant.h  ������ͷ�ļ�
#pragma once

#include <cmath>
#include <vector>
#include "Style.h"

using namespace std;

//��λ������
/* ���ڲ��� */
#define WIDTH		800					//���ڵĿ�Ĭ��ֵ�� 800
#define HEIGHT		600					//���ڵĸߣ�Ĭ��ֵ�� 600
#define SOLUTION	(WIDTH * HEIGHT)	//���ڷֱ��� 800 * 600

const int HALFW = WIDTH	 / 2;		//���ڵĿ������ 400
const int HALFH = HEIGHT / 2;		//���ڵĸ߶����� 300

/* ���˵����� */
#define NUMBERS		4		//��ť���� 4
#define DIMENTIONS	2		//����ά�� 2
const int RECT_WIDTH		= 200;	//Բ�Ǿ��ΰ�ť�Ŀ� 200
const int RECT_HEIGHT		= 50;	//Բ�Ǿ��ΰ�ť�ĸ� 50
const int ELLIPSE_WIDTH		= 50;	//Բ�Ǿ��ε���Բ�Ŀ� 50 
const int ELLIPSE_HEIGHT	= 100;	//Բ�Ǿ��ε���Բ�ĸ� 100
const int g_coordinate[NUMBERS][DIMENTIONS] = { 
	{250,200},{250,300},{250,400},{250,500} };			//��ťλ����ʼ���꣺��ʼ��ѡ��������˳�

const TCHAR g_title[10]		= _T("��  ��");			//��Ϸ����
const TCHAR g_subtitle[20]	= _T("Machete  v1.0");	//��Ϸ�����⣨Ӣ�ģ����汾��

const TCHAR g_menutext[NUMBERS][10] = {
	_T("�� ʼ"),_T("ѡ ��"), _T("�� ��"), _T("�� ��") 
};													 //�˵���ť�ı�

/* ��ѧ���� */
const double PI = 3.14159265358979323846;	//Բ����

#define RAD(angle) (angle / 180.0 * PI)		//����ת���꣺���Ƕ�ת��Ϊ���� 

/* ��Ϸģʽѡ����棨����Ǵ��ڣ�*/
//#define MODE_SINGE	100		//����ģʽ
//#define MODE_COUPLE 200		//˫��ģʽ
//#define MODE_TRIPLE 300		//��սģʽ
//#define MODE_TEAM	400			//���ģʽ

const enum Mode { SELECT = 0, SINGLE = 1, COUPLE = 2, TRIPLE = 3, TEAM = 4, BLANK = 10 };	//��Ϸģʽ
				//ѡ����ʾ	  ����ģʽ��  ˫��ģʽ��  ��սģʽ��  ���ģʽ��//�հ�����

#define STARS  5				//����ǵ������ΰ�ť���� 5
#define POINTS 15				//������������ 15
const LONG FACTOR = 5;				//��������겹������ 5
const LONG RADIUS = 300;			//��������Բ�İ뾶��Ĭ��ֵ�� 300
const LONG REDUCE = 250;			//��������Բ�������뾶 280

const POINT g_stars[POINTS] = {		//����Ƕ�������
/*�±�*/	//�ǵ����꣺�Ϊ��ʼ�㣬˳ʱ�뷽��
/*0  10*/	{ (LONG)(HALFW) 					   , (LONG)(HALFH - RADIUS)                },
/*1  20*/	{ (LONG)(HALFW + RADIUS * cos(RAD(18))), (LONG)(HALFH - RADIUS * sin(RAD(18))) },
/*2  30*/	{ (LONG)(HALFW + RADIUS * sin(RAD(36))), (LONG)(HALFH + RADIUS * cos(RAD(36))) },
/*3  40*/	{ (LONG)(HALFW - RADIUS * sin(RAD(36))), (LONG)(HALFH + RADIUS * cos(RAD(36))) },
/*4  50*/	{ (LONG)(HALFW - RADIUS * cos(RAD(18))), (LONG)(HALFH - RADIUS * sin(RAD(18))) },
			//�������꣺�ƫ��Ϊ��ʼ�㣬˳ʱ�뷽��
/*5  15*/	{ (LONG)(HALFW + (RADIUS - RADIUS * sin(RAD(18))) * tan(RAD(18))), (LONG)(HALFH - RADIUS * sin(RAD(18)))							   },
/*6  25*/	{ (LONG)(HALFW + RADIUS / 2 * tan(RAD(36)))						 , (LONG)(HALFH + RADIUS * sin(RAD(18)) * sin(RAD(18)) / cos(RAD(36))) },
/*7  35*/	{ (LONG)(HALFW)													 , (LONG)(HALFH + RADIUS * sin(RAD(18)) / cos(RAD(36)))				   },
/*8  45*/	{ (LONG)(HALFW - RADIUS / 2 * tan(RAD(36)))						 , (LONG)(HALFH + RADIUS * sin(RAD(18)) * sin(RAD(18)) / cos(RAD(36))) },
/*9  55*/	{ (LONG)(HALFW - (RADIUS - RADIUS * sin(RAD(18)))* tan(RAD(18))) , (LONG)(HALFH - RADIUS * sin(RAD(18)))							   },
			//��������ǵĽ������꣺�Ϊ��ʼ�㣬˳ʱ�뷽��
/*10  010*/	{ (LONG)(HALFW) 					   , (LONG)(HALFH - REDUCE)                },
/*11  020*/	{ (LONG)(HALFW + REDUCE * cos(RAD(18))), (LONG)(HALFH - REDUCE * sin(RAD(18))) },
/*12  030*/	{ (LONG)(HALFW + REDUCE * sin(RAD(36))), (LONG)(HALFH + REDUCE * cos(RAD(36))) },
/*13  040*/	{ (LONG)(HALFW - REDUCE * sin(RAD(36))), (LONG)(HALFH + REDUCE * cos(RAD(36))) },
/*14  050*/	{ (LONG)(HALFW - REDUCE * cos(RAD(18))), (LONG)(HALFH - REDUCE * sin(RAD(18))) }
};						
//LONG sx = 300 * sin(RAD(18));							//Բ�ĵ�����ǽ������εĴ�ֱ����
//LONG sy = (300 - 300 * sin(RAD(18))) * tan(RAD(18));	//����ǽ������εױ߳���һ��
//LONG sz = 300 * sin(RAD(18)) / cos(RAD(36));			//Բ�ĵ���������߾���

//const TCHAR g_modeHint[] = _T("��ѡ����Ϸģʽ��");		//��Ϸģʽ�ı�
const TCHAR g_mode[STARS][5] = { { _T("") }, { _T("����") }, { _T("˫��") }, { _T("��ս") }, { _T("���") } };
								//0				//1-0 1			//2-0 1			//3-0 1			//4-0 1

/* ϵͳ���� */
#define FIELD 5									//�Ծ����ط�������Ĭ��ֵ�� 5
#define BLOOD 12								//�������ֵ��Ĭ��ֵ�� 12
					//���Σ�	��ͷ��		ʮ��
const enum Mouse { MOUSE_HAND, MOUSE_ARROW, MOUSE_CROSS };	//���ָ����״

const int OUT_W		= 80;		//���ư�ťԲ�Ǿ��εĿ��
const int OUT_H		= 40;		//���ư�ťԲ�Ǿ��εĸ߶�
//const int OUT_EW	= 20;		//���ư�ťԲ�Ǿ��ε���Բ�Ŀ��
//const int OUT_EH	= 40;		//���ư�ťԲ�Ǿ��ε���Բ�Ŀ��
const TCHAR g_outtext[2][4] = { _T("����") ,_T("ս��") };		//���ư�ť�ı�
const enum Putout { Ensure, Attack };							//����ѡ����ơ�ս��
const enum Draw { Before, After };	//�����Ⱥ��ȹ� VS ��
const enum Player { Self, Other };	//��ң����� VS �Է�

const TCHAR g_result[3][10] = { _T("DRAW"), _T("YOU WIN"), _T("YOU LOSE") };	//���������ƽ�֡�ʤ����ʧ��

/* �˿��� */
#define CARDS	 54			//�˿���������Ĭ��ֵ�� 54���ƣ�������1�ŷ��棩
#define POKER_W	 80			//�˿��ƵĿ� 80
#define POKER_H	120			//�˿��Ƶĸ� 120

const int DRIFT = POKER_W / 4;	//���Ƹ����߶�
const int THICK = 5;			//������������ʾ

const enum Color { Spade = 1, Heart = 2, Club = 3, Diamond = 4 };										//�˿��ƻ�ɫ
//4 5 6 7 8 9 10 J Q K A B C SMALL LARGE 
const enum Point { P4 = 4, P5 = 5, P6 = 6, P7 = 7, P8 = 8, P9 = 9, P10 = 10,
J = 11, Q = 12, K = 13, A = 14, B = 15, C = 16, SMALL = 1000, LARGE = 2000 };	//�˿��Ƶ���
//11 12 13 % 10 = 1 2 3��//100 200 300 / 100 = 1 2 3��//...

static Poker g_pokers[CARDS + 2] = { Poker(_T("res/images/cover.jpg")),
/*����/��ɫ*/					//����								//����								//÷��									//����
/*4-  1*/	Poker(_T("res/images/4_spade.jpg")), Poker(_T("res/images/4_heart.jpg")), Poker(_T("res/images/4_club.jpg")), Poker(_T("res/images/4_diamond.jpg")), 
/*5-  5*/	Poker(_T("res/images/5_spade.jpg")), Poker(_T("res/images/5_heart.jpg")), Poker(_T("res/images/5_club.jpg")), Poker(_T("res/images/5_diamond.jpg")),
/*6-  9*/	Poker(_T("res/images/6_spade.jpg")), Poker(_T("res/images/6_heart.jpg")), Poker(_T("res/images/6_club.jpg")), Poker(_T("res/images/6_diamond.jpg")),
/*7- 13*/	Poker(_T("res/images/7_spade.jpg")), Poker(_T("res/images/7_heart.jpg")), Poker(_T("res/images/7_club.jpg")), Poker(_T("res/images/7_diamond.jpg")),
/*8- 17*/	Poker(_T("res/images/8_spade.jpg")), Poker(_T("res/images/8_heart.jpg")), Poker(_T("res/images/8_club.jpg")), Poker(_T("res/images/8_diamond.jpg")),
/*9- 21*/	Poker(_T("res/images/9_spade.jpg")), Poker(_T("res/images/9_heart.jpg")), Poker(_T("res/images/9_club.jpg")), Poker(_T("res/images/9_diamond.jpg")),
/*10-25*/	Poker(_T("res/images/0_spade.jpg")), Poker(_T("res/images/0_heart.jpg")), Poker(_T("res/images/0_club.jpg")), Poker(_T("res/images/0_diamond.jpg")),
/*J- 29*/	Poker(_T("res/images/j_spade.jpg")), Poker(_T("res/images/j_heart.jpg")), Poker(_T("res/images/j_club.jpg")), Poker(_T("res/images/j_diamond.jpg")),
/*Q- 33*/	Poker(_T("res/images/q_spade.jpg")), Poker(_T("res/images/q_heart.jpg")), Poker(_T("res/images/q_club.jpg")), Poker(_T("res/images/q_diamond.jpg")),
/*K- 37*/	Poker(_T("res/images/k_spade.jpg")), Poker(_T("res/images/k_heart.jpg")), Poker(_T("res/images/k_club.jpg")), Poker(_T("res/images/k_diamond.jpg")),
/*A- 41*/	Poker(_T("res/images/1_spade.jpg")), Poker(_T("res/images/1_heart.jpg")), Poker(_T("res/images/1_club.jpg")), Poker(_T("res/images/1_diamond.jpg")),
/*2- 45*/	Poker(_T("res/images/2_spade.jpg")), Poker(_T("res/images/2_heart.jpg")), Poker(_T("res/images/2_club.jpg")), Poker(_T("res/images/2_diamond.jpg")),
/*3- 49*/	Poker(_T("res/images/3_spade.jpg")), Poker(_T("res/images/3_heart.jpg")), Poker(_T("res/images/3_club.jpg")), Poker(_T("res/images/3_diamond.jpg")),
/*SL-53*/	Poker(_T("res/images/joker_small.jpg")), Poker(_T("res/images/joker_large.jpg")),
/*zone-55*/	Poker(_T("res/images/zone.jpg"))
};												//һ���˿���

/* ȫ�ֱ������� */
extern int g_DeckThick;				//�����ȣ���ʾ����Ч��
extern CardButton g_cbDeck;			//������
extern vector<CardButton> g_cbOtherHand;	//�Է�������
extern vector<CardButton> g_cbOtherField;	//�Է�������
extern vector<CardButton> g_cbSelfField;	//����������
extern vector<CardButton> g_cbSelfHand;		//����������
//extern RECT g_rectOtherHint;				//�Է�������ʾ
//extern RECT g_rectSelfHint;				//����������ʾ
extern int g_OtherLife;			//�Է�������ֵ
extern int g_SelfLife;			//����������ֵ
extern vector<CardButton> g_check;		//���ȥ����
extern vector<CardButton> g_respond;	//�Է���Ӧ����
extern int g_hurt;						//�˺�������
extern int g_defend;					//����������
