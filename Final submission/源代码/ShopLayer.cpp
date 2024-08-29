#include "ShopLayer.h"
#include"HeroData.h"
#include"Hero.h"
#include"Information.h"
#include"Player.h"
#include"TeamManager.h"
#include"MapScene.h"
#include<vector>
#include<algorithm>
#include "cocos/ui/UIButton.h"  // 引入UIButton头文件
#include "cocos/ui/UIWidget.h"  // 引入UIWidget头文件

const int DisplayedCardNum = 5;

bool ShopLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    /*--------------初始化商店界面----------------*/
        //创建商店背景
    this->createShopBackground();

	//角色位背景
	this->createItemPlace();

	this->createRefreshButton();

	this->createGoldIcon();

	//经验
	levelLabel = nullptr;  // 在成员变量的初始化中添加这一行
	warHeroNum = 0;
	this->createUpgradeButton();

	this->displayLevelLabel();
    /*--------------初始化商店界面----------------*/
	this->displayCards();
	return true;
}

void ShopLayer::createShopBackground()
{
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	shopBackground = Sprite::create("shopbackground2.png");
	// 配置商店背景和其他元素
	Size originalSize = shopBackground->getContentSize();//获取原始图片大小
	// 设置锚点为中点
	shopBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	// 设置新的宽度和高度
	float newWidth = visibleSize.width; // 占据整个屏幕宽度
	float newHeight = visibleSize.height / 4; // 占据屏幕高度的1/4
	// 应用缩放
	shopBackground->setScale(0.85, 0.23);
	// 设置位置，使商店位于屏幕底部
	shopBackground->setPosition(Vec2(950, 0));
	this->addChild(shopBackground, 0);
}

void ShopLayer::createItemPlace()
{
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// 计算第一张背景图的起始位置
	float startX = 800.0f;
	float startY = 20;
	float itemWidth = 125.0f; // 假设每张背景图的宽度
	float itemHeight = 125.0f; // 假设每张背景图的高度
	float itemSpacing = 5.0f;//间距
	// 循环创建和放置四张背景图
	for (int i = 0; i < DisplayedCardNum; ++i) {
		auto itemBackground = Sprite::create("position.png");
		itemBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		//itemBackground->setScale(0.6, 0.6);
		itemBackground->setContentSize(Size(itemWidth, itemHeight)); // 设置背景图尺寸
		//startY = (shopBackground->getContentSize().height/2);
		//float itemWidth = itemBackground->getContentSize().width;
		itemBackground->setPosition(startX + i * (itemWidth + itemSpacing), startY);
		this->addChild(itemBackground);
	}
}

