#pragma once
//���Ԥ������Ϊ�˷�ֹ�ظ����������޵ݹ�
//�������ifndef......endif.....

#include "cocos2d.h"
#include"Hero.h"
#include "Battle.h"
#include "ShopLayer.h"
#include "Server.h"
#include "Client.h"
#include"Command.h"
#include "NetMessage.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class Battle;
class MapScene :public Scene
{
protected:
	cocos2d::Vec2 lastHeroPosition;  // ��¼���һ��Ӣ�۵�λ��

	Player* player; // �洢�� Player ʵ�������û�ָ��
	ShopLayer* shopLayer;
	Battle* battlelayer;
	TeamManager* teamManager;
	Player* enPlayer;//�з����
	bool isStartBattle;
	Label* roundLabel;
	int round;//�غ���
	bool isadd;
	Layer* borderLayer;
public:
	//��ͼ
	TMXTiledMap* background;

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);//���ڴ���Cocos2d-x��Ϸ�����еĽڵ������Զ������ʵ��

	//�����̵��ʵ��
	void createShopLayer(Player* player, TMXTiledMap* background);

	cocos2d::Vec2 getStartPosition();  // �·�������ȡ��ʼλ��

	void addHeroToMap(Hero* hero);

	void Playerinit();

	Player* getCurrentPlayer();

	void addBorder(TMXTiledMap* background);

	void CreateBattle(float t);

	virtual	void update(float dt);

	void gamePauseCallback(Ref* pSender);

	void musicTimer(float t);
};
