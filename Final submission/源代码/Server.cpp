#include"Server.h"

int Server::init()
{

    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        WSACleanup();
        return -1;
    }
    ///
    //SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);//创建套链字
    //if (sock == -1) {
    //    WSACleanup();
    //    return -1;
    //}
    //sockaddr_in addr;
    //addr.sin_family = AF_INET;
    //addr.sin_port = htons(9999);
    //addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //result = bind(sock, (sockaddr*)&addr, sizeof(addr));
    //if (result == -1) {
    //    WSACleanup();
    //    return -1;
    //}
    //result = listen(sock, 5);
    //if (result == -1) {
    //    WSACleanup();
    //    return -1;
    //}
    //sockaddr addrCli;
    //int len = sizeof(addrCli);
    //SOCKET sockCli = accept(sock, &addrCli, &len);
    //if (sockCli == -1) {
    //    WSACleanup();
    //    return -1;
    //}
    //char buf[0xFF] = "";
    //result = send(sockCli, buf, strlen(buf), 0);
    //if (result == -1) {
    //    WSACleanup();
    //    return -1;
    //}
    //result = recv(sockCli, buf, 0xFF, 0);
    //if (result <= 0) {
    //    WSACleanup();
    //    return -1;
    //}
    //WSACleanup();
    ///
    struct addrinfo hints, * res;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, PORT, &hints, &res) != 0) {
        WSACleanup();
        return 1;
    }

    listenSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (listenSocket == INVALID_SOCKET) {
        freeaddrinfo(res);
        WSACleanup();
        return 1;
    }

    if (bind(listenSocket, res->ai_addr, (int)res->ai_addrlen) == SOCKET_ERROR)
    {
        closesocket(listenSocket);
        freeaddrinfo(res);
        WSACleanup();
        return 1;
    }
    else
    {
        CCLOG("Successfully listening\n");
    }
  
    freeaddrinfo(res);

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        CCLOG("Successfully listening\n");
    }

    clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        CCLOG("Successfully listening\n");
    }

}

GameData* Server::communicate(GameData* mydata, GameData* enemydata)
{
    GameData* tmp = new GameData;
    string msg = "";
    msg = mydata->serializeGameData(mydata);
    send(clientSocket, (const char*)msg.c_str(), msg.length(), 0);

    char recvbuf[1000] = { 0 };
    int recvbuflen = 1000;
    int recvResult = 0;
    recvResult=recv(clientSocket, recvbuf, recvbuflen, 0);
    if (recvResult > 0) {
        // 将接收到的对方字符串反序列化为战斗信息
        CCLOG("Successfully recv\n"); 
        std::string recvString = std::string(recvbuf); // 将 char[] 转换为 std::string
        tmp = enemydata->deserializeGameData(recvString);
    }

    // 将自己状态信息序列化为字符串发送给对方
    /*string msg="";
    msg = mydata->serializeGameData(mydata);
    send(clientSocket, (const char*)msg.c_str(), msg.length(), 0);*/
    return tmp;
}

void Server::Send(std::string message) {
    send(clientSocket, message.c_str(), message.size(),0);
}

NetMessage Server::receive() {
    char recvbuf[1000];
    recv(clientSocket, recvbuf, 1000, 0);
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
        else {
            int a, b, c, d;
            lineStream >> a >> temp >> b >> temp >> c >> temp >> d;
            netMessage.SetNetHero(a, b, c, d, lineCount - 1);
        }
        lineCount++;
    }
    return netMessage;
}

void Server::close()
{
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();
}

/*int main() {
    Server server;
    server.init();
    server.communicate();
    server.communicate();
    server.close();
    return 0;
}*/