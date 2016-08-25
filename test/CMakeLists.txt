file(GLOB srcs "*.h" "*.cc")

# a.out
add_executable(a.out ${srcs})
target_compile_options(a.out PRIVATE --std=c++11)
target_include_directories(a.out PRIVATE ${gtest_SOURCE_DIR}/include)
target_link_libraries(a.out glucosamine gtest)

# make test
add_custom_target(
    test
    COMMAND a.out
    DEPENDS a.out
)

find_program(gdb_path gdb)

# make debug
add_custom_target(
    debug
    COMMAND ${gdb_path} a.out
    DEPENDS a.out
)
