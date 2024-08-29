#include"PauseScene.h"
#include"cocos2d.h"
#include "AudioEngine.h"
#include"AppDelegate.h"

Scene* PauseScene::createScene()
{
	return PauseScene::create();
}

bool PauseScene::init()
{
	if (!Scene::init())
		return false;

	createMenu();
	this->setOpacity(5);
	/*createButtonLayer();
	createSliderLayer();
	createLabel();
	createCheckBox();*/
	
	return true;
}

void PauseScene::createMenu()
{
	//auto myLabel = Label::createWithBMFont("bitmapRed.fnt", "Your Text");

	auto myLabel = Label::createWithSystemFont("return", "Arial", 50);

	auto returnItem = MenuItemLabel::create(myLabel, CC_CALLBACK_1(PauseScene::menuReturnCallBack, this));

	returnItem->setPosition(Vec2(900, 400));

	menuItems.pushBack(returnItem);

	auto menu = Menu::createWithArray(menuItems);

	menu->setPosition(Vec2::ZERO);

	this->addChild(menu);

	//auto startItem = MenuItemImage::create("replay.png",
	//	"start2.png", CC_CALLBACK_0(Battle::Start, battlelayer));
	//startItem->setScale(0.8);
	//auto menu = Menu::create(startItem, NULL);
	//menu->setPosition(Vec2(visibleSize.width / 2 + origin.x, 80));
	//this->addChild(menu, 5);

	return;
}

void PauseScene::menuReturnCallBack(Ref* pSender)
{
	/*if (soundEffectSign)
		AudioEngine::play2d("buttonDown.mp3", false);*/
	Director::getInstance()->popScene();

	return;
}