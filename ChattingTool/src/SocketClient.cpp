#include "SocketClient.h"

CClient_t::CClient_t(){
    clientFileDescriptor = socket(AF_UNIX, SOCK_STREAM, 0);
    if(clientFileDescriptor < 0){
        std::cerr << "Socket initialization failed!" << std::endl;
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    std::cout << "Client created successfully!" << std::endl;
    connectionFlag = false;
}

CClient_t::~CClient_t(){
}

int CClient_t::ConnectToServer(const int &serverID){
    string socketFile = SERVER_DIR + "-" + std::to_string(serverID);

    serverAddr.sun_family = AF_UNIX;
    
    strcpy(serverAddr.sun_path, socketFile.c_str());
    int connectResult = connect(clientFileDescriptor, (sockaddr *)&serverAddr, SUN_LEN(&serverAddr));
    if(connectResult < 0){
        std::cerr << "Connecting to server failed!" << std::endl;
        return -1;
    }
    
    std::cout << "Connected to server!" << std::endl;
    unlinkFlag = false;
    connectionFlag = true;
    return 0;
}

int CClient_t::ReceiveServerMessage(string &message){
    int bytesRecived = 0;
    while(bytesRecived < BUFFER_LENGTH){
        int bytesReceiving = recv(clientFileDescriptor, &recivingBuffer[bytesRecived], BUFFER_LENGTH - bytesRecived, 0);
        if(bytesReceiving < 0){
            std::cerr << "An error has orcurse when receiving client message!" << std::endl;
            return -1;
        }
        else if(bytesReceiving == 0){
            std::cerr << "The server closed the connection!" << std::endl;
            connectionFlag = false;
            return -2;
        }
        bytesRecived += bytesReceiving;
    }
    message = recivingBuffer;
    return 0;
}

int CClient_t::SendMessageToServer(const string &message){
    if(message.length() > BUFFER_LENGTH){
        std::cerr << "Message too long!" << std::endl;
        return -1;
    }
    
    strcpy(sendingBuffer, message.c_str());
    int sendResult = send(clientFileDescriptor, sendingBuffer, BUFFER_LENGTH, 0);
    if(sendResult < 0){
        std::cerr << "Sending failed!";
        return -2;
    }

    // std::cout << "Message was sent!" << std::endl;
    return 0;
}

int CClient_t::CloseConnect(){
    int closeResult = close(clientFileDescriptor);
    if(closeResult < 0){
        std::cerr << "Clossing connection failed!" << std::endl;
        return -1;
    }
    std::cout << "Connection closed!" << std::endl;
    connectionFlag = false;
    return 0;
}

int CClient_t::UnlinkSocket(){
    if(!unlinkFlag){
        string socketFile = serverAddr.sun_path;
        int unlinkResult = unlink(socketFile.c_str());
        if(unlinkResult < 0){
            std::cerr << "Unlink failed!" << std::endl;
            return -1;
        }
        std::cout << "Unlinked!" << std::endl;
        unlinkFlag = true;
    }
    return 0;
}