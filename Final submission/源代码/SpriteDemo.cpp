#include "SpriteDemo.h"

Sprite* SpriteDemo::createsprite()
{
    auto sprite = cocos2d::Sprite::create("hero1.png");
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    sprite->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize() / 2));
    // 使用缩放来设置精灵的大小
    sprite->setScale(100.0f / sprite->getContentSize().width, 100.0f / sprite->getContentSize().height);
    return sprite;
	
}
