cmake_minimum_required(VERSION 3.1)

project(expression CXX)
enable_testing()

# Compilation of googletest library #####
set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")

include_directories(
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
    )

set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
    )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})
##########################################

add_subdirectory("src")
add_subdirectory("test")

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Always optimized" FORCE)
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

#IF(CMAKE_BUILD_TYPE MATCHES Debug)
#  message("Debug build.")
#ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
#  message("Release build.")
#ELSE()
#  message("Some other build type.")
#ENDIF()
