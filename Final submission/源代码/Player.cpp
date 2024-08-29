#include "Player.h"

// 初始化静态成员变量

Player* Player::createSprite()
{
	Player* sprite = new (std::nothrow) Player();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Player::init() {
	if (!Sprite::init())
	{
		return false;
	}
	gold = 100;//初始金币
	playerLevel = 1;
	playerNeedExperience = 4;
	playerExperience = 0;
	playerIsDead = 0;
	playerBlood = 30;
	return true;
}

//// 构造函数
//Player::Player(int initialGold, bool isAI) : gold(initialGold) {
//	// 初始化其他成员变量
//	playerLevel = 1;
//	playerNeedExperience = 4;
//	playerExperience = 0;
//	playerIsDead = 0;
//	playerBlood = 30;
//	//smallHero = SmallHero::create();
//	//smallHero->SetBaseInfo("SmallHero.png", Vec2(400, 400));
//	if (isAI) {
//		playerLevel = 5;
//		Vec2 pos1 = Vec2(600, 550);
//		for (int i = 1; i <= MaxLine; i++) {
//			frontPos[i] = pos1;
//			pos1.x += 100;
//		}
//		Vec2 pos2 = Vec2(600, 650);
//		for (int i = 1; i <= MaxLine; i++) {
//			backPos[i] = pos2;
//			pos2.x += 100;
//		}
//		pos2.x = 600, pos2.y += 100;
//		for (int i = MaxLine + 1; i <= 2 * MaxLine; i++) {
//			backPos[i] = pos2;
//			pos2.x += 100;
//		}
//		//CreateHero();
//	}
//}

void Player::SetSmallHero(Vec2 pos,bool enabled) {
	//小小英雄的创建转到这里
	smallHero = SmallHero::create();
	smallHero->SetBaseInfo("SmallHero.png", pos, enabled);
	this->getParent()->addChild(smallHero, 2);
	
}

Player::~Player() {
	//smallHero->removeFromParentAndCleanup(true);
	// 清理资源，如果有的话
}

void Player::CreateHero() {
	Vec2 pos1 = Vec2(600, 550);
	for (int i = 1; i <= MaxLine; i++) {
		frontPos[i] = pos1;
		pos1.x += 100;
	}
	Vec2 pos2 = Vec2(600, 650);
	for (int i = 1; i <= MaxLine; i++) {
		backPos[i] = pos2;
		pos2.x += 100;
	}
	pos2.x = 600, pos2.y += 100;
	for (int i = MaxLine + 1; i <= 2 * MaxLine; i++) {
		backPos[i] = pos2;
		pos2.x += 100;
	}
	//根据随机生成的整数匹配英雄的tag，将对应英雄加入队伍
	//tag 1,2,3,4（法师）,5,6,7（射手）,8(辅助1）为后排
	//tag 9（辅助2），10,11,12,13,14（战士）为前排
	if (heroNum >= playerLevel) {
		return;
	}
	srand((unsigned int)time(NULL));
	Vec2 pos;
	std::unordered_map<int, Vec2> existBackPos;
	std::unordered_map<int, Vec2> existFrontPos;
	for (int i = heroNum; i < playerLevel; i++) {//随机生成玩家等级个英雄
		int tag = mintag + rand() % (maxtag - mintag + 1);
		if (tag >= 1 && tag <= 8) {
			//在后排位置数组中随机选择一个位置
			while (1) {
				int x = rand() % (2 * MaxLine) + 1;
				if (existBackPos.count(x) == 0) {
					pos = backPos[x];
					existBackPos[x] = pos;
					break;
				}
			}
			//pos = Vec2(600, 750);
		}
		else {
			while (1) {
				int x = rand() % (MaxLine) + 1;
				if (existFrontPos.count(x) == 0) {
					pos = frontPos[x];
					existFrontPos[x] = pos;
					break;
				}
			}
			//pos = Vec2(1300, 550);
		}
		Hero* AIhero = Hero::create();
		AIhero->SetHeroDataByTag(tag, pos);
		AIhero->ChangeHeroName("En-");//实现视角转换
		//AIhero->SetBaseInfo(AIinfo->GetInfoByTag(tag), AIinfo->GetNameByTag(tag), pos);
		SetHero(AIhero);
	}
}

bool Player:: hasEnoughGold(int amount) {
	return gold >= amount;  // 检查金币是否足够
}


void Player::spendGold(int amount) {
	if (gold >= amount) {
		gold -= amount;  // 减少金币
	}
}

int Player::getGold()
{
	return gold;
}

void Player::addGold(int data) {
	gold += data;
}

int Player::GetHeroNum()
{
	return heroNum;
}

bool Player::addHeroToWar(Hero& hero)
{
		chessWarPlayer[heroNum].SetHeroDataByTag(hero.getTag(), hero.GetHeroPos());
		chessWarPlayer[heroNum].setLevel(hero.getLevel());
		chessWarPlayer[heroNum].SetOn(1);
		heroNum++;
		return true;
}

int Player::GetplayerExperience()
{
	return playerExperience;
}

void Player::SetplayerExperience(int x)
{
	playerExperience = x;
}

int Player::GetplayerNeedExperience()
{
	return playerNeedExperience;
}

void Player::SetplayerNeedExperience(int x)
{
	playerNeedExperience = x;
}

int Player::GetplayerLevel()
{
	return playerLevel;
}

void Player::SetplayerLevel(int x)
{
	playerLevel = x;
	if (x > 9)
		playerLevel = 9;
}

SmallHero* Player::getSmallHero()
{
	return smallHero;
}

class Hero* Player::GetWarHero() {
	return chessWarPlayer;
}

void Player::changeplayerBlood(int hurt)
{
	playerBlood -= hurt;
	smallHero->ChangeHP(hurt);

	if (smallHero->IsDead())
	{
		playerIsDead = true;//玩家死亡
	}
}

void Player::SetHero(Hero* hero) {
	chessWarPlayer[heroNum].SetBaseInfo(hero->GetBaseInfo(), hero->GetName(), hero->GetHeroPos());
	//chessWarPlayer.onBattle[chessWarPlayer.heroNum].SetHeroOn();
	chessWarPlayer[heroNum].SetOn(1);
	heroNum++;
}

void Player::Restart() {
	heroNum = 0;
}

void Player::GetNetHero(NetHeroInfo* NetInfo) {
	for (int i = 0; i < heroNum; i++) {
		Hero* netHero = Hero::create();
		netHero->SetHeroDataByTag(NetInfo[i].tag , Vec2(NetInfo[i].posX ,NetInfo[i].posY));
		netHero->ChangeHeroName("En-");//实现视角转换
		chessWarPlayer[i].SetBaseInfo(netHero->GetBaseInfo(), netHero->GetName(), netHero->GetHeroPos());
		chessWarPlayer[i].setLevel(NetInfo[i].level);
		chessWarPlayer[i].SetOn(1);
	}
}

