cmake_minimum_required(VERSION 3.29)
project(CodeWars)

set(CMAKE_CXX_STANDARD 17)

add_executable(CodeWars main.cpp
        connection_handler.cpp
        connection_handler.h)

if (WIN32)
    target_link_libraries(CodeWars PRIVATE iphlpapi ws2_32)
    target_compile_definitions(CodeWars PRIVATE NOMINMAX)
endif()