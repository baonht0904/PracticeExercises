#ifndef _SOCKET_SERVER_H_
#define _SOCKET_SERVER_H_

#include "header.h"
#include <vector>
#include <future>

const int MAX_CLIENTS{10};

struct ClientData_t
{
    int fileDescriptor;
    string name;
};

struct ClientHandler_t{
    std::future<int> asyncHandler;
    ClientData_t clientData;
};

class CServer_t{
    private:
        int id;
        int serverFileDescriptor;
        char buffer[BUFFER_LENGTH];
        sockaddr_un serverAddr;
        bool unlinkFlag;
        fd_set readFD;
        timeval timeout;
        int maxFD;
        std::vector<ClientHandler_t> clientHandlerVec;
    public:
        CServer_t();
        ~CServer_t();
        CServer_t(const CServer_t &) = delete;
        int GetFileDescripter() { return serverFileDescriptor; }
        int SetupListen();
        int AcceptClient(ClientData_t &client);
        int AcceptMultipleClientAsynchronous(bool stopCondition, int (*HandleClient)(CServer_t*, ClientData_t));
        int ReceiveClientMessage(ClientData_t &client, string &message);
        int SendMessageToClient(ClientData_t &client, const string &message);
        int BroadcastMessage(const string &message);
        int CloseClient(ClientData_t &client);
        int UnlinkSocket();
};

#endif