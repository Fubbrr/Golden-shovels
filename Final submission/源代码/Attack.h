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
	//void SetTargetPos(Vec2 data);//��ʼ��Ŀ��λ��
	void SetPosition(Vec2 pos,Size heroSize);//���ݷ���������Ӣ�۵�λ�ó�ʼ���������λ��
	//void SetMark();
	void SetTarget(Hero* atktarget);//��ʼ������Ŀ��
	void GetAttack(double atk);
	void GetDistance();//���㵱ǰλ�õ�Ŀ��ľ���
	static Attack* Attack::create(const std::string& filename);
	void SetName(std::string filename);
	virtual	void update(float dt);
	void destroy();
	
	void timer(float delta);//ÿ0.05s�ƶ���ť���� ����ķ���
private:
	Hero* target;//����Ŀ��
	Vec2 targetPos;//����Ŀ��λ��
	Vec2 direction;
	double attack;//���𹥻���Ӣ�۵Ĺ�����
	double distance;//����Ŀ��ľ���
	int isHit = 0;//�Ƿ�����
	std::string name;
	//int mark;//���//0����δ���� 1���������
	};

#endif