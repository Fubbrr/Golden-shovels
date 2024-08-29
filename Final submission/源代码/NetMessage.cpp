#include "NetMessage.h"

NetMessage::NetMessage() {
	playerBlood = 100;
	heroNum = 0;
}

void NetMessage::SetPlayerBlood(int data) {
	playerBlood = data;
}

void NetMessage::SetHeroNum(int data) {
	heroNum = data;
}

void NetMessage::SetNetHero(int a, int b, int c, int d,int i) {
	netHero[i].tag = a;
	netHero[i].level = b;
	netHero[i].posX = c;
	netHero[i].posY = d;
}

string NetMessage::GetNetMessage() {
	std::stringstream ss;
	std::string netMessage;
	ss << playerBlood << "," << heroNum << "\n";
	for (int i = 0; i < heroNum; i++) {
		ss << netHero[i].tag << "," << netHero[i].level << "," << netHero[i].posX << "," << netHero[i].posY << "\n";
		netMessage = ss.str();
	}
	return netMessage;
}

int NetMessage::GetPlayerBlood() {
	return playerBlood;
}

int NetMessage::GetHeroNum() {
	return heroNum;
}

NetHeroInfo* NetMessage::GetHero() {
	return netHero;
}