#pragma once
//���Ԥ������Ϊ�˷�ֹ�ظ����������޵ݹ�
//�������ifndef......endif.....

#include "cocos2d.h"
#include "Hero.h"  // ���� Hero �ඨ��
#include"HeroData.h"
#include <algorithm> 
#include <vector> 
#include"Information.h"
#include"Player.h"
#include "TeamManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


class ShopLayer:public Layer
{
protected:
	Sprite* shopBackground;
	std::vector<Hero*> heroesInShop;  // �̵��е�Ӣ���б�
   const  std::vector<HeroData> allHeroes = {
		{"hero1","hero1.png"},
		{"hero2","hero2.png"},
		{"hero3","hero3.png"},
		{"hero4","hero4.png"}
	};
   Player* player;
   TMXTiledMap* background;
   Label* goldLabel;

   Vec2 previousHighlightedTile;//�ϸ�λ�õĵ�ͼ����

   Vec2 originalPosition;
   Label* levelLabel;  // ��ʾ��ǰ�غ����ı�ǩ
   TeamManager* teamManager;

   int warHeroNum;//�ϳ�ս����Ӣ������
public:
	//CREATE_FUNC(ShopLayer);
	static ShopLayer* createWithPlayer(Player* player, TMXTiledMap* background) {
		ShopLayer* layer = new ShopLayer(player,background);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	ShopLayer(Player* player, TMXTiledMap* background) : player(player),background(background) {
		// ���캯��ʵ��
	}
	virtual bool init() override;  // ��ʼ������
	void createShopBackground();//����
	void createItemPlace();//��ɫλ
	vector<int>  selectRandomHeroes(int count);//���ѡ�����
	void displayCards();
	void addTouchListenerToCard(Hero* heroCard,int tag);
	void onCardSelected(int heroTag);
	void removeHeroFromShop(Hero* hero);
	void createRefreshButton();
	void refreshShopCards();
	void createGoldIcon();
	void showMessage(const std::string& message);
	
	void addTouchListenerToTeamHero(Hero* hero, TMXTiledMap* background);

	void highlightTileAt(Vec2 mapPos,int color,bool highlight);

	void ShopLayer::createUpgradeButton();
	void ShopLayer::upgradeButtonClickCallback();
	void ShopLayer::onUpgrade();
	void ShopLayer::displayLevelLabel();
	class UpgradeCallback {
	public:
		virtual void onUpgrade() = 0;
	};

	// �����ĺ����������������ص�
	void setUpgradeCallback(UpgradeCallback* callback);
	void showAllHero(int data);
	void updateGolden();//���ڸ���ÿ�غϽ�������ҽ��
};