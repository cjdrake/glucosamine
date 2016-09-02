include(CodeCoverage) # setup_target_for_coverage

# a.out
file(GLOB srcs "*.h" "*.cc")
add_executable(a.out ${srcs})
target_compile_options(a.out PRIVATE -std=c++11 -Wall)
target_link_libraries(a.out glucosamine gtest)

# make test
add_custom_target(
    test
    COMMAND a.out
    DEPENDS a.out
)

# make cover
setup_target_for_coverage(cover a.out html)
