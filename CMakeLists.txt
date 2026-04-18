cmake_minimum_required(VERSION 3.22)
project(LTL_checker CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Boost library
find_package(Boost REQUIRED)

# Find fmt library
find_package(fmt REQUIRED)

# Find ANTLR4 runtime
find_path(ANTLR4_INCLUDE_DIR
        NAMES antlr4-runtime.h
        PATH_SUFFIXES antlr4-runtime
)
find_library(ANTLR4_LIB
        NAMES antlr4-runtime
)

if (NOT ANTLR4_INCLUDE_DIR OR NOT ANTLR4_LIB)
    message(FATAL_ERROR "antlr4-runtime is required but not found. Please install it or specify ANTLR4_INCLUDE_DIR and ANTLR4_LIB via CMake args.")
endif ()

# Define source files
set(SOURCES
        main.cpp
        grammar/LTLLexer.cpp
        grammar/LTLParser.cpp
        src/ast/ast_node.cpp
        src/ast/ast.cpp
        src/ast/ast_builder.cpp
        src/ltl_to_gnba_builder.cpp
        src/persistence_checker.cpp
        src/ts.cpp
)

add_executable(LTL_checker ${SOURCES})

# Configure include directories
target_include_directories(LTL_checker PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/grammar
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${ANTLR4_INCLUDE_DIR}
)

# Configure linked libraries
target_link_libraries(LTL_checker PRIVATE
        ${ANTLR4_LIB}
        Boost::boost
        fmt::fmt
)