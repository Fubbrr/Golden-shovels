#include "ShopLayer.h"
#include"HeroData.h"
#include"Hero.h"
#include"Information.h"
#include"Player.h"
#include"TeamManager.h"
#include"MapScene.h"
#include<vector>
#include<algorithm>
#include "cocos/ui/UIButton.h"  // ����UIButtonͷ�ļ�
#include "cocos/ui/UIWidget.h"  // ����UIWidgetͷ�ļ�

const int DisplayedCardNum = 5;

bool ShopLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    /*--------------��ʼ���̵����----------------*/
        //�����̵걳��
    this->createShopBackground();

	//��ɫλ����
	this->createItemPlace();

	this->createRefreshButton();

	this->createGoldIcon();

	//����
	levelLabel = nullptr;  // �ڳ�Ա�����ĳ�ʼ���������һ��
	warHeroNum = 0;
	this->createUpgradeButton();

	this->displayLevelLabel();
    /*--------------��ʼ���̵����----------------*/
	this->displayCards();
	return true;
}

void ShopLayer::createShopBackground()
{
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	shopBackground = Sprite::create("shopbackground2.png");
	// �����̵걳��������Ԫ��
	Size originalSize = shopBackground->getContentSize();//��ȡԭʼͼƬ��С
	// ����ê��Ϊ�е�
	shopBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	// �����µĿ�Ⱥ͸߶�
	float newWidth = visibleSize.width; // ռ��������Ļ���
	float newHeight = visibleSize.height / 4; // ռ����Ļ�߶ȵ�1/4
	// Ӧ������
	shopBackground->setScale(0.85, 0.23);
	// ����λ�ã�ʹ�̵�λ����Ļ�ײ�
	shopBackground->setPosition(Vec2(950, 0));
	this->addChild(shopBackground, 0);
}

void ShopLayer::createItemPlace()
{
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// �����һ�ű���ͼ����ʼλ��
	float startX = 800.0f;
	float startY = 20;
	float itemWidth = 125.0f; // ����ÿ�ű���ͼ�Ŀ��
	float itemHeight = 125.0f; // ����ÿ�ű���ͼ�ĸ߶�
	float itemSpacing = 5.0f;//���
	// ѭ�������ͷ������ű���ͼ
	for (int i = 0; i < DisplayedCardNum; ++i) {
		auto itemBackground = Sprite::create("position.png");
		itemBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		//itemBackground->setScale(0.6, 0.6);
		itemBackground->setContentSize(Size(itemWidth, itemHeight)); // ���ñ���ͼ�ߴ�
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
	float cardSpacing = 12.0f;//���
	float startX = 800.0f;//��ʼ����ֵ
	float itemWidth = 117.0f; // ����ÿ�ű���ͼ�Ŀ��
	float itemHeight = 117.0f; // ����ÿ�ű���ͼ�ĸ߶�
/*-----------------------Ԥ��ֵ------------------------*/

	int count = DisplayedCardNum ;
	std::vector<int> heroTags = selectRandomHeroes(DisplayedCardNum);

	for (int i = 0; i < heroTags.size(); ++i) {
		int tag = heroTags[i];
		std::string heroName = Information::getNameByTag(tag);
		std::string heroImagePath = Information::getHeroPathByTag(tag);  

		Hero* heroCard = Hero::create(heroImagePath);  // ʹ����ȷ��ͼƬ·��
		if (!heroCard) {
			continue;
		}
		heroCard->setId(tag);
		heroCard->setContentSize(Size(itemWidth, itemHeight));
		float posX = startX + i * (itemWidth + cardSpacing);
		float posY = 83;
		heroCard->setPosition(Vec2(posX, posY));
		heroCard->setUserData(new std::string(heroName));  // �洢Ӣ������

		this->addTouchListenerToCard(heroCard, tag);
		this->addChild(heroCard);
		heroesInShop.push_back(heroCard);
		
	}
	//this->createRefreshButton();  // ���ˢ�°�ť
}


void ShopLayer::addTouchListenerToCard(Hero* heroCard,int tag) {
	// Ϊ������Ӵ����¼����������߼�
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [heroCard, this, tag](Touch* touch, Event* event) -> bool {
		if (heroCard->getBoundingBox().containsPoint(touch->getLocation())) {
			this->onCardSelected(tag);
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, heroCard);//Ϊ������Ӽ�����
	// �Ժ��Ƴ��ض��ļ�����
	//_eventDispatcher->removeEventListener(touchListener);
}

void ShopLayer::onCardSelected(int heroTag) {
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//Player* player = Player::getInstance();
	teamManager = TeamManager::getInstance();
	const int HeroCost = 10;  // ����ÿ��Ӣ�۵ĳɱ���10���

	if (player->hasEnoughGold(HeroCost)) {
		player->spendGold(HeroCost);  // ������ҵĽ��

		// ���½��������ǩ����ʾ����
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));

		// ���Ѵ�����Ӣ�����ҵ���Ӧ��Ӣ��ʵ��
		Hero* selectedHero = nullptr;
		for (auto& hero : heroesInShop) {
			std::string* heroName = static_cast<std::string*>(hero->getUserData());
			if (heroName && *heroName == Information::getNameByTag(heroTag)) {
				selectedHero = hero;
				selectedHero->setId(hero->getId());
				break;
			}
		}//�����̵��е�Ӣ�ۣ��ҵ���tag��Ӧ��Ӣ�ۼ������

		if (selectedHero) {
			// �Ƴ����ƵĴ����¼�������
			_eventDispatcher->removeEventListenersForTarget(selectedHero);
			// ����µĴ����¼��������Դ�������߼�
			this->addTouchListenerToTeamHero(selectedHero,background);
			teamManager->addOrUpdateHeroToTeam(selectedHero);  // ��Ӣ����ӵ�����
			removeHeroFromShop(selectedHero);
			
		}

	}
	else {
		// ��ʾһ����ʾ��Ϣ
		auto label = Label::createWithSystemFont("No enough money!", "arial", 50);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(label);
		label->setColor(Color3B::RED);
		label->runAction(Sequence::create(
			DelayTime::create(2),  // �ӳ�2��
			RemoveSelf::create(),   // �Ƴ�����
			nullptr
		));
	}
	 
}

