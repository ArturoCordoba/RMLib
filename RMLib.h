//
// Created by arturocv on 13/10/17.
//

#ifndef RMLIB_RMLIB_H
#define RMLIB_RMLIB_H


#include "SocketClient.h"
#include "DataStructures/RMRef_H.h"

class RMLib {
public:
    static RMLib* getInstance();

    void rm_init(char *ip, int port, char *ipHA, int portHA);

    string rm_new(char *key, char *value, int value_size);

    RMRef_H rm_get(char* key);

    string rm_delete(char *key);

    void close();

private:
    RMLib();

    static RMLib* instance;

    static SocketClient* server;

    static SocketClient* serverHA;

    bool serverOnline = false;

    bool serverHAOnline = false;

    string sendRequest(string message);

};


#endif //RMLIB_RMLIB_H
