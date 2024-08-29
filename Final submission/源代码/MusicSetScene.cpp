#include "SetScene.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include "MusicSetScene.h"
#include "SimpleAudioEngine.h"
#include "GUI\CCControlExtension\CCControl.h"
#include "GUI\CCControlExtension\CCControlSwitch.h"
USING_NS_CC;
using namespace cocos2d::extension;
using namespace CocosDenshion;
using namespace cocos2d::ui;

Scene* MusicSetScene::createScene()
{
    return MusicSetScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool MusicSetScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //获取导演单例，窗口大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //新增一个标签
    auto label = Label::createWithTTF("MusicSetting", "fonts/Marker Felt.ttf", 75);
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
    /*stop menu*/
    MenuItemImage* beginMenuItem = MenuItemImage::create("musicbeginNormal.png", "musicbeginSelected.png", this, menu_selector(MusicSetScene::menu_click_begin));
    beginMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 1.9)));

    /*stop menu*/
    MenuItemImage* stopMenuItem = MenuItemImage::create("musicstopNormal.png", "musicstopSelected.png", this, menu_selector(MusicSetScene::menu_click_stop));
    stopMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 2.6)));

    /*return menu*/
    MenuItemImage* returnMenuItem = MenuItemImage::create("returnNormal.png", "returnSelected.png", CC_CALLBACK_1(MusicSetScene::menuCloseCallback, this));
    returnMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 3.3)));


    //最后一个参数为null,表示列表结束
    Menu* menu = Menu::create(beginMenuItem, stopMenuItem, returnMenuItem, NULL);

    //加入菜单
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);

    createSlider();
    return true;
}

/*-------------------菜单点击返回时调用该函数------------------*/
void MusicSetScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

/*-------------------菜单点击关闭音乐时调用该函数------------------*/
void MusicSetScene::menu_click_stop(Ref* pSender)
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

/*-------------------菜单点击开启音乐时调用该函数------------------*/
void MusicSetScene::menu_click_begin(Ref* pSender)
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->resumeBackgroundMusic();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

/*---------------创建滑动条调节音量函数------------------*/
void MusicSetScene::createSlider()
{
    //获取导演单例，窗口大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //新建音量条
    auto slider = Slider::create();
    slider->loadBarTexture("SliderBack.png");
    slider->loadSlidBallTextures("SliderButtonNormal.png", "SlideButtonSelected.png", "SliderButtonDisable.png");
    slider->loadProgressBarTexture("SliderProgress.png");
    slider->setPercent(100 * SimpleAudioEngine::getInstance()->getBackgroundMusicVolume());
    slider->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 1.2)));
    slider->addEventListener([=](Ref* pSender, Slider::EventType type)
        {
            if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
            {
                float soundvalue = slider->getPercent() * 0.01;
                log("NOW=%.2f", soundvalue);
                SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(soundvalue);
            }
        });
    this->addChild(slider);
}
//在创建音量调节条时，对三个文件进行过修改，分别为SimpleAudioEngine.cpp MciPlayer.h MciPlayer.cpp