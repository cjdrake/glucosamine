include(CodeCoverage) # setup_target_for_coverage

find_program(gdb_path gdb)

# a.out
file(GLOB srcs "*.h" "*.cc")
add_executable(a.out ${srcs})
target_link_libraries(a.out glucosamine gtest)

# make test
add_custom_target(
    test
    COMMAND a.out
    DEPENDS a.out
)

# make debug
add_custom_target(
    debug
    COMMAND ${gdb_path} a.out
    DEPENDS a.out
)

# make cover
setup_target_for_coverage(cover a.out html)
