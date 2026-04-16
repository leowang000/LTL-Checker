cmake_minimum_required(VERSION 3.22)
project(LTL_checker)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

add_executable(LTL_checker main.cpp
        grammar/LTLLexer.cpp
        grammar/LTLParser.cpp
        src/ast/ast_node.cpp
        src/ast/ast.cpp
        src/ast/ast_builder.cpp
        src/ltl_to_gnba_builder.cpp
        src/persistence_checker.cpp
        src/ts.cpp)

target_include_directories(LTL_checker PRIVATE
        ${CMAKE_SOURCE_DIR}/grammar
        ${CMAKE_SOURCE_DIR}/include
        /usr/local/include/antlr4-runtime)

target_link_directories(LTL_checker PRIVATE /usr/local/lib)

target_link_libraries(LTL_checker
        antlr4-runtime
        Boost::boost
        fmt
)