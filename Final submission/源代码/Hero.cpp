#include "Hero.h"
#include"Information.h"
//#include<string>
//using namespace std;
USING_NS_CC;

Hero::Hero() {
    atkTarget = NULL;//攻击的敌方目标英雄
    ison = 0;//是否上场
    isdead = 0;//是否死亡
    isatk = 0;//是否正在攻击
    ismove = 0;//是否正在移动
    isrecover = 0;
    isFull = 0;//蓝条是否已满（是否释放大招）
    isupdate = 0;//是否在update
    moveAction = NULL;//移动动作序列
    attackAction = NULL;//攻击动作序列
    location = 0;
    id = 0;
    level = 1;
}

void Hero::upgrade()
{
    if (level < 4) {
        level++;
        // 更新星级显示
        updateStarLevel();

        //heroInformation* attributes = Information::getheroInformation(this->getId(), level);
        //if (attributes) {
        //    // 使用新的属性更新英雄
        //    baseInfo->HP = attributes->HP;
        //    baseInfo->HP = attributes->attack;
        //    // ... 更新其他属性 ...

        //    // 释放 attributes 对象以避免内存泄漏
        //    delete attributes;
        //}
    }
}

int Hero::getId() const {
    return id;
}

void Hero::setId(int x)
{
    id = x;
}

int Hero::getLevel() const {
    return level;
}

void Hero::setLevel(int x)
{
    level = x;
}

void Hero::updateStarLevel()
{
    std::string StarList[4] = { "star1.png","star2.png","star3.png","star4.png" };
    // 清除旧的星星精灵
    //this->removeAllChildren();
    std::string starFileName = StarList[this->level - 1];
    if (this->level == 1) {
        this->star = Sprite::create(starFileName);
        if (star) {
            float spacing = 15.0f;
            float CardWidth = this->getContentSize().width;
            float CardHeight = this->getContentSize().height;
            float posY = this->getPositionY() / 10;
            float posX = this->getPositionX() / 50;
            //大小
            if (level == 1)
                star->setScale(0.1, 0.1);
            else
                star->setScale(0.15, 0.15);
            //位置
            star->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            Vec2 StarPosition = this->getPosition();
            star->setPosition(posX, posY);
            this->addChild(star, 0);
        }
    }
    else {
        star->setTexture(starFileName);
        if (star) {
            float spacing = 15.0f;
            float CardWidth = this->getContentSize().width;
            float CardHeight = this->getContentSize().height;
            float posY = this->getPositionY() / 10;
            float posX = this->getPositionX() / 50;
            //大小
            if (level == 1)
                star->setScale(0.1, 0.1);
            else
                star->setScale(0.15, 0.15);
            //位置
            star->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            Vec2 StarPosition = this->getPosition();
            star->setPosition(posX, posY);
            //this->addChild(star, 0);
        }
    }
}

void Hero::updateImage()
{
    int id = this->getId();
    //float itemWidth = 110.0f; // 假设每张背景图的宽度
    //float itemHeight = 110.0f; // 假设每张背景图的高度

    // 查找对应的图像路径
    auto it = Information::warimagePaths.find(id);
    if (it != Information::warimagePaths.end()) {
        // 如果找到了图像路径
        const std::string& warimagePath = it->second;
        // 更新精灵的纹理
        this->setTexture(warimagePath);

        // 可能需要调整精灵的大小以适应新的纹理
        //this->setContentSize(Size(itemWidth-10, itemHeight+10));
        this->setScale(0.45);
    }
    else {
        // 找不到对应的图像路径
        CCLOG("Image path for hero ID %d not found", id);
    }
}



