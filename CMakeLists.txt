cmake_minimum_required(VERSION 3.22)
project(LTL_checker)

set(CMAKE_CXX_STANDARD 20)

add_executable(LTL_checker main.cpp)

target_include_directories(LTL_checker PRIVATE grammar /usr/include/antlr4-runtime)

target_link_libraries(LTL_checker antlr4-runtime)