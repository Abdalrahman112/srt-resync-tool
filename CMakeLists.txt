cmake_minimum_required(VERSION 3.16.3)
project(SRT-Resync-Tool VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "Adding linker options.")
add_link_options(-pthread)

message(STATUS "Adding compiler options.")
add_compile_options(-static-libstdc++)

message(STATUS "Adding libraries.")
add_library(SRT-LIB STATIC 
    helper_functions.cpp)

add_executable(srt-resync-tool main.cpp)
target_link_libraries(srt-resync-tool SRT-LIB)