void ShopLayer::removeHeroFromShop(Hero* hero) {
	if (hero) {
		//hero->removeFromParent();  // �Ӳ����Ƴ�Ӣ�ۿ��ƣ��Ῠ��
		heroesInShop.erase(std::remove(heroesInShop.begin(), heroesInShop.end(), hero), heroesInShop.end());  // ���������Ƴ�

	}
}

void ShopLayer::createRefreshButton() {
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Size shopbgSize = shopBackground->getContentSize();
	float startX = visibleSize.width / 2 - shopbgSize.width / 2;

	auto refreshButton = cocos2d::ui::Button::create("Refresh1.png", "Refresh1.png");

	float scale = 0.6f; // ��С��ԭʼ��С��
	refreshButton->setScale(scale);

	Size buttonSize = refreshButton->getContentSize();//ע�⣺�õ��Ĵ�С��û������ǰ�Ĵ�С��

	// ���ð�ť��λ��Ϊ�̵����½�
	float posX = 530;
	float posY = 50;
	refreshButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	refreshButton->setPosition(Vec2(posX, posY));

	refreshButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			this->refreshShopCards();  // ����ˢ���̵꿨�Ƶķ���
		}
		});
	this->addChild(refreshButton, 2);
}

void ShopLayer::refreshShopCards() {
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//Player* player = Player::getInstance();
	TeamManager* teamManager = TeamManager::getInstance();
	
	const int Cost = 20;
	if (player->hasEnoughGold(Cost)) {
		if (heroesInShop.empty() == 0) {
			for (auto& hero : heroesInShop) {
				hero->removeFromParent();  // �Ӳ����Ƴ�Ӣ�ۿ���
			}
		}
		player->spendGold(Cost);  // ������ҵĽ��

		// ���½��������ǩ����ʾ����
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));
		heroesInShop.clear();  // �������
		displayCards();  // ����չʾ�����ȡ�Ľ�ɫ
	}
	else {
		// ��ʾһ����ʾ��Ϣ
		auto label = Label::createWithSystemFont("No enough money!", "arial", 50);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(label);
		label->setColor(Color3B::RED);
		label->runAction(Sequence::create(
			DelayTime::create(2),  // �ӳ�2��
			RemoveSelf::create(),   // �Ƴ�����
			nullptr
		));
	}
}

