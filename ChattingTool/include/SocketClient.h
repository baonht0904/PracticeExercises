#ifndef _SOCKET_CLIENT_H_
#define _SOCKET_CLIENT_H_

#include "header.h"

class CClient_t{
    private:
        int clientFileDescriptor;
        char sendingBuffer[BUFFER_LENGTH];
        char recivingBuffer[BUFFER_LENGTH];
        sockaddr_un serverAddr;
        bool unlinkFlag;
        bool connectionFlag;
    public:
        CClient_t();
        ~CClient_t();
        CClient_t(const CClient_t &) = delete;
        int GetFileDescriptor() { return clientFileDescriptor; }
        bool GetConnectionFlag() { return connectionFlag; }
        int ConnectToServer(const int &serverID);
        int ReceiveServerMessage(string &message);
        int SendMessageToServer(const string &message);
        int CloseConnect();
        int UnlinkSocket();
};

#endif