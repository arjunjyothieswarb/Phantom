cmake_minimum_required(VERSION 3.20.0)
project(kb_interface)
set(CMAKE_CXX_STANDARD 17)

include_directories(include/)
add_library(udp_serv_lib src/udp_serv.cpp)
add_executable(${PROJECT_NAME} src/udp_interface.cpp)

target_link_libraries(${PROJECT_NAME} udp_serv_lib)