void ShopLayer::createGoldIcon() {

	/*------------------���ͼ-------------------------------------------------*/

	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size shopbgSize = shopBackground->getContentSize();
	float startX = visibleSize.width / 2 - shopbgSize.width / 2;
	auto gold = Sprite::create("gold.png");
	float scale = 1.2f; // ��С��ԭʼ��С��
	gold->setScale(scale);
	gold->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	gold->setPosition(Vec2(1500, 900));
	this->addChild(gold);
	/*------------------���ͼ-------------------------------------------------*/

	/*-----------Ǯ��-------------------------------*/
	 // ��ȡPlayerʵ��
	//auto player = Player::getInstance();

	int currentGold = this->player->getGold();
	// ������ǩ������ʾǮ��
	goldLabel = Label::createWithSystemFont(StringUtils::format("%d", currentGold), "MarkerFelt.ttf", 40);
	goldLabel->setColor(Color3B::WHITE);
	// ���ñ�ǩλ�ã��������ǽ������ͼ����Ҳࣩ
	goldLabel->setPosition(Vec2(1510, 900));

	// ����ǩ��Ϊ�ӽڵ���ӵ�����
	this->addChild(goldLabel);
	/*-----------Ǯ��-------------------------------*/

}

void ShopLayer::addTouchListenerToTeamHero(Hero* hero, TMXTiledMap* background) {
	auto touchListener = EventListenerTouchOneByOne::create();

	// ������ʼʱ�Ļص�
	touchListener->onTouchBegan = [this,hero](Touch* touch, Event* event) -> bool {
		if (hero->getBoundingBox().containsPoint(touch->getLocation())) {
			originalPosition = hero->getPosition(); // ��¼��ʼλ��
			return true;
		}
		return false;
	};

	// �����ƶ�ʱ�Ļص�
	touchListener->onTouchMoved = [this, hero, background](Touch* touch, Event* event) {
		auto newPosition = hero->getPosition() + touch->getDelta();
		hero->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		hero->setPosition(newPosition); // �����µ�λ��

		Size mapSize = background->getMapSize();
		Size tileSize = (background->getTileSize());
		int x = newPosition.x / tileSize.width;
		int y = ((background->getMapSize().height * background->getTileSize().height) - newPosition.y) / background->getTileSize().height;
		Vec2 mapPos = Vec2(x, y);
		if (x >= 0 && x < background->getMapSize().width && y >= 0 && y < background->getMapSize().height && y >= background->getMapSize().height / 2) {
			// mapPos �� TileMap ��Χ��
			this->highlightTileAt(mapPos, 1, true);
		}
		else {
			// mapPos ���� TileMap ��Χ
			this->highlightTileAt(mapPos, 0, true);
		}

		// ��������Ը��� x �� y ����һ���Ĵ���
	};

	// ��������ʱ�Ļص�
	touchListener->onTouchEnded = [this, hero, background](Touch* touch, Event* event) {
		Size mapSize = background->getMapSize();
		Size tileSize = background->getTileSize();
		//Vec2 mapPos = Vec2((int)(hero->getPosition().x / tileSize.width),
			//(int)(hero->getPosition().y / tileSize.height));
		Vec2 newPosition = hero->getPosition(); // �����µ�λ��
		int x = newPosition.x / tileSize.width;
		int y = ((background->getMapSize().height * background->getTileSize().height) - newPosition.y) / background->getTileSize().height;
		Vec2 mapPos = Vec2(x, y);
		auto movableLayer = background->getLayer("move");
		//bool isMovable = movableLayer && movableLayer->getTileGIDAt(mapPos) != 0;
		//isMovable��������ҵȼ����ж�
		bool isMovable = (x >= 0 && (warHeroNum < player->GetplayerLevel())&& x < background->getMapSize().width && y >= 0 && y < background->getMapSize().height && y >= background->getMapSize().height / 2);
		if (isMovable) {
			// ����� movableLayer ��Χ�ڣ����½�ɫ��λ��
			hero->setPosition(hero->getPosition()); // ���������Ҫ��������ת������Ӧ��ͼ
			hero->SetLocation(1);
			//hero->StarVisible(0);
			hero->SetHeroPos(hero->getPosition());
			warHeroNum++;
		}
		else {
			// ������ڷ�Χ�ڣ�����ɫ�ƻص������λ��
			hero->setPosition(hero->GetoriPosition());
			if (hero->GetLocation() == 1)
				warHeroNum--;
			hero->SetLocation(0);
		}

		// ���������ʾ
		this->highlightTileAt(previousHighlightedTile, 1, false);
	};

	// ����ȡ��ʱ�Ļص�������Ŀǰû����
	touchListener->onTouchCancelled = [hero](Touch* touch, Event* event) {
		// ͨ�����䴦���߼���onTouchEnded��ͬ
		hero->setLocalZOrder(0); // �ָ�Z˳��
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, hero);
}

