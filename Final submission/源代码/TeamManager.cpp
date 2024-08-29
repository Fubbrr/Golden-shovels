#include "TeamManager.h"
#include"MapScene.h"
#include"ShopLayer.h"
#include"Player.h"

// ��ʼ����̬��Ա����
TeamManager* TeamManager::_instance = nullptr;

void TeamManager::addOrUpdateHeroToTeam(Hero* hero)
{
	if (hero) {
		bool heroFound = false;
		std::string* newHeroName = static_cast<std::string*>(hero->getUserData());

		for (auto& teamHero : teamHeroes) {
			std::string* teamHeroName = static_cast<std::string*>(teamHero->getUserData());
			if (teamHeroName && newHeroName && *teamHeroName == *newHeroName) {
				// Ӣ�����ڶ����У�ִ����������
				teamHero->upgrade();
				heroFound = true;
				hero->setVisible(0);
				break;
			}
		}

		if (!heroFound) {
			// Ӣ�۲��ڶ����У���ӵ�����
			teamHeroes.push_back(hero);
			hero->setLevel(1);
			hero->updateStarLevel();
			hero->updateImage();
			// ��ȡ��ͼ����������
			auto mapScene = dynamic_cast<MapScene*>(Director::getInstance()->getRunningScene());
			if (mapScene) {
				mapScene->addHeroToMap(hero);
				hero->SetoriPosition(hero->getPosition());
				// ��Ӣ����ӵ���ͼ��
				//mapScene->addHeroToMap(selectedHero);
			}
		}
	}
}

TeamManager* TeamManager::getInstance()
{
	if (_instance == nullptr) {
		_instance = new TeamManager();
		// ������Գ�ʼ���������ԣ�������
	}
	return _instance;
}

void TeamManager::addHeroToPlayer(Player* player)
{
	for (Hero* hero : teamHeroes) {
		if (hero&&(hero->GetLocation())) {
			bool added = player->addHeroToWar(*hero);
			if (!added) {
				// �����޷���Ӹ���Ӣ�۵����
				break;
			}
		}
		/*else {
			hero->setVisible(0);
		}*/
	}
	setAllVisiable(0);
}

void TeamManager::setAllVisiable(int data) {
	for (Hero* hero : teamHeroes) {
		if (hero && (hero->GetLocation()))
		hero->setVisible(data);
	}
}
