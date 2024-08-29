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
	void Start();//ս����ʽ��ʼ
	void SetPlayer(Player* my, Player* en);//����˫�����
	void SetHeroData();//���ó������ӵ���Ϣ��Ӧ���Ǳ�սʱ���
	double CountDistance(Vec2 pos1, Vec2 pos2);//����ĳ����Ӣ��֮��ľ���
	void SetAtkTarget(Hero** atk, Hero** tar, int atkNum, int tarNum);
	void UpdateTarget(Hero** atk, Hero** tar, int atkNum, int tarNum);//�������ӵĹ���Ŀ��
	void ResetHero();//��������״̬
	int IsEnd();//�жϱ��غ��Ƿ���������Ƿ�ֳ�ʤ��
	void End();//��ս��������Ĵ�������ССӢ�۵Ŀ�Ѫ
	bool IsNext();
	void Recover(Hero** hero,int num, double data);//�ָ�ȫ��Ѫ��
	virtual	void update(float dt);
	void Destory();//ע�����ж�ʱ��
	void CallBack(float t);
private:
	//std::vector <Hero*> self;
	//std::vector <Hero*> enemy;
	Hero* self[MaxHero];//�ҷ������Ӣ��
	Hero* enemy[MaxHero];//�з������Ӣ��

	site* myPos;//��¼�ҷ��ϳ�Ӣ�۵�λ��
	site* enPos;//��¼�з��ϳ�Ӣ�۵�λ��
	Player* myPlayer;//�ҷ�ССӢ��
	Player* enPlayer;//�з�ССӢ��
	int myHeroNum;
	int enHeroNum;
	int myLive;
	int enLive;

	bool isNext=0;
};

#endif
