#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include <vector>
#include "NetMessage.h"
#include "Hero.h"
#include "SmallHero.h"
#define MaxLine 8//һ�����ܷ��õ����Ӣ����
#define mintag 1
#define maxtag 14
#define MaxHero 9

USING_NS_CC;

//��ʼѪ��
constexpr int initplayerBlood = 100;
//ÿ�������� 4 ����
constexpr int addExperience = 4;
//���������ֵ�� 4
constexpr int addMaxExperience = 4;

struct site {
    int x;
    int y;
};

struct NetHeroInfo;

class Player :public Sprite
{
public:
    //static Player* getInstance();  // ��ȡ���ʵ���ķ���

    //Player();

    CREATE_FUNC(Player);
    static Player* createSprite();
    //Player(int initialGold,bool isAI);
    virtual bool init();
    ~Player();

    bool hasEnoughGold(int amount);

    void spendGold(int amount);
    int  getGold();
    void addGold(int data);

    //Ѫ������
    void changeplayerBlood(int hurt);

    int GetPlayerBlood() { return playerBlood; };

    void SetSmallHero(Vec2 pos, bool enabled);//ԭSetHP

    int GetLv();

    void SetHero(Hero* hero);//(�з���)�����ϳ�Ӣ�ۣ������ǲ���������

    Hero* GetWarHero();//�����ϳ�Ӣ��

    bool IsDead() {
        return playerIsDead;
    }
    void SetHeroNum(int data) { heroNum = data; };
    int GetHeroNum();

    bool addHeroToWar(Hero& hero);

    int GetplayerExperience();

    void SetplayerExperience(int x);

    int GetplayerNeedExperience();

    void SetplayerNeedExperience(int x);

    int GetplayerLevel();

    void SetplayerLevel(int x);

    SmallHero* getSmallHero();

    void Restart();
    void clearWarPlayer() {
        for (auto& hero : chessWarPlayer) {
            Hero* hero1 = Hero::create();
            hero = *hero1;
        }
    }

    void CreateHero();

    void GetNetHero(NetHeroInfo* NetInfo);
protected:
    int gold;  // ��ҵĽ������

    //��������
    bool playerIsDead;

    //���Ѫ��
    int playerBlood;

    //��ҵȼ�
    int playerLevel;

    //��������һ����Ҫ���پ���
    int playerNeedExperience;

    //��Ҿ���
    int playerExperience;

    SmallHero* smallHero;//ССӢ�۵�Ѫ��ת�Ƶ�����

    //showHPMP* myHP;//ССӢ�۵�Ѫ��

    Hero chessWarPlayer[MaxHero];//�����Ӣ��

    int heroNum = 0;//����Ӣ������
    ///����ΪAI����
    Vec2 frontPos[MaxLine];//ǰ��Ӣ�ۿɷ��õ�λ��
    Vec2 backPos[MaxLine * 2];//����Ӣ�ۿɷ��õ�λ��
    //Information* AIinfo;
};


#endif