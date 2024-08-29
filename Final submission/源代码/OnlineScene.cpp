#include "OnlineScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include "MapScene.h"
#include "Server.h"
#include "Client.h"
USING_NS_CC;

Server server;
Client client;
//全局变量记录游戏模式,0为单机，1为联机服务端，2为联机客户端，默认为单机
int isOnline = 0;

Scene* OnlineScene::createScene()
{
    return OnlineScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool OnlineScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //获取导演单例，窗口大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //新增一个标签
    auto label = Label::createWithTTF("Online Type", "fonts/Marker Felt.ttf", 75);
    label->enableShadow(Color4B::BLUE);
    //label->enableOutline(Color4B::BLUE, 1);
    //label->enableGlow(Color4B::BLUE);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height * 1.5));
        this->addChild(label, 1);
    }

    //新增一个sprite
    auto sprite = Sprite::create("bg2.png");
    if (sprite == nullptr)
    {
        problemLoading("'bg2.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 0);
    }


    //新建一个菜单

    /*openroom menu*/
    MenuItemImage* openroomMenuItem = MenuItemImage::create("openroomNormal.png", "openroomSelected.png", this, menu_selector(OnlineScene::menu_click_openroom));
    openroomMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 1.2)));

    /*joinroom menu*/
    MenuItemImage* joinroomMenuItem = MenuItemImage::create("joinroomNormal.png", "joinroomSelected.png", this, menu_selector(OnlineScene::menu_click_joinroom));
    joinroomMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 1.9)));

    /*return menu*/
    MenuItemImage* returnMenuItem = MenuItemImage::create("returnmenuNormal.png", "returnmenuSelected.png", CC_CALLBACK_1(OnlineScene::menuCloseCallback, this));
    returnMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 2.6)));

    //最后一个参数为null,表示列表结束
    Menu* menu = Menu::create(openroomMenuItem, joinroomMenuItem, returnMenuItem, NULL);

    //加入菜单
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);
    return true;
}

/*-------------------菜单点击返回菜单时调用该函数------------------*/
void OnlineScene::menuCloseCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button1.mp3");
    Director::getInstance()->popScene();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}


/*-------------------菜单点击创建房间时调用该函数------------------*/
void OnlineScene::menu_click_openroom(Ref* pSender)
{
    isOnline = 1;
    server.init();

    auto mapScene = MapScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button1.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, mapScene, Color3B(0, 0, 0)));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

/*-------------------菜单点击进入房间时调用该函数------------------*/
void OnlineScene::menu_click_joinroom(Ref* pSender)
{
    isOnline = 2;
    //初始化用户端并连接服务端
    client.init();

    auto mapScene = MapScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button1.mp3");
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, mapScene, Color3B(0, 0, 0)));


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}