Hero* Hero::create(const std::string& filename)
{
    Hero* sprite = new (std::nothrow) Hero();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Hero::SetHeroDataByTag(int tag,Vec2 pos) {
    id = tag;
    Information InfoMap;
    InfoMap.SetHeroInfo();
    baseInfo = InfoMap.GetInfoByTag(id);
    heroName = InfoMap.getNameByTag(id);
    heroPos = pos;
    this->setTexture(heroName + "-action1.png");
    this->setVisible(0);
}

void Hero::SetBaseInfo(heroInformation* info, std::string name, Vec2 pos) {
    baseInfo = info;
    heroName = name;
    heroPos = pos;
    this->setTexture(heroName + "-action1.png");
    this->setVisible(0);
}

void Hero::HPInit() {
    heroHP = showHPMP::create();
    this->getParent()->addChild(heroHP, 5);
    heroHP->retain();
    heroMP = showHPMP::create();
    this->getParent()->addChild(heroMP, 5);
    heroMP->retain();
}

void Hero::SetLocation(int x)
{
    location = x;
}

int Hero::GetLocation()
{
    return location;
}

void Hero::StarVisible(int x)
{
    star->setVisible(x);
}

void Hero::SetHeroPos(Vec2 pos) {
    heroPos = pos;
}

void Hero::SetHeroOn() {
    //heroAttack = Attack::create(heroName);
    //this->getParent()->addChild(heroAttack);//相当于把攻击物加为英雄的兄弟
    //heroAttack->GetAttack(baseInfo->attack);
    //heroAttack->setVisible(0);

    //heroHP = showHPMP::create();
    //this->getParent()->addChild(heroHP,2);
    //heroMP = showHPMP::create();
    //this->getParent()->addChild(heroMP,2);

    this->setPosition(heroPos);
    this->setScale(0.55);
    //血条初始化
    Vec2 posBlood;
    posBlood.x = heroPos.x;
    posBlood.y = heroPos.y + this->getContentSize().height / 2 - 55;
    heroHP->setPosition(posBlood);
    heroHP->setBackgroundTexture("Blood-back.png");
    heroHP->setForegroundTexture(heroName + "Blood-front.png");
    heroHP->setTotalProgress(baseInfo->HP);
    heroHP->setCurrentProgress(baseInfo->HP);
    heroHP->setScale(0.4);
    //蓝条初始化
    Vec2 posMP;
    posMP.x = heroPos.x;
    posMP.y = posBlood.y - 10;
    heroMP->setPosition(posMP);
    heroMP->setBackgroundTexture("MP-back.png");
    heroMP->setForegroundTexture("MP-front.png");
    heroMP->setTotalProgress(baseInfo->MP);
    heroMP->setCurrentProgress(0.0f);
    heroMP->setScale(0.4);
    //英雄设为可见
    this->setVisible(1);
    heroHP->setVisible(1);
    heroMP->setVisible(1);
    SetAction();
    ison = 1;
}

//void Hero::ChangeHPColor() {
//    heroHP->changeColor("RedBlood-front.png");
//}

//初始化移动和攻击动画
void Hero::SetAction() {
    //设置攻击动作
    Vector<SpriteFrame*>spriteFrameVec;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-action%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.5);
    attackAction = Animate::create(ani);
    //设置移动动作
    Vector<SpriteFrame*>spriteFrameVec2;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-move%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec2.pushBack(spriteFrame);
    }
    Animation* ani2 = Animation::createWithSpriteFrames(spriteFrameVec2, 0.5);
    moveAction = Animate::create(ani2);
}


void Hero::StartBattle(Hero* target) {
    atkTarget = target;
    //auto attackcopy = attackAction;
    //MoveBy* stop = MoveBy::create(baseInfo->atkspeed - 1, Vec2(0, 0));//用来做停顿
    //Sequence* Atk = Sequence::create(attackAction, stop, NULL);
    //this->runAction(RepeatForever::create(Atk));

    atktimer = baseInfo->atkspeed * 60;//60是帧数
    curAtkTimer = 0;
    //this->schedule(schedule_selector(Hero::musicTimer), baseInfo->atkspeed);
    this->scheduleUpdate();//启用定时器，开始执行update函数
}

