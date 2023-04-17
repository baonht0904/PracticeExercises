#ifndef _CHATTING_SOCKET_H_
#define _CHATTING_SOCKET_H_

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>

using std::string;

const string SERVER_DIR{"/tmp/SocketServer"};
const int BUFFER_LENGTH{255};

namespace chattingSocket{
    int CreateServer(int &server, char* buffer);
    int ClientAccept(int &server, int &client);
    int ReciveClientMessage(int &client, char* buffer);
    int CreateClient(int &client, char*buffer);
    int ClientConnectServer(int &client);
    int SendMessageToServer(int &client, char* buffer, const string &message);
    int ReciveServerMessage(int &client, char* buffer);
    int UnlinkSocket();
}

#endif