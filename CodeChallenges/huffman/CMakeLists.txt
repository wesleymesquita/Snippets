cmake_minimum_required(VERSION 3.27)

project(huffman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(huffman_lib Huffman.cpp Huffman.h)

add_executable(huffman_test test.cpp)

target_link_libraries(huffman_test GTest::gtest_main huffman_lib)
include_directories("build/_deps/googletest-src/googletest/include")

include(GoogleTest)
gtest_discover_tests(huffman_test)
