cmake_minimum_required(VERSION 3.20.0)
project(udp_client)
set(CMAKE_CXX_STANDARD 17)

include_directories(include/)
add_library(term_utils src/term_utils.cpp)
add_executable(${PROJECT_NAME} src/udp_client.cpp)

target_link_libraries(${PROJECT_NAME} term_utils)
