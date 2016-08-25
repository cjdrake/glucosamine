cmake_minimum_required(VERSION 2.8.12.2)

project(glucosamine)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Glucosamine
file(GLOB srcs "src/*/*.h" "src/core/Solver.cc")

# libglucosamine.a
add_library(glucosamine STATIC ${srcs})
target_compile_options(glucosamine PRIVATE --std=c++11)
target_include_directories(glucosamine PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Unit tests
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    # Google Test
    add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/googletest)
    # Unit tests
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()
