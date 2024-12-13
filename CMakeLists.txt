cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(concurrency LANGUAGES CXX)


set(SOURCES
    src/mutex/mutexes.cpp
    src/thread_pool/thread_pool.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src/)

add_executable(main src/main.cpp)

target_link_libraries(main ${PROJECT_NAME})

target_include_directories(main PRIVATE src/)