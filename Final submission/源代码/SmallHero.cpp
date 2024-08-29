#include "SmallHero.h"

bool SmallHero::init()
{
    if (!Sprite::init())//����ʼ��ʧ�ܣ�����0
    {
        return false;
    }
    heroHP = showHPMP::create();
    this->addChild(heroHP);
    // ����һ��������
    auto _mouseListener = EventListenerMouse::create();
    // ���� onMouseUp �¼��ص�
    _mouseListener->onMouseUp = [=](EventMouse* event) {
        // �����갴���Ƿ�Ϊ�Ҽ���EventMouse::MouseButton::BUTTON_RIGHT��
        if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
            onMouseUp(event);
        }
    };
    //_mouseListener->onMouseUp = CC_CALLBACK_1(SmallHero::onMouseUp, this);
    // ����������ӵ��¼��ַ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    return true;
}

SmallHero* SmallHero::create()
{
    SmallHero* sprite = new SmallHero();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        //sprite->SetBaseInfo("SmallHero.png", Vec2(500, 500));  // ����Ĭ�ϳ�ʼλ�ú�ͼƬ
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void SmallHero::SetBaseInfo(string name, Vec2 pos,bool enabled)
{
    smallHeroName = name;
    smallHeroPos = pos;
    isMoveEnabled = enabled;
    HP = 30;
    isdead = 0;
    ismove = 0;
    this->setTexture(smallHeroName);
    this->setPosition(smallHeroPos);
    //Ѫ����ʼ��
    Vec2 posBlood;
    posBlood.x = 0.05*smallHeroPos.x+30;
    posBlood.y = 0.15*smallHeroPos.y + this->getContentSize().height / 2+30;
    heroHP->setPosition(posBlood);
    heroHP->setScale(2.2f);
    heroHP->setBackgroundTexture("Blood-back.png");
    heroHP->setForegroundTexture("Blood-front.png");
    heroHP->setTotalProgress(HP);
    heroHP->setCurrentProgress(HP);
    heroHP->setScale(0.6);
   
    this->setVisible(1);
}

Vec2 SmallHero::onMouseUp(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e)
    {
        // ��ȡ�����λ��
        Vec2 mouseClickPos = Vec2(e->getCursorX(), e->getCursorY());

        // ��������ô�����λ�õĺ���
        handleMouseClick(mouseClickPos);

        return mouseClickPos;
    }

    return nullptr;
}

void SmallHero::handleMouseClick(const Vec2& clickPos)
{
    if (clickPos.x >= 380 && clickPos.x <= 1500 && clickPos.y >= 250 && clickPos.y <= 850 && ismove == 0&& isMoveEnabled)
        //�ƶ�Ӣ�۵����λ��
        smallHeroMoveTo(clickPos);
}

//�ƶ���ָ��λ��
void SmallHero::smallHeroMoveTo(const Vec2& clickPos)
{
    ismove = 1;
    //Vec2 pos1 = smallHeroPos;
    //Vec2 pos2 = clickPos;
    //double distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
    double time = 1;
    //double time = distance / 500;
    MoveTo* moveTo = MoveTo::create(time, clickPos);
    Sequence* seq = Sequence::create(moveTo, CallFuncN::create(CC_CALLBACK_1(SmallHero::StopMove, this)), NULL);
    this->runAction(seq);
}

//ֹͣ����
void SmallHero::StopMove(Ref* obj)
{
    this->stopAllActions();
    this->setTexture(smallHeroName);
    ismove = 0;
}

void SmallHero::ChangeHP(float data)
{
    heroHP->setCurrentProgress(heroHP->getCurrentProgress() - data);
    HP = heroHP->getCurrentProgress();
    if (HP <= 0) {
        isdead = true;
    }
}

void SmallHero::update(float dt)
{
    if (HP <= 0) {
        this->isdead = 1;//����
        this->setVisible(0);
    }
    if (isdead) {
        this->unscheduleUpdate();//ֹͣ��Ӣ�۵����ж�ʱ��
    }
}

bool SmallHero::IsDead()
{
    return isdead;
}

void SmallHero::SetisMoveEnabled(bool enabled)
{
    isMoveEnabled = enabled;
}

bool SmallHero::GetisMoveEnabled()
{
    return isMoveEnabled;
}