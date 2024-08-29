#include "TeamManager.h"
#include"MapScene.h"
#include"ShopLayer.h"
#include"Player.h"

// 初始化静态成员变量
TeamManager* TeamManager::_instance = nullptr;

void TeamManager::addOrUpdateHeroToTeam(Hero* hero)
{
	if (hero) {
		bool heroFound = false;
		std::string* newHeroName = static_cast<std::string*>(hero->getUserData());

		for (auto& teamHero : teamHeroes) {
			std::string* teamHeroName = static_cast<std::string*>(teamHero->getUserData());
			if (teamHeroName && newHeroName && *teamHeroName == *newHeroName) {
				// 英雄已在队伍中，执行升级操作
				teamHero->upgrade();
				heroFound = true;
				hero->setVisible(0);
				break;
			}
		}

		if (!heroFound) {
			// 英雄不在队伍中，添加到队伍
			teamHeroes.push_back(hero);
			hero->setLevel(1);
			hero->updateStarLevel();
			hero->updateImage();
			// 获取地图场景的引用
			auto mapScene = dynamic_cast<MapScene*>(Director::getInstance()->getRunningScene());
			if (mapScene) {
				mapScene->addHeroToMap(hero);
				hero->SetoriPosition(hero->getPosition());
				// 将英雄添加到地图层
				//mapScene->addHeroToMap(selectedHero);
			}
		}
	}
}

TeamManager* TeamManager::getInstance()
{
	if (_instance == nullptr) {
		_instance = new TeamManager();
		// 这里可以初始化其他属性，比如金币
	}
	return _instance;
}

void TeamManager::addHeroToPlayer(Player* player)
{
	for (Hero* hero : teamHeroes) {
		if (hero&&(hero->GetLocation())) {
			bool added = player->addHeroToWar(*hero);
			if (!added) {
				// 处理无法添加更多英雄的情况
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
