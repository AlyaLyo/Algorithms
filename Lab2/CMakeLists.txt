cmake_minimum_required(VERSION 4.0)
project(example)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)

add_executable(example
        main.cpp
        Array.h
)

add_executable(tests
        tests.cpp
        Array.h
)

target_link_libraries(tests gtest)