#include "showHPMP.h"  

showHPMP::showHPMP()
{
    P_back = NULL;
    P_front = NULL;
    total = 0.0f;
    P_current = 0.0f;
    P_scale = 1.0f;
}

showHPMP* showHPMP::create()
{
    showHPMP* sprite = new (std::nothrow) showHPMP();
    if (sprite)
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void showHPMP::setBackgroundTexture(const std::string& pName)
{
    P_back = CCSprite::create(pName);
    this->addChild(P_back);
}

void showHPMP::setForegroundTexture(const std::string& pName)
{
    P_front = CCSprite::create(pName);
    P_front->setAnchorPoint(ccp(0.0f, 0.5f));//ÉèÖÃÃªµã  
    P_front->setPosition(ccp(-P_front->getContentSize().width * 0.5f, 0));
    this->addChild(P_front);
}

void showHPMP::changeColor(const std::string& pName) {
    P_front->setTexture(pName);
}

void showHPMP::setTotalProgress(float data)
{
    if (P_front == NULL) { return; }
    P_scale = P_front->getContentSize().width / data;
    total = data;
}

void showHPMP::setCurrentProgress(float progress)
{
    if (P_front == NULL) { return; }
    if (progress < 0.0f) { progress = 0.0f; }
    if (progress > total) { progress = total; }
    P_current = progress;
    if (P_current <= 0.0f) {
        return;
    }
    float rectWidth = progress * P_scale;
    const CCPoint from = P_front->getTextureRect().origin;
    const CCRect rect = CCRectMake(from.x, from.y, rectWidth, P_front->getContentSize().height);
    setForegroundTextureRect(rect);
}

void showHPMP::setForegroundTextureRect(const CCRect& rect)
{
    P_front->setTextureRect(rect);
}

float showHPMP::getCurrentProgress() const
{
    return P_current;
}

float showHPMP::getTotalProgress() const
{
    return total;
}