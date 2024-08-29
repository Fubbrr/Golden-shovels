#pragma once
//这个预编译是为了防止重复，产生无限递归
//可以替代ifndef......endif.....

#include "cocos2d.h"
#include "Hero.h"  // 引入 Hero 类定义
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
	std::vector<Hero*> heroesInShop;  // 商店中的英雄列表
   const  std::vector<HeroData> allHeroes = {
		{"hero1","hero1.png"},
		{"hero2","hero2.png"},
		{"hero3","hero3.png"},
		{"hero4","hero4.png"}
	};
   Player* player;
   TMXTiledMap* background;
   Label* goldLabel;

   Vec2 previousHighlightedTile;//上个位置的地图坐标

   Vec2 originalPosition;
   Label* levelLabel;  // 显示当前回合数的标签
   TeamManager* teamManager;

   int warHeroNum;//上场战斗的英雄数量
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
		// 构造函数实现
	}
	virtual bool init() override;  // 初始化方法
	void createShopBackground();//背景
	void createItemPlace();//角色位
	vector<int>  selectRandomHeroes(int count);//随机选择五个
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

	// 新增的函数用于设置升级回调
	void setUpgradeCallback(UpgradeCallback* callback);
	void showAllHero(int data);
	void updateGolden();//用于更新每回合结束后玩家金币
};