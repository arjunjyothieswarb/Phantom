cmake_minimum_required(VERSION 3.20.0)
project(kb_interface)
set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

add_executable(${PROJECT_NAME} src/interface.cpp)