#include "SocketClient.h"
#include <future>

int InitializeClient(CClient_t &client){
    int serverID{-1};
    std::cout << "Input server's ID: ";
    std::cin >> serverID;
    string clientName;
    std::cout << "Input your name: ";
    std::cin >> clientName;
    clientName += "-" + std::to_string(getpid());
    int connectResult = client.ConnectToServer(serverID);
    if(connectResult < 0){
        return -1;
    }
    int sendNameResult = client.SendMessageToServer(clientName);
    if (sendNameResult < 0){
        return -2;
    }
    return 0;
}

int HandleSendMessage(CClient_t *client){
    string message;
    do{
        // std::cout << "You: ";
        std::getline(std::cin, message);
        client->SendMessageToServer(message);
    }while (message != "/exit");
    client->CloseConnect();
    return 0;
}

int HandleReciveMessage(CClient_t *client){
    string message;
    do{
        int reciveResult = client->ReceiveServerMessage(message);
        if(reciveResult < 0)
            break;
        else{
            int startPID = message.find('-');
            int endPID = message.find(':');
            string pid = message.substr(startPID + 1, endPID - startPID - 1);
            if(std::stoi(pid) != getpid()){
                std::cout << "\n" << message << std::endl;
                // std::cout << "You: ";
            }
        }
    }while(client->GetConnectionFlag());
    return 0;
}

int main(){
    CClient_t client;

    int initializationResult = InitializeClient(client);
    if(initializationResult < 0){
        std::cerr << "Client initialization failed!" << std::endl;
        std::cerr << "Exit code: " << initializationResult << std::endl;
        return -1;
    }
    std::cout << "Client initialization succeeded!" << std::endl;
    std::cin.ignore();  // ignore previous cin
    
    auto asyncSendingHandler = std::async(std::launch::async, HandleSendMessage, &client);
    auto asyncRecivingHandler = std::async(std::launch::async, HandleReciveMessage, &client);



    return 0;
}