#pragma once
#include "cocos2d.h"
class OnlineScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menu_click_openroom(cocos2d::Ref* pSender);
    void menu_click_joinroom(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(OnlineScene);
};