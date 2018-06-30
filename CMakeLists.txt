cmake_minimum_required(VERSION 3.10)
project(satsub CXX)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=sandybridge")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Enable GTest for GBenchmark")

add_subdirectory(extern/googletest/googletest)
add_subdirectory(extern/benchmark)

set(SOURCE satsub.cpp)
set(TESTS test.cpp)
set(BENCHMARKS bench.cpp)

add_executable(satsubbench ${SOURCE} ${BENCHMARKS})
target_link_libraries(satsubbench benchmark benchmark_main)

add_executable(satsubtest ${SOURCE} ${TESTS})
target_link_libraries(satsubtest gtest gtest_main)

# Call with `make test`
enable_testing()
add_test(SATSUB satsubtest)

# Call with `make format`
add_custom_target(format clang-format -i ${SOURCE} ${TESTS} ${BENCHMARKS}
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
