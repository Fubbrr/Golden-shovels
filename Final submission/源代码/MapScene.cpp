#include<iostream>
#include"MapScene.h"
#include"TeamManager.h"
#include "PauseScene.h"
#include "ui/CocosGUI.h"

using namespace ui;
using namespace std;

extern Server server;
extern Client client;
extern int isOnline;
class PauseScene;

Scene* MapScene::createScene()
{
	return MapScene::create();
}

bool MapScene::init()
{
    //父类初始化失败
    if (!Scene::init())
        return false;

    //获取屏幕显示大小
    auto visibleSize = Director::getInstance()->getVisibleSize();

    /*---------背景-----------*/
    // 获取屏幕尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
     //创建瓦片地图作为背景
    this->background = TMXTiledMap::create("warmap.tmx");
    if (!this->background) {
        return false; // 如果创建失败，则返回 false
    }
    // 将地图添加到场景
    this->addChild(background,0);
    //红色边框
    this->addBorder(background);
    /*---------背景-----------*/

    lastHeroPosition = getStartPosition();

    auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
    for (int i = 1; i < 5; ++i) {
        std::string frameName = "star" + std::to_string(i) + ".png";
        spriteFrameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 50, 50)), frameName);
    }
    Playerinit();//初始化玩家及血条
    isStartBattle = 0;
    //添加商店
    this->createShopLayer(this->player, this->background);

    //设置回合数标签
    round = 1;
    //goldLabel = Label::createWithSystemFont(StringUtils::format("%d", currentGold), "MarkerFelt.ttf", 40);
    Label* textLabel=Label::createWithSystemFont("Round ", "fonts/Marker Felt.ttf", 70);
    textLabel->setColor(Color3B::WHITE);
    textLabel->setPosition(Vec2(visibleSize.width / 2 - 30 + origin.x, visibleSize.height / 2 + origin.y + 400));
    this->addChild(textLabel,4);
    roundLabel = Label::createWithSystemFont(StringUtils::format("%d", round),"fonts/Marker Felt.ttf", 70);
    roundLabel->setColor(Color3B::WHITE);
    roundLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x +100, visibleSize.height / 2 + origin.y +400));//经验显示的位置
    this->addChild(roundLabel, 4);

    //设置暂停按钮
    auto startItem = MenuItemImage::create("pauseButton1.png",
        "pauseButton1.png", CC_CALLBACK_1(MapScene::gamePauseCallback, this));
    startItem->setScale(0.8);
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(visibleSize.width / 2+800 + origin.x, 80));
    this->addChild(menu, 5);

    this->CreateBattle(0);//创建战斗层
    teamManager = TeamManager::getInstance();
    this->scheduleUpdate();
    //this->schedule(schedule_selector(MapScene::musicTimer, 1.4));

    return true;
}

void MapScene::createShopLayer(Player*player, TMXTiledMap* background)
{
	shopLayer = ShopLayer::createWithPlayer(player,background);
	this->addChild(shopLayer);
}

cocos2d::Vec2 MapScene::getStartPosition()
{

	auto objectGroup = background->getObjectGroup("startpoint");  // 获取名为 "start" 的对象层
	if (objectGroup) {
		auto startObject = objectGroup->getObject("startpoint");  // 获取名为 "start" 的对象
		if (!startObject.empty()) {
			float x = startObject["x"].asFloat();
			float y = startObject["y"].asFloat();
			return cocos2d::Vec2(x, y);
		}
	}
	return cocos2d::Vec2::ZERO;  // 如果找不到对象，返回零向量
}

void MapScene::addHeroToMap(Hero* hero)
{
	// 计算新英雄的位置
	const float offset = 150.0f;  // 英雄间的水平间距
	cocos2d::Vec2 newPosition = lastHeroPosition + cocos2d::Vec2(offset, 0);

    hero->setPosition(Vec2(newPosition.x, newPosition.y + 10));

    
	// 更新最后一个英雄的位置
	lastHeroPosition = newPosition;

}

