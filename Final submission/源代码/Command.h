#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>
#include <sstream>
#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

class heroMsg
{
public:
	int level;  // Ó¢ÐÛµÄµÈ¼¶
    Vec2 position;//Ó¢ÐÛÎ»ÖÃ
    int tag=0;//Ó¢ÐÛ±êºÅ
};

class GameData {
private:
    heroMsg heromsg[14];
    int playerBlood;
    int playerLevel;
    int heroNum=0;
public:
    GameData();
    ~GameData();
    string serializeGameData(GameData* data);
    GameData* deserializeGameData(string buffer);
    std::string floatToStr(float f);
    std::string intToStr(int f);
    float strToFloat(std::string str);
    int strToInt(std::string str);
    int getplayerBlood();
    void setplayerBlood(int blood);
    heroMsg getheromsg(int i);
    void setheromsg(float x, float y, int tag, int i);
    int getheroNum();
    void setheroNum();
};

#endif // !_MESSAGE_H_
