cmake_minimum_required(VERSION 2.8.12.2)

project(glucosamine)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(glucosamine_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src)

# libglucosamine.a
file(GLOB_RECURSE srcs "src/*.h" "src/core/Solver.cc")
add_library(glucosamine STATIC ${srcs})
target_compile_options(glucosamine PRIVATE --std=c++11)
target_include_directories(glucosamine PUBLIC ${glucosamine_INCLUDE_DIRS})

# Unit tests
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    # Google Test
    add_subdirectory(third_party/googletest)
    # Unit tests
    add_subdirectory(test)
endif()
