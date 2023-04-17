#ifndef _HEADER_H_
#define _HEADER_H_

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

#endif