#pragma once
#include "cocos2d.h"
#include"Hero.h"
#include"Player.h"
class TeamManager {
public:
    std::vector<Hero*>teamHeroes;//���Ӣ�۵Ķ��飬һ���ǽ��̵��е�Ӣ��ת�ƹ���
    void addOrUpdateHeroToTeam(Hero* hero);

    static TeamManager* getInstance();  // ��ȡ���������ʵ���ķ���
    
    void setAllVisiable(int data);
   // Hero* findHeroByTag(int heroTag);  // ���ݱ�ǩ����Ӣ��

    //�����еĽ�ɫ��ӵ�chesswarplayer�У�������ͼ�����ʼ��ť�����

    void addHeroToPlayer(Player* player);
private:
    static TeamManager* _instance; // ��̬ʵ��ָ��

    
};