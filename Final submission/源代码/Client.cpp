#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include<string>
#include "Client.h"
#include "Command.h"
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
//#define SERVER_IP "100.81.213.146"

int Client::init()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        WSACleanup();
        return -1;
    }

    struct addrinfo hints, * res;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(SERVER_IP, PORT, &hints, &res) != 0) {
        WSACleanup();
        return 1;
    }

    connectSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (connectSocket == INVALID_SOCKET) {
        freeaddrinfo(res);
        WSACleanup();
        return 1;
    }

    if (connect(connectSocket, res->ai_addr, (int)res->ai_addrlen) == SOCKET_ERROR) {
        closesocket(connectSocket);
        freeaddrinfo(res);
        WSACleanup();
        return 1;
    }
    else
    {
        CCLOG("Successfully connecting\n");
    }

    freeaddrinfo(res);
}

GameData* Client::communicate(GameData* mydata, GameData* enemydata)
{
//    // 将自己状态信息序列化为字符串发送给对方
//    string msg="";
//    msg = mydata->serializeGameData(mydata);
//    send(connectSocket, (const char*)msg.c_str(), msg.length(), 0);
    GameData* tmp = new GameData;
    char recvbuf[1000] = { 0 };
    int recvbuflen = 1000;
    int recvResult = 0;
    recvResult=recv(connectSocket, recvbuf, recvbuflen, 0);
    if (recvResult > 0) {
        // 将接收到的对方字符串反序列化为战斗信息
        CCLOG("Successfully recv\n");
        std::string recvString = std::string(recvbuf); // 将 char[] 转换为 std::string
       tmp = enemydata->deserializeGameData(recvString);
    }
    // 将自己状态信息序列化为字符串发送给对方
    string msg = "";
    msg = mydata->serializeGameData(mydata);
    send(connectSocket, (const char*)msg.c_str(), msg.length(), 0);
    return tmp;
}

void Client::Send(std::string message) {
    send(connectSocket, message.c_str(), message.size(), 0);
}

NetMessage Client::receive() {
    char recvbuf[1000];
    recv(connectSocket, recvbuf, 1000, 0);
    std::string message(recvbuf);
    std::stringstream ss(message);
    std::string line;
    int lineCount = 0;
    while (std::getline(ss, line)) {
        char temp;
        std::stringstream lineStream(line);
        if (lineCount == 0) {
            int blood;
            int heroNum;
            lineStream >> blood >> temp >> heroNum;
            netMessage.SetPlayerBlood(blood);
            netMessage.SetHeroNum(heroNum);
        }
        else{
            int a, b, c, d;
            lineStream >> a >> temp >> b >> temp >> c >> temp >> d;
            netMessage.SetNetHero(a, b, c, d,lineCount-1);
        }
        lineCount++;
    }
    return netMessage;
}

void Client::close()
{
    closesocket(connectSocket);
    WSACleanup();
}

/*int main() {

    Client client;
    client.init();
    client.communicate();
    client.communicate();
    client.close();

    return 0;
}*/