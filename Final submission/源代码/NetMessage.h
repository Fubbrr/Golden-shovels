#pragma once
#ifndef _NETMESSAGE_H_
#define _NETMESSAGE_H_

#include <string>
#include <sstream>
#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

struct NetHeroInfo {
	int tag;
	int level;
	int posX;
	int posY;
};

class NetMessage {
public:
	NetMessage();
	void SetPlayerBlood(int data);
	void SetHeroNum(int data);
	void SetNetHero(int a, int b, int c, int d,int i);
	int GetPlayerBlood();
	int GetHeroNum();
	NetHeroInfo* GetHero();
	std::string GetNetMessage();
private:
	int playerBlood;//玩家血量
	int heroNum;//玩家上阵英雄数量
	NetHeroInfo netHero[14];
};


#endif