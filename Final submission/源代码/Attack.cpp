#include "Attack.h"

bool Attack::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isHit = 0;
	attack = 100;
	return true;
}

//创建攻击物，初始化攻击物图片
Attack* Attack::create(const std::string& filename)
{
	Attack* sprite = new (std::nothrow) Attack();
	if (sprite && sprite->initWithFile(filename + "-attack.png"))
	{
		sprite->autorelease();
		sprite->SetName(filename);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Attack::SetName(std::string filename) {
	name = filename;
}

void Attack::SetPosition(Vec2 pos,Size heroSize) {//应该要根据英雄名称进行分类讨论
	Vec2 site = Vec2(pos.x, pos.y );
	//if(name=="Taric")
	 //   this->setPosition(site.x-23, site.y- 10);//10是调整值
	//else if(name=="En-Taric")
	//	this->setPosition(site.x - 50, site.y - 10);//10是调整值
	//else if()
	//else
		this->setPosition(site.x, site.y);//10是调整值
}

void Attack::SetTarget(Hero* atktarget)
{
	target = atktarget;
	targetPos.x = target->getPosition().x;
	targetPos.y = target->getPosition().y;

	Vec2 enemyPos = target->getPosition();
	GetDistance();
	direction = Vec2(enemyPos.x - this->getPosition().x, enemyPos.y - this->getPosition().y) / distance;

	MoveTo* attackMoveTo = MoveTo::create(1.3, targetPos);
	//this->runAction(attackMoveTo);
	//this->scheduleUpdate();
	if (isHit == 0)
		this->schedule(schedule_selector(Attack::timer), 0.0005f);
}


void Attack::timer(float delta) {//这段代码每0.05s执行一次
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();//获取屏幕的尺寸、位置信息等
	this->setPosition(this->getPosition() + direction/8);//按钮精灵向右移动2像素
	GetDistance();
	//if (present_position == target_position)
	if (distance <= 70){//如果按钮精灵超过屏幕的1/4
		if (!isHit) {
			isHit = 1;//设为已命中
			if (target->IsDead() == 0)
				target->ChangeHP(attack);//target攻击目标是一个Hero类
			this->setVisible(false);//让攻击物消失
			this->unschedule(schedule_selector(Attack::timer));
		}
	}
}

void Attack::GetAttack(double atk)
{
	attack = atk;
}

void Attack::GetDistance() {
	Vec2 currentPos = this->getPosition();
	Vec2 targetPos = target->getPosition();
	//当前位置与目标攻击位置的距离
	distance = sqrt(pow(targetPos.x - currentPos.x, 2) + pow(targetPos.y - currentPos.y, 2));
}

void Attack::update(float dt)//更新攻击物状态
{
	GetDistance();
	//if (present_position == target_position)
	if (distance <= 1)
	{
		isHit = 1;//设为已命中
		target->ChangeHP(attack);//target攻击目标是一个Hero类
		this->unscheduleUpdate();
		this->setVisible(false);//让攻击物消失
	}
}
void Attack::destroy()
{
	if (isHit)
	{
		
		this->unscheduleUpdate();
		isHit = 0;
	}
}
