# add_library(ChattingSocket ${CMAKE_CURRENT_SOURCE_DIR}/chattingSocket.cpp)
# target_include_directories(ChattingSocket PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(SocketServer ${CMAKE_CURRENT_SOURCE_DIR}/SocketServer.cpp)
target_include_directories(SocketServer PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(SocketClient ${CMAKE_CURRENT_SOURCE_DIR}/SocketClient.cpp)
target_include_directories(SocketClient PUBLIC ${CMAKE_SOURCE_DIR}/include)