void MapScene::addBorder(TMXTiledMap* background)
{
	auto movableLayer = background->getLayer("move");
	movableLayer->setVisible(1);
	if (!movableLayer)//判断是否存在该图层
		return;
	Size mapSize = background->getMapSize();
	Size tileSize = background->getTileSize();

	// 创建一个新的图层用于添加红色边框
	borderLayer = Layer::create();
	this->addChild(borderLayer);

	for (int x = 0; x < mapSize.width; x++) {
		for (int y = 0; y < mapSize.height; y++) {
			int tileGid = movableLayer->getTileGIDAt(Vec2(x, y));
			if (tileGid > 0) {
				// 获取图块的位置
					Vec2 tilePos = movableLayer->getPositionAt(Vec2(x, y));
				// 创建一个红色边框的精灵
				Sprite* redBorder = Sprite::create("border.png");
				redBorder->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				redBorder->setScale(0.12);
				// 设置红色边框的位置为图块的中心
				redBorder->setPosition(tilePos);
				// 将红色边框添加到图层中
				borderLayer->addChild(redBorder,1);
			}
		}
	}
}

void MapScene::Playerinit()
{
    player = Player::create();
    enPlayer = Player::create();
	//player = new Player(100,0);
	this->addChild(player);
	player->SetSmallHero(Vec2(400, 400),true);
    //player->changeplayerBlood(50);
    /*if (isOnline == 0) {
        enPlayer = new Player(100, 1);
    }
    else {
        enPlayer = new Player(100, 0);
    }*/
	this->addChild(enPlayer);
	enPlayer->SetSmallHero(Vec2(1600, 800),false);
}

Player* MapScene::getCurrentPlayer() {
	return  player;
}

void MapScene::CreateBattle(float t) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (isOnline == 0)//单机模式
    {
        battlelayer = Battle::create();
        this->addChild(battlelayer);
        battlelayer->SetPlayer(player, enPlayer);//设置双方玩家

        //----开始战斗按钮-----
   //创建按钮
        auto startBattleButton = cocos2d::ui::Button::create("startfight.png", "startfight1.png", "startfight.png");

        // 设置按钮的位置、大小等属性
        startBattleButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        startBattleButton->setPosition(cocos2d::Vec2(origin.x + 10, visibleSize.height - 20));
        startBattleButton->setScale(1.2, 1.2);

        // 添加按钮到场景或层
        this->addChild(startBattleButton);

        startBattleButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
                // 按钮点击事件
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
                // 停止当前音乐
                CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("battle.mp3", true);
                CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5); // 设置音量为50%
                //borderLayer->setVisible(0);
                //player->clearWarPlayer();
                enPlayer->SetplayerLevel(player->GetplayerLevel());
                enPlayer->CreateHero();
                teamManager->addHeroToPlayer(this->player);
                isStartBattle = 1;
                battlelayer->Start();
            }
            });
    }
    else {
        battlelayer = Battle::create();
        this->addChild(battlelayer);

        //----开始战斗按钮-----
        //创建按钮
        auto startBattleButton = cocos2d::ui::Button::create("play.png", "play1.png", "play2.png");

        // 设置按钮的位置、大小等属性
        startBattleButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        startBattleButton->setPosition(cocos2d::Vec2(origin.x, visibleSize.height));

        // 添加按钮到场景或层
        this->addChild(startBattleButton);

        startBattleButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
                // 按钮点击事件
                teamManager->addHeroToPlayer(this->player);
                if (isOnline == 1)
                {
                    GameData* mydata = new GameData;
                    GameData* enemydata = new GameData;
                    NetMessage myMessage;
                    NetMessage enMessage;
                    Information information;
                    mydata->setplayerBlood(player->GetPlayerBlood());//获取玩家血量
                    myMessage.SetPlayerBlood(player->GetPlayerBlood());
                    for (int i = 0; i < player->GetHeroNum(); i++)
                    {
                        myMessage.SetNetHero(player->GetWarHero()[i].getId(), player->GetWarHero()[i].getLevel(),
                            1800 - player->GetWarHero()[i].GetHeroPos().x, 980 - player->GetWarHero()[i].GetHeroPos().y, i);
                        myMessage.SetHeroNum(player->GetHeroNum());
                    }
                    std::string serverMessage = myMessage.GetNetMessage();
                    //server.communicate(mydata, enemydata);
                    server.Send(serverMessage);
                    enMessage = server.receive();
                    //enPlayer->changeplayerBlood(100 - enMessage.GetPlayerBlood());
                    enPlayer->SetHeroNum(enMessage.GetHeroNum());
                    enPlayer->GetNetHero(enMessage.GetHero());
                }
                if (isOnline == 2)
                {
                    GameData* mydata = new GameData;
                    GameData* enemydata = new GameData;
                    NetMessage myMessage;
                    NetMessage enMessage;
                    Information information;
                    myMessage.SetPlayerBlood(player->GetPlayerBlood());
                    for (int i = 0; i < player->GetHeroNum(); i++)
                    {
                        myMessage.SetNetHero(player->GetWarHero()[i].getId(), player->GetWarHero()[i].getLevel(),
                            1800 - player->GetWarHero()[i].GetHeroPos().x, 980 - player->GetWarHero()[i].GetHeroPos().y, i);
                        myMessage.SetHeroNum(player->GetHeroNum());
                    }
                    std::string serverMessage = myMessage.GetNetMessage();
                    client.Send(serverMessage);
                    enMessage = client.receive();
                    //enPlayer->changeplayerBlood(100 - enMessage.GetPlayerBlood());
                    enPlayer->SetHeroNum(enMessage.GetHeroNum());
                    enPlayer->GetNetHero(enMessage.GetHero());
                }
                //this->schedule(schedule_selector(MapScene::timer), 0.0005f);

                battlelayer->SetPlayer(player, enPlayer);//设置双方玩家
                isStartBattle = 1;
                battlelayer->Start();
            }
            });
    }
}