vector<int>  ShopLayer::selectRandomHeroes(int count)
{
	std::vector<int> tags = {1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	std::random_shuffle(tags.begin(), tags.end());
	if (count > tags.size()) 
		count = tags.size();
	return std::vector<int>(tags.begin(), tags.begin() + count);
}

void ShopLayer::displayCards()
{
	Vec2 shopbg = shopBackground->getPosition();
	float cardSpacing = 12.0f;//间隔
	float startX = 800.0f;//起始坐标值
	float itemWidth = 117.0f; // 假设每张背景图的宽度
	float itemHeight = 117.0f; // 假设每张背景图的高度
/*-----------------------预置值------------------------*/

	int count = DisplayedCardNum ;
	std::vector<int> heroTags = selectRandomHeroes(DisplayedCardNum);

	for (int i = 0; i < heroTags.size(); ++i) {
		int tag = heroTags[i];
		std::string heroName = Information::getNameByTag(tag);
		std::string heroImagePath = Information::getHeroPathByTag(tag);  

		Hero* heroCard = Hero::create(heroImagePath);  // 使用正确的图片路径
		if (!heroCard) {
			continue;
		}
		heroCard->setId(tag);
		heroCard->setContentSize(Size(itemWidth, itemHeight));
		float posX = startX + i * (itemWidth + cardSpacing);
		float posY = 83;
		heroCard->setPosition(Vec2(posX, posY));
		heroCard->setUserData(new std::string(heroName));  // 存储英雄名称

		this->addTouchListenerToCard(heroCard, tag);
		this->addChild(heroCard);
		heroesInShop.push_back(heroCard);
		
	}
	//this->createRefreshButton();  // 添加刷新按钮
}


void ShopLayer::addTouchListenerToCard(Hero* heroCard,int tag) {
	// 为卡牌添加触摸事件监听器的逻辑
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [heroCard, this, tag](Touch* touch, Event* event) -> bool {
		if (heroCard->getBoundingBox().containsPoint(touch->getLocation())) {
			this->onCardSelected(tag);
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, heroCard);//为卡牌添加监听器
	// 稍后移除特定的监听器
	//_eventDispatcher->removeEventListener(touchListener);
}

void ShopLayer::onCardSelected(int heroTag) {
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//Player* player = Player::getInstance();
	teamManager = TeamManager::getInstance();
	const int HeroCost = 10;  // 假设每个英雄的成本是10金币

	if (player->hasEnoughGold(HeroCost)) {
		player->spendGold(HeroCost);  // 减少玩家的金币

		// 更新金币数量标签的显示内容
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));

		// 从已创建的英雄中找到对应的英雄实例
		Hero* selectedHero = nullptr;
		for (auto& hero : heroesInShop) {
			std::string* heroName = static_cast<std::string*>(hero->getUserData());
			if (heroName && *heroName == Information::getNameByTag(heroTag)) {
				selectedHero = hero;
				selectedHero->setId(hero->getId());
				break;
			}
		}//遍历商店中的英雄，找到和tag对应的英雄加入队伍

		if (selectedHero) {
			// 移除卡牌的触摸事件监听器
			_eventDispatcher->removeEventListenersForTarget(selectedHero);
			// 添加新的触摸事件监听器以处理队伍逻辑
			this->addTouchListenerToTeamHero(selectedHero,background);
			teamManager->addOrUpdateHeroToTeam(selectedHero);  // 将英雄添加到队伍
			removeHeroFromShop(selectedHero);
			
		}

	}
	else {
		// 显示一个提示消息
		auto label = Label::createWithSystemFont("No enough money!", "arial", 50);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(label);
		label->setColor(Color3B::RED);
		label->runAction(Sequence::create(
			DelayTime::create(2),  // 延迟2秒
			RemoveSelf::create(),   // 移除自身
			nullptr
		));
	}
	 
}

void ShopLayer::removeHeroFromShop(Hero* hero) {
	if (hero) {
		//hero->removeFromParent();  // 从层中移除英雄卡牌，会卡死
		heroesInShop.erase(std::remove(heroesInShop.begin(), heroesInShop.end(), hero), heroesInShop.end());  // 从容器中移除

	}
}

void ShopLayer::createRefreshButton() {
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Size shopbgSize = shopBackground->getContentSize();
	float startX = visibleSize.width / 2 - shopbgSize.width / 2;

	auto refreshButton = cocos2d::ui::Button::create("Refresh1.png", "Refresh1.png");

	float scale = 0.6f; // 缩小到原始大小的
	refreshButton->setScale(scale);

	Size buttonSize = refreshButton->getContentSize();//注意：得到的大小是没有缩放前的大小！

	// 设置按钮的位置为商店左下角
	float posX = 530;
	float posY = 50;
	refreshButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	refreshButton->setPosition(Vec2(posX, posY));

	refreshButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			this->refreshShopCards();  // 调用刷新商店卡牌的方法
		}
		});
	this->addChild(refreshButton, 2);
}

void ShopLayer::refreshShopCards() {
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//Player* player = Player::getInstance();
	TeamManager* teamManager = TeamManager::getInstance();
	
	const int Cost = 20;
	if (player->hasEnoughGold(Cost)) {
		if (heroesInShop.empty() == 0) {
			for (auto& hero : heroesInShop) {
				hero->removeFromParent();  // 从层中移除英雄卡牌
			}
		}
		player->spendGold(Cost);  // 减少玩家的金币

		// 更新金币数量标签的显示内容
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));
		heroesInShop.clear();  // 清空容器
		displayCards();  // 重新展示随机抽取的角色
	}
	else {
		// 显示一个提示消息
		auto label = Label::createWithSystemFont("No enough money!", "arial", 50);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(label);
		label->setColor(Color3B::RED);
		label->runAction(Sequence::create(
			DelayTime::create(2),  // 延迟2秒
			RemoveSelf::create(),   // 移除自身
			nullptr
		));
	}
}

