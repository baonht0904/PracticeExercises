#include "SocketServer.h"
#include <signal.h>

bool interruptFlag{false};

void handleInterrupt(int signum){
    interruptFlag = true;
}

int AsyncHandleClient(CServer_t *serverPtr, ClientData_t newClient){
    ClientData_t client = newClient;
    string message;
    string broadcastedMessage;
    int receiveResult = -1;
    do{
        receiveResult = serverPtr->ReceiveClientMessage(client, message);
        if(receiveResult == 0){
            if(message == "/exit"){
                serverPtr->CloseClient(client);
                return 1;
            }
            else{
                std::cout << client.name << " sent: " << message << std::endl;
                broadcastedMessage = client.name + ": " + message;
                serverPtr->BroadcastMessage(broadcastedMessage);
            }
        }
        else
            serverPtr->CloseClient(client);
    }while(receiveResult == 0);
    
    return 0;
}

int main(){
    CServer_t server;
    std::vector<ClientHandler_t> clientHandle;

    signal(SIGINT, handleInterrupt);

    server.SetupListen();
    server.AcceptMultipleClientAsynchronous(interruptFlag, AsyncHandleClient);

    server.UnlinkSocket();

    return 0;
}