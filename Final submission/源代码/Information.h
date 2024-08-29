#pragma once
#include <string>
#include <unordered_map>
#include "cocos2d.h"

struct heroInformation {

	float HP;                 //����ֵ
	float MP;                 //����ֵ
	float attack;            //������
	float atkspeed;          //�����ٶ�(ÿ���빥��һ��)
	float defence;           //������
	float atkrange;          //��������
	float movespeed;         //�ƶ��ٶ�
	//double attackSpeed;     //����������ٶ�

	//int price;             //���Ӽ۸�
};
class Information {
public:
	Information();
	static heroInformation* getheroInformation(int heroTag, int level);
	void SetHeroInfo();
    static std::string getNameByTag(int tag);
    static std::string getHeroPathByTag(int tag);
	heroInformation* GetInfoByTag(int tag);
    // �������������ȡӢ����Ϣ�ķ���

public:
	heroInformation HeroInfo[14];
    static std::unordered_map<int, std::string> name;
    static std::unordered_map<int, std::string> imagePaths;
	static std::unordered_map<int, std::string> warimagePaths;
	static std::map<int, heroInformation> info;
    // ������������洢Ӣ����Ϣ�ĳ�Ա����
};
