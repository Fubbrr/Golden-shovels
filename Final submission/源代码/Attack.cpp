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

//�����������ʼ��������ͼƬ
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

void Attack::SetPosition(Vec2 pos,Size heroSize) {//Ӧ��Ҫ����Ӣ�����ƽ��з�������
	Vec2 site = Vec2(pos.x, pos.y );
	//if(name=="Taric")
	 //   this->setPosition(site.x-23, site.y- 10);//10�ǵ���ֵ
	//else if(name=="En-Taric")
	//	this->setPosition(site.x - 50, site.y - 10);//10�ǵ���ֵ
	//else if()
	//else
		this->setPosition(site.x, site.y);//10�ǵ���ֵ
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


void Attack::timer(float delta) {//��δ���ÿ0.05sִ��һ��
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();//��ȡ��Ļ�ĳߴ硢λ����Ϣ��
	this->setPosition(this->getPosition() + direction/8);//��ť���������ƶ�2����
	GetDistance();
	//if (present_position == target_position)
	if (distance <= 70){//�����ť���鳬����Ļ��1/4
		if (!isHit) {
			isHit = 1;//��Ϊ������
			if (target->IsDead() == 0)
				target->ChangeHP(attack);//target����Ŀ����һ��Hero��
			this->setVisible(false);//�ù�������ʧ
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
	//��ǰλ����Ŀ�깥��λ�õľ���
	distance = sqrt(pow(targetPos.x - currentPos.x, 2) + pow(targetPos.y - currentPos.y, 2));
}

void Attack::update(float dt)//���¹�����״̬
{
	GetDistance();
	//if (present_position == target_position)
	if (distance <= 1)
	{
		isHit = 1;//��Ϊ������
		target->ChangeHP(attack);//target����Ŀ����һ��Hero��
		this->unscheduleUpdate();
		this->setVisible(false);//�ù�������ʧ
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
