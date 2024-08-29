#include "Player.h"

// ��ʼ����̬��Ա����

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
	gold = 100;//��ʼ���
	playerLevel = 1;
	playerNeedExperience = 4;
	playerExperience = 0;
	playerIsDead = 0;
	playerBlood = 30;
	return true;
}

//// ���캯��
//Player::Player(int initialGold, bool isAI) : gold(initialGold) {
//	// ��ʼ��������Ա����
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
	//ССӢ�۵Ĵ���ת������
	smallHero = SmallHero::create();
	smallHero->SetBaseInfo("SmallHero.png", pos, enabled);
	this->getParent()->addChild(smallHero, 2);
	
}

Player::~Player() {
	//smallHero->removeFromParentAndCleanup(true);
	// ������Դ������еĻ�
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
	//����������ɵ�����ƥ��Ӣ�۵�tag������ӦӢ�ۼ������
	//tag 1,2,3,4����ʦ��,5,6,7�����֣�,8(����1��Ϊ����
	//tag 9������2����10,11,12,13,14��սʿ��Ϊǰ��
	if (heroNum >= playerLevel) {
		return;
	}
	srand((unsigned int)time(NULL));
	Vec2 pos;
	std::unordered_map<int, Vec2> existBackPos;
	std::unordered_map<int, Vec2> existFrontPos;
	for (int i = heroNum; i < playerLevel; i++) {//���������ҵȼ���Ӣ��
		int tag = mintag + rand() % (maxtag - mintag + 1);
		if (tag >= 1 && tag <= 8) {
			//�ں���λ�����������ѡ��һ��λ��
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
		AIhero->ChangeHeroName("En-");//ʵ���ӽ�ת��
		//AIhero->SetBaseInfo(AIinfo->GetInfoByTag(tag), AIinfo->GetNameByTag(tag), pos);
		SetHero(AIhero);
	}
}

bool Player:: hasEnoughGold(int amount) {
	return gold >= amount;  // ������Ƿ��㹻
}


void Player::spendGold(int amount) {
	if (gold >= amount) {
		gold -= amount;  // ���ٽ��
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
		playerIsDead = true;//�������
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
		netHero->ChangeHeroName("En-");//ʵ���ӽ�ת��
		chessWarPlayer[i].SetBaseInfo(netHero->GetBaseInfo(), netHero->GetName(), netHero->GetHeroPos());
		chessWarPlayer[i].setLevel(NetInfo[i].level);
		chessWarPlayer[i].SetOn(1);
	}
}