//得到的应该是战斗场某个格子的中心位置
Vec2 Hero::GetTargetPos() {
    Vec2 enemyPos = atkTarget->getPosition();
    double distance = CountDistance();
    Vec2 direction = Vec2(enemyPos.x - this->getPosition().x, enemyPos.y - this->getPosition().y) / distance;
    Vec2 tarPos;
    if (distance - baseInfo->atkrange > 0)
        tarPos = direction * (distance - baseInfo->atkrange) + this->getPosition();
    else
        tarPos = (0, 0);
    return direction;
}

//移动到指定位置
void Hero::HeroMoveTo() {
    Vec2 pos = GetTargetPos();
    direction = pos;
    double distance = CountDistance();
    movetime = distance / baseInfo->movespeed;
    moveActTimer = 100;
    curMoveActTimer = 100;
    this->schedule(schedule_selector(Hero::Movetimer), 0.01f);


    Vec2 posBlood;
    posBlood.x = pos.x;
    posBlood.y = pos.y + this->getContentSize().height / 2 + 30;
    Vec2 posMP;
    MoveTo* HPMoveTo = MoveTo::create(4, posBlood);
    //heroHP->runAction(HPMoveTo);
    posMP.x = pos.x;
    posMP.y = posBlood.y - 14;
    MoveTo* MPMoveTo = MoveTo::create(4, posMP);
    //heroMP->runAction(MPMoveTo);
}

void Hero::Movetimer(float delta) {
    Vector<SpriteFrame*>spriteFrameVec2;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-move%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec2.pushBack(spriteFrame);
    }
    Animation* ani2 = Animation::createWithSpriteFrames(spriteFrameVec2, 0.5);
    auto ani = Animate::create(ani2);
    if (curMoveActTimer == moveActTimer) {//到了发动攻击的时间
        this->runAction(ani);
    }
    curMoveActTimer++;//当前时间加一
    if (curMoveActTimer > moveActTimer)
        curMoveActTimer = 0;

    this->setPosition(this->getPosition() + direction / 2);//按钮精灵向右移动2像素
    heroHP->setPosition(heroHP->getPosition() + direction / 2);
    heroMP->setPosition(heroMP->getPosition() + direction / 2);
    if (CountDistance() <= baseInfo->atkrange) {
        this->unschedule(schedule_selector(Hero::Movetimer));
        this->stopAllActions();
    }

}

//停止动作
void Hero::StopMove(Ref* obj) {
    this->stopAllActions();
    this->setTexture(heroName + "-action1.png");
}

void Hero::StopAttack(Ref* obj) {
    this->stopAllActions();
    this->setTexture(heroName + "-action1.png");
    isatk = 0;
}

//计算英雄位置到攻击目标的位置
double Hero::CountDistance() {
    Vec2 pos1 = this->getPosition();//实时更新英雄位置
    Vec2 pos2 = atkTarget->getPosition();
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

void Hero::HeroAttack() {

    Vector<SpriteFrame*>spriteFrameVec;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-action%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.5);
    auto atk = Animate::create(ani);
    MoveBy* stop = MoveBy::create(baseInfo->atkspeed - 1, Vec2(0, 0));//用来做停顿
    Sequence* Atk = Sequence::create(atk, stop, NULL);
    this->runAction(Atk);
    //this->runAction(attackAction);//开始攻击动作
    heroAttack = Attack::create(heroName);
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("attack2.mp3");
    heroAttack->setScale(1.5);
    this->getParent()->addChild(heroAttack, 5);//相当于把攻击物加为英雄的兄弟
    if (heroMP->getCurrentProgress() >= baseInfo->MP) {
        heroAttack->GetAttack(baseInfo->attack * 3);
        heroAttack->setScale(3);
        heroMP->setCurrentProgress(0);
        if (heroName == "Lilia" || heroName == "En-Lilia")
            isrecover = 1;//全体回血
    }
    else {
        isrecover = 0;
        heroAttack->GetAttack(baseInfo->attack);
    }
    heroAttack->SetPosition(this->getPosition(), this->getContentSize());
    heroAttack->setVisible(1);
    //float flyTime = CountDistance() / baseInfo->attackSpeed;

    //攻击物计时器
    heroAttack->SetTarget(atkTarget);//告诉攻击物攻击目标，Attack内部调用定时器，实现飞行与攻击
}

