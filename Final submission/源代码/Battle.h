#pragma once
#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Player.h"
#include "MapScene.h"
#define MaxRow 3
#define MaxCol 6
#define MaxHero 9
#define MaxDis 1000000
USING_NS_CC;

struct site;
class Player;
class Battle :public Layer {
public:
	CREATE_FUNC(Battle);
	virtual bool init();
	static Battle* createLayer();
	void Start();//战斗正式开始
	void SetPlayer(Player* my, Player* en);//加载双方玩家
	void SetHeroData();//设置场上棋子的信息，应该是备战时完成
	double CountDistance(Vec2 pos1, Vec2 pos2);//计算某两个英雄之间的距离
	void SetAtkTarget(Hero** atk, Hero** tar, int atkNum, int tarNum);
	void UpdateTarget(Hero** atk, Hero** tar, int atkNum, int tarNum);//更新棋子的攻击目标
	void ResetHero();//重置棋子状态
	int IsEnd();//判断本回合是否结束，即是否分出胜负
	void End();//做战斗结束后的处理，包括小小英雄的扣血
	bool IsNext();
	void Recover(Hero** hero,int num, double data);//恢复全体血量
	virtual	void update(float dt);
	void Destory();//注销所有定时器
	void CallBack(float t);
private:
	//std::vector <Hero*> self;
	//std::vector <Hero*> enemy;
	Hero* self[MaxHero];//我方上阵的英雄
	Hero* enemy[MaxHero];//敌方上阵的英雄

	site* myPos;//记录我方上场英雄的位置
	site* enPos;//记录敌方上场英雄的位置
	Player* myPlayer;//我方小小英雄
	Player* enPlayer;//敌方小小英雄
	int myHeroNum;
	int enHeroNum;
	int myLive;
	int enLive;

	bool isNext=0;
};

#endif
