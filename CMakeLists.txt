cmake_minimum_required(VERSION 3.10)
project(optional)

set(CMAKE_CXX_FLAGS "-pthread -Wall -std=c++14 -pedantic ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined -D_GLIBCXX_DEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_COVERAGE "-g --coverage")
set(LINK_FLAGS "-pthread ${LINK_FLAGS}")

include_directories(.)
add_subdirectory(gtest)

add_library(counted
        counted.h
        counted.cpp)

add_executable(optional
        optional.cpp
        optional.h
        tests.inl)

target_link_libraries(optional counted gtest)