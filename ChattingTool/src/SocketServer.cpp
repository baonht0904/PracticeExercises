#include "SocketServer.h"

CServer_t::CServer_t(){
    // Initailization
    unlinkFlag = false;
    id = getpid();
    string socketFile = SERVER_DIR + "-" + std::to_string(id);
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, socketFile.c_str());
    

    // Creating socket
    serverFileDescriptor = socket(AF_UNIX, SOCK_STREAM, 0);
    if(serverFileDescriptor < 0){
        std::cerr << "Socket initialization failed!" << std::endl;
    }
    else{
        // Binding
        int bindingResult = bind(serverFileDescriptor, (sockaddr *)&serverAddr, SUN_LEN(&serverAddr));
        if(bindingResult < 0){
            std::cerr << "Binding failed!" << std::endl;
        }
        std::cout << "Server initailization succeeded!" << std::endl;
        std::cout << "Server's id: " << id << std::endl;
    }   
}

CServer_t::~CServer_t(){
}

int CServer_t::SetupListen(){
    int listenResult = listen(serverFileDescriptor, MAX_CLIENTS);
    if(listenResult < 0){
        std::cerr << "Listen failed!" << std::endl;
        return -1;
    }
    std::cout << "Ready for client connection!" << std::endl;
    return 0;
}

int CServer_t::AcceptClient(ClientData_t &client){
    client.fileDescriptor = accept(serverFileDescriptor, NULL, NULL);
    if(client.fileDescriptor < 0){
        std::cerr << "Client acception failed!" << std::endl;
        return -2;
    }

    int length = BUFFER_LENGTH;
    int setsockoptResult = setsockopt(client.fileDescriptor, SOL_SOCKET, SO_RCVLOWAT, (char*)&length, sizeof(length));
    if(setsockoptResult < 0){
        std::cerr << "setsockopt(SO_RCVLOWAT) failed!" << std::endl;
        close(client.fileDescriptor);
        return -2;
    }
    
    int receiveNameResult = recv(client.fileDescriptor, buffer, BUFFER_LENGTH, 0);
    client.name = buffer;
    if(receiveNameResult < 0){
        std::cerr << "Cannot receive client's name!" << std::endl;
        close(client.fileDescriptor);
        return -3;
    }

    std::cout << "Client " << client.name << " connection establishment succeeded!" << std::endl;
    return 0;
}

int CServer_t::AcceptMultipleClientAsynchronous(bool stopCondition, int (*HandleClient)(CServer_t*, ClientData_t)){
    maxFD = serverFileDescriptor;
    do{
        errno = 0;
        FD_ZERO(&readFD);
        FD_SET(serverFileDescriptor, &readFD);
        
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        int selectResult = select(maxFD + 1, &readFD, NULL, NULL, &timeout);
        // if(selectResult == 0){
        //     std::cerr << "Time out!" << std::endl;
        // }
        if(selectResult < 0){
            std::cerr << "select() error: " << strerror(errno) << std::endl;
            return -1;
        }
        else if(selectResult > 0){
            if(clientHandlerVec.size() < MAX_CLIENTS){
                ClientData_t newClient;
                int clientAcceptResult = AcceptClient(newClient);
                if(newClient.fileDescriptor > maxFD)
                    maxFD = newClient.fileDescriptor;
                if (clientAcceptResult == 0){
                    ClientHandler_t tempClientHandler;
                    tempClientHandler.asyncHandler = std::async(HandleClient, this, newClient);
                    tempClientHandler.clientData = newClient;
                    clientHandlerVec.push_back(std::move(tempClientHandler));
                }
            }
            else{
                std::cout << "Server full" << std::endl;
            }
        }
        for(int i=0; i<clientHandlerVec.size(); ++i){
            auto asyncWaitStatue = clientHandlerVec.at(i).asyncHandler.wait_for(std::chrono::seconds(1));
            if(asyncWaitStatue == std::future_status::ready){
                // auto resultAsync = clientHandlerVec.at(i).asyncHandler.get();
                clientHandlerVec.erase(clientHandlerVec.begin() + i);
            }
        }
    }while(!stopCondition);
    return 0;
}

int CServer_t::ReceiveClientMessage(ClientData_t &client, string &message){
    int reciveResult = recv(client.fileDescriptor, buffer, BUFFER_LENGTH, 0);
    if(reciveResult < 0){
        std::cerr << "Reciving client " << client.name << " massage failed!" << std::endl;
        return -1;
    }

    if(reciveResult == 0 || reciveResult < BUFFER_LENGTH){
        std::cout << reciveResult << " bytes of data were received!" << std::endl;
        std::cerr << "Client " << client.name << " closed the connection!" << std::endl;
        return -2;
    }

    message = buffer;
    return 0;
}

int CServer_t::SendMessageToClient(ClientData_t &client, const string &message){
    strcpy(buffer, message.c_str());
    int sendResult = send(client.fileDescriptor, buffer, BUFFER_LENGTH, 0);
    if(sendResult < 0){
        std::cerr << "Sending message to client " << client.name << " failed!" << std::endl;
        return -1;
    }

    std::cout << "Message was sent to client " << client.name << " successfully!" << std::endl;
    return 0;
}

int CServer_t::BroadcastMessage(const string &message){
    int returnFlag{0};
    for(int i=0; i<clientHandlerVec.size(); ++i){
        ClientData_t client = clientHandlerVec.at(i).clientData;
        int sendResult = SendMessageToClient(client, message);
        if(sendResult != 0){
            std::cerr << "Cannot send message to client " << client.name << "!" << std::endl;
            std::cerr << "Error code: " << sendResult << std::endl;
            returnFlag = -1;
        }
    }
    return returnFlag;
}

int CServer_t::CloseClient(ClientData_t &client){
    int closeResult = close(client.fileDescriptor);
    if(closeResult < 0){
        std::cerr << "Clossing connection to client " << client.name << " failed" << std::endl;
        return -1;
    }
    std::cout << "Connection to client " << client.name << " closed!" << std::endl;
    return 0;
}

int CServer_t::UnlinkSocket(){
    if(!unlinkFlag){
        string socketFile = serverAddr.sun_path;
        int unlinkResult = unlink(socketFile.c_str());
        if(unlinkResult < 0){
            std::cerr << "Unlink failed or socket file have already been removed!" << std::endl;
            return -1;
        }
        std::cout << "Unlinked!" << std::endl;
        unlinkFlag = true;
    }
    return 0;
}