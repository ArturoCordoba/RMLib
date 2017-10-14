//
// Created by arturocv on 18/09/17.
//

#ifndef RMLIB_SOCKETCLIENT_H
#define RMLIB_SOCKETCLIENT_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

class SocketClient {
public:
    SocketClient(char* ip, int port);

    bool connect();

    int sendMessage(const char *message);

    string getResponse();

    void disconnect();

private:
    int socketNum;

    sockaddr_in info;

    char* ip;

    int port;

};


#endif //RMLIB_SOCKETCLIENT_H
