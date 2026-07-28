cmake_minimum_required(VERSION 3.20.0)
project(udp_server)
set(CMAKE_CXX_STANDARD 17)

include_directories(include/)
add_library(udp_serv_utils_lib src/udp_serv_utils.cpp)

add_library(motor_driver_lib src/motor_driver.cpp)
target_link_libraries(motor_driver_lib wiringPi)

add_library(motor_controls_lib src/motor_controls.cpp)
add_executable(${PROJECT_NAME} src/udp_interface.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE udp_serv_utils_lib motor_controls_lib motor_driver_lib)