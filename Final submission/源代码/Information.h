#pragma once
#include <string>
#include <unordered_map>
#include "cocos2d.h"

struct heroInformation {

	float HP;                 //生命值
	float MP;                 //法力值
	float attack;            //攻击力
	float atkspeed;          //攻击速度(每几秒攻击一次)
	float defence;           //防御力
	float atkrange;          //攻击距离
	float movespeed;         //移动速度
	//double attackSpeed;     //攻击物飞行速度

	//int price;             //棋子价格
};
class Information {
public:
	Information();
	static heroInformation* getheroInformation(int heroTag, int level);
	void SetHeroInfo();
    static std::string getNameByTag(int tag);
    static std::string getHeroPathByTag(int tag);
	heroInformation* GetInfoByTag(int tag);
    // 可以添加其他获取英雄信息的方法

public:
	heroInformation HeroInfo[14];
    static std::unordered_map<int, std::string> name;
    static std::unordered_map<int, std::string> imagePaths;
	static std::unordered_map<int, std::string> warimagePaths;
	static std::map<int, heroInformation> info;
    // 可以添加其他存储英雄信息的成员变量
};
