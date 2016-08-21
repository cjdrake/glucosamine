cmake_minimum_required(VERSION 2.8.12.2)

project(glucosamine)

# Glucosamine
add_subdirectory(src)

# Unit tests
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    # Google Test
    add_subdirectory(third_party/googletest)
    # Unit tests
    add_subdirectory(test)
endif()
