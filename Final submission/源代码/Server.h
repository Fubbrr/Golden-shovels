#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#ifndef __SERVER_H__  
#define __SERVER_H__  
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include<string>
#pragma comment(lib, "Ws2_32.lib")
#define PORT "8888"
#include "Command.h"

class Server
{
private:
    SOCKET listenSocket;
    SOCKET clientSocket;
    NetMessage netMessage;
public:
    int init();
    GameData* communicate(GameData* mydata,GameData* enemydata);
    void close();
    void Send(std::string message);
    NetMessage receive();
};

#endif