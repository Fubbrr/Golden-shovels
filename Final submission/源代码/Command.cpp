#include"Command.h"
#include<string>
GameData::GameData()
{
    for (int i = 0; i < 14; i++)
    {
        heromsg[i].level = 0;
        heromsg[i].position.x = 0;
        heromsg[i].position.y = 0;
        heromsg[i].tag = 0;
    }
    playerBlood=0;
    playerLevel=0;
    heroNum = 0;
}

GameData::~GameData()
{

}

std::string GameData::floatToStr(float f)
{
    std::stringstream stream;
    stream << f;
    return stream.str();
}
std::string GameData::intToStr(int f)
{
    std::stringstream stream;
    stream << f;
    return stream.str();
}
int GameData::strToInt(std::string str)
{
    int a;
    a = std::stoi(str);
    return a;
}
float GameData::strToFloat(std::string str)
{
    float f=0.0f;
    if (str == "")
    {
        f = NULL;
        return 0;
    }
    else
    {
        std::stringstream stream(str);
        stream >> f;
        return f;
    }
}
//将数据格式化
string GameData::serializeGameData(GameData* data) {
    string buffer = "";
    for(int i=0;i<heroNum;i++)
    {
        if (data->heromsg[i].tag == 0)
            break;
        buffer = buffer + data->intToStr(data->heromsg[i].tag);
        buffer = buffer + ",";
        buffer = buffer + data->intToStr(data->heromsg[i].level);
        buffer = buffer + ",";
        buffer = buffer + data->floatToStr(data->heromsg[i].position.x);
        buffer = buffer + ",";
        buffer = buffer + data->floatToStr(data->heromsg[i].position.y);
        buffer = buffer + ",";
    }
    buffer = buffer + data->intToStr(playerBlood);
    buffer = buffer + ",";
    buffer = buffer + data->intToStr(heroNum);
    buffer = buffer + ",";
    return buffer;
}

//将数据反格式化，读取出来
GameData* GameData::deserializeGameData(string buffer) {
    GameData* data=new GameData;
    string s="";
    int lenth = buffer.length();
    /*int j = 0;
    int i = 0;
    while(j<lenth)
    {
        if (buffer[j] == '*')
        {
            data->heromsg[i].tag = strToInt(s);
            s = "";
        }
        if (buffer[j] == '&')
        {
            data->heromsg[i].level = strToInt(s);
            s = "";
        }
        if (buffer[j] == '#')
        {
            data->heromsg[i].position.x = strToFloat(s);
            s = "";
        }
        if (buffer[j] == '%')
        {
            data->heromsg[i].position.y = strToFloat(s);
            s = "";
            i++;
        }
        if (buffer[j] == '$')
        {
            playerBlood = strToInt(s);
            s = "";
        }
        if (buffer[j] == '@')
        {
            heroNum = strToInt(s);
            s = "";
        }
         if (buffer[j] != '@'&& buffer[j] != '#'&& buffer[j] != '$'&& buffer[j] != '%'&& buffer[j] != '&'&& buffer[j] != '*')
            s = s + buffer[j];
        j++;
    }*/
    int i = 0;

    std::istringstream iss(buffer);
    std::string token;

    // 获取int值
    std::getline(iss, token, ',');
    data->heromsg[i].tag = strToInt(token);
    // 获取int值
    std::getline(iss, token, ',');
    data->heromsg[i].level = strToInt(token);
    //获取float值
    std::getline(iss, token, ',');
    data->heromsg[i].position.x = strToFloat(token);
    //获取float值
    std::getline(iss, token, ',');
    data->heromsg[i].position.y = strToFloat(token);
    // 获取int值
    std::getline(iss, token, ',');
    playerBlood = strToInt(token);
    // 获取int值
    std::getline(iss, token, ',');
    heroNum = strToInt(token);
    return data;
}

int GameData::getplayerBlood()
{
    return playerBlood;
}

void GameData::setplayerBlood(int blood)
{
    playerBlood = blood;
}
heroMsg GameData::getheromsg(int i)
{
    return heromsg[i];
}
void GameData::setheromsg(float x,float y,int tag,int i)
{
    heromsg[i].position.x = x;
    heromsg[i].position.y = y;
    heromsg[i].tag = tag;
}

int GameData::getheroNum()
{
    return heroNum;
}
void GameData::setheroNum()
{
    heroNum++;
}