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
    //�����ʼ��ʧ��
    if (!Scene::init())
        return false;

    //��ȡ��Ļ��ʾ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();

    /*---------����-----------*/
    // ��ȡ��Ļ�ߴ�
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
     //������Ƭ��ͼ��Ϊ����
    this->background = TMXTiledMap::create("warmap.tmx");
    if (!this->background) {
        return false; // �������ʧ�ܣ��򷵻� false
    }
    // ����ͼ��ӵ�����
    this->addChild(background,0);
    //��ɫ�߿�
    this->addBorder(background);
    /*---------����-----------*/

    lastHeroPosition = getStartPosition();

    auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
    for (int i = 1; i < 5; ++i) {
        std::string frameName = "star" + std::to_string(i) + ".png";
        spriteFrameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 50, 50)), frameName);
    }
    Playerinit();//��ʼ����Ҽ�Ѫ��
    isStartBattle = 0;
    //����̵�
    this->createShopLayer(this->player, this->background);

    //���ûغ�����ǩ
    round = 1;
    //goldLabel = Label::createWithSystemFont(StringUtils::format("%d", currentGold), "MarkerFelt.ttf", 40);
    Label* textLabel=Label::createWithSystemFont("Round ", "fonts/Marker Felt.ttf", 70);
    textLabel->setColor(Color3B::WHITE);
    textLabel->setPosition(Vec2(visibleSize.width / 2 - 30 + origin.x, visibleSize.height / 2 + origin.y + 400));
    this->addChild(textLabel,4);
    roundLabel = Label::createWithSystemFont(StringUtils::format("%d", round),"fonts/Marker Felt.ttf", 70);
    roundLabel->setColor(Color3B::WHITE);
    roundLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x +100, visibleSize.height / 2 + origin.y +400));//������ʾ��λ��
    this->addChild(roundLabel, 4);

    //������ͣ��ť
    auto startItem = MenuItemImage::create("pauseButton1.png",
        "pauseButton1.png", CC_CALLBACK_1(MapScene::gamePauseCallback, this));
    startItem->setScale(0.8);
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(visibleSize.width / 2+800 + origin.x, 80));
    this->addChild(menu, 5);

    this->CreateBattle(0);//����ս����
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

	auto objectGroup = background->getObjectGroup("startpoint");  // ��ȡ��Ϊ "start" �Ķ����
	if (objectGroup) {
		auto startObject = objectGroup->getObject("startpoint");  // ��ȡ��Ϊ "start" �Ķ���
		if (!startObject.empty()) {
			float x = startObject["x"].asFloat();
			float y = startObject["y"].asFloat();
			return cocos2d::Vec2(x, y);
		}
	}
	return cocos2d::Vec2::ZERO;  // ����Ҳ������󣬷���������
}

void MapScene::addHeroToMap(Hero* hero)
{
	// ������Ӣ�۵�λ��
	const float offset = 150.0f;  // Ӣ�ۼ��ˮƽ���
	cocos2d::Vec2 newPosition = lastHeroPosition + cocos2d::Vec2(offset, 0);

    hero->setPosition(Vec2(newPosition.x, newPosition.y + 10));

    
	// �������һ��Ӣ�۵�λ��
	lastHeroPosition = newPosition;

}

void MapScene::addBorder(TMXTiledMap* background)
{
	auto movableLayer = background->getLayer("move");
	movableLayer->setVisible(1);
	if (!movableLayer)//�ж��Ƿ���ڸ�ͼ��
		return;
	Size mapSize = background->getMapSize();
	Size tileSize = background->getTileSize();

	// ����һ���µ�ͼ��������Ӻ�ɫ�߿�
	borderLayer = Layer::create();
	this->addChild(borderLayer);

	for (int x = 0; x < mapSize.width; x++) {
		for (int y = 0; y < mapSize.height; y++) {
			int tileGid = movableLayer->getTileGIDAt(Vec2(x, y));
			if (tileGid > 0) {
				// ��ȡͼ���λ��
					Vec2 tilePos = movableLayer->getPositionAt(Vec2(x, y));
				// ����һ����ɫ�߿�ľ���
				Sprite* redBorder = Sprite::create("border.png");
				redBorder->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				redBorder->setScale(0.12);
				// ���ú�ɫ�߿��λ��Ϊͼ�������
				redBorder->setPosition(tilePos);
				// ����ɫ�߿���ӵ�ͼ����
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

    if (isOnline == 0)//����ģʽ
    {
        battlelayer = Battle::create();
        this->addChild(battlelayer);
        battlelayer->SetPlayer(player, enPlayer);//����˫�����

        //----��ʼս����ť-----
   //������ť
        auto startBattleButton = cocos2d::ui::Button::create("startfight.png", "startfight1.png", "startfight.png");

        // ���ð�ť��λ�á���С������
        startBattleButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        startBattleButton->setPosition(cocos2d::Vec2(origin.x + 10, visibleSize.height - 20));
        startBattleButton->setScale(1.2, 1.2);

        // ��Ӱ�ť���������
        this->addChild(startBattleButton);

        startBattleButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
                // ��ť����¼�
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
                // ֹͣ��ǰ����
                CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("battle.mp3", true);
                CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5); // ��������Ϊ50%
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

        //----��ʼս����ť-----
        //������ť
        auto startBattleButton = cocos2d::ui::Button::create("play.png", "play1.png", "play2.png");

        // ���ð�ť��λ�á���С������
        startBattleButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        startBattleButton->setPosition(cocos2d::Vec2(origin.x, visibleSize.height));

        // ��Ӱ�ť���������
        this->addChild(startBattleButton);

        startBattleButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
                // ��ť����¼�
                teamManager->addHeroToPlayer(this->player);
                if (isOnline == 1)
                {
                    GameData* mydata = new GameData;
                    GameData* enemydata = new GameData;
                    NetMessage myMessage;
                    NetMessage enMessage;
                    Information information;
                    mydata->setplayerBlood(player->GetPlayerBlood());//��ȡ���Ѫ��
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

                battlelayer->SetPlayer(player, enPlayer);//����˫�����
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
        shopLayer->updateGolden();//���½������
        if (isadd == 0) {
            round++;
            isadd = 1;
        }
        roundLabel->setString(StringUtils::format("%d", round));//���»غ���
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
        // ֹͣ��ǰ����
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
        // ֹͣ��ǰ����
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