void ShopLayer::highlightTileAt(Vec2 mapPos,int color,bool highlight)
{
	auto movableLayer = background->getLayer("move");
	if (!movableLayer)//�ж��Ƿ���ڸ�ͼ��
		return;

	// ���'Movable'ͼ�����Ƿ�����Ƭ
	bool isMovable = movableLayer && movableLayer->getTileGIDAt(mapPos) != 0;

	// ���������һ����������Ƭ
	if (previousHighlightedTile != Vec2::ZERO) {
		auto previousTile = movableLayer->getTileAt(previousHighlightedTile);
		if (previousTile) {
			previousTile->setColor(Color3B::WHITE); // ����ΪĬ����ɫ
			previousTile->setOpacity(255); // ����Ϊ��͸��
		}
	}
	// ��ȡҪ��������Ƭ
	auto tile = movableLayer->getTileAt(mapPos);
	if (color) {
		if (tile && highlight) {
			if (isMovable) {
				// ������Ƭ����ɫΪ��ɫ
				tile->setColor(Color3B::GREEN);

				// ������Ƭ�Ĳ�͸����Ϊ��͸��
				tile->setOpacity(100);
				previousHighlightedTile = mapPos; // ������һ�θ�����λ��
			}
			else {
				previousHighlightedTile = Vec2::ZERO; // �����������������
			}
		}
		else if (tile) {
			tile->setColor(Color3B::WHITE);    // δ������ʾʱ��Ĭ����ɫ
		}
	}
	else {
		if (tile && highlight) {
			if (isMovable) {
				// ������Ƭ����ɫΪ��ɫ
				tile->setColor(Color3B::RED);

				// ������Ƭ�Ĳ�͸����Ϊ��͸��
				tile->setOpacity(100);
				previousHighlightedTile = mapPos; // ������һ�θ�����λ��
			}
			else {
				previousHighlightedTile = Vec2::ZERO; // �����������������
			}
		}
		else if (tile) {
			tile->setColor(Color3B::WHITE);    // δ������ʾʱ��Ĭ����ɫ
		}
	}
}

void ShopLayer::createUpgradeButton() {
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Size shopbgSize = shopBackground->getContentSize();

	auto upgradeButton = cocos2d::ui::Button::create("exp.png", "exp.png");
	// ����������ť

	float scale = 0.53f; // ��С��ԭʼ��С��
	upgradeButton->setScale(0.55, 0.57);
	upgradeButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	Size buttonSize = upgradeButton->getContentSize();
	float posX = 621;
	float posY = 80;
	upgradeButton->setPosition(Vec2(posX, posY));

	upgradeButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			this->upgradeButtonClickCallback();  // ����ˢ���̵꿨�Ƶķ���
		}
		});
	this->addChild(upgradeButton, 1);
}

void ShopLayer::upgradeButtonClickCallback() {
	// ����ť����¼������ӵȼ�

	if ( player->getGold() >= 4) {
		// ������ʵ�������߼�
		onUpgrade();
		player->spendGold(4);
		// ���½��������ǩ����ʾ����
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));
		// ������ʾ��ǰ�ȼ��ı�ǩ
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
	// �Ƴ�֮ǰ�ĵȼ���ǩ
	if (levelLabel) {
		levelLabel->removeFromParent();
	}

	// ������ǩ������ʾ�ȼ�
	levelLabel = Label::createWithSystemFont("Level: " + std::to_string(player->GetplayerLevel()) +
		"  Exp: " + std::to_string(player->GetplayerExperience()) + " / " + std::to_string(player->GetplayerNeedExperience()), "arial", 30);

	levelLabel->setColor(Color3B::WHITE);
	levelLabel->setPosition(Vec2(300, 50));//������ʾ��λ��
	this->addChild(levelLabel, 4);
}

void ShopLayer::showAllHero(int data) {
	teamManager->setAllVisiable(data);
}

void ShopLayer::updateGolden() {
	int currentGold = player->getGold();
	goldLabel->setString(StringUtils::format("%d", currentGold));
}