void ShopLayer::createGoldIcon() {

	/*------------------金币图-------------------------------------------------*/

	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size shopbgSize = shopBackground->getContentSize();
	float startX = visibleSize.width / 2 - shopbgSize.width / 2;
	auto gold = Sprite::create("gold.png");
	float scale = 1.2f; // 缩小到原始大小的
	gold->setScale(scale);
	gold->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	gold->setPosition(Vec2(1500, 900));
	this->addChild(gold);
	/*------------------金币图-------------------------------------------------*/

	/*-----------钱数-------------------------------*/
	 // 获取Player实例
	//auto player = Player::getInstance();

	int currentGold = this->player->getGold();
	// 创建标签用于显示钱数
	goldLabel = Label::createWithSystemFont(StringUtils::format("%d", currentGold), "MarkerFelt.ttf", 40);
	goldLabel->setColor(Color3B::WHITE);
	// 设置标签位置（这里我们将其放在图标的右侧）
	goldLabel->setPosition(Vec2(1510, 900));

	// 将标签作为子节点添加到精灵
	this->addChild(goldLabel);
	/*-----------钱数-------------------------------*/

}

void ShopLayer::addTouchListenerToTeamHero(Hero* hero, TMXTiledMap* background) {
	auto touchListener = EventListenerTouchOneByOne::create();

	// 触摸开始时的回调
	touchListener->onTouchBegan = [this,hero](Touch* touch, Event* event) -> bool {
		if (hero->getBoundingBox().containsPoint(touch->getLocation())) {
			originalPosition = hero->getPosition(); // 记录初始位置
			return true;
		}
		return false;
	};

	// 触摸移动时的回调
	touchListener->onTouchMoved = [this, hero, background](Touch* touch, Event* event) {
		auto newPosition = hero->getPosition() + touch->getDelta();
		hero->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		hero->setPosition(newPosition); // 放置新的位置

		Size mapSize = background->getMapSize();
		Size tileSize = (background->getTileSize());
		int x = newPosition.x / tileSize.width;
		int y = ((background->getMapSize().height * background->getTileSize().height) - newPosition.y) / background->getTileSize().height;
		Vec2 mapPos = Vec2(x, y);
		if (x >= 0 && x < background->getMapSize().width && y >= 0 && y < background->getMapSize().height && y >= background->getMapSize().height / 2) {
			// mapPos 在 TileMap 范围内
			this->highlightTileAt(mapPos, 1, true);
		}
		else {
			// mapPos 超出 TileMap 范围
			this->highlightTileAt(mapPos, 0, true);
		}

		// 这里你可以根据 x 和 y 做进一步的处理
	};

	// 触摸结束时的回调
	touchListener->onTouchEnded = [this, hero, background](Touch* touch, Event* event) {
		Size mapSize = background->getMapSize();
		Size tileSize = background->getTileSize();
		//Vec2 mapPos = Vec2((int)(hero->getPosition().x / tileSize.width),
			//(int)(hero->getPosition().y / tileSize.height));
		Vec2 newPosition = hero->getPosition(); // 放置新的位置
		int x = newPosition.x / tileSize.width;
		int y = ((background->getMapSize().height * background->getTileSize().height) - newPosition.y) / background->getTileSize().height;
		Vec2 mapPos = Vec2(x, y);
		auto movableLayer = background->getLayer("move");
		//bool isMovable = movableLayer && movableLayer->getTileGIDAt(mapPos) != 0;
		//isMovable增加了玩家等级的判断
		bool isMovable = (x >= 0 && (warHeroNum < player->GetplayerLevel())&& x < background->getMapSize().width && y >= 0 && y < background->getMapSize().height && y >= background->getMapSize().height / 2);
		if (isMovable) {
			// 如果在 movableLayer 范围内，更新角色的位置
			hero->setPosition(hero->getPosition()); // 这里可能需要进行坐标转换以适应地图
			hero->SetLocation(1);
			//hero->StarVisible(0);
			hero->SetHeroPos(hero->getPosition());
			warHeroNum++;
		}
		else {
			// 如果不在范围内，将角色移回到最初的位置
			hero->setPosition(hero->GetoriPosition());
			if (hero->GetLocation() == 1)
				warHeroNum--;
			hero->SetLocation(0);
		}

		// 清除高亮显示
		this->highlightTileAt(previousHighlightedTile, 1, false);
	};

	// 触摸取消时的回调（好像目前没有用
	touchListener->onTouchCancelled = [hero](Touch* touch, Event* event) {
		// 通常将其处理逻辑与onTouchEnded相同
		hero->setLocalZOrder(0); // 恢复Z顺序
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, hero);
}

