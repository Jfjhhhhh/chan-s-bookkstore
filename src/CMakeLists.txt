cmake_minimum_required(VERSION 3.16)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp error.h Token_scanner.h user.h user.cpp database.h book.h book.cpp)