void Hero::ChangeHP(float data) {
    if (heroHP->getCurrentProgress() > 0)
        heroHP->setCurrentProgress(heroHP->getCurrentProgress() - data + baseInfo->defence);
}

void Hero::ChangeMP() {
    if (!isFull)
        heroMP->setCurrentProgress(heroMP->getCurrentProgress() + 10);
}

void Hero::update(float dt)
{
    if (heroHP->getCurrentProgress() <= 0)
    {
        this->isdead = 1;//死亡
        this->setVisible(0);//或许更改为淡出会更好，视后期效果而定
        //this->unschedule(schedule_selector(Hero::musicTimer));
        heroHP->setVisible(0);
        heroMP->setVisible(0);
    }

    if (isdead)//如果死了就停止攻击
    {
        isatk = 0;
        //heroAttack->setVisible(0);
        this->stopAllActions();
        this->unscheduleUpdate();//停止该英雄的所有定时器
        //this->Destory();
    }

    //if (atkTarget->IsDead()) {
    //    isatk = 0;
    //    heroAttack->setVisible(0);
    //    //this->stopAllActions();
    //}
    if (!ismove&&isdead==0)
    {
        //若攻击目标在攻击范围内则发动攻击
        if (CountDistance() <= baseInfo->atkrange)//或许需要加一个可允许的误差值，先将所有英雄图片大小弄成一样的看看能不能避免误差
        {
            if (curAtkTimer == atktimer && atkTarget->IsDead() == 0) {//到了发动攻击的时间
                isatk = 1;//设置攻击状态为正在攻击//isatk何时置零？
                HeroAttack();
                ChangeMP();
                //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("attack2.mp3");
            }
            curAtkTimer++;//当前时间加一
            if (curAtkTimer > atktimer)
                curAtkTimer = 0;
        }

        //目标不在攻击范围内
        else
        {
            this->stopAllActions();
            ismove = 1;//标记正在移动
            HeroMoveTo();//移动到能够发动攻击的位置
            movetimer = movetime * 60;
            curMoveTimer = 0;
        }
    }
    if (ismove&&isdead==0) {
        curMoveTimer++;
        if (curMoveTimer >= movetimer || CountDistance() <= baseInfo->atkrange) {
            ismove = 0;
            atktimer = baseInfo->atkspeed * 60;
            curAtkTimer = atktimer - 20;
        }

    }
    isupdate = 1;
}


bool Hero::IsDead() {
    return isdead;
}

bool Hero::IsOn() {
    return ison;
}

bool Hero::IsRecover() {
    return isrecover;
}

void Hero::SetRecover() {
    isrecover = 0;
}

void Hero::SetOn(int data) {
    ison = 1;
}

void Hero::SetDead(int data) {
    isdead = data;
    //this->unscheduleUpdate();
    heroHP->setCurrentProgress(baseInfo->HP);
    heroMP->setCurrentProgress(0);
}

Hero* Hero::ShowTarget() {
    return atkTarget;
}

void Hero::Destory() {
    if (isupdate) {
        //this->unscheduleAllSelectors();
        this->unscheduleUpdate();
        this->stopAllActions();
        //this->getParent()->removeChild(heroHP);
        //this->getParent()->removeChild(heroMP);
        //heroHP->release();
        //heroMP->release();
        this->release();//减少一次引用计数
        isupdate = 0;
    }
}

heroInformation* Hero::GetBaseInfo() {
    return baseInfo;
}

std::string Hero::GetName() {
    return heroName;
}

Vec2 Hero::GetHeroPos() {
    return heroPos;
}

int Hero::getTag() {
    return id;
}

void Hero::musicTimer(float t) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("attack2.mp3");
}

void Hero::updateInfo() {
    if (level > 1) {
        baseInfo->HP += level * 80;
        baseInfo->attack += level * 60;
    }
}