void ShopLayer::highlightTileAt(Vec2 mapPos,int color,bool highlight)
{
	auto movableLayer = background->getLayer("move");
	if (!movableLayer)//判断是否存在该图层
		return;

	// 检查'Movable'图层中是否有瓦片
	bool isMovable = movableLayer && movableLayer->getTileGIDAt(mapPos) != 0;

	// 首先清除上一个高亮的瓦片
	if (previousHighlightedTile != Vec2::ZERO) {
		auto previousTile = movableLayer->getTileAt(previousHighlightedTile);
		if (previousTile) {
			previousTile->setColor(Color3B::WHITE); // 设置为默认颜色
			previousTile->setOpacity(255); // 设置为不透明
		}
	}
	// 获取要高亮的瓦片
	auto tile = movableLayer->getTileAt(mapPos);
	if (color) {
		if (tile && highlight) {
			if (isMovable) {
				// 设置瓦片的颜色为绿色
				tile->setColor(Color3B::GREEN);

				// 设置瓦片的不透明度为半透明
				tile->setOpacity(100);
				previousHighlightedTile = mapPos; // 更新上一次高亮的位置
			}
			else {
				previousHighlightedTile = Vec2::ZERO; // 如果不高亮，则重置
			}
		}
		else if (tile) {
			tile->setColor(Color3B::WHITE);    // 未高亮显示时的默认颜色
		}
	}
	else {
		if (tile && highlight) {
			if (isMovable) {
				// 设置瓦片的颜色为红色
				tile->setColor(Color3B::RED);

				// 设置瓦片的不透明度为半透明
				tile->setOpacity(100);
				previousHighlightedTile = mapPos; // 更新上一次高亮的位置
			}
			else {
				previousHighlightedTile = Vec2::ZERO; // 如果不高亮，则重置
			}
		}
		else if (tile) {
			tile->setColor(Color3B::WHITE);    // 未高亮显示时的默认颜色
		}
	}
}

void ShopLayer::createUpgradeButton() {
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Size shopbgSize = shopBackground->getContentSize();

	auto upgradeButton = cocos2d::ui::Button::create("exp.png", "exp.png");
	// 创建升级按钮

	float scale = 0.53f; // 缩小到原始大小的
	upgradeButton->setScale(0.55, 0.57);
	upgradeButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	Size buttonSize = upgradeButton->getContentSize();
	float posX = 621;
	float posY = 80;
	upgradeButton->setPosition(Vec2(posX, posY));

	upgradeButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			this->upgradeButtonClickCallback();  // 调用刷新商店卡牌的方法
		}
		});
	this->addChild(upgradeButton, 1);
}

void ShopLayer::upgradeButtonClickCallback() {
	// 处理按钮点击事件，增加等级

	if ( player->getGold() >= 4) {
		// 在这里实现升级逻辑
		onUpgrade();
		player->spendGold(4);
		// 更新金币数量标签的显示内容
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));
		// 更新显示当前等级的标签
		displayLevelLabel();
	}

}

void ShopLayer::onUpgrade() {
	player->SetplayerExperience(player->GetplayerExperience()+4);
	while (player->GetplayerExperience() >=player->GetplayerNeedExperience()) {
		player->SetplayerExperience(player->GetplayerExperience() - player->GetplayerNeedExperience());
		player->SetplayerNeedExperience(player->GetplayerNeedExperience() + 4);
		player->SetplayerLevel(player->GetplayerLevel() + 1);
	}
}

void ShopLayer::displayLevelLabel() {
	// 移除之前的等级标签
	if (levelLabel) {
		levelLabel->removeFromParent();
	}

	// 创建标签用于显示等级
	levelLabel = Label::createWithSystemFont("Level: " + std::to_string(player->GetplayerLevel()) +
		"  Exp: " + std::to_string(player->GetplayerExperience()) + " / " + std::to_string(player->GetplayerNeedExperience()), "arial", 30);

	levelLabel->setColor(Color3B::WHITE);
	levelLabel->setPosition(Vec2(300, 50));//经验显示的位置
	this->addChild(levelLabel, 4);
}

void ShopLayer::showAllHero(int data) {
	teamManager->setAllVisiable(data);
}

void ShopLayer::updateGolden() {
	int currentGold = player->getGold();
	goldLabel->setString(StringUtils::format("%d", currentGold));
}