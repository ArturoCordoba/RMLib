cmake_minimum_required(VERSION 3.8)
project(RMLib)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DataStructures/LinkedList.cpp DataStructures/LinkedList.h DataStructures/Node.cpp DataStructures/Node.h DataStructures/RMRef_H.cpp DataStructures/RMRef_H.h RMLib.cpp RMLib.h SocketClient.cpp SocketClient.h)
add_executable(RMLib ${SOURCE_FILES})