#include "chattingSocket.h"

int chattingSocket::CreateServer(int &server, char* buffer){
    server = socket(AF_UNIX, SOCK_STREAM, 0);
    if(server < 0){
        std::cerr << "Socket initialization failed!" << std::endl;
        return -1;
    }

    sockaddr_un serverAddr;
    int pid = getpid();
    string socketFile = SERVER_DIR + "-" + std::to_string(pid);

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, socketFile.c_str());

    int bindingResult = bind(server, (sockaddr *)&serverAddr, SUN_LEN(&serverAddr));
    if(bindingResult < 0){
        std::cerr << "Binding failed!" << std::endl;
        return -2;
    }

    std::cout << "Server initailization succeeded!" << std::endl;
    std::cout << "Server's id: " << pid << std::endl;
    return 0;
}

int chattingSocket::ClientAccept(int &server, int &client){
    client = accept(server, NULL, NULL);
    if(client < 0){
        std::cerr << "Client acception failed!" << std::endl;
        return -1;
    }

    int length = BUFFER_LENGTH;
    int setsockoptResult = setsockopt(client, SOL_SOCKET, SO_RCVLOWAT, 
                                        (char*)&length, sizeof(length));
    if(setsockoptResult < 0){
        std::cerr << "setsockopt(SO_RCVLOWAT) failed!" << std::endl;
        return -2;
    }
    
    std::cout << "Client connection establishment succeeded!" << std::endl;
    return 0;
}

int chattingSocket::ReciveClientMessage(int &client, char* buffer){
    int reciveResult = recv(client, buffer, BUFFER_LENGTH, 0);
    if(reciveResult < 0){
        std::cerr << "Reciving client massage failed!" << std::endl;
        return -1;
    }

    std::cout << reciveResult << "bytes of data were received!" << std::endl;
    if(reciveResult == 0 || reciveResult < BUFFER_LENGTH){
        std::cerr << "Client closed the connection before all of the data was sent!" << std::endl;
        return -2;
    }

    std::cout << "Client sent: " << buffer << std::endl;
    return 0;
}

int chattingSocket::CreateClient(int &client, char* buffer){
    client = socket(AF_UNIX, SOCK_STREAM, 0);
    if(client < 0){
        std::cerr << "Socket initialization failed!" << std::endl;
        return -1;
    }
    
    std::cout << "Client created successfully!" << std::endl;
    return 0;
}

int chattingSocket::ClientConnectServer(int &client){
    sockaddr_un serverAddr;
    string serverID{"0"};
    std::cout << "Input server's ID: ";
    std::cin >> serverID;
    string socketFile = SERVER_DIR + "-" + serverID;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, socketFile.c_str());

    int connectResult = connect(client, (sockaddr *)&serverAddr, SUN_LEN(&serverAddr));
    if(connectResult < 0){
        std::cerr << "Connecting to server failed!" << std::endl;
        return -1;
    }
    
    std::cout << "Connected to server!" << std::endl;
    return 0;
}

int chattingSocket::SendMessageToServer(int &client, char* buffer, const string &message){
    if(message.length() > BUFFER_LENGTH){
        std::cerr << "Message too long!" << std::endl;
        return -1;
    }
    
    strcpy(buffer, message.c_str());
    int sendResult = send(client, buffer, BUFFER_LENGTH, 0);
    if(sendResult < 0){
        std::cerr << "Sending failed!";
        return -2;
    }
    std::cout << "Message was sent!" << std::endl;
    return 0;
}

int chattingSocket::ReciveServerMessage(int &client, char* buffer){
    int bytesRecived = 0;
    while(bytesRecived < BUFFER_LENGTH){
        int bytesReceiving = recv(client, &buffer[bytesRecived], BUFFER_LENGTH - bytesRecived, 0);
        if(bytesReceiving < 0){
            std::cerr << "An error has orcurse when receiving client message!" << std::endl;
            return -1;
        }
        else if(bytesReceiving == 0){
            std::cerr << "The server closed the connection!" << std::endl;
            return -2;
        }
        bytesRecived += bytesReceiving;
    }
    std::cout << "Server sent: " << buffer << std::endl;
    std::cout << "Server sent: " << buffer << std::endl;
    return 0;
}

int chattingSocket::UnlinkSocket(){
    int pid = getpid();
    string socketFile = SERVER_DIR + "-" + std::to_string(pid);
    int unlinkResult = unlink(socketFile.c_str());
    if(unlinkResult < 0){
        std::cerr << "Unlink failed!" << std::endl;
        return -1;
    }
    std::cout << "Unlinked server!" << std::endl;
    return 0;
}

