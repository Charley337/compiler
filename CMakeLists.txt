cmake_minimum_required(VERSION 2.8)
project(MyCompiler)
set(CMAKE_BUILD_TYPE "Release")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

# 头文件路径
include_directories(./lab1)
include_directories(./lab2)

# 编译生成库文件
add_library(lexer_shared SHARED ./lab1/lexer.cpp)
add_library(lr1_analyser_shared SHARED ./lab2/lr1_analyser.cpp)

# 添加可执行文件
add_executable(compiler main.cpp)
target_link_libraries(compiler lexer_shared)
target_link_libraries(compiler lr1_analyser_shared)