void MapScene::update(float dt) {
    if (battlelayer->IsEnd()) {
        //this->unscheduleUpdate();
        shopLayer->showAllHero(1);
        borderLayer->setVisible(1);
        shopLayer->updateGolden();//更新金币数量
        if (isadd == 0) {
            round++;
            isadd = 1;
        }
        roundLabel->setString(StringUtils::format("%d", round));//更新回合数
        player->Restart();
        isStartBattle = 0;
    }
    else {
        isadd = 0;
        if (isStartBattle) {
            shopLayer->showAllHero(0);
            borderLayer->setVisible(0);
        }
    }
    if (player->IsDead()) {
        // 停止当前音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("fail.mp3", true);

        auto lose = Scene::create();
        auto fail = Sprite::create("fail1.png");
        fail->setScale(1.5, 1.5);
        fail->setPosition(Vec2(960, 540));
        lose->addChild(fail);
        /*auto label1 = Label::createWithTTF("LOSE", "fonts/Marker Felt.ttf", 140);
        label1->setPosition(Vec2(960, 540));
        lose->addChild(label1);*/
        Director::getInstance()->pushScene(lose);
        //this->unschedule(schedule_selector(MapScene::musicTimer));
        this->unscheduleUpdate();
    }
    else if (enPlayer->IsDead()) {
        // 停止当前音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("success.mp3", true);

        auto win = Scene::create();
        auto success = Sprite::create("success1.png");
        success->setScale(1.5, 1.5);
        success->setPosition(Vec2(960, 540));
        win->addChild(success);
        /* auto label1 = Label::createWithTTF("WIN", "fonts/Marker Felt.ttf", 140);
         label1->setPosition(Vec2(960, 540));
         win->addChild(label1);*/
        Director::getInstance()->pushScene(win);
        //this->unschedule(schedule_selector(MapScene::musicTimer));
        this->unscheduleUpdate();
    }
}

void MapScene::gamePauseCallback(Ref* pSender)
{
    Director::getInstance()->pushScene(PauseScene::create());

    return;
}

void MapScene::musicTimer(float t) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("attack2.mp3");
}


