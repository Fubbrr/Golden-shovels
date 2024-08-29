#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include <vector>
#include "NetMessage.h"
#include "Hero.h"
#include "SmallHero.h"
#define MaxLine 8//一行中能放置的最大英雄数
#define mintag 1
#define maxtag 14
#define MaxHero 9

USING_NS_CC;

//初始血量
constexpr int initplayerBlood = 100;
//每次提升加 4 经验
constexpr int addExperience = 4;
//升级最大经验值加 4
constexpr int addMaxExperience = 4;

struct site {
    int x;
    int y;
};

struct NetHeroInfo;

class Player :public Sprite
{
public:
    //static Player* getInstance();  // 获取玩家实例的方法

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

    //血量减少
    void changeplayerBlood(int hurt);

    int GetPlayerBlood() { return playerBlood; };

    void SetSmallHero(Vec2 pos, bool enabled);//原SetHP

    int GetLv();

    void SetHero(Hero* hero);//(敌方用)设置上场英雄，里面是测试用数据

    Hero* GetWarHero();//传出上场英雄

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
    int gold;  // 玩家的金币数量

    //还活着吗
    bool playerIsDead;

    //玩家血量
    int playerBlood;

    //玩家等级
    int playerLevel;

    //提升到下一级需要多少经验
    int playerNeedExperience;

    //玩家经验
    int playerExperience;

    SmallHero* smallHero;//小小英雄的血条转移到这里

    //showHPMP* myHP;//小小英雄的血条

    Hero chessWarPlayer[MaxHero];//上阵的英雄

    int heroNum = 0;//上阵英雄数量
    ///以下为AI部分
    Vec2 frontPos[MaxLine];//前排英雄可放置的位置
    Vec2 backPos[MaxLine * 2];//后排英雄可放置的位置
    //Information* AIinfo;
};


#endif