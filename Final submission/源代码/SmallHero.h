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
	static SmallHero* create();//����Ӣ��
	void SetBaseInfo(string name, Vec2 pos, bool enabled);//���ó�ʼ��Ϣ
	Vec2 onMouseUp(Event* event);//�õ����Ŀ��λ��
	void handleMouseClick(const Vec2& clickPos);
	void smallHeroMoveTo(const Vec2& clickPos);//�ƶ���ָ��λ��
	void StopMove(Ref* obj);//�ص�����
	void ChangeHP(float data);//Ѫ���仯
	showHPMP* heroHP;//��ʾӢ�۵�Ѫ��
	bool IsDead();
	void SetisMoveEnabled(bool enabled);
	bool GetisMoveEnabled();
	//CREATE_FUNC(SmallHero);

	virtual	void update(float dt);//ÿһ֡����һ��Ӣ��״̬

private:
	string smallHeroName;//��������ͼƬ����
	Vec2 smallHeroPos;//Ӣ��λ��
	bool isMoveEnabled;
	
	bool isdead;//�Ƿ�����
	bool ismove;//�Ƿ������ƶ�
	int HP;//���Ѫ��
};

#endif  