//Duel.h  决斗 头文件
#pragma once

extern void StartGame();	//开始游戏
extern void SelectMode();	//选择游戏模式
extern void SingleMode();	//单机模式
extern void CoupleMode();	//双人模式
extern void TripleMode();	//混战模式
extern void TeamMode();		//组队模式

extern void GameInit();			//游戏初始化
extern void DrawSelf(int i);	//己方先抽牌
extern void DrawOther(int i);	//对方先抽牌
extern void LifeValue(int player, int value);	//重绘双方生命数值、血条
extern void DeckCount();						//重绘卡组计数、卡组立体动态显示
extern void RightDown();									//手牌重置
extern void SwapCard(CardButton& src, CardButton& dst);		//交换卡牌
extern void ShuffleHand();									//洗牌（升序排列）
extern bool CheckOut(vector<CardButton>& check);			//出牌牌型检验
extern bool CheckAttack(vector<CardButton>& check);			//战斗牌型检验
extern bool OtherProduce(vector<CardButton>& play, vector<CardButton>& respond);	//对方压牌
extern bool OtherAgainst(vector<CardButton>& play, vector<CardButton>& respond);		//对方反击

extern void DealCards(int draw);							//重新分法手牌
extern bool CheckProduce(vector<CardButton>& play, vector<CardButton>& respond);	//己方压牌判断大小
extern bool CheckAgainst(vector<CardButton>& play);									//自己反击
extern void OtherStart();									//对方先攻
