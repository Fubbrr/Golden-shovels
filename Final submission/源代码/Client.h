#pragma once
#ifndef __CLIENT_H__  
#define __CLIENT_H__  
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include<string>
#include "Command.h"
#include "NetMessage.h"
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
#define PORT "8888"
//#define SERVER_IP "100.81.213.146"
#define SERVER_IP "127.0.0.1"

class Client
{
private:
    SOCKET connectSocket;
    NetMessage netMessage;
public:
    int init();
    GameData* communicate(GameData* mydata, GameData* enemydata);
    void close();
    void Send(std::string message);
    NetMessage receive();
};
#endif