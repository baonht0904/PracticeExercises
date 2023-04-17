# Set prerequisite
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Initialize some used name and lists
set(PROJECT_NAME ChattingRoom)
project(${PROJECT_NAME} VERSION 1.0)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/release)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_DIR}/archive")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
# set(CMAKE_BUILD_TYPE Debug)

# option(INSTALL_DEBUG "On for debug version/Off for release version" ON)
option(BUILD_EXECUTABLE "Build executable file!" ON)

set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(${MY_SRC_DIR})

if(BUILD_EXECUTABLE)
    add_executable(ChattingServer ${MY_SRC_DIR}/server.cpp)
    target_link_libraries(ChattingServer SocketServer)
    add_executable(ChattingClient ${MY_SRC_DIR}/client.cpp)
    target_link_libraries(ChattingClient SocketClient)
endif()