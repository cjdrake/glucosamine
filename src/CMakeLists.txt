file(GLOB srcs "core/*.h" "mtl/*.h" "utils/*.h" "core/Solver.cc")

# libglucosamine.a
add_library(glucosamine STATIC ${srcs})

target_compile_options(glucosamine PRIVATE --std=c++11)
target_include_directories(glucosamine PUBLIC ${PROJECT_SOURCE_DIR}/src)
