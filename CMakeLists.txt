cmake_minimum_required(VERSION 2.8)

project(stl1 CXX)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory("src")
add_subdirectory("test")

