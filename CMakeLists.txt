cmake_minimum_required(VERSION 2.8.12.2)

project(glucosamine)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

file(GLOB_RECURSE srcs "src/*.h" "src/core/Solver.cc")

add_library(glucosamine ${srcs})
target_compile_options(glucosamine PUBLIC -std=c++11 -Wall)
target_include_directories(glucosamine PUBLIC ${PROJECT_SOURCE_DIR}/src)

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    # Google Test
    add_subdirectory(third_party/googletest)
    # Unit tests
    add_subdirectory(test)
endif()
