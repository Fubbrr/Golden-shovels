#pragma once
#ifndef __HERO_H__  
#define __HERO_H__  
#include "cocos2d.h"  
#include "showHPMP.h"
#include "Attack.h"
#include "Information.h"
using namespace cocos2d;

//英雄（卡牌）基础信息
class showHPMP;
class Attack;

class Hero :public cocos2d::Sprite
{
public:
	// 赋值操作符
	Hero& operator=(const Hero& other) {
		// 检查自赋值
		if (this != &other) {
			// 复制 other 的数据到 this
		}
		return *this;
	}
	static Hero* create(const std::string& filename);
	Hero();
	bool isEmpty() const { 
		return id == 0; 
	} // 判断英雄是否为空
	void upgrade();
	int getId() const;
	void setId(int x);
	int getTag();
	int getLevel() const;
	void setLevel(int x);
	void updateStarLevel();  // 更新星级显示的方法
	void updateImage();
	///原Hero
	void SetHeroDataByTag(int tag,Vec2 pos);//Battle中用，在已知tag时进行英雄初始化
	void SetBaseInfo(heroInformation* info, std::string name, Vec2 pos);//设置英雄初始信息
	void HPInit();
	void SetHeroOn();//设置英雄上场，包括血条初始化，根据heroPos设置位置
	void SetAction();//初始化移动和攻击动作序列
	void SetHeroPos(Vec2 Pos);
	Vec2 GetTargetPos();//根据攻击目标得到英雄的战斗位置
	void Movetimer(float delta);
	void HeroMoveTo();//英雄移动到指定位置，包括移动动画的实现（提供移动时间，目标位置）
	void StopMove(Ref* obj);//回调函数，停止所有动作
	void StopAttack(Ref* obj);//回调函数，停止所有动作
	void StartBattle(Hero* target);
	void HeroAttack();//开始攻击动作
	void ChangeHP(float data);//受到攻击减少血量或得到治疗恢复血量
	void ChangeMP();//回蓝，暂时写一个普攻回蓝的简单机制
	void ChangeHeroName(std::string str) {
		heroName = str + heroName;
	}
	double GetAtk();
	bool IsDead();
	bool IsOn();
	bool IsRecover();
	void SetRecover();
	void SetOn(int data);
	void SetDead(int data);
	Hero* ShowTarget();
	double CountDistance();
	CREATE_FUNC(Hero);
	virtual	void update(float dt);//每一帧更新一次英雄状态
	void Destory();
	heroInformation* GetBaseInfo();
	std::string GetName();
	Vec2 GetHeroPos();
	/// ///
	void SetLocation(int x);
	int GetLocation();
	void StarVisible(int x);
	void SetoriPosition(Vec2 pos) {//设置英雄在备战区中的位置
		a = pos;
	}
	Vec2 GetoriPosition() {//得到在备战区中的位置
		return a;
	}
	void musicTimer(float t);
	void updateInfo();//根据当前等级更新生命值和攻击力
private:
	Sprite* star;
	int id;//tag值
	int level;  // 英雄的等级
	cocos2d::Sprite* starSprite;  // 星级表示的精灵
	std::string heroName;         //卡牌名，图片名称
	heroInformation* baseInfo;
	Vec2 heroPos;//英雄位置
	showHPMP* heroHP;//显示英雄的血条
	showHPMP* heroMP;//显示英雄的蓝条
	Attack* heroAttack;//该英雄的攻击物指针
	Hero* atkTarget;//攻击的敌方目标英雄
	bool ison;//是否上场
	bool isdead;//是否死亡
	bool isatk;//是否正在攻击
	bool ismove;//是否正在移动
	bool isFull;//蓝条是否已满（是否释放大招）
	bool isupdate;//是否在update
	bool isrecover;//是否为队友恢复血量
	Animate* moveAction;//移动动作序列
	Animate* attackAction;//攻击动作序列
	float atktimer;//攻击计时器
	float curAtkTimer;//记录当前时间的计时器
	float movetime;//移动需要的时间
	float movetimer;//移动计时器
	float curMoveTimer;//记录当前时间的计时器
	float moveActTimer;
	float curMoveActTimer;
	Vec2 direction;
	int location;
	Vec2 a;
};

#endif  