#ifndef __SMALL_HERO_H__  
#define __SMALL_HERO_H__ 

#include "cocos2d.h" 
#include "showHPMP.h"
#include "ui/CocosGUI.h"

#include <string>  

using namespace cocos2d;
using std::string;
USING_NS_CC;

class SmallHero : public Sprite
{
public:
	virtual bool init();
	static SmallHero* create();//创建英雄
	void SetBaseInfo(string name, Vec2 pos, bool enabled);//设置初始信息
	Vec2 onMouseUp(Event* event);//得到点击目标位置
	void handleMouseClick(const Vec2& clickPos);
	void smallHeroMoveTo(const Vec2& clickPos);//移动到指定位置
	void StopMove(Ref* obj);//回调函数
	void ChangeHP(float data);//血量变化
	showHPMP* heroHP;//显示英雄的血条
	bool IsDead();
	void SetisMoveEnabled(bool enabled);
	bool GetisMoveEnabled();
	//CREATE_FUNC(SmallHero);

	virtual	void update(float dt);//每一帧更新一次英雄状态

private:
	string smallHeroName;//卡牌名，图片名称
	Vec2 smallHeroPos;//英雄位置
	bool isMoveEnabled;
	
	bool isdead;//是否死亡
	bool ismove;//是否正在移动
	int HP;//玩家血量
};

#endif  