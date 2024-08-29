#pragma once
#include<stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace ui;
class MusicSetScene : public Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void createSlider();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menu_click_stop(cocos2d::Ref* pSender);
    void menu_click_begin(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MusicSetScene);
};
