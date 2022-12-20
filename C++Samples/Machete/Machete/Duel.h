//Duel.h  ���� ͷ�ļ�
#pragma once

extern void StartGame();	//��ʼ��Ϸ
extern void SelectMode();	//ѡ����Ϸģʽ
extern void SingleMode();	//����ģʽ
extern void CoupleMode();	//˫��ģʽ
extern void TripleMode();	//��սģʽ
extern void TeamMode();		//���ģʽ

extern void GameInit();			//��Ϸ��ʼ��
extern void DrawSelf(int i);	//�����ȳ���
extern void DrawOther(int i);	//�Է��ȳ���
extern void LifeValue(int player, int value);	//�ػ�˫��������ֵ��Ѫ��
extern void DeckCount();						//�ػ濨��������������嶯̬��ʾ
extern void RightDown();									//��������
extern void SwapCard(CardButton& src, CardButton& dst);		//��������
extern void ShuffleHand();									//ϴ�ƣ��������У�
extern bool CheckOut(vector<CardButton>& check);			//�������ͼ���
extern bool CheckAttack(vector<CardButton>& check);			//ս�����ͼ���
extern bool OtherProduce(vector<CardButton>& play, vector<CardButton>& respond);	//�Է�ѹ��
extern bool OtherAgainst(vector<CardButton>& play, vector<CardButton>& respond);		//�Է�����

extern void DealCards(int draw);							//���·ַ�����
extern bool CheckProduce(vector<CardButton>& play, vector<CardButton>& respond);	//����ѹ���жϴ�С
extern bool CheckAgainst(vector<CardButton>& play);									//�Լ�����
extern void OtherStart();									//�Է��ȹ�
