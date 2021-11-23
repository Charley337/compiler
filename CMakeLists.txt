cmake_minimum_required(VERSION 2.9)
project(MyCompiler)
set(CMAKE_BUILD_TYPE "Release")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 头文件路径
include_directories(./lab1)
include_directories(./lab2)
include_directories(./lab3)
include_directories(./lab4)

# 编译生成库文件
add_library(flex_buffer_shared SHARED ./lab1/flex_buffer.cpp)
add_library(lexer_shared SHARED ./lab1/lexer.cpp)
add_library(lr1_analyser_shared SHARED ./lab2/lr1_analyser.cpp)
add_library(translate_proc_shared SHARED ./lab3/translate_proc.cpp)
add_library(assembly_generator_static STATIC ./lab4/assembly_generator.cpp)
add_library(assembly_functions_static STATIC ./lab4/assembly_functions.cpp)

# 资源文件
file (COPY input_code.txt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file (COPY LR1.csv DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file (COPY wenfa.txt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file (COPY code_list.txt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file (COPY keyword_set.txt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 添加可执行文件
add_executable(compiler main.cpp)

# 连接库文件
target_link_libraries(lr1_analyser_shared translate_proc_shared)
target_link_libraries(lexer_shared flex_buffer_shared)
target_link_libraries(compiler lexer_shared)
target_link_libraries(compiler lr1_analyser_shared)
target_link_libraries(compiler assembly_generator_static)
target_link_libraries(translate_proc_shared lexer_shared)
target_link_libraries(assembly_generator_static assembly_functions_static)
target_link_libraries(assembly_functions_static assembly_generator_static)