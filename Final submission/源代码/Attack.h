#pragma once
#ifndef __ATTACK_H__
#define __ATTACK_H__

#include "cocos2d.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class Hero;
class Attack : public cocos2d::Sprite
{
public:
	CREATE_FUNC(Attack);
	virtual bool init();
	//void SetTargetPos(Vec2 data);//初始化目标位置
	void SetPosition(Vec2 pos,Size heroSize);//根据发出攻击的英雄的位置初始化攻击物的位置
	//void SetMark();
	void SetTarget(Hero* atktarget);//初始化攻击目标
	void GetAttack(double atk);
	void GetDistance();//计算当前位置到目标的距离
	static Attack* Attack::create(const std::string& filename);
	void SetName(std::string filename);
	virtual	void update(float dt);
	void destroy();
	
	void timer(float delta);//每0.05s移动按钮精灵 具体的方法
private:
	Hero* target;//攻击目标
	Vec2 targetPos;//攻击目标位置
	Vec2 direction;
	double attack;//发起攻击的英雄的攻击力
	double distance;//距离目标的距离
	int isHit = 0;//是否命中
	std::string name;
	//int mark;//标记//0代表未飞行 1代表飞行中
	};

#endif