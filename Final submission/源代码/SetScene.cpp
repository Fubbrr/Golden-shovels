#include "SetScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include "MusicSetScene.h"

USING_NS_CC;

Scene* SetScene::createScene()
{
    return SetScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SetScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //获取导演单例，窗口大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //新增一个标签
    auto label = Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 75);
    label->enableShadow(Color4B::BLUE);
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
    auto sprite = Sprite::create("bg3.png");
    if (sprite == nullptr)
    {
        problemLoading("'bg3.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 0);
    }


    //新建一个菜单
     /*begin menu*/
    Sprite* nusicsetNormal = Sprite::create("musicsetNormal.png");
    Sprite* musicsetSelected = Sprite::create("musicsetSelected.png");
    MenuItemSprite* musicsetMenuItem = MenuItemSprite::create(nusicsetNormal, musicsetSelected, this, menu_selector(SetScene::menu_click_music));
    musicsetMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 1.3)));

    /*return menu*/
    MenuItemImage* returnMenuItem = MenuItemImage::create("returnmenuNormal.png", "returnmenuSelected.png", CC_CALLBACK_1(SetScene::menuCloseCallback, this));
    returnMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 2.2)));

    //最后一个参数为null,表示列表结束
    Menu* menu = Menu::create(musicsetMenuItem, returnMenuItem, NULL);

    //加入菜单
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);

    return true;
}

/*-------------------菜单点击返回菜单时调用该函数------------------*/
void SetScene::menuCloseCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button1.mp3");
    Director::getInstance()->popScene();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

/*-------------------菜单点击调节音乐时调用该函数------------------*/
void SetScene::menu_click_music(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button1.mp3");
    auto scene = MusicSetScene::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(215, 237, 255)));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}