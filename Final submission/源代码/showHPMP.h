#pragma once
#ifndef __SHOWHPMP_H__
#define __SHOWHPMP_H__

#include "cocos2d.h"  
using namespace cocos2d;

class showHPMP : public cocos2d::Sprite
{
public:
    showHPMP();
    static showHPMP* showHPMP::create();

public:
    //����Ѫ������  
    void setBackgroundTexture(const std::string& pName);
    //����Ѫ��ǰ��  
    void setForegroundTexture(const std::string& pName);
    void changeColor(const std::string& pName);
    //������Ѫ��  
    void setTotalProgress(float data);
    //���õ�ǰѪ��  
    void setCurrentProgress(float progress);
    //�õ���ǰѪ��  
    float getCurrentProgress() const;
    //�õ���Ѫ��  
    float getTotalProgress() const;

private:
    //����ǰ��Ѫ����ʾ�ĳ���  
    void setForegroundTextureRect(const CCRect& rect);

private:
    CCSprite* P_back;//����Ѫ��  
    CCSprite* P_front;//ǰ��Ѫ��  
    float total;//��Ѫ��  
    float P_current;//��ǰѪ��  
    float P_scale;//�Ŵ���  